#pragma once
#include"clsDate.h"
class clsPeriod
{
public:
	clsDate startDate;
	clsDate endDate;

	clsPeriod(clsDate startDate, clsDate endDate) {
		this->startDate = startDate;
		this->endDate = endDate;
	}
	void print()
	{
		cout << "Period Start: ";
		startDate.print();


		cout << "Period End: ";
		endDate.print();


	}

	static bool isDateInPeriod(clsDate date, clsPeriod period)
	{
		return !(clsDate::compareDates(date, period.startDate) == clsDate::Before
			||
			clsDate::compareDates(date, period.endDate) == clsDate::After);
	}
	bool isDateInPeriod(clsDate date) {
		return isDateInPeriod(date, *this);
	}

	static bool isOverlapPeriods(clsPeriod period1, clsPeriod period2)
	{
		return(clsDate::compareDates(period2.endDate, period1.startDate) ==clsDate:: Before 
			||
			clsDate::compareDates(period2.startDate, period1.endDate) == clsDate::After ? false : true);
	}
	bool isOverlapWith(clsPeriod period) {
		return isOverlapPeriods(*this, period);
	}

	static int periodLengthInDays(clsPeriod period, bool includeEndDate = false) {

		return clsDate::getDifferenceInDays(period.startDate, period.endDate, includeEndDate);
	}
	int periodLengthInDays(bool includeEndDate = false) {
		return periodLengthInDays(*this, includeEndDate);
	}

	static int countOverlapDays(clsPeriod period1, clsPeriod period2) {

		int period1Length = periodLengthInDays(period1, true);
		int period2Length = periodLengthInDays(period2, true);
		int overlapDays = 0;

		if (!isOverlapPeriods(period1, period2))
			return 0;

		if (period1Length > period2Length) {
			while (clsDate::isDate1BeforeDate2(period1.startDate, period1.endDate))
			{
				if (isDateInPeriod(period1.startDate, period2))
					overlapDays++;

				period1.startDate = clsDate::increaseDateByOneDay(period1.startDate);

			}
		}
		else {
			while (clsDate::isDate1BeforeDate2(period2.startDate, period2.endDate))
			{
				if (isDateInPeriod(period2.startDate, period1))
					overlapDays++;

				period2.startDate = clsDate::increaseDateByOneDay(period2.startDate);

			}
		}
		return overlapDays;
	}
	int countOverlapDays(clsPeriod period) {
		return countOverlapDays(*this, period);
	}
};

