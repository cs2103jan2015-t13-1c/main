#pragma once

/**********************************************************************************************************
Name: Command
Type: Class
Purpose: Parent class of all command functionality classes.
Holds common attributes and methods used across command functionality classes under protected.
executeInput API is a virtual method with each child command functionality class having its own
customised implementation.
Private methods are functions used to support implementation of its protected methods, for
increased abstraction.
Holds a private attribute of pointer to TextManipulator object
**********************************************************************************************************/

#include "TextManipulator.h"
#include "Task.h"

//Command strings:
static const std::string COMMAND_ADD = "add";
static const std::string COMMAND_SHOW = "show";
static const std::string COMMAND_EDIT = "edit";
static const std::string COMMAND_DELETE = "del";
static const std::string COMMAND_EXIT = "exit";
static const std::string COMMAND_DONE = "done";
static const std::string COMMAND_UNDONE = "undone";
static const std::string COMMAND_UNDO = "undo";
static const std::string COMMAND_REDO = "redo";
static const std::string COMMAND_SEARCH = "search";
static const std::string COMMAND_HELP = "help";

//Task type strings:
const std::string TASKTYPE_EVENT = "EVENT";
const std::string TASKTYPE_DEADLINE = "DEADLINE";
const std::string TASKTYPE_TASK = "TO-DO";

//Attribute keyword string array and indexes:
const int ATTRIBUTEKEYWORDSARRAYSIZE = 4;
const std::string ATTRIBUTEKEYWORDSARRAY[ATTRIBUTEKEYWORDSARRAYSIZE] = { " .d ", " .s ", " .e ", " .l " };
const int INDEX_DESCRIPTION = 0;
const int INDEX_STARTDATETIME = 1;
const int INDEX_ENDDATETIME = 2;
const int INDEX_LOCATION = 3;

//Natural keyword string array and indexes:
const int NATURALKEYWORDSARRAYSIZE = 5;
const std::string NATURALKEYWORDSARRAY[NATURALKEYWORDSARRAYSIZE] = { " on ", " from ", " to ", " by ", " in " };
const int INDEX_ON = 0;
const int INDEX_FROM = 1;
const int INDEX_TO = 2;
const int INDEX_BY = 3;
const int INDEX_IN = 4;

//processTime boolean indicators:
const bool START = true;
const bool END = false;
const bool WEEK_PERMITTED = true;
const bool WEEK_NOT_PERMITTED = false;

//processTime DD, MM, YY, time, HH and MM lengths:
const int LENGTH_MDAYINPUT = 2;
const int LENGTH_MONTHINPUT = 2;
const int LENGTH_YEARINPUT = 2;
const int LENGTH_TIMEINPUT = 4;
const int LENGTH_HOURINPUT = 2;
const int LENGTH_MININPUT = 2;

//processTime keyword string array and indexes:
static const int SIZE_TYPEKEYWORDSARRAY = 3 + 7 + 1;
static const std::string TYPEKEYWORDS[SIZE_TYPEKEYWORDSARRAY] = { "today", "tomorrow", "yesterday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday", "week" };
static const int INDEX_TODAY = 0;
static const int INDEX_TOMORROW = 1;
static const int INDEX_YESTERDAY = 2;
static const int INDEX_MONDAY = 3;
static const int INDEX_TUESDAY = 4;
static const int INDEX_WEDNESDAY = 5;
static const int INDEX_THURSDAY = 6;
static const int INDEX_FRIDAY = 7;
static const int INDEX_SATURDAY = 8;
static const int INDEX_SUNDAY = 9;
static const int INDEX_WEEK = 10;

//processTime this/next/last string array and indexes:
static const int SIZE_THISNEXTLASTARRAY = 3;
static const std::string THISNEXTLAST[SIZE_THISNEXTLASTARRAY] = { "this", "next", "last" };
static const int INDEX_THIS = 0;
static const int INDEX_NEXT = 1;
static const int INDEX_LAST = 2;

