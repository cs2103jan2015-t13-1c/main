#pragma once

/**********************************************************************************************************
Name: Done
Type: Child Class
Purpose: Child class of Command parent class.
Responsible for marking a task in todo text file done -
by invalidating the task in todo text file,
and appending it into done text file.
**********************************************************************************************************/

class Done : public Command {
private:
	std::vector<int> _doneTaskIndexes;
	std::vector<Task> _doneTasks;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain specified task index(es) and pushes them into the _doneTaskIndexes int
	vector private attribute.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback using _doneTasks vector private attribute to reflect successful marking
	done of task(s).
	****************************************************************************************************/
	std::string prepareFeedback(void);

	/****************************************************************************************************
	Name: prepareUndoFeedback
	Type: Method
	Purpose: Prepares undo feedback using _doneTasks vector private attribute to reflect successful reverting
	of done task(s) to undone.
	****************************************************************************************************/
	std::string prepareUndoFeedback(void);

	//@author A0088797Y
public:
	Done(Manipulator*, Manipulator*);
	~Done(void);

	/****************************************************************************************************
	Name: executeInput
	Type: Method
	Purpose: Executes input received - marks tasks with specified task indexes in input string done by transferring
	them from todo to done task file, pushes done tasks into _doneTasks vector private attribute and returns
	feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);

	//@author A0080917B
	/****************************************************************************************************
	Name: undo
	Type: Method
	Purpose: Executes undo of this instance of done, and returns feedback string.
	****************************************************************************************************/
	std::string undo(void);

	/****************************************************************************************************
	Name: redo
	Type: Method
	Purpose: Executes redo of this instance of done, and returns feedback string.
	****************************************************************************************************/
	std::string redo(void);
};

