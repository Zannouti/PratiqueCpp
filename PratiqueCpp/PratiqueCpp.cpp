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


short NumbersOfDaysInMonth(short Month, short Year)
{
	if (Month < 1 || Month > 12) {
		return 0;
	}

	int daysInMonth[12] = { 31, 28,31,30,31,30,31,31,30,31,30,31 };

	return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : daysInMonth[Month - 1];

}



bool IsLastDayInMonth(stDate Date)
{
	return Date.Day == NumbersOfDaysInMonth(Date.Month, Date.Year);
}

bool IsLastMonthInYear(stDate Date)
{
	return Date.Month == 12;
}


bool ValidateDate(stDate Date )
{
	if (Date.Day < 1  || Date.Day > 31)
	{
		return false;
	}
	 if (Date.Month < 1 || Date.Month > 12)
	{
		return false;
	}
	

	if (Date.Month == 2)
	{
		if (isLeapYear(Date.Year))
		{
			if (Date.Day > 28)
			{
				return false;
			}
		
		}
		else {
			if (Date.Day > 29)
			{
				return false;
			}
		}
	}
	short DaysMonth = NumbersOfDaysInMonth( Date.Month,  Date.Year);
	if (Date.Day > DaysMonth)
	{
		return false;
	}
	else
		return true; 
}











short ReadDay()
{
	short Day;
	cout << "\n Please enter a Day? ";
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
	stDate Date;

	Date.Day = ReadDay();
	Date.Month = ReadMonth();
	Date.Year = ReadYear();

	return Date;
}





int main()
{
	stDate Date;

	Date = ReadDate();

	if (ValidateDate(Date))
	{
		cout << "Yes , is  valide Date ";
	}else
		cout << "No , is not   valide Date ";


}