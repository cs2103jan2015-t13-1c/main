#pragma once

#include <string>
#include <exception>

//Help message header and line spacing strings:
const std::string HEADER_HELP = "\n ===============================  TAC.exe HELP  ===============================";
const std::string LINESPACING_SINGLE = "\n";
const std::string LINESPACING_DOUBLE = "\n\n";

//Help sheet strings:
const std::string TASKHELP_TYPEANDFORMAT = "[F]-Floating: Has description\nE.g: [F]\tThis is a floating task\t-\t-\t-\n\n[D]-Deadline: Has description and deadline(end date-time)\nE.g: [D]\tThis is a deadline task\t-\t31/04/14 2359\t-\n\n[P]-Partial-Timed: Has description and start date-time\nE.g: [P]\tThis is a partial-timed task\t31/04/14 1200\t-\t-\n\n[T]-Timed: Has description, start date-time and end date-time\nE.g: [T]\tThis is a timed task\t31/04/14 1200\t31/04/14 1300\t-\n\nLocation is optional in all.";
const std::string INPUTHELP_COMMAND = "******  Commands  ******\n1. add\t\t: To add a task\n2. edit\t\t: To edit a task\n3. del\t\t: To delete a task\n4. done\t\t: To mark a task as done\n5. undone\t: To revert a done task to undone\n6. undo\t\t: To undo last command entered.\n7. redo\t\t: To redo last undo action.\n8. search\t: To search for tasks based on attributes\n\nFor input help on each command, pls enter \"help <command>\" - e.g. \"help add\"\nshows input help for add command.";
const std::string INPUTHELP_TIME = "******  Time Input  ******\n\"HHMM\"\nE.g.:\t\"0830\" represents 8:30 AM\n\t\"1600\" represents 4:00 PM";
const std::string INPUTHELP_DATE = "******  Date Input  ******\n\"DD/MM/YY\"\nE.g.:\t\"31/04/14\" represents 31 April 2014\n\t\"01/05/14\" represents 1 May 2014";
const std::string INPUTHELP_DATETIMEADDEDIT = "******  Date/Day Inputs  ******\n1. \"DD/MM/YY\"\t: Specific date e.g. \"31/04/14\" represents 31 April 2014\n\n2. \"yesterday\"\t: Yesterday\n\n3. \"today\"\t: Today\n\n4. \"tomorrow\"\t: Tomorrow\n\n5. \"this <day>\"\t: This coming occurence of the specified day\nE.g. \"this Wednesday\" represents this coming Wednesday\n\n6. \"next <day>\"\t: Next occurrence of the specified day\nE.g. \"next Friday\" represents the Friday after this coming Friday\n\n7. \"last <day>\"\t: Previous occurrence of the specified day\nE.g. \"last Sunday\" represents the Sunday that just passed\n\n*******Time Input********\n\"HHMM\"\nE.g.:\t\"0830\" represents 8:30 AM\n\t\"1600\" represents 4:00 PM";
const std::string INPUTHELP_DATETIMESHOWSEARCH = "******  Date/Day Inputs  ******\n1. \"DD/MM/YY\"\t: Specific date e.g. \"31/04/14\" represents 31 April 2014\n\n2. \"yesterday\"\t: Yesterday\n\n3. \"today\"\t: Today\n\n4. \"tomorrow\"\t: Tomorrow\n\n5. \"this <day>\"\t: This coming occurence of the specified day\nE.g. \"this Wednesday\" represents this coming Wednesday\n\n6. \"next <day>\"\t: Next occurrence of the specified day\nE.g. \"next Friday\" represents the Friday after this coming Friday\n\n7. \"last <day>\"\t: Previous occurrence of the specified day\nE.g. \"last Sunday\" represents the Sunday that just passed\n\n8. \"week DD/MM/YY\" OR \"DD/MM/YY week\": Week of Monday to Sunday containing the\nspecified date\nE.g. \"week 31/04/14\" represents the week containing 31 April 2014\n\n9. \"this/next/last week\": This/Next/Last week of Monday to Sunday";
const std::string INPUTHELP_EDIT = "******  edit  ******\nA. To edit all attributes of a task, enter \"edit <task index>\n.d <new description> .s <new start date-time> .e <new end date/time>\n.l <new location>\"\nE.g.: edit 1 .d NewDescription .s 01/01/14 1000 .e 02/01/14 1100 .l NewLocation\n\nNote: You may edit a single or multiple attributes in any order and combination.\nB. To edit date/day but not time of a task, enter \"edit <task index>\n.s <new date/day>\"\nE.g.: edit 1 .s Sunday\n\nC. To edit time but not date/day of a task, enter \"edit <task index>\n.e <new time>\"\nE.g.: edit 1 .e 1230";
const std::string INPUTHELP_ADD = "******  add  ******\nA. To add a timed task, enter either format I) or II):\nI) For tasks that start and end on the same date, enter a) or b):\n\ta) \"add .d <task description> .s <start date/day> <start time>\n\t.e <end time> .l <location>\"\n\tE.g.: add .d SampleTask .s today 1000 .e 1100 .l school\n\n\tb) \"add <task description> on <start date/day> from <start time>\n\tto <end time> in <location>\"\n\tE.g.: add SampleTask on tomorrow from 1000 to 1100\n\tin school\n\nII) For tasks that start and end on different dates, enter a) or b):\n\ta) \"add .d <task description> .s <start date/day> <start time>\n\t.e <end date/day> <end time> .l <location>\"\n\tE.g.: add .d SampleTask .s Saturday 1000 .e Sunday 03/01/14 1000\n\t.l school\n\n\tb) \"add <task description> from <start date/Day> <start time>\n\tto <end date/day> <end time> in <location>\"\n\tE.g.: add SampleTask from next Friday 1000 to next Saturday 1000\n\tin school\n\nB. To add a partial timed task, enter a) or b):\n\ta) \"add .d <task description> .s <start date/day> <start time>\n\t.l <location>\"\n\tE.g.: add .d SampleTask .s 01/01/14 1000 .l school\n\n\t(b) \"add <task description> on <start date/day> <start time>\n\tin <location>\"\n\tE.g.: add SampleTask on 02/01/14 1000 in school\n\nC. To add a deadline task, enter a) or b):\n\ta) \"add .d <task description> .e <deadline date/day> <deadline time>\n\t.l <location>\"\n\tE.g.: add .d SampleTask .by 01/01/14 1000 .l school\n\n\tb) \"add <task description> by <deadline date/Day> <deadline time>\n\tin <location>\"\n\tE.g.: add SampleTask by 01/01/14 1000 in school\n\nD. To add a floating task, enter a) or b):\n\ta) \"add .d <task description> .l <location>\"\n\tE.g.: add .d SampleTask .l school\n\n\tb) \"add <task description> in <location>\"\n\tE.g.: add SampleTask in school\n\nNote: Location attribute is optional for all task types.";
const std::string INPUTHELP_SHOW = "******  show  ******\nA. To show calendar for today, enter either a) or b):\na) \"show\"\nb) \"show today\"\n\nB. To show calendar for a specific date/day, enter \"show <date/day>\"\nE.g.:\tshow 01/01/14\n\tshow tomorrow\n\tshow Friday\n\tshow next Sunday\n\nC. To show calendar for this week, enter either a) or b):\na) \"show week\"\nb) \"show this week\"\n\nD. To show calendar for a specific week, enter either a) or b):\na) \"show week <date>\"\nb) \"show <date> week\"\nE.g.:\tshow week 01/01/14\n\tshow next week\n\nE. To show to-do tasks, enter \"show todo\"\n\nF. To show all done tasks, enter \"show done\"\n\nG. To show done tasks on a specific date/day, enter \"show done <date/day>\"\nE.g.:\tshow done 01/01/14\n\tshow done yesterday\n\tshow done last Tuesday\n\nH. To show done tasks this week, enter \"show done this week\"\n\nI. To show done tasks on a specific week, enter either a) or b):\na) \"show done week <date>\"\nb) \"show done <date> week\"\nE.g.:\tshow done week 01/01/14\n\tshow done last week";
const std::string INPUTHELP_DEL = "******  del  ******\nA. To delete a task, enter \"del <task index>\"\nE.g.: del 1\n\nB. To delete multiple tasks, enter \"del <taskindex1 taskindex2 ...>\"\nE.g.: del 1 2";
const std::string INPUTHELP_DONE = "******  done  ******\nA. To mark a single task done, enter \"done <task index>\"\nE.g.: done 1\n\nB. To mark multiple tasks done, enter \"done <taskindex1 taskindex2 ...>\"\nE.g.: done 1 2";
const std::string INPUTHELP_UNDONE = "******  undone  ******\nA. To mark a single done task undone, enter \"undone <task index>\"\nE.g.: undone 1\n\nB. To mark multiple done tasks undone, enter \"undone <taskindex1 taskindex2>\"\nE.g.: undone 1 2";
const std::string INPUTHELP_SEARCH = "******  search  ******\nSearch has the following 4 elements:\n1. Task file to search from - \"todo\" or \"done\" - if not specified, this is\ndefaulted as \"todo\"\n\n2) Search attributes:\nI) \" .d \": Description\nII) \" .s \": Start date range - e.g.: \"today\", \"next week\", \"next Monday to next Friday\"\nIII) \" .e \": End date range - e.g.: \"tomorrow\", \"next week\", \"01/01/14\nto 04/01/14\"\n\nIV) \" .l \": Location\n\n3. Search conditions:\nI) AND: Both search statements must be satisfied,\n\ta) AND with different attribute e.g.: \" and.d \"\n\tb) AND with same attribute e.g.: \" and \"\nII) OR: Either search statement must be satisfied,\n\ta) OR with different attribute e.g.: \" or.s \"\n\tb) OR with same attribute e.g.: \" or \"\nIII) EXCLUDE: Tasks satisfying the following search statement are excluded from the search results,\n\ta) EXCLUDE with different attribute e.g.: \" --.e \"\n\tb) EXCLUDE with same attribute e.g.: \" -- \"\n\n4. Nesting search statements: You may nest search statements by adding curly\nbraces - \"{\" and \"}\" around them.\n\nOverall search statement - \"search <task file> <statements and conditions>\"\nE.g.: \"search todo { .d lunch and .l NUS} or { .d dinner and mum}\" - searches in\ntodo task file for all lunch appointments in NUS, and all dinner appointments\nwith mum.\n\nNote:\t- Search statements and conditions are executed from left to right.\n\t- Only one nesting level is permitted.";
const std::string INPUTHELP_ATTRIBUTEKEYWORDS = "******  Attribute keywords  ******\n1. \" .d \": Description\n2. \" .s \": Start date-time\n3. \" .e \": End date-time\n4. \" .l \": Location";
const std::string INPUTHELP_NATURALKEYWORDS = "******  Natural keywords  ******\nA. To add a timed task, enter either format I) or II):\nI)For tasks that start and end on the same date, enter \"add <task description> on <start date/day> from <start time> to <end time> in <location>\"\nE.g.: add SampleTask on 02/01/14 from 1000 to 1100 in school\n\nII) For tasks that start and end on different dates, enter \"add <task description> from <start date/Day> <start time> to <end date/day> <end time> in <location>\"\nE.g.: add SampleTask from 02/01/14 1000 to 03/01/14 1000 in school\n\nB. To add a partial timed task, enter \"add <task description> on <start date/day> <start time> in <location>\"\nE.g.: add SampleTask on 02/01/14 1000 in school\n\nC. To add a deadline task, enter \"add <task description> by <deadline date/Day> <deadline time> in <location>\"\nE.g.: add SampleTask by 01/01/14 1000 in school\n\nD. To add a floating task, enter \"add <task description> in <location>\"\nE.g.: add SampleTask in school\n\nNote: Location attribute is optional for all task types.";
const std::string INPUTHELP_HELP = "******  help  ******\n1. add command help list: \"help add\"\n2. show command help list: \"help show\"\n3. edit command help list: \"help edit\"\n4. del command help list: \"help del\"\n5. done command help list: \"help done\"\n6. undone command help list: \"help undone\"\n7. show command help list: \"help search\"";

