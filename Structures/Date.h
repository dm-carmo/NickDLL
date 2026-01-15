#pragma once
#include "NString.h"

enum Day
{
	DontCare = -1,
	Monday = 0,
	Tuesday = 1,
	Wednesday = 2,
	Thursday = 3,
	Friday = 4,
	Saturday = 5,
	Sunday = 6
};

enum TimeOfDay
{
	Morning,
	Afternoon,
	Evening
};

enum Month
{
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

class Date
{
public:
	Date(int y = 1970, int m = 1, int d = 1)
		: year(y), month(m), day(d)
	{
		normalize();
	}

	Date(const unsigned char* data, int position = 0)
	{
		short dayOfYear = ReadInt16(data + position);
		short y = ReadInt16(data + position + 2);

		if (y == 0 && dayOfYear == 0)
		{
			year = 1900;
			month = 1;
			day = 1;
			return;
		}

		year = y;
		DayOfYearToDate(year, dayOfYear, month, day);
		normalize();
	}

	// Getters
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }

	// Setters
	void setYear(int y)
	{
		year = y;
		normalize();
	}

	void setMonth(int m)
	{
		if (m < 1) m = 1;
		if (m > 12) m = 12;
		month = m;
		normalize();
	}

	void setDay(int d)
	{
		day = d;
		normalize();
	}

	// Add days (can be negative)
	void addDays(int days)
	{
		day += days;
		normalize();
	}

	void ToBytes(unsigned char* outBytes, bool includeLeapYear = true) const
	{
		short dayOfYear = (short)(DateToDayOfYear(year, month, day));
		short y = (short)year;
		int leap = isLeapYear(year) ? 1 : 0;

		WriteInt16(outBytes + 0, dayOfYear);
		WriteInt16(outBytes + 2, y);
		if (includeLeapYear)
			WriteInt32(outBytes + 4, leap);
	}


	int DayOfWeek() const	// 0 = Monday, 1 = Tuesday, 2 = Wednesday, 3 = Thursday, 4 = Friday, 5 = Saturday, 6 = Sunday
	{
		// Zeller’s Congruence (Gregorian calendar)
		int y = year;
		int m = month;
		int d = day;

		if (m < 3)
		{
			m += 12;
			y -= 1;
		}

		int K = y % 100;
		int J = y / 100;

		int h = (d + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;

		// Zeller: 0=Saturday -> convert to 0=Sunday
		int dow = (h + 6) % 7;   // 0=Sunday
		dow = (dow + 6) % 7;    // 0=Monday (as CM0102 has 0 = Monday)
		return dow;
	}

	int DayOfYear() const
	{
		return DateToDayOfYear(year, month, day);
	}

	void print(const char* szPrefix = NULL) const
	{
		const char* szDaysOfWeek[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };
		const char* szMonthsOfYear[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
		if (szPrefix)
			dprintf("%s ", szPrefix);
		dprintf("Date: y:%d m:%d d:%d DoW: %d - DayOfYear: %02X (%s %d %s %d)\n", getYear(), getMonth(), getDay(), DayOfWeek(), DayOfYear(), szDaysOfWeek[DayOfWeek()], getDay(), szMonthsOfYear[getMonth() - 1], getYear());
	}

	bool operator == (const Date& d) {
		return (day == d.day && month == d.month && year == d.year);
	}

	static Date easter_gregorian(int y) {
		if (y < 1583 || y > 9999) throw std::out_of_range("Gregorian years only");
		int a = y % 19;
		int b = y / 100, c = y % 100;
		int d = b / 4, e = b % 4;
		int f = (b + 8) / 25;
		int g = (b - f + 1) / 3;
		int h = (19 * a + b - d - g + 15) % 30;
		int i = c / 4, k = c % 4;
		int l = (32 + 2 * e + 2 * i - h - k) % 7;
		int m = (a + 11 * h + 22 * l) / 451;
		int month = (h + l - 7 * m + 114) / 31;          // 3=March, 4=April
		int day = ((h + l - 7 * m + 114) % 31) + 1;
		return Date(y, month, day);
	}

private:
	int year;
	int month; // 1-12
	int day;   // 1-31

	static bool isLeapYear(int y)
	{
		return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
	}

	static int daysInMonth(int y, int m)
	{
		static const int days[12] =
		{
			31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31
		};

		if (m == 2 && isLeapYear(y))
			return 29;

		return days[m - 1];
	}

	void normalize()
	{
		// Normalize day forward
		while (day > daysInMonth(year, month))
		{
			day -= daysInMonth(year, month);
			month++;
			if (month > 12)
			{
				month = 1;
				year++;
			}
		}

		// Normalize day backward
		while (day < 1)
		{
			month--;
			if (month < 1)
			{
				month = 12;
				year--;
			}
			day += daysInMonth(year, month);
		}
	}

	static int DateToDayOfYear(int y, int m, int d)
	{
		int daysInMonth[12] =
		{
			31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31
		};

		if (isLeapYear(y))
			daysInMonth[1] = 29;

		int doy = 0;
		for (int i = 0; i < m - 1; ++i)
			doy += daysInMonth[i];

		doy += (d - 1); // C# stored zero-based day-of-year
		return doy;
	}

	static void DayOfYearToDate(int y, int dayOfYear, int& m, int& d)
	{
		int daysInMonth[12] =
		{
			31, 28, 31, 30, 31, 30,
			31, 31, 30, 31, 30, 31
		};

		if (isLeapYear(y))
			daysInMonth[1] = 29;

		int remaining = dayOfYear;
		int monthIndex = 0;

		while (monthIndex < 12 && remaining >= daysInMonth[monthIndex])
		{
			remaining -= daysInMonth[monthIndex];
			monthIndex++;
		}

		if (monthIndex >= 12)
		{
			m = 1;
			d = 1;
			return;
		}

		m = monthIndex + 1;
		d = remaining + 1;
	}


	static short ReadInt16(const unsigned char* p)
	{
		return (short)(p[0] | (p[1] << 8));
	}

	static int ReadInt32(const unsigned char* p)
	{
		return (int)(p[0] |
			(p[1] << 8) |
			(p[2] << 16) |
			(p[3] << 24));
	}

	static void WriteInt16(unsigned char* p, short value)
	{
		p[0] = (unsigned char)(value & 0xFF);
		p[1] = (unsigned char)((value >> 8) & 0xFF);
	}

	static void WriteInt32(unsigned char* p, int value)
	{
		p[0] = (unsigned char)(value & 0xFF);
		p[1] = (unsigned char)((value >> 8) & 0xFF);
		p[2] = (unsigned char)((value >> 16) & 0xFF);
		p[3] = (unsigned char)((value >> 24) & 0xFF);
	}
};
