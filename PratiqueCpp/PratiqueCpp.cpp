#pragma warning(disable : 4996)
#include <iostream>
using namespace std;
struct stDate
{
	short Year;
	short Month;
	short Day;
};

struct stPeriod
{
	stDate StartDate;
	stDate EndDate;

};


bool isLeapYear(short Year)
{
	return (Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0);
}

bool IsDate1BeforeDate2(stDate Date1, stDate Date2)
{
	return (Date1.Year < Date2.Year) ? true : ((Date1.Year ==
		Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month ==
			Date2.Month ? Date1.Day < Date2.Day : false)) : false);
}



bool IsDate1EqualDate2(stDate Date1, stDate Date2)
{
	return (Date1.Year == Date2.Year) ? ((Date1.Month ==
		Date2.Month) ? ((Date1.Day == Date2.Day) ? true : false) : false)
		: false;
}

bool IsDate1AfterDate2(stDate Date1, stDate Date2)
{
	return (!IsDate1BeforeDate2(Date1, Date2) && !IsDate1EqualDate2(Date1, Date2));
}

enum enDateCompare {
	After = 1, Equal = 0, Before = -1
};

enDateCompare DateCompare(stDate Date1, stDate Date2)
{
	if (IsDate1BeforeDate2(Date1, Date2))
	{
		return enDateCompare::Before;

	}
	if (IsDate1AfterDate2(Date1, Date2))
	{
		return enDateCompare::After;
	}

	return enDateCompare::Equal;
}

bool  IsOverLap(stPeriod period1, stPeriod period2  )
{
	if (DateCompare(period2.EndDate, period1.StartDate) == enDateCompare::Before || DateCompare(period2.StartDate, period1.EndDate) == enDateCompare::After)
	{
		return false;

	}
	else 
		return true;
}

bool IsDateInPeriod(stPeriod period , stDate Date)
{
	return !(DateCompare(Date, period.StartDate) == enDateCompare::Before || DateCompare(Date, period.EndDate) == enDateCompare::After);
	
}

short ReadDay()
{
	short Day;
	cout << "\nPlease enter a Day? ";
	cin >> Day;
	return Day;
}
short ReadMonth()
{
	short Month;
	cout << "Please enter a Month? ";
	cin >> Month;
	return Month;
}

short ReadYear()
{
	short Year;
	cout << "Please enter a Year? ";
	cin >> Year;
	return Year;
}

stDate  ReadDate()
{
	stDate StartDate;

	StartDate.Day = ReadDay();
	StartDate.Month = ReadMonth();
	StartDate.Year = ReadYear();

	return StartDate;
}


stPeriod ReadPeriod()
{
	stPeriod Period;
	cout << "Enter Start Date\n";
	Period.StartDate = ReadDate();
	cout << "Enter End Date\n";
	Period.EndDate = ReadDate();

	return Period;

}


int main()
{
	cout << "Enter Period \n";

	stPeriod period = ReadPeriod();

	cout << "Enter Date\n";

	stDate Date = ReadDate();


	if (IsDateInPeriod(period, Date))
	{
		cout << "Yes , Date is within peiod\n";
	}
	else {
		cout << "No , Date isn't within period\n";
	}


}