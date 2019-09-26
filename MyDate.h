/** MyDate.h - My Date Class 
 *	
 *	The MyDate class stores and manipulates Gregorian dates in a C++ program. 
 *  The aim of creating this class is to demonstrate some fundamental and 
 *  intermediate class/object concepts. It will serve as a base for exploring
 *	and implementing further OOP techniques.
 *
 *   
 *	@author		Thom MacDonald <thom.macdonald@durhamcollege.ca>
 *	@author		
 *	@version	2018.01
 *	@since		28 Jul 2018
 *	@see		<http://en.wikipedia.org/wiki/Gregorian_calendar>
 *	@see		
*/

#ifndef _MY_DATE_H

#define _MY_DATE_H

#include <iostream> 	// for console I/O
#include <iomanip>		// for output stream formatting
#include <sstream>		// for stringstream
#include <stdexcept>	// for standard exceptions
#include <ctime>		// for time related items
using namespace std;

class MyDate
{
	public:

	/***************************************************************************
	*	CONSTRUCTORS
	***************************************************************************/
	
		/** Default Constructor
		 *	Initializes the day/month/year fields to 1/1/2000.
		 */
		MyDate():myDay(1), myMonth(1), myYear(2000) {}

		/** Parametrized Constructor
		 *	Sets the day/month/year fields to parameters.
		 *	@param day (int) - the day to set to
		 *	@param month (int) - the month to set to
		 *	@param year (int) - the year to set to
		 */
		MyDate(int day, int month, int year) { SetDate(day, month, year); }
		
		/** Copy Constructor
		 *	Sets the day/month/year fields to an existing objects day/month/year fields.
		 *	@param copy (MyDate) - the existing object to copy
		 */
		MyDate(const MyDate& copy): myDay(copy.myDay), myMonth(copy.myMonth), myYear(copy.myYear) {}
		
		/** Long Constructor
		 *	Sets the day/month/year fields from a long. Also used to 
		 *  convert a long to a MyDate.
		 *	@param daysSince (long) - the days since 1/1/0001
		 *	@throws (out_of_range) if the parameter is < 1.
		 */
		MyDate(long daysSince);
		
	/***************************************************************************
	*	PUBLIC MUTATORS
	***************************************************************************/		
		
		/** SetDate()
		 *	Sets the day/month/year fields to parameters.
		 *	@param day (int) - the day to set to
		 *	@param month (int) - the month to set to
		 *	@param year (int) - the year to set to
		 */
		virtual void SetDate(int day, int month, int year) { SetYear(year); SetMonth(month); SetDay(day); }

		/** Individual Property Mutators (Sets)
		 *	Sets the corresponding field to the parameter.
		 *	@param (int) - the value to set to
		 *	@throws (out_of_range) if the parameter is out of a valid range
		 */
		void SetYear(int year);
		void SetMonth(int month);
		void SetDay(int day);

	/***************************************************************************
	*	PUBLIC ACCESSORS
	***************************************************************************/
		
		/** isLeapYear()
		 *	Determines if the year stored in the object is a leap year.
		 *	@return (bool) - true for leap year, false for non-leap year.
		 */
		bool IsLeapYear() const { return IsLeapYear(myYear); }

		/** GetDayOfWeek()
		 *	Returns the day of the week the date stored in the object is.
		 *	@return (string) - the day of the week the date stored in the object is.
		 */		
		string GetDayOfWeek() const {return DAYS_OF_WEEK[(long)(*this) % 7 + 1];}

		/** Individual Property Accessors (Gets)
		 *	Gets the value stored in the corresponding.
		 *	@return (int) - the value stored in the field
		 */
		int GetMonth() const { return myMonth; }
		int GetYear() const { return myYear; }
		int GetDay() const { return myDay; }
		
	/***************************************************************************
	*	STATIC METHODS
	***************************************************************************/
		/** isLeapYear(int)
		 *	Determines if the year passed as a parameter is a leap year.
		 *	@return (bool) - true for leap year, false for non-leap year.
		 */
		static bool IsLeapYear(int year);

		/** Today()
		 *	Returns the current date as a MyDate object.
		 *	@return (MyDate) - today's date.
		 */
		static MyDate Today();
		
