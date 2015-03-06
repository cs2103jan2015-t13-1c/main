#pragma once

/**********************************************************************************************************
Name: Delete
Type: Class
Purpose: Child class of Command parent class.
Responsible for executing delete task in tasks database text file, when its executeInput API
is called by Logic class.
Its private attribute holds the specified task index(es) to be deleted.
Private methods are functions used to support implementation of its API, for increased abstraction.
**********************************************************************************************************/

#include "Command.h"

class Delete : public Command {
private:
	std::vector<int> _deleteTaskIndexes;
	std::vector<Task> _deletedTasks;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain specified task index(es) and pushed them into _deletedTaskIndexes int
	vector private attribute.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback using _deletedTasks vector private attribute to reflect successful deletion of task(s).
	****************************************************************************************************/
	std::string prepareFeedback(void);

	/****************************************************************************************************
	Name: prepareUndoFeedback
	Type: Method
	Purpose: Prepares undo feedback using _deletedTasks vector private attribute to reflect successful addition
	of task(s).
	****************************************************************************************************/
	std::string prepareUndoFeedback(void);

public:
	Delete(Manipulator*, Manipulator*);
	~Delete(void);

	/****************************************************************************************************
	Name: executeInput
	Type: Method
	Purpose: Executes input received - deletes tasks with specified task indexes in input string, pushes deleted
	tasks into _deletedTasks vector private attribute and returns feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);

	/****************************************************************************************************
	Name: undo
	Type: Method
	Purpose: Executes undo of this instance of delete, and returns feedback string.
	****************************************************************************************************/
	std::string undo(void);

	/****************************************************************************************************
	Name: redo
	Type: Method
	Purpose: Executes redo of this instance of delete, and returns feedback string.
	****************************************************************************************************/
	std::string redo(void);
};
