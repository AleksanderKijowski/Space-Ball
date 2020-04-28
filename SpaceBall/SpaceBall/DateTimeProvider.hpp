#pragma once
#include "stdafx.h"

class DateTime
{
	unsigned day = 0;
	unsigned month = 0;
	unsigned year = 0;
	unsigned hours = 0;
	unsigned minutes = 0;
	unsigned seconds = 0;
	
public:
	DateTime() = default;
	
	DateTime Now()
	{
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);

		day = now->tm_mday;
		month = now->tm_mon + 1;
		year = now->tm_year + 1900;
		hours = now->tm_hour;
		minutes = now->tm_min;
		seconds = now->tm_sec;

		return *this;
	}

	string ToString() const
	{
		return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year) + " " + std::to_string(hours) + "-" + std::to_string(minutes) + "-" + std::to_string(seconds);
	}
	
};