	/***************************************************************************
	*	OPERATOR METHODS
	***************************************************************************/
	
	/** operator + (Addition)
	 *	Adds a specified number of days to the date and returns it.
	 *	@param  days (int) - the number of days to add
	 *	@return (MyDate) - the new date.
	 */
	MyDate operator+(int days) const;

	/** operator - (int) (Subtract days)
	 *	Subtracts a specified number of days from this date and returns it.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate) - the new date.
	 */
	MyDate operator-(int days) const;

	/** operator - (MyDate) (Subtract a MyDate) **NEW!**
	 *	Subtracts a specified date from this date and returns it.
	 *	@param  aDate (MyDate) - the number of days to subtract
	 *	@return (long) - the number of days difference.
	 */
	long operator-(const MyDate& aDate) const {return (long) *(this) - (long) aDate;}

	/** operator = (Assignment)
	 *	Assigns the member values of a specified date to this date.
	 *	@param  copy (MyDate by const ref) - the date being compared to
	 *	@return (MyDate by ref) - returns this date
	 */
	MyDate& operator=(const MyDate& copy);

	/** operator -= (Shorthand Subtract Assignment)
	 *	Subtracts a specified number of days from this date.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator-=(int days) {return *(this) = *(this) - days;}

	/** operator += (Shorthand Addition Assignment)
	 *	Adds a specified number of days to this date.
	 *	@param  days (int) - the number of days to subtract
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator+=(int days) {return *(this) = *(this) + days;}
	
	/** operator ++ (Prefix Increment)
	 *	Adds one day to this date.
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator++() {return *(this) = *(this) + 1;}
	
	/** operator ++ (Postfix Increment)
	 *	Adds one day to this date.
	 *	@return (MyDate) - the original date.
	 */
	MyDate operator++(int) 
	{ 
	    MyDate originalDate = *(this); // copy this date
		*(this) = *(this) + 1; // modify this date
		return originalDate; // return the copy
	}
	
	/** operator -- (Prefix Increment)
	 *	Subtracts one day from this date.
	 *	@return (MyDate by ref) - this date.
	 */
	MyDate& operator--() {return *(this) = *(this) - 1;}
	
	/** operator -- (Postfix Increment)
	 *	Subtracts one day from this date.
	 *	@return (MyDate) - the original date.
	 */
	MyDate operator--(int) 
	{ 
	    MyDate originalDate = *(this); // copy this date
		*(this) = *(this) - 1; // modify this date
		return originalDate; // return the copy
	}

	/** operator == (Equality)
	 *	Compares two dates memberwise and returns true if they are the same date.
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - true if the dates are the same, false if not
	 */
	bool operator==(const MyDate& compare) const
	{ 	
		return (myDay == compare.myDay &&
		    myMonth == compare.myMonth &&
		    myYear == compare.myYear);
	}

	/** operator != (Non-Equality)
	 *	Compares two dates memberwise and returns false if they are the same date.
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - false if the dates are the same, true if not
	 */
	bool operator!=(const MyDate& compare) const
	{ 	
		return (!(myDay == compare.myDay &&
		    myMonth == compare.myMonth &&
		    myYear == compare.myYear));
	}
	
	/** operator < (Less than)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is < the parameter date, false if not
	 */
	bool operator<(const MyDate& compare) const{ return (long) *this < (long) compare;}
	
	/** operator > (Greater than)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is > the parameter date, false if not
	 */
	bool operator>(const MyDate& compare) const{ return (long) *this > (long) compare;}

	/** operator <= (Less than or equal to)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is <= the parameter date, false if not
	 */
	bool operator<=(const MyDate& compare) const{ return (long) *this <= (long) compare;}
	
	/** operator > (Greater than or equal to)
	 *	Compares two dates
	 *	@param  compare (MyDate by const ref) - the date being compared to
	 *	@return (bool) - returns true if this date is >= the parameter date, false if not
	 */
	bool operator>=(const MyDate& compare) const{ return (long) *this >= (long) compare;}
	

	/** operator (long) (Typecast)
	 *	Typecasts this date as a long.
	 *	@return (long) - the number of days since 1/1/0001
	 */
	virtual operator long() const;
	
