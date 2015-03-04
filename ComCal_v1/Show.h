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
#include "TextManipulator.h"
#include "Exception.h"

#include <sstream>
#include <ctime>

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