//Prestart check error message strings:
const std::string TASKERROR_INVALIDSTRINGFORMAT = "TASK ERROR: Invalid String format - each attribute should be tab-separated.";
const std::string TASKERROR_INVALIDTYPECODE = "TASK ERROR: Invalid type code - unrecognised - recognised type codes are:\n" + TASKHELP_TYPEANDFORMAT;
const std::string TASKERROR_INCORRECTEMPTYATTRIBUTESYMBOL = "TASK ERROR: Incorrect empty attribute symbol - should be '-'.";
const std::string TASKERROR_NODESCRIPTION = "TASK ERROR: No description.";
const std::string TASKERROR_INVALIDDATETIME = "TASK ERROR: Invalid date-time format - should be 'DD/MM/YY HHMM'.";
const std::string TASKERROR_INVALIDDATE = "TASK ERROR: Invalid date format - should be 'DD/MM/YY'.";
const std::string TASKERROR_INVALIDTIME = "TASK ERROR: Invalid time format - should be 'HHMM'.";
const std::string TASKERROR_INCORRECTTYPECODE = "TASK ERROR: Incorrect type code - is not in line with its attributes:\n" + TASKHELP_TYPEANDFORMAT;
const std::string TASKERROR_MDAYOUTOFRANGELEAPFEB = "TASK ERROR: Day of month is out of range - leap year Feb only has 29 days.";
const std::string TASKERROR_MDAYOUTOFRANGENONLEAPFEB = "TASK ERROR: Day of month is out of range - non-leap year Feb only has 28 days.";
const std::string TASKERROR_MDAYOUTOFRANGE30DAYMONTH = "TASK ERROR: Day of month is out of range - specified month only has 30 days.";
const std::string TASKERROR_MDAYOUTOFRANGE31DAYMONTH = "TASK ERROR: Day of month is out of range - specified month only has 31 days.";
const std::string TASKERROR_MONTHOUTOFRANGE = "TASK ERROR: Month is out of range - max is 12.";
const std::string TASKERROR_HOUROUTOFRANGE = "TASK ERROR: Hour is out of range - max is 23.";
const std::string TASKERROR_MINOUTOFRANGE = "TASK ERROR: Min is out of range - max is 59.";