	/** operator (string) (Typecast)
	 *	Typecasts this date as a string.
	 *	@return (string) - the date stored formatted as a Long Date
	 */
	virtual operator string() const;
	
	/** operator [char] (Subscript)
	 *	Returns the day, month or year value depending on the parameter specified
	 *  @param  valueType (char) - 'd' for day, 'm' for month, 'y' for year
	 *	@return (int) - the day, month or year value
	 */
	int operator[](char valueType) const;
	
	/***************************************************************************
	*	OPERATOR FRIENDS (NEW!)
	***************************************************************************/	
	
	/** operator << (Insertion/Output)
	 *	Inserts a date into an ostream
	 *  @param  out (ostream by ref) - the output stream to insert into
	 *  @param  theDate (const MyDate by ref) - the date to insert
	 *	@return (ostream by ref) - supports daisy-chaining
	 */
 	friend ostream& operator<<(ostream& out, const MyDate& theDate);
    
	/** operator >> (Extraction/Input)
	 *	Extracts a date from an istream
	 *  @param  in (istream by ref) - the input stream to extract from
	 *  @param  theDate (MyDate by ref) - stores the extracted date
	 *	@return (istream by ref) - supports daisy-chaining
	 */
	friend istream& operator>>(istream& in, MyDate& theDate);
		
	protected: //**NEW!**
	/***************************************************************************
	*	PRIVATE INSTANCE ATTRIBUTES/FIELDS
	***************************************************************************/
		int myDay;		// stores the day of the month (1-28, 29, 30, or 31)
		int myMonth;	// stores the month (1-12)
		int myYear;		// stores the year (1+)

	/***************************************************************************
	*	PRIVATE STATIC DATA MEMBERS
	***************************************************************************/		
		static const int DAY_LIMITS[];		// the limit of the day based on the month, e.g. 31
		static const string MONTH_NAMES[];	// the month names e.g. "January"
		static const string DAYS_OF_WEEK[];	// the day of week names e.g. "Sunday"
}; // End of MyDate class declaration section

/***************************************************************************
 *	STATIC DATA MEMBER DEFINITIONS
 ***************************************************************************/
 
