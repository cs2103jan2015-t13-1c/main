#pragma once

/*********************************************************************************************************
Name: Task
Type: Class
Purpose: Serves as an object that holds all attributes of a task.
It supports the overloading of constructors by the following:
(1) Tabbed formatted string (format stored in .txt files)
(2) int task index and tabbed formatted string
(3) Task attributes - string Description, time_t Start date/time,
time_t End/Deadline date/time, string Location
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
#include <sstream>
#include <ctime>

#include "Exception.h"

//Task internal int:
const int END_OF_STRING = -1;
const int NO_INDEX = -1;
const long NO_TIME = 0;

//Task type codes:
const std::string CODE_TIMED = "[T]";
const std::string CODE_PARTIALTIMED = "[P]";
const std::string CODE_DEADLINE = "[D]";
const std::string CODE_FLOATING = "[F]";
const std::string CODE_INVALID = "[I]";

//Positive int chars:
const std::string INTS = "0123456789";

//Command/Search attribute strings:
const std::string GENERAL = "General";
const std::string DESCRIPTION = "Description";
const std::string STARTDATE = "Start date";
const std::string ENDDATE = "End date";
const std::string LOCATION = "Location";

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