//Input error message strings:
const std::string INPUTERROR_NOCOMMAND = "INPUT ERROR: No command entered - pls enter one of the following valid commands:\n" + INPUTHELP_COMMAND;
const std::string INPUTERROR_INVALIDCOMMAND = "INPUT ERROR: Invalid command - pls enter one of the following valid commands:\n" + INPUTHELP_COMMAND;
const std::string INPUTERROR_INVALIDTIME = "INPUT ERROR: Invalid time format - pls enter the following valid time format:\n" + INPUTHELP_TIME;
const std::string INPUTERROR_INVALIDDATE = "INPUT ERROR: Invalid date format - pls enter the following valid date format:\n" + INPUTHELP_DATE;
const std::string INPUTERROR_INVALIDDATETIMEADDEDIT = "INPUT ERROR: Invalid date-time format - pls enter one of the following valid date-time formats:\n" + INPUTHELP_DATETIMEADDEDIT;
const std::string INPUTERROR_INVALIDDATETIMESHOWSEARCH = "INPUT ERROR: Invalid date-time format - pls enter one of the following valid date-time formats:\n" + INPUTHELP_DATETIMESHOWSEARCH;
const std::string INPUTERROR_INVALIDTIMESHOWSEARCH = "INPUT ERROR: Invalid date-time format - show and search commands do not require/permit time input.\n" + INPUTHELP_DATETIMESHOWSEARCH;
const std::string INPUTERROR_MDAYOUTOFRANGELEAPFEB = "INPUT ERROR: Day of month is out of range - leap year Feb only has 29 days.";
const std::string INPUTERROR_MDAYOUTOFRANGENONLEAPFEB = "INPUT ERROR: Day of month is out of range - non-leap year Feb only has 28 days.";
const std::string INPUTERROR_MDAYOUTOFRANGE30DAYMONTH = "INPUT ERROR: Day of month is out of range - specified month only has 30 days.";
const std::string INPUTERROR_MDAYOUTOFRANGE31DAYMONTH = "INPUT ERROR: Day of month is out of range - specified month only has 31 days.";
const std::string INPUTERROR_MONTHOUTOFRANGE = "INPUT ERROR: Month is out of range - max is 12.";
const std::string INPUTERROR_HOUROUTOFRANGE = "INPUT ERROR: Hour is out of range - max is 23.";
const std::string INPUTERROR_MINOUTOFRANGE = "INPUT ERROR: Min is out of range - max is 59.";
const std::string INPUTERROR_MISSINGADDPARAMS = "INPUT ERROR: Missing parameters following add command - pls see below for input help:\n" + INPUTHELP_ADD;
const std::string INPUTERROR_MISSINGEDITTASKINDEXANDPARAMS = "INPUT ERROR: Missing task index number, attribute keyword(s) and parameters - pls see below for input help:\n" + INPUTHELP_EDIT;
const std::string INPUTERROR_MISSINGEDITPARAMS = "INPUT ERROR: Missing attribute keyword(s) and parameters(s) - pls see below for input help:\n" + INPUTHELP_EDIT;
const std::string INPUTERROR_REPEATATTRIBUTEKEYWORDS = "INPUT ERROR: Repeat attribute keywords entered - pls enter each attribute keyword not more than once.";
const std::string INPUTERROR_REPEATNATURALKEYWORDS = "INPUT ERROR: Repeat natural keywords entered - pls enter each natural keyword not more than once.";
const std::string INPUTERROR_MISSINGATTRIBUTEPARAM = "INPUT ERROR: Missing parameter following attribute keyword - pls enter parameter after attribute keyword.\n" + INPUTHELP_ATTRIBUTEKEYWORDS;
const std::string INPUTERROR_MISSINGNATURALPARAM = "INPUT ERROR: Missing parameter following natural keyword - pls enter parameter after natural keyword.\n" + INPUTHELP_NATURALKEYWORDS;
const std::string INPUTERROR_INVALIDNATURALKEYWORDSCOMBINATION = "INPUT ERROR: Invalid natural keywords combination - pls see below for valid combinations:\n" + INPUTHELP_NATURALKEYWORDS;
const std::string INPUTERROR_MISSINGDESCRIPTION = "INPUT ERROR: Missing description - pls enter a description for the task.";
const std::string INPUTERROR_MISSINGATTRIBUTEKEYWORD = "INPUT ERROR: Missing attribute keyword - pls see below for input help:\n" + INPUTHELP_ATTRIBUTEKEYWORDS;
const std::string INPUTERROR_STARTLATERTHANENDTIME = "INPUT ERROR: Start time is later than end time - pls correct start time or end time such that end time is later than start time.";
const std::string INPUTERROR_MISSINGSTARTTIME = "INPUT ERROR: Missing start time - pls specify a start time.\n" + INPUTHELP_NATURALKEYWORDS;
const std::string INPUTERROR_MISSINGENDTIME = "INPUT ERROR: Missing end time - pls specify an end time.\n" + INPUTHELP_NATURALKEYWORDS;
const std::string INPUTERROR_MISSINGTASKINDEX = "INPUT ERROR: Missing task index(es) - pls enter number index(es) of desired task(s) from above task display. If there are no tasks displayed above, pls display tasks by entering show command.\n" + INPUTHELP_SHOW;
const std::string INPUTERROR_INVALIDTASKINDEX = "INPUT ERROR: Invalid task index format - pls enter number index of desired task from above task display. If there are no tasks displayed above, pls display tasks by entering show command.\n" + INPUTHELP_SHOW;
const std::string INPUTERROR_INVALIDTASKINDEXOUTOFRANGE = "INPUT ERROR: Invalid task index - out of range - pls enter number index of desired task from above task display. If there are no tasks displayed above, pls display tasks by entering show command.\n" + INPUTHELP_SHOW;
const std::string INPUTERROR_TASKALREADYREMOVED = "INPUT ERROR: Specified task already removed.";
const std::string INPUTERROR_INVALIDATTRIBUTEKEYWORD = "INPUT ERROR: Invalid attribute keyword - pls see below for valid keywords:\n" + INPUTHELP_ATTRIBUTEKEYWORDS;
const std::string INPUTERROR_INVALIDEDITREMOVEDESCRIPTION = "INPUT ERROR: Cannot remove description - every task requires a description.";
const std::string INPUTERROR_NOEXISTINGDATE = "INPUT ERROR: No existing date - pls specify a date/day along with the time.";
const std::string INPUTERROR_IDENTICALTASKPRESENT = "INPUT ERROR: Identical task already present in task list.";
const std::string INPUTERROR_INVALIDDONE = "INPUT ERROR: Invalid done - can only done TO-DO or DEADLINE.";
const std::string INPUTERROR_INVALIDDONEDISPLAYEDTASKS = "INPUT ERROR: Invalid done - above displayed are done tasks - pls view todo tasks to select desired task(s) to mark done.\n" + INPUTHELP_SHOW;
const std::string INPUTERROR_INVALIDUNDONEDISPLAYEDTASKS = "INPUT ERROR: Invalid undone - above displayed are todo tasks - pls view done tasks to select desired task(s) to mark undone.\n" + INPUTHELP_SHOW;
const std::string INPUTERROR_INVALIDUNDO = "INPUT ERROR: No further previous actions to undo.";
const std::string INPUTERROR_INVALIDREDO = "INPUT ERROR: No further previous undo actions to redo.";
const std::string INPUTERROR_INVALIDUNDOPARAM = "INPUT ERROR: Undo command should not be followed by any parameters.";
const std::string INPUTERROR_INVALIDREDOPARAM = "INPUT ERROR: Redo command should not be followed by any parameters.";
const std::string INPUTERROR_INVALIDHELPCOMMAND = "INPUT ERROR: Invalid help command. Pls see below for valid help commands:\n" + INPUTHELP_HELP;
const std::string INPUTERROR_INVALIDSHOWDONE = "INPUT ERROR: 'done' should immediately follow show command";
const std::string INPUTERROR_INVALIDSEARCHPARENTHESESMATCHING = "INPUT ERROR: Invalid parentheses matching - pls check input parentheses conditions.";
const std::string INPUTERROR_SEARCHEXCESSNESTCONDITIONS = "INPUT ERROR: Excess nest conditions.";
const std::string INPUTERROR_SEARCHMISSINGNESTCONDITION = "INPUT ERROR: Missing nest condition.";
const std::string INPUTERROR_REPEATTIMERANGEKEYWORDS = "INPUT ERROR: Repeat time range keywords entered - pls enter time range keyword not more than once.";
const std::string INPUTERROR_SEARCHEXCEEDPERMITTEDNESTING = "INPUT ERROR: Search parameters exceed permitted nesting level - sorry, TAC.exe only handles not more than one nesting level.\n";
const std::string INPUTERROR_MISSINGSEARCHPARAMS = "INPUT ERROR: Missing search parameters - pls see below for input help:\n" + INPUTHELP_SEARCH;