const int MyDate::DAY_LIMITS[] = { -1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // Index 0 not used.

const string MyDate::MONTH_NAMES[] = { "Not Used", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" }; 

const string MyDate::DAYS_OF_WEEK[] = { "Not Used", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" }; 	

/***************************************************************************
 *	CONSTRUCTOR DEFINITIONS
 ***************************************************************************/
// MyDate(long) definition
MyDate::MyDate(long dayNumber)
{
 	 const long LAST_DAY = 3652059L; // 31 Dec 9999
	  
	 // if the parameter is valid
	 if(dayNumber >= 1L && dayNumber <= LAST_DAY)
 	 {
		// Local variables
		int day = 1;	// temporary day
	 	int month = 1;	// temporary month
	 	int year = 1;	// temporary year
	 	int dayLimit;	// the highest day of any given month
	 	 
		// Loop from 1 to the parameter 
		for(int i = 1; i < dayNumber; i++)
		{
		 	// determine the highest day for the current month
			dayLimit = DAY_LIMITS[month];
			// adjust if it is a leap year and Feb
			if(IsLeapYear(year) && month == 2)
			{
				dayLimit = 29;
			}
		 	
			// increase the day counter by 1
			day++;
			
			// if the day counter exceeded the limit for this month:
			if(day > dayLimit)
			{
				month++; // roll to the next month
				day = 1; // reset to the 1st
				
				// if the month counter exceeded December (12)
				if(month > 12)
		 		{
			 		year++; // roll to the next year
			 		month = 1; // reset to Jan (1)
			 	}
		 	} // end of adjustment for roll-over
		 } // end of counting up to parameter
		 
		 // Sets the fields to the day/month/year counters
		 myDay = day;
		 myMonth = month;
		 myYear = year;
     }
     else // Otherwise, parameter was not valid
     {
		// Build an error string
		stringstream errorMessage;
		errorMessage << dayNumber << " is an invalid value for a day number.\nValue must be greater than 0.";
		// throw exception
		throw out_of_range(errorMessage.str());	
     }
}

/***************************************************************************
 *	MUTATOR DEFINITIONS
 ***************************************************************************/
// MyDate::SetYear 
void MyDate::SetYear(int year)
{
	const int MAX_YEAR = 9999; // max possible year
	const int MIN_YEAR = 1; // min possible year

	// if the year is in range
	if(year >= MIN_YEAR && year <= MAX_YEAR)
	{
		myYear = year; // set the year field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << year << " is an invalid value for year.\nValue must be between " 
					 << setfill('0') << setw(4) << MIN_YEAR << " and " 
					 << setw(4) << MAX_YEAR << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());		 
	}
}
// MyDate::SetMonth
void MyDate::SetMonth(int month)
{
	const int MAX_MONTH = 12; // max possible month
	const int MIN_MONTH = 1; // min possible month	
	
	// if the month is in range
	if(month >= MIN_MONTH && month <= MAX_MONTH)
	{
		myMonth = month; // set the month field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << month << " is an invalid value for month.\nValue must be between " 
					 << MIN_MONTH << " and " << MAX_MONTH << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());		 
	}
}

// MyDate::SetDay
void MyDate::SetDay(int day)
{
	const int MIN_DAY = 1;// min possible day
	int maxDay = DAY_LIMITS[myMonth]; // max possible day (depends on month)
	
	// if it is Feb and a leap year
	if(IsLeapYear() && myMonth == 2) 
		maxDay = 29; // set the max to 29
	
	// if the day is in range
	if(day >= MIN_DAY && day <= maxDay)
	{
		myDay = day; // set the day field
	}
	else // otherwise
	{
		// Build an error msg
		stringstream errorMessage;
		errorMessage << day << " is an invalid value for a day in " << MONTH_NAMES[myMonth] << " " 
					 << setfill('0') << setw(4) << myYear << ".\nValue must be between " 
					 << MIN_DAY << " and " << maxDay << " inclusive.";
		// throw an exception
		throw out_of_range(errorMessage.str());		 
	}
}


/***************************************************************************
 *	ACCESSOR DEFINITIONS
 ***************************************************************************/



/***************************************************************************
 *	STATIC METHOD DEFINITIONS
 ***************************************************************************/

 // MyDate::IsLeapYear(int)
bool MyDate::IsLeapYear(int year)
{
	/*
	In the Gregorian calendar 3 criteria must be taken into account to identify leap years:

    The year is evenly divisible by 4;
    If the year can be evenly divided by 100, it is NOT a leap year, unless;
    The year is also evenly divisible by 400. Then it is a leap yea
    */
    bool leapYear = false; // assume it is not a leap year
    
    if(year % 4 == 0) // Leap years must be evenly divisible by 4
    {
    	// If year can be evenly divided by 100
		if(year % 100 == 0) 
		{
			// it is NOT a leap year, UNLESS 
			// year is also evenly divisible by 400
			if(year % 400 == 0)
			{
				// it is a leap year
				leapYear = true; 
			}
		} 
		else // Leap year was not divisible by 100
		{
			// it is a leap year
			leapYear = true; 
		}
	}
    return leapYear;
}

// MyDate::Today() definition
MyDate MyDate::Today()
{
	MyDate today; // the object to set to today and return
	time_t theTime = time(NULL); // get the current time/date
	tm timeStructure = *(localtime(&theTime)); // convert to a tm structure
	today.myDay = timeStructure.tm_mday; // set the day
	today.myMonth = timeStructure.tm_mon + 1; // set the month (tm_mon is months from Jan <0-11>)
	today.myYear = timeStructure.tm_year + 1900; // set the year (tm_year is years since 1900)
	// return the object
	return today; 
}

/***************************************************************************
 *	Operator DEFINITIONS
 ***************************************************************************/

// operator + (Addition)
MyDate MyDate::operator+(int days) const
{
	MyDate newDate; // create a new empty date
	long thisDateNumber = (long) (*this); // store this date as a long
	thisDateNumber += days; // add the number of days to it
	newDate = (MyDate) thisDateNumber; // set the new date based on the long
	return newDate; // return the new date
}

// operator - (Subtraction)
MyDate MyDate::operator-(int days) const
{
	MyDate newDate; // create a new empty date
	long thisDateNumber = (long) (*this); // store this date as a long
	thisDateNumber -= days; // subtract the number of days from it
	newDate = (MyDate) thisDateNumber; // set the new date based on the long
	return newDate; // return the new date
}

// operator = (Assignment)
MyDate& MyDate::operator=(const MyDate& copy)
{
	// assign each member the corresponding 
	// member from the copy object
	myDay = copy.myDay;
	myMonth = copy.myMonth;
    myYear = copy.myYear;
    // return this object (supports obj3 = obj2 = obj1)
    return *(this);
}

// MyDate::operator string definition		
MyDate::operator string() const
{
	stringstream dateString; // string stream to build the formatted date string
	int postFixDigit;		 // the last digit of the day value
	
	// Stream the day of the week, followed by month name and day value 
	dateString << GetDayOfWeek() << ", " << MONTH_NAMES[myMonth] << " " << myDay;
	
	// determine the last digit of the day value
	postFixDigit = myDay % 10;
	
	// determine and stream the approriate post-fix
	if(postFixDigit == 1 && myDay != 11)
	{
		dateString << "st";
	}
	else if (postFixDigit == 2 && myDay != 12)
	{
			dateString << "nd";
	}
	else if (postFixDigit == 3 && myDay != 13)
	{
		dateString << "rd";
	}
	else
	{
		dateString << "th";
	}
		
	// stream the year, showing 4 digits (minimum) 
	dateString << ", " << setfill('0') << setw(4) << myYear;
	
	// return the formatted string
	return dateString.str();
}

// MyDate::operator long definition
MyDate::operator long() const
{
	long dayNumber = 0; // counter for the days since 1/1/0001
	int leapYears = 0;	// counter for the leap years since 1/1/0001
	
	// Add 365 for each year up to but not including this year
	dayNumber = (myYear - 1) * 365;

	// Count the leap years up to but not including this year
	for(int year = 1; year < myYear; year++)
	{
		if(IsLeapYear(year))
			leapYears++;
	}
	// Add 1 more day for each leap year found
	dayNumber += leapYears;
	
	// Add the number of days in each month for each month of this year
	// up to but not including this month
	for(int i = 1; i < myMonth; i++)
	{
		dayNumber += DAY_LIMITS[i];
	}
	// Add the days for this month
	dayNumber += myDay;

	// if this is a leap year and it is past 28 Feb
	if(IsLeapYear() && myMonth > 2)
	{
	    dayNumber++;
	}

	// return the sum.
	return dayNumber;
}
	
// operator [char] (Subscript)
int MyDate::operator[](char valueType) const
{
	int value = 0; // value to return
	switch(valueType) // based on the parameter char
	{
		case 'd':
		case 'D':
			value = myDay; // get day
			break;
		case 'm':
		case 'M':
			value = myMonth; // get month
			break;
		case 'y':
		case 'Y':
			value = myYear; // get year
			break;	
		default: // error, throw invalid_argument exception
			// Build an error msg
			stringstream errorMessage;
			errorMessage << valueType << " is an invalid parameter. Options are \'d\', \'m\', or \'y\'";
			// throw an exception
			throw invalid_argument(errorMessage.str());	
	}
	return value;
}

// operator << (Insertion/Output)
ostream& operator<<(ostream& out, const MyDate& theDate)
{
    // output the date in the format dd/mm/yyyy
	out << setfill('0')
         << setw(2) << theDate.myDay << '/'
         << setw(2) << theDate.myMonth << '/'
         << setw(4) << theDate.myYear << setfill(' ');
    return out;  // return the output stream
}

// operator >> (Extraction/Input)
istream& operator>>(istream& in, MyDate& theDate)
{
    int day;  // temp day
    int month; // temp month
    int year; // temp year

    in >> day; // get day
    in.ignore(); // ignore the '/'
    in >> month; // get month
    in.ignore(); // ignore the '/'
    in >> year; // get year
    
    // store the date
    theDate.SetDate(day, month, year);
    
    return in; // return the input stream
}

#endif