//processTime DD/MM/YY date input seperator char and position int:
static const int SIZE_SEPARATORSARRAY = 1;
static const char SEPARATORS[SIZE_SEPARATORSARRAY] = { '/' };
static const int POSITION_SEPARATOR1 = LENGTH_MDAYINPUT;
static const int POSITION_SEPARATOR2 = LENGTH_MDAYINPUT + 1 + LENGTH_MONTHINPUT;

//processTimeUndefined time int code:
static const int UNDEFINED = -1;

//processTimeTToString return date/time string lengths:
static const int LENGTH_FEEDBACKDATESTRING = 16;
static const int LENGTH_FEEDBACKTIMESTRING = 7;

//prepareTaskDisplayAttributeBreakdown attribute indentation position for wrapText:
static const int POS_ATTRIBUTE_LINE = 17;

//wrapText console height and width sizes:
static const int CONSOLE_HEIGHT = 300;
static const int CONSOLE_WIDTH = 80;

class Command
{
protected:
	Manipulator* _todoTMPtr;
	Manipulator* _doneTMPtr;

	/************************************************************************************************************
	Name: extractParamsForKeywords
	Type: Protected Method
	Purpose: Processes input string with given vector of keywords and extracts params for each keyword,
	Returns the params extracted as a vector of vector of strings, with the params extracted for each keyword
	as a vector of strings assigned to its corresponding index element
	eg. If element 0 of keyword vector is " `from ", then element 0 of return vector is vector of strings of
	all parameters for " `from " keyword.
	*************************************************************************************************************/
	std::vector<std::vector<std::string>> extractParamsForKeywords(std::string&, std::vector<std::string>);

	/*************************************************************************************************************
	Name: processTime
	Type: Protected Method
	Purpose: Processes input string to time_t format, requires start of day (START) or end of day (END) string
	specification, throws exception if input string violates any accepted input specifications.
	The detailed accepted input specifications are as follows:
	Date inputs that will be allowed:
	1. Date in day: "DD/MM/YY"
	2. Date in week:
	i. "week DD/MM/YY"
	ii. "DD/MM/YY week"
	3. Yesterday: "yesterday"
	4. Today:
	i. ""
	ii. "today"
	5. Tomorrow: "tomorrow"
	6. Next occurrence of a certain day:
	i. "<day>"
	ii. "this <day>"
	7. Next next occurrence of a certain day: "next <day>"
	8. Previous occurrence of a certain day: "last <day>"
	9. This week: "this week"
	10. Next week: "next week"
	11. Last week: "last week"

	Time inputs that will be allowed: HHMM
	**************************************************************************************************************/
	time_t processTime(std::string, bool, bool);


	/*************************************************************************************************************
	Name: prepareTaskDisplayAttributeBreakdown
	Type: Protected Method
	Purpose: Processes input task into task display string of the following format:
	Description: ...
	Start date/time: ...
	End date/time OR Deadline: ...
	Location: ...
	**************************************************************************************************************/
	std::string prepareTaskDisplayAttributeBreakdown(Task);

	/**************************************************************************************************************
	Name: prepareTaskDisplayOneLine
	Type: Protected Method
	Purpose: Processes input task into task display string of the following format:
	<task type> (<task index>): <start date-time> - <end date-time/deadline>: <description>; <location>
	eg.
	TO-DO (10): Buy flowers for Valentine’s day; Clementi MRT florist
	DEADLINE (15): Fri, 14 Feb 2014, 06:00PM: Order Lamborghini for wife; Lamborghini showroom
	SCHEDULE (20): Fri, 14 Feb 2014, 08:00PM - 10:00PM: Dinner with wife; Ritz Carlton hotel
	SCHEDULE (20): Sat, 15 Feb 2014, 08:00AM - Sun, 16 Feb 2014, 08:00PM: Fishing trip; Sentosa jetty
	***************************************************************************************************************/
	std::string prepareTaskDisplayOneLine(Task);