class ExceptionTaskInvalidStringFormat : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INVALIDSTRINGFORMAT.c_str();
	}
} static exceptionTaskInvalidStringFormat;

class ExceptionTaskInvalidTypeCode : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INVALIDTYPECODE.c_str();
	}
} static exceptionTaskInvalidTypeCode;

class ExceptionTaskIncorrectEmptyAttributeSymbol : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INCORRECTEMPTYATTRIBUTESYMBOL.c_str();
	}
} static exceptionTaskIncorrectEmptyAttributeSymbol;

class ExceptionTaskNoDescription : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_NODESCRIPTION.c_str();
	}
} static exceptionTaskNoDescription;

class ExceptionTaskInvalidDateTime : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INVALIDDATETIME.c_str();
	}
} static exceptionTaskInvalidDateTime;

class ExceptionTaskInvalidDate : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INVALIDDATE.c_str();
	}
} static exceptionTaskInvalidDate;

class ExceptionTaskInvalidTime : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INVALIDTIME.c_str();
	}
} static exceptionTaskInvalidTime;

class ExceptionTaskIncorrectTaskTypeCode : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_INCORRECTTYPECODE.c_str();
	}
} static exceptionTaskIncorrectTaskTypeCode;

class ExceptionTaskMdayOutOfRangeLeapFeb : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MDAYOUTOFRANGELEAPFEB.c_str();
	}
} static exceptionTaskMdayOutOfRangeLeapFeb;

