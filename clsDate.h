#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<vector>
#include<string>
#include"clsString.h"
using namespace std;
class clsDate
{
	short _Day, _Month, _Year;
  

public:
	clsDate() {
        time_t t = time(0);
        tm* now = localtime(&t);
        _Day = now->tm_mday;
        _Month = now->tm_mon + 1;
        _Year = now->tm_year + 1900;
	}
    
    clsDate(short Day, short Month, short Year) {
        _Day = Day;
        _Month = Month;
        _Year = Year;
	}
    clsDate(string Date) {
        clsDate date = stringToDate(Date);
        _Day = date.Day;
        _Month = date.Month;
        _Year = date.Year;
	}
    clsDate(short numberOfDays,short year) {
        clsDate Date1 = dateFromDayOrderInYear(numberOfDays, year);
        _Day = Date1.Day;
        _Month = Date1.Month;
        _Year = Date1.Year;
	}

    void setDay(short Day) {
        _Day = Day;
    }
    short getDay() {
        return _Day;
    }
    __declspec(property(get = getDay, put = setDay))short Day;

    void setMonth(short Month) {
        _Month = Month;
    }
    short getMonth() {
        return _Month;
    }
    __declspec(property(get = getMonth, put = setMonth))short Month;

    void setYear(short Year) {
        _Year = Year;
    }
    short getYear() {
        return _Year;
    }
    __declspec(property(get = getYear, put = setYear))short Year;

    void print() {
        cout << dateToString() << endl;

    }
    void printWithFormat(string format = "dd/mm/yyyy") {
        cout << dateFormate(format) << endl;
    }
//===========================================================================

    static string dateToString(clsDate Date)
    {
        return to_string(Date.Day) + "/" +
            to_string(Date.Month) + "/" + to_string(Date.Year);
    }
    string dateToString()
    {
        return dateToString(*this);
    }

    static string dateFormate(clsDate date, string format = "dd/mm/yyyy")
    {
        string formatDateToString = "";

        formatDateToString = clsString:: replaceUsingBultIn(format, "dd", to_string(date.Day));
        formatDateToString = clsString::replaceUsingBultIn(formatDateToString, "mm", to_string(date.Month));
        formatDateToString = clsString::replaceUsingBultIn(formatDateToString, "yyyy", to_string(date.Year));

        return formatDateToString;
    }
    string dateFormate(string format = "dd/mm/yyyy") {
        return dateFormate(*this, format);
    }

    static clsDate stringToDate(string strDate)
    {
        clsDate date;

        vector<string>vString = clsString::split(strDate, "/");

        date.Day = stoi(vString[0]);
        date.Month = stoi(vString[1]);
        date.Year = stoi(vString[2]);
        return date;
    }

    static clsDate systemDate()
    {
        //system date
        time_t t = time(0);
        tm* now = localtime(&t);
        short Day, Month, Year;
        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        return clsDate(Day, Month, Year);
    }