	/**************************************************************************************************************
	Name: getTaskType
	Type: Protected Method
	Purpose: Returns task type string with input task type code.
	***************************************************************************************************************/
	std::string getTaskType(std::string);

	/**************************************************************************************************************
	Name: processTimeToString
	Type: Protected Method
	Purpose: Processes input time_t into human-understandable date-time string of the following format:
	<day>, DD <month> YYYY, HH:MM<AM/PM>.
	***************************************************************************************************************/
	std::string processTimeTToString(time_t);

	/**************************************************************************************************************
	Name: checkStartEndTimeValidity
	Type: Protected Method
	Purpose: Checks if input start and end time_t are valid - end time must be later than start time -
	end time_t must be bigger than start time_t, returns true if valid and false if invalid.
	****************************************************************************************************************/
	bool checkStartEndTimeValidity(time_t, time_t);

	//@author A0092201X
	/****************************************************************************************************************
	Name: updateDisplayedTask
	Type: Protected Method
	Purpose: Updates private attributes static Manipulator* _displayedTMPtr and
	static std::vector<int> _displayedTasksIndexes.
	*****************************************************************************************************************/
	void updateDisplayedTask(Manipulator*, std::vector<int>);

	/****************************************************************************************************************
	Name: getDisplayedTask
	Type: Protected Method
	Purpose: Retrieves the vector<int> of task indexes that was stored previously in
	static std::vector<int> _displayedTasksIndexes.
	*****************************************************************************************************************/
	std::vector<int> getDisplayedTask(void);

	/****************************************************************************************************************
	Name: getDisplayedTMPtr
	Type: Protected Method
	Purpose: Retrieves the Manipulator pointer that is stored in
	static Manipulator* _displayedTMPt
	*****************************************************************************************************************/
	Manipulator* getDisplayedTMPtr(void);

	/****************************************************************************************************************
	Name: wrapText
	Type: Protected Method
	Arguements:(unsigned int) indent needed; (string) text that is not to be wrapped; (string) text to be wrapped
	Purpose: present text in a column that is indented
	Pre-conditions: the indent(first argument) cannot be larger than console width
	Post-conditions: a wrapped string will be returned
	******************************************************************************************************************/
	std::string wrapText(unsigned int, std::string, std::string);

	/****************************************************************************************************************
	Name: prepareHeader
	Type: Protected Method
	Purpose: format a string into a standard header
	Pre-conditions: the string cannot be larger than CONSOLE_WIDTH - 6
	Post-conditions: a formatted header string will be returned
	******************************************************************************************************************/
	std::string prepareHeader(std::string);

public:
	Command(Manipulator*, Manipulator*);
	~Command(void);
	virtual std::string executeInput(std::string);
	virtual std::string undo(void);
	virtual std::string redo(void);

private:
	//These attributes stores the last show or search results
	//_displayedTMPtr stores the file was last shown or searched (todo or done)
	static Manipulator* _displayedTMPtr;
	//_displayTaskIndexes stores the indexes that was last shown or searched
	static std::vector<int> _displayedTasksIndexes;

	//@author A0080917B
	/***************************************************************************************************************************
	Name: get<time type>Time
	Type: Methods
	Purpose: Support processTime method in generating time based on different time types, for increased
	abstraction.
	****************************************************************************************************************************/
	time_t getTodayTime(bool, int, int);
	time_t getYesterdayTime(bool, int, int);
	time_t getTomorrowTime(bool, int, int);
	time_t getDayTime(bool, int, int, int, int);
	time_t getWeekTime(int, int, int, int);
	time_t getDateTime(bool, int, int, int, int, int);

	/**************************************************************************************************************************
	Name: check<Date/Time>Validity
	Type: Methods
	Purpose: Support processTime method in checking validity of date/time based on valid date/time ranges
	***************************************************************************************************************************/
	bool checkDateValidity(int, int, int);
	bool checkTimeValidity(int, int);
};