class ExceptionTaskMdayOutOfRangeNonLeapFeb : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MDAYOUTOFRANGENONLEAPFEB.c_str();
	}
} static exceptionTaskMdayOutOfRangeNonLeapFeb;

class ExceptionTaskMdayOutOfRange30DayMonth : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MDAYOUTOFRANGE30DAYMONTH.c_str();
	}
} static exceptionTaskMdayOutOfRange30DayMonth;

class ExceptionTaskMdayOutOfRange31DayMonth : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MDAYOUTOFRANGE31DAYMONTH.c_str();
	}
} static exceptionTaskMdayOutOfRange31DayMonth;

class ExceptionTaskMonthOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MONTHOUTOFRANGE.c_str();
	}
} static exceptionTaskMonthOutOfRange;

class ExceptionTaskHourOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_HOUROUTOFRANGE.c_str();
	}
} static exceptionTaskHourOutOfRange;

class ExceptionTaskMinOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return TASKERROR_MINOUTOFRANGE.c_str();
	}
} static exceptionTaskMinOutOfRange;

class ExceptionInputNoCommand : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_NOCOMMAND.c_str();
	}
} static exceptionInputNoCommand;

class ExceptionInputInvalidCommand : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDCOMMAND.c_str();
	}
} static exceptionInputInvalidCommand;

