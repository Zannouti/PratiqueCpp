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


stDate IncreaseDateByOneDay(stDate Date)
{
	if (IsLastDayInMonth(Date))
	{
		if (IsLastMonthInYear(Date))
		{
			Date.Month = 1;
			Date.Day = 1;
			Date.Year++;
		}
		else {
			Date.Month++;
		}

	}
	else {
		Date.Day++;
	}

	return Date;
}

int GetDiffrenceInDays(stDate Date1, stDate Date2, bool IncludeEndDay = false)
{
	int Days = 0;
	while (IsDate1BeforeDate2(Date1, Date2))
	{
		Days++;
		Date1 = IncreaseDateByOneDay(Date1);
	}
	return IncludeEndDay ? ++Days : Days;
}


int PeriodLengthInDays(stPeriod period, bool IncludeEndDay = false)
{
	return GetDiffrenceInDays(period.StartDate, period.EndDate, IncludeEndDay);

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

bool IsDateInPeriod(stPeriod period, stDate Date)
{
	return !(DateCompare(Date, period.StartDate) == enDateCompare::Before || DateCompare(Date, period.EndDate) == enDateCompare::After);

}


bool  IsOverLap(stPeriod period1, stPeriod period2)
{
	if (DateCompare(period2.EndDate, period1.StartDate) == enDateCompare::Before || DateCompare(period2.StartDate, period1.EndDate) == enDateCompare::After)
	{
		return false;

	}
	return true;
}

int CountOverLapsDays(stPeriod period1, stPeriod period2)
{
	int Period1Length = PeriodLengthInDays(period1, true);

	int Period2Length = PeriodLengthInDays(period2, true);
	int DaysOverlap = 0;

	if (!IsOverLap(period1, period2))
	{
		return 0;
	}

	if (Period1Length < Period2Length)
	{
		while (IsDate1BeforeDate2(period1.StartDate,period1.EndDate))
		{
			if (IsDateInPeriod(period2, period1.StartDate))
			{
				DaysOverlap++;

			}
				period1.StartDate = IncreaseDateByOneDay(period1.StartDate);
			
		}
	}
	else
	{
		while (IsDate1BeforeDate2(period2.StartDate, period2.EndDate))
		{
			if (IsDateInPeriod(period1, period2.StartDate)) {
				DaysOverlap++;

			}
			period2.StartDate = IncreaseDateByOneDay(period2.StartDate);
		}
	}
	return DaysOverlap;
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
	cout << "Enter Period 1 \n";

	stPeriod period1 = ReadPeriod();

	cout << "Enter Period 2 \n";

	stPeriod period2 = ReadPeriod();

	cout << "Days Overlap is : \n";

	cout << CountOverLapsDays(period1, period2);
	

}