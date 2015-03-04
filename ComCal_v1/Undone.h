#pragma once

/**********************************************************************************************************
Name: Undone
Type: Class
Purpose: Child class of Command parent class.
Responsible for marking a done task in done text file undone -
by invalidating the task in done text file,
and appending it into todo text file.
**********************************************************************************************************/

#include "Command.h"

class Undone : public Command {
private:
	std::vector<int> _undoneTaskIndexes;
	std::vector<Task> _undoneTasks;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain specified task index(es) and pushes them into the _undoneTaskIndexes
	int vector private attribute.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback using _undoneTasks vector private attribute to reflect successful reverting of
	done task(s) to undone.
	****************************************************************************************************/
	std::string prepareFeedback(void);

	/****************************************************************************************************
	Name: prepareUndoFeedback
	Type: Method
	Purpose: Prepares undo feedback using _undoneTasks vector private attribute to reflect successful marking
	done of task(s).
	****************************************************************************************************/
	std::string prepareUndoFeedback(void);

public:
	Undone(Manipulator*, Manipulator*);
	~Undone(void);

	/****************************************************************************************************
	Name: executeInput
	Type: Method
	Purpose: Executes input received - reverts tasks with specified task indexes in input string to undone
	by transferring them from done to todo task file, pushes undone tasks into _undoneTasks vector private
	attribute and returns feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);

	/****************************************************************************************************
	Name: undo
	Type: Method
	Purpose: Executes undo of this instance of undone, and returns feedback string.
	****************************************************************************************************/
	std::string undo(void);

	/****************************************************************************************************
	Name: redo
	Type: Method
	Purpose: Executes redo of this instance of undone, and returns feedback string.
	****************************************************************************************************/
	std::string redo(void);
};