class ExceptionInputInvalidTime : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDTIME.c_str();
	}
} static exceptionInputInvalidTime;

class ExceptionInputInvalidDate : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDDATE.c_str();
	}
} static exceptionInputInvalidDate;

class ExceptionInputInvalidDateTimeAddEdit : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDDATETIMEADDEDIT.c_str();
	}
} static exceptionInputInvalidDateTimeAddEdit;

class ExceptionInputInvalidDateTimeShowSearch : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDDATETIMESHOWSEARCH.c_str();
	}
} static exceptionInputInvalidDateTimeShowSearch;

class ExceptionInputInvalidTimeShowSearch : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDTIMESHOWSEARCH.c_str();
	}
} static exceptionInputInvalidTimeShowSearch;

class ExceptionInputMdayOutOfRangeLeapFeb : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MDAYOUTOFRANGELEAPFEB.c_str();
	}
} static exceptionInputMdayOutOfRangeLeapFeb;

class ExceptionInputMdayOutOfRangeNonLeapFeb : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MDAYOUTOFRANGENONLEAPFEB.c_str();
	}
} static exceptionInputMdayOutOfRangeNonLeapFeb;

class ExceptionInputMdayOutOfRange30DayMonth : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MDAYOUTOFRANGE30DAYMONTH.c_str();
	}
} static exceptionInputMdayOutOfRange30DayMonth;

