#pragma once

/**********************************************************************************************************
Name: Show
Type: Class
Purpose: Responsible for executing the show command.
Formats the task display according to type parameters input by the user -
TYPE_SHOW_DEFAULT, TYPE_SHOW_DAY, TYPE_SHOW_WEEK, TYPE_SHOW_TODO,
TYPE_DONE_DEFAULT, TYPE_DONE_DAY, TYPE_DONE_WEEK
Post Conditions: Updates the static Manipulator* _displayedTMPtr and
static std::vector<int> _displayedTasksIndexes in command
with every valid show.
**********************************************************************************************************/

#include "Command.h"

//Today string:
const std::string TODAY = "today";

//Show type int codes:
static const int SHOWTYPE_DEFAULT = 1;
static const int SHOWTYPE_DAY = 2;
static const int SHOWTYPE_WEEK = 3;
static const int SHOWTYPE_TODO = 4;
static const int SHOWTYPE_DONE_DEFAULT = 5;
static const int SHOWTYPE_DONE_DAY = 6;
static const int SHOWTYPE_DONE_WEEK = 7;

//Show heading strings:
static const std::string HEADER_FLOATING = "TO-DOS";
static const std::string HEADER_DEADLINE = "DEADLINES";
static const std::string HEADER_TIMED = "EVENTS";
static const std::string HEADER_DONE = "DONE ";
static const std::string HEADER_FOR = " FOR ";
static const std::string HEADER_THEWEEK = "THE WEEK";
static const std::string HEADER_TOMMORROW = "TOMMORROW";

//Show footer strings:
static const std::string FOOTER_YOU_HAVE = "You have ";
static const std::string FOOTER_DEADLINES_AND = " deadlines and ";
static const std::string FOOTER_EVENTS_TML = " events tomorrow.";
static const std::string FOOTER_YOUR_EVENT_STARTS = "Your first event starts at ";

//No task to display message strings:
static const std::string NO_FLOATING_ALL = "\t\t\t-- No to-dos currently --";
static const std::string NO_DEADLINE_ALL = "\t\t\t-- No deadlines currently --";
static const std::string NO_DEADLINE_DAY = "\t\t\t-- No deadlines for the day --";
static const std::string NO_DEADLINE_WEEK = "\t\t\t-- No deadlines for the week --";
static const std::string NO_SCHEDULE_DAY = "\t\t\t-- No events for the day --";

//Task spans over a day message string:
static const std::string NOTIFICATION_SPANSOVERADAY = "  -- Spans Over A day --";

//Indentation positions for wrapText for each task type:
static const int POS_FLOATING_DEFAULT = 8;
static const int POS_DEADLINES_DAY = 17;
static const int POS_DEADLINES_DEFAULT = 31;
static const int POS_TIMED_DAY = 27;

class Show : public Command {
private:
	int _type;
	time_t _startDateTime;
	Manipulator* _TMUsed;
	std::vector<int> _taskIndexes;
	int _numFloating;
	int _numDeadlines;
	int _numSchedules;
	int _numDeadlinesTml;
	int _numSchedulesTml;

	/************************************************************************************************************
	Name: processInput
	Type: Method
	Purpose: Processes the input string and determines the type of display and date/time range of tasks requested.
	************************************************************************************************************/
	void processInput(std::string);

	/************************************************************************************************************
	Name: processVector
	Type: Method
	Purpose: Reposonsible for processing the vector of tasks to find the appropriate tasks that satisfies the
	type and date/time range of tasks requested
	************************************************************************************************************/
	std::string processVector(std::vector<Task>&);

	std::string prepareAllFloatingOutput(std::vector<Task>&);
	std::string formatFloatingOutput(Task);

	std::string prepareAllDeadlineOutput(std::vector<Task>&);
	std::string prepareRestrictedDeadlineOutput(std::vector<Task>);
	std::string prepareDeadlineDayOutput(std::vector<Task>, time_t);
	std::string prepareDeadlineWeekOutput(std::vector<Task>);
	std::string formatDeadlineOutput(Task);

	std::string prepareTimedOutput(std::vector<Task>&);
	std::string prepareTimedDayOutput(std::vector<Task>&, time_t);
	std::string prepareTimedWeekOutput(std::vector<Task>&);
	std::string formatTimedOutput(Task, time_t);

	std::string prepareTmlOutput(std::vector<Task>);

	void storeDisplayed(void);
	void removeDuplicatedTaskIndexes(void);

public:
	Show(Manipulator*, Manipulator*);
	~Show(void);

	/************************************************************************************************************
	Name:executeInput
	Type: Method
	Purpose: Executes input received, extracts tasks to be shown based on input string, and returns feedback string.
	************************************************************************************************************/
	std::string executeInput(std::string);
};