    static string GetSystemDateTimeString()
    {
        //system datetime string
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
            + to_string(Hour) + ":" + to_string(Minute)
            + ":" + to_string(Second));

    }


    static clsDate dateFromDayOrderInYear(short DateOrderInYear, short Year)
    {
        clsDate Date;
        short RemainingDays = DateOrderInYear;
        short MonthDays = 0;
        Date.Year = Year;
        Date.Month = 1;
        while (true)
        {
            MonthDays = numberOfDaysInMonth(Date.Month, Year);
            if (RemainingDays > MonthDays)
            {
                RemainingDays -= MonthDays;
                Date.Month++;
            }
            else
            {
                Date.Day = RemainingDays;
                break;
            }
        }
        return Date;
    }

    static short numberOfDaysInYear(short year) {

        return isLeapYear(year) ? 366 : 365;
    }
     short numberOfDaysInYear() {

        return isLeapYear(_Year) ? 366 : 365;
    }

     static int numberOfHoursInYear(short year) {

         return numberOfDaysInYear(year) * 24;
     }
     int numberOfHoursInYear() {

         return numberOfDaysInYear(_Year) * 24;
     }

     static int numberOfMinutesInAYear(short Year)
     {
         return numberOfHoursInYear(Year) * 60;
     }
     int numberOfMinutesInAYear()
     {
         return numberOfMinutesInAYear(_Year);
     }

     static int numberOfSecondsInAYear(short Year)
     {
         return numberOfMinutesInAYear(Year) * 60;
     }
     int numberOfSecondsInAYear()
     {
         return numberOfSecondsInAYear(_Year);
     }

    static short numberOfDaysInMonth(short Month, short Year) {

        if (Month < 1 || Month>12)
            return 0;

        int numberOfDays[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };

        return (Month == 2 ? (isLeapYear(Year) ? 29 : 28) : numberOfDays[Month]);
    }
    short numberOfDaysInMonth() {

        return numberOfDaysInMonth(_Month, _Year);
    }

    static short numberOfHoursInMonth(short Month, short Year)

    {
        return numberOfDaysInMonth(Month, Year) * 24;
    }
    short numberOfHoursInMonth()
    {
        return numberOfDaysInMonth(_Month, _Year) * 24;
    }

    static int numberOfMinutesInMonth(short Month, short Year)
    {
        return numberOfHoursInMonth(Month, Year) * 60;
    }
    int numberOfMinutesInMonth()
    {
        return numberOfHoursInMonth(_Month, _Year) * 60;
    }

    static int numberOfSecondsInMonth(short Month, short Year)
    {
        return numberOfMinutesInMonth(Month, Year) * 60;
    }
    int numberOfSecondsInMonth()
    {
        return numberOfMinutesInMonth(_Month, _Year) * 60;
    }

   static short dayOfWeekOrder(clsDate date) {

        short a, y, m;

        a = (14 - date.Month) / 12;

        y = date.Year - a;

        m = date.Month + (12 * a) - 2;

        return (date.Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
   static short dayOfWeekOrder(short day, short month, short year) {

       short a, y, m;

       a = (14 - month) / 12;

       y = year - a;

       m = month + (12 * a) - 2;

       return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
   }
   short dayOfWeekOrder() {

       return dayOfWeekOrder(*this);
   }

   static string dayShortName(short Day, short Month, short Year) {

       string arrDayName[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri" , "Sat" };

       return arrDayName[dayOfWeekOrder(Day, Month, Year)];
   }
     string dayShortName() {

       string arrDayName[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri" , "Sat" };

       return arrDayName[dayOfWeekOrder(_Day, _Month, _Year)];
   }

   static string montShortName(short month) {
       string arrDayName[] = { "Jan", "Feb", "Mars", "April", "May", "June" , "July", "Aug", "Sep", "Oct" , "Nov", "Dec" };
       return arrDayName[month - 1];
   }
   string montShortName() {

       return montShortName(_Month);
   }

   static void printMonthCalender(short month, short year) {

       short current, numberOfDays;
       current = dayOfWeekOrder(1, month, year);
       numberOfDays = numberOfDaysInMonth(month, year);

       printf("\n  _______________%s_______________\n\n", montShortName(month).c_str());

       printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

       int i;
       for (i = 0; i < current; i++)
           printf("     ");

       for (short j = 1; j <= numberOfDays; j++)
       {
           printf("%5d", j);
           if (++i == 7) {
               i = 0;
               printf("\n");
           }
       }

       printf("\n  __________________________________\n");
   }
   void printMonthCalender() {

       printMonthCalender(_Month, _Year);
   }

   static void printYearCalender(short year) {

       printf("  __________________________________\n\n");
       printf("          Calender - %d", year);
       printf("\n  __________________________________\n");

       for (short i = 1; i <= 12; i++)
       {
           printMonthCalender(i, year);
       }
   }
   void printYearCalender() {

       printYearCalender(_Year);
   }
   
   static short DaysFromTheBeginingOfTheYear(short day, short month, short year) {
       short totalDays = day;

       for (short i = 1; i < month; i++)

           totalDays += numberOfDaysInMonth(month, year);


       return totalDays;
   }
   short DaysFromTheBeginingOfTheYear() {

       return DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
   }

   void addDaysToDate( short DaysToAdd) {

       short RemainingDays = DaysToAdd + DaysFromTheBeginingOfTheYear(_Day, _Month, _Year);
       short MonthDays = 0;
       _Month = 1;
       while (true)
       {
           MonthDays = numberOfDaysInMonth(_Month, _Year);
           if (RemainingDays > MonthDays)
           {
               RemainingDays -= MonthDays;
               _Month++;
               if (_Month > 12)
               {
                   _Month = 1;
                   _Year++;
               }
           }
           else
           {
               _Day = RemainingDays;
               break;
           }
       }

   }

//===========================================================================
//bool Excepretiond
    static bool isLeapYear(short year) {


        return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));

    }
    bool isLeapYear() {


        return isLeapYear(_Year);

    }

   static bool isDate1BeforeDate2(clsDate date1, clsDate date2){
    return (date1.Year < date2.Year) ? true : ((date1.Year ==
        date2.Year) ? (date1.Month < date2.Month ? true : (date1.Month ==
            date2.Month ? date1.Day < date2.Day : false)) : false);
    }
    bool isDateBeforeDate2( clsDate date){
        return isDate1BeforeDate2(*this, date);
    }

    static bool isDate1EqualDate2(clsDate date1, clsDate date2) {

        return (date1.Year == date2.Year) ? ((date1.Month ==
            date2.Month) ? ((date1.Day == date2.Day) ? true : false) : false)
            : false;
    }
    bool isDateEqualDate2( clsDate date) {

        return isDate1EqualDate2(*this, date);
    }

   static bool isDateAfterDate2(clsDate date1, clsDate date2) {

        return (!isDate1BeforeDate2(date1, date2) &&
            !isDate1EqualDate2(date1, date2));
    }
   bool isDateAfterDate2( clsDate date) {

       return isDateAfterDate2(*this, date);
   }

  static bool isLastDayInMonth(clsDate date)
   {

       return(date.Day == numberOfDaysInMonth(date.Month, date.Year));
   }
   bool isLastDayInMonth()
   {
       return isLastDayInMonth(*this);
   }

   static bool isLastMonthInYear(short month) {

       return (month == 12);
   }
   bool isLastMonthInYear() {

       return isLastMonthInYear(_Month);

   }

   static bool isEndOfWeek(clsDate date) {

       return (dayOfWeekOrder(date) == 6);
   }
   bool isEndOfWeek() {

       return (dayOfWeekOrder(*this) == 6);
   }

   static bool isWeekEnd(clsDate date) {

       short dayIndex = dayOfWeekOrder(date);

       return (dayIndex == 5 || dayIndex == 6);
   }
   bool isWeekEnd() {

       return isWeekEnd(*this);
   }

   static bool isBusinessDay(clsDate date)
   {

       return (!isWeekEnd(date));
   }
   bool isBusinessDay()
   {

       return isBusinessDay(*this);
   }

   static bool isValidDate(clsDate date) {
     
       return ((date.Day < 1) || date.Day > numberOfDaysInMonth(date.Year, date.Month) ? false : (date.Month > 12 || date.Month < 1) ? false : true);
   }
   bool isValid() {
     
       return isValidDate(*this);
   }
//===========================================================================
//Days Untill , Get Difference Between Days, Claculate Age In Days & Vacations & Modify Date,Get Date From Vacation Days (2 Versions);
   static void swapDates(clsDate& date1, clsDate& date2) {
       clsDate TempDate;
       TempDate = date1;
       date1 = date2;
       date2 = TempDate;
   }
   void swapDates( clsDate& date) {
       
       swapDates(*this, date);
   }

   static short daysUntillEndOfTheWeek(clsDate date)
   {
       return 6 - dayOfWeekOrder(date);
   }
   short daysUntillEndOfTheWeek()
   {
       return 6 - dayOfWeekOrder(*this);
   }

  static int getDifferenceInDays(clsDate date1, clsDate date2, bool includeEndDay = false)
   {
       int days = 0;
       int swapFalg = 1;

       if (!isDate1BeforeDate2(date1, date2)) {
           swapFalg = -1;
           swapDates(date1, date2);

       }

       while (isDate1BeforeDate2(date1, date2)) {

           days++;
           date1 = increaseDateByOneDay(date1);
       }

       return includeEndDay ? ++days * swapFalg : days * swapFalg;

   }
   int getDifferenceInDays(clsDate date, bool includeEndDay = false)
   {
       return getDifferenceInDays(*this, date, includeEndDay);
   }

   static short CalculateMyAgeInDays(clsDate DateOfBirth)
   {
       return getDifferenceInDays(DateOfBirth, clsDate::systemDate(), true);
   }

   static short daysUntillEndOfTheMonth(clsDate date) {

       clsDate EndOfMonthDate;
       EndOfMonthDate.Day = numberOfDaysInMonth(date.Month, date.Year);
       EndOfMonthDate.Month = date.Month;
       EndOfMonthDate.Year = date.Year;

       return getDifferenceInDays(date, EndOfMonthDate, true);
   }
   short daysUntillEndOfTheMonth() {

       return daysUntillEndOfTheMonth(*this);
   }

   static short daysUntillEndOfTheYear(clsDate date) {

       clsDate EndOfYearDate;
       EndOfYearDate.Day = 31;
       EndOfYearDate.Month = 12;
       EndOfYearDate.Year = date.Year;

       return getDifferenceInDays(date, EndOfYearDate, true);
   }
   short daysUntillEndOfTheYear() {

       return daysUntillEndOfTheYear(*this);
   }

   static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo)
   {
       short Days = 0;
       while (isDate1BeforeDate2(DateFrom, DateTo))
       {
           if (isBusinessDay(DateFrom))
               Days++;
           DateFrom = increaseDateBy1Decade(DateFrom);
       }
       return Days;
   }

  static short calculateAcualVacations(clsDate dateFrom, clsDate dateTo)
   {
       //short daysCount = 0;

       //while (isDateBeforeDate2(dateFrom, dateTo)) {

       //    if (isBusinessDay(dateFrom))
       //        daysCount++;

       //    dateFrom = increaseDateByOneDay(dateFrom);

       //}
      return CalculateBusinessDays(dateFrom, dateTo);
   }
   short calculateAcualVacations( clsDate dateTo)
   {
      return calculateAcualVacations(*this, dateTo);
   }

  static clsDate getDateFromVacationDays(clsDate& DateFrom, short Days) {

       while (Days > 0) {

           if (isBusinessDay(DateFrom))
               Days--;

           DateFrom = increaseDateByOneDay(DateFrom);
       }
       return DateFrom;
   }
   void getDateFromVacationDays( short Days) {

       getDateFromVacationDays(*this, Days);
   }

   static clsDate calVacationsReturnDate(clsDate &DateFrom, short Days) {

       short weeKEndCounter = 0;

       while (isWeekEnd(DateFrom)) {

           DateFrom = increaseDateByOneDay(DateFrom);
       }

       for (short i = 0; i < Days + weeKEndCounter; i++) {
           if (isWeekEnd(DateFrom))
               weeKEndCounter++;

           DateFrom = increaseDateByOneDay(DateFrom);
       }

       while (isWeekEnd(DateFrom)) {

           DateFrom = increaseDateByOneDay(DateFrom);
       }

       return DateFrom;
   }
   void calVacationsReturnDate( short Days)
   {
       calVacationsReturnDate(*this, Days) ;
   }

   static clsDate modifyDate(clsDate &date) {
       //last check day in date should not exceed max days in
   //the current month
       // example if date is 31/1/2022 increasing one month
       //should not be 31 / 2 / 2022, it should
       // be 28/2/2022
       short numberOfDays = numberOfDaysInMonth(date.Month, date.Year);
       if (date.Day > numberOfDays)
           date.Day = numberOfDays;

       return date;
   }


//===========================================================================
//increase Date 
   static clsDate increaseDateByOneDay(clsDate &date) {

       if (isLastDayInMonth(date)) {

           if (isLastMonthInYear(date.Month)) {
               date.Month = 1;
               date.Day = 1;
               date.Year++;
           }
           else {
               date.Day = 1;
               date.Month++;
           }

       }
       else {
           date.Day++;
       }

       date = modifyDate(date);


       return date;
   }
   void increaseDateByOneDay() {

       increaseDateByOneDay(*this);
   }

  static clsDate increaseDateByXDays(clsDate &date,short numberOfDays) {
       for (short i = 0; i < numberOfDays; i++)
       {
           date = increaseDateByOneDay(date);
       }
       return date;
   }
   void increaseDateByXDays(short numberOfDays) {
       
       increaseDateByXDays(*this, numberOfDays);
   }

   static clsDate increaseDateBy1Week(clsDate &date) {

       for (short i = 0; i < 7; i++)
       {
           date = increaseDateByOneDay(date);
       }
       return date;
   }
   void increaseDateBy1Week() {

       increaseDateBy1Week(*this);
   }

   static clsDate increaseDateByXWeeks( clsDate &date, short numberOfWeeks) {

       for (short i = 0; i < numberOfWeeks; i++)
       {
           date = increaseDateBy1Week(date);
       }
       return date;
   }
   void increaseDateByXWeeks(short numberOfWeeks)
   {
       increaseDateByXWeeks(*this, numberOfWeeks);
   }

   static clsDate increaseDateBy1Month(clsDate &date) {

       if (date.Month == 12)
       {
           date.Month = 1;
           date.Year++;

       }
       else {
           date.Month++;

       }

       date = modifyDate(date);

       return date;
   }
   void increaseDateBy1Month() {
       increaseDateBy1Month(*this);
   }

   static clsDate increaseDateByXMonths( clsDate &date, short numberOfMonths)
   {
       for (short i = 0; i < numberOfMonths; i++)
       {
           date = increaseDateBy1Month(date);
       }
       return date;
   }
   void increaseDateByXMonths(short numberOfMonths)
   {
       increaseDateByXMonths(*this, numberOfMonths);
   }

   static clsDate increaseDateBy1Year(clsDate& date) {

       date.Year++;
       date = modifyDate(date);

       return date;
   }
   void increaseDateBy1Year() {
       increaseDateBy1Year(*this);
   }

   static clsDate increaseDateByXYears(clsDate& date, short numberOfYears) {

       date.Year += numberOfYears;
       date = modifyDate(date);

       return date;
   }
   void increaseDateByXYears(short numberOfYears) {
       increaseDateByXYears(*this,numberOfYears);
    }

   static clsDate increaseDateBy1Decade(clsDate& date) {

       date.Year += 10;
       date = modifyDate(date);

       return date;
   }
   void increaseDateBy1Decade()
   {
        increaseDateBy1Decade(*this) ;
   }

   static clsDate increaseDateByXDecades(clsDate& date, short numberOfDecades) {

       date.Year += (10 * numberOfDecades);

       date = modifyDate(date);

       return date;
   }
   void increaseDateByXDecades(short numberOfDecades) {
        increaseDateByXDecades(*this, numberOfDecades) ;

   }

   static clsDate increaseDateByCentury(clsDate& date) {

       date.Year += 100;
       date = modifyDate(date);

       return date;
   }
   void increaseDateByCentury()
   {
       increaseDateByCentury(*this) ;
   }

   static clsDate increaseDateByMillennium(clsDate& date)
   {

       date.Year += 1000;
       date = modifyDate(date);

       return date;
   }
   void increaseDateByMillennium() {
        increaseDateByMillennium(*this) ;
   }

//===========================================================================
//Decrease Date 
  static clsDate decreaseDateByOneDay(clsDate& date) {

       if (date.Day == 1) {

           if (date.Month == 1) {
               date.Day = 31;
               date.Month = 12;
               date.Year--;
           }
           else {
               date.Month--;
               date.Day = numberOfDaysInMonth(date.Year, date.Month);

           }

       }
       else {
           date.Day--;
       }
       return date;
   }
   void decreaseDateByOneDay() {
        decreaseDateByOneDay(*this) ;
   }

   static clsDate decreaseDateByXDays(clsDate& date, short numberOfDays) {
       for (short i = 0; i < numberOfDays; i++)
       {
           date = decreaseDateByOneDay(date);
       }
       return date;
   }
   void decreaseDateByXDays(short numberOfDays) {
       decreaseDateByXDays(*this, numberOfDays) ;
   }

   static clsDate decreaseDateBy1Week(clsDate& date) {

       for (short i = 0; i < 7; i++)
       {
           date = decreaseDateByOneDay(date);
       }
       return date;
   }
   void decreaseDateBy1Week() {
        decreaseDateBy1Week(*this) ;
   }

   static clsDate decreaseDateByXWeeks( clsDate& date,short numberOfWeeks) {

       for (short i = 0; i < numberOfWeeks; i++)
       {
           date = decreaseDateBy1Week(date);
       }
       return date;
   }
   void decreaseDateByXWeeks(short numberOfWeeks) {
        decreaseDateByXWeeks(*this, numberOfWeeks) ;
   }

   static clsDate decreaseDateBy1Month(clsDate& date) {

       if (date.Month == 1)
       {
           date.Month = 12;
           date.Year--;

       }
       else {
           date.Month--;

       }
       date = modifyDate(date);

       return date;
   }
   void decreaseDateBy1Month() {
        decreaseDateBy1Month(*this) ;
   }

   static clsDate decreaseDateByXMonths( clsDate& date,short numberOfMonths)
   {
       for (short i = 0; i < numberOfMonths; i++)
       {
           date = decreaseDateBy1Month(date);
       }
       return date;
   }
   void decreaseDateByXMonths(short numberOfMonths) {
        decreaseDateByXMonths(*this, numberOfMonths) ;
   }

   static clsDate decreaseDateBy1Year(clsDate& date) {

       date.Year--;
       date = modifyDate(date);

       return date;
   }
   void decreaseDateBy1Year() {
        decreaseDateBy1Year(*this) ;
   }

   static clsDate decreaseDateByXYears( clsDate& date, short numberOfYears) {

       date.Year -= numberOfYears;
       date = modifyDate(date);

       return date;
   }
   void decreaseDateByXYears(short numberOfYears) {
      decreaseDateByXYears(*this, numberOfYears) ;
   }

  static clsDate decreaseDateBy1Decade(clsDate& date) {

       date.Year -= 10;
       date = modifyDate(date);

       return date;
   }
  void decreaseDateBy1Decade() {
      decreaseDateBy1Decade(*this) ;
  }

  static clsDate decreaseDateByXDecades(clsDate& date,short numberOfDecades) {

       date.Year -= (10 * numberOfDecades);
       date = modifyDate(date);

       return date;
   }
   void decreaseDateByXDecades(short numberOfDecades) {
       decreaseDateByXDecades(*this, numberOfDecades) ;
   }

   static clsDate decreaseDateByCentury(clsDate& date) {

       date.Year -= 100;
       date = modifyDate(date);

       return date;
   }
   void decreaseDateByCentury() {
        decreaseDateByCentury(*this) ;
   }

  static clsDate decreaseDateByMillennium(clsDate& date) {

       date.Year -= 1000;
       date = modifyDate(date);

       return date;
   }
   void decreaseDateByMillennium() {
        decreaseDateByMillennium(*this) ;
   }

   enum enDateCompare { Before = -1, Equal = 0, After = 1 };
   static enDateCompare compareDates(clsDate Date1, clsDate Date2)
   {
       if (isDate1BeforeDate2(Date1, Date2))
           return enDateCompare::Before;
       if (isDate1EqualDate2(Date1, Date2))
           return enDateCompare::Equal;
       return enDateCompare::After;
   }
   enDateCompare compareDates(clsDate Date2)
   {
       return compareDates(*this, Date2);
   }
};