class ExceptionInputMdayOutOfRange31DayMonth : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MDAYOUTOFRANGE31DAYMONTH.c_str();
	}
} static exceptionInputMdayOutOfRange31DayMonth;

class ExceptionInputMonthOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MONTHOUTOFRANGE.c_str();
	}
} static exceptionInputMonthOutOfRange;

class ExceptionInputHourOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_HOUROUTOFRANGE.c_str();
	}
} static exceptionInputHourOutOfRange;

class ExceptionInputMinOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MINOUTOFRANGE.c_str();
	}
} static exceptionInputMinOutOfRange;

class ExceptionInputMissingAddParams : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGADDPARAMS.c_str();
	}
} static exceptionInputMissingAddParams;

class ExceptionInputMissingEditTaskIndexAndParams : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGEDITTASKINDEXANDPARAMS.c_str();
	}
} static exceptionInputMissingEditTaskIndexAndParams;

class ExceptionInputMissingEditParams : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGEDITPARAMS.c_str();
	}
} static exceptionInputMissingEditParams;

class ExceptionInputRepeatAttributeKeywords : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_REPEATATTRIBUTEKEYWORDS.c_str();
	}
} static exceptionInputRepeatAttributeKeywords;

class ExceptionInputRepeatNaturalKeywords : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_REPEATNATURALKEYWORDS.c_str();
	}
} static exceptionInputRepeatNaturalKeywords;

class ExceptionInputMissingAttributeParam : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGATTRIBUTEPARAM.c_str();
	}
} static exceptionInputMissingAttributeParam;

class ExceptionInputMissingNaturalParam : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGNATURALPARAM.c_str();
	}
} static exceptionInputMissingNaturalParam;

class ExceptionInputInvalidNaturalKeywordsCombination : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDNATURALKEYWORDSCOMBINATION.c_str();
	}
} static exceptionInputInvalidNaturalKeywordsCombination;

class ExceptionInputMissingDescription : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGDESCRIPTION.c_str();
	}
} static exceptionInputMissingDescription;

class ExceptionInputMissingAttributeKeyword : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGATTRIBUTEKEYWORD.c_str();
	}
} static exceptionInputMissingAttributeKeyword;

