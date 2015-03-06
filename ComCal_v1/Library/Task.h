#pragma once

/*********************************************************************************************************
Name: Task
Type: Class
Purpose: Serves as an object that holds all attributes of a task.
It supports the overloading of constructors by the following:
(1) Tabbed formatted string (format stored in .txt files)
(2) int task index and tabbed formatted string
(3) Task attributes - string Description, time_t Start date/time, time_t End/Deadline date/time, string Location
Pre-conditions: (Tabbed formatted string constructor) Assume input taskString is tab seperated by the following attributes:
(1) Task type code
(2) Description
(3) Start date/time
(4) End/Deadline date/time
(5) Location
Post-conditions: Each task object's private attributes should be furnished with task attributes upon construction.
Non-specified task index will be stored as -1 (int), time as 0 (time_t), and location as "".
Each task object's public methods only allow its construction and retrieval of it and its attributes in various formats.
**************************************************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <algorithm>
#include <cassert>

#include "Exceptions.h"

//Task type codes:
const std::string TASKTYPECODE_TIMED = "[T]";
const std::string TASKTYPECODE_PARTIALTIMED = "[P]";
const std::string TASKTYPECODE_DEADLINE = "[D]";
const std::string TASKTYPECODE_FLOATING = "[F]";
const std::string TASKTYPECODE_INVALID = "[I]";

//Task type code length:
const int LENGTH_TASKTYPECODE = 3;

//Task attribute strings:
const std::string GENERAL = "General";
const std::string DESCRIPTION = "Description";
const std::string STARTDATE = "Start date";
const std::string STARTTIME = "Start time";
const std::string STARTDATETIME = "Start date-time";
const std::string ENDDATE = "End date";
const std::string ENDTIME = "End time";
const std::string ENDDATETIME = "End date-time";
const std::string DEADLINEDATE = "Deadline date";
const std::string DEADLINETIME = "Deadline time";
const std::string DEADLINE = "Deadline";
const std::string LOCATION = "Location";

//Positive int chars:
const std::string INTS_POSITIVE = "0123456789";

//Month int codes:
const int FEBRUARY = 1;
const int APRIL = 3;
const int JUNE = 5;
const int SEPTEMBER = 8;
const int NOVEMBER = 10;

//Time in seconds:
const int SECONDS_MINUTE = 60;
const int SECONDS_HOUR = 60 * 60;
const int SECONDS_DAY = 24 * 60 * 60;
const int SECONDS_WEEK = SECONDS_DAY * 7;

//Task object attribute indicators:
static const int END_OF_STRING = -1;
static const int NO_INDEX = -1;
static const long NO_TIME = 0;

//Task in storage format date/time string lengths, positions int:
static const int LENGTH_STORAGEMDAYSTRING = 2;
static const int LENGTH_STORAGEMONTHSTRING = 2;
static const int LENGTH_STORAGEYEARSTRING = 2;
static const int LENGTH_STORAGEHOURSTRING = 2;
static const int LENGTH_STORAGEMINSTRING = 2;
static const int LENGTH_STORAGEDATESTRING = LENGTH_STORAGEMDAYSTRING + 1 + LENGTH_STORAGEMONTHSTRING + 1 + LENGTH_STORAGEYEARSTRING + 1 + LENGTH_STORAGEHOURSTRING + LENGTH_STORAGEMINSTRING;
static const int POSITION_DATESEPARATOR1 = LENGTH_STORAGEMDAYSTRING;
static const int POSITION_DATESEPARATOR2 = LENGTH_STORAGEMDAYSTRING + 1 + LENGTH_STORAGEMONTHSTRING;
static const int POSITION_DATETIMESEPARATOR = LENGTH_STORAGEMDAYSTRING + 1 + LENGTH_STORAGEMONTHSTRING + 1 + LENGTH_STORAGEYEARSTRING;

//Task storage empty attribute symbol string:
static const std::string SYMBOL_EMPTYATTRIBUTE = "-";

class Task
{
private:
	int _index;
	std::string _code;
	std::string _description;
	time_t _startDateTime;
	time_t _endDateTime;
	std::string _location;

	void initialise(std::string);
	int getTabPosition(std::string, unsigned int);
	bool checkTaskCodeValidity(std::string);
	time_t getTimeT(std::string);
	void checkDateTimeValidity(int, int, int, int, int);

public:
	Task(std::string);
	Task(int, std::string);
	Task(std::string, time_t, time_t, std::string);
	~Task(void);
	int getIndex(void);
	std::string getCode(void);
	std::string getDescription(void);
	time_t getStartDateTime(void);
	time_t getEndDateTime(void);
	std::string getLocation(void);
	std::string prepareLine(void);
	void setInvalid();
};