class ExceptionInputStartLaterThanEndTime : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_STARTLATERTHANENDTIME.c_str();
	}
} static exceptionInputStartLaterThanEndTime;

class ExceptionInputMissingStartTime : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGSTARTTIME.c_str();
	}
} static exceptionInputMissingStartTime;

class ExceptionInputMissingEndTime : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGENDTIME.c_str();
	}
} static exceptionInputMissingEndTime;

class ExceptionInputMissingTaskIndex : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGTASKINDEX.c_str();
	}
} static exceptionInputMissingTaskIndex;

class ExceptionInputInvalidTaskIndex : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDTASKINDEX.c_str();
	}
} static exceptionInputInvalidTaskIndex;

class ExceptionInputInvalidTaskIndexOutOfRange : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDTASKINDEXOUTOFRANGE.c_str();
	}
} static exceptionInputInvalidTaskIndexOutOfRange;

class ExceptionInputTaskAlreadyRemoved : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_TASKALREADYREMOVED.c_str();
	}
} static exceptionInputTaskAlreadyRemoved;

class ExceptionInputInvalidAttributeKeyword : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDATTRIBUTEKEYWORD.c_str();
	}
} static exceptionInputInvalidAttributeKeyword;

class ExceptionInputInvalidEditRemoveDescription : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDEDITREMOVEDESCRIPTION.c_str();
	}
} static exceptionInputInvalidEditRemoveDescription;

class ExceptionInputNoExistingDate : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_NOEXISTINGDATE.c_str();
	}
} static exceptionInputNoExistingDate;

class ExceptionInputIdenticalTaskPresent : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_IDENTICALTASKPRESENT.c_str();
	}
} static exceptionInputIdenticalTaskPresent;

class ExceptionInputInvalidDone : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDDONE.c_str();
	}
} static exceptionInputInvalidDone;

class ExceptionInputInvalidDoneDisplayedTasks : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDDONEDISPLAYEDTASKS.c_str();
	}
} static exceptionInputInvalidDoneDisplayedTasks;

class ExceptionInputInvalidUndoneDisplayedTasks : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDUNDONEDISPLAYEDTASKS.c_str();
	}
} static exceptionInputInvalidUndoneDisplayedTasks;

class ExceptionInputInvalidUndo : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDUNDO.c_str();
	}
} static exceptionInputInvalidUndo;

class ExceptionInputInvalidRedo : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDREDO.c_str();
	}
} static exceptionInputInvalidRedo;

class ExceptionInputInvalidUndoParam : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDUNDOPARAM.c_str();
	}
} static exceptionInputInvalidUndoParam;

class ExceptionInputInvalidRedoParam : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDREDOPARAM.c_str();
	}
} static exceptionInputInvalidRedoParam;

class ExceptionInputInvalidHelpCommand : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDHELPCOMMAND.c_str();
	}
} static exceptionInputInvalidHelpCommand;

class ExceptionInputInvalidShowDone : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDSHOWDONE.c_str();
	}
} static exceptionInputInvalidShowDone;

class ExceptionInputInvalidSearchParenthesesMatching : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_INVALIDSEARCHPARENTHESESMATCHING.c_str();
	}
} static exceptionInputInvalidSearchParenthesesMatching;

class ExceptionInputSearchExcessNestConditions : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_SEARCHEXCESSNESTCONDITIONS.c_str();
	}
} static exceptionInputSearchExcessNestConditions;

class ExceptionInputSearchMissingNestCondition : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_SEARCHMISSINGNESTCONDITION.c_str();
	}
} static exceptionInputSearchMissingNestCondition;

class ExceptionInputRepeatTimeRangeKeywords : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_REPEATTIMERANGEKEYWORDS.c_str();
	}
} static exceptionInputRepeatTimeRangeKeywords;

class ExceptionInputSearchExceedPermittedNesting : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_SEARCHEXCEEDPERMITTEDNESTING.c_str();
	}
} static exceptionInputSearchExceedPermittedNesting;

class ExceptionInputMissingSearchParams : public std::exception {
	const char* what() const throw()
	{
		return INPUTERROR_MISSINGSEARCHPARAMS.c_str();
	}
} static exceptionInputMissingSearchParams;
