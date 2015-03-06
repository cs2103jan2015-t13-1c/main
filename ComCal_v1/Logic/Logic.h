#pragma once

/**********************************************************************************************************
Name: Logic
Type: Class
Purpose: Responsible for interpreting the commands that the user inputs. It will call the respective
functionality child class of Command to execute the command.
It will also store 2 stack<Command*>. 1 for _commandHistory and 1 for _undoHistory, which is required
for the implementation fo undo and redo
**********************************************************************************************************/

#include "Command.h"
#include "Add.h"
#include "Show.h"
#include "Edit.h"
#include "Delete.h"
#include "Done.h"
#include "Undone.h"
#include "Search.h"
#include "Help.h"

#include <stack>

//Thank you message string:
static const std::string MESSAGE_THANKYOU = "Thank you for using TAC, do come back soon! Good bye!";

enum CommandType {
	ADD,
	SHOW,
	EDIT,
	DEL,
	DONE,
	UNDONE,
	UNDO,
	REDO,
	SEARCH,
	HELP,
	EXIT
};

class Logic
{
private:
	/***************************************************************************************************
	Name: _commandHistory
	Type: Stack of Command pointers attribute
	Purpose: Holds history of executed commands(except show, search and help) since start of application.
	***************************************************************************************************/
	std::stack<Command*> _commandHistory;

	/****************************************************************************************************
	Name: _undoHistory
	Type: Stack of Command pointers attribute
	Purpose: Holds history of undo commands(except show, search and help) since start of application.
	***************************************************************************************************/
	std::stack<Command*> _undoHistory;

	/****************************************************************************************************
	Name: _todoTMPtr
	Type: Manipulator pointer attribute
	Purpose: Holds Manipulator pointer dedicated to manipulating todo task text file.
	***************************************************************************************************/
	Manipulator* _todoTMPtr;

	/****************************************************************************************************
	Name: _doneTMPtr
	Type: Manipulator pointer attribute
	Purpose: Holds Manipulator pointer dedicated to manipulating done task text file.
	***************************************************************************************************/
	Manipulator* _doneTMPtr;

	/****************************************************************************************************
	Name: extractCommand
	Type: Method
	Purpose: Extracts command and removes it and following ending space from input reference string, and returns
	enum CommandType.
	****************************************************************************************************/
	CommandType extractCommand(std::string&);

	/****************************************************************************************************
	Name: getSpacePosition
	Type: Method
	Purpose: Obtains first space position in input string, and returns it as int.
	****************************************************************************************************/
	int getSpacePosition(std::string);

public:
	Logic(Manipulator*, Manipulator*);
	~Logic(void);

	/****************************************************************************************************
	Name: executeCommand
	Type: Method
	Purpose: Executes command specified in first input string, assigns feedback string to second input
	reference string, and returns bool value of whether exit command is read, i.e. true when extractCommand
	returns exit CommandType, and false otherwise.
	****************************************************************************************************/
	bool executeCommand(std::string, std::string&);
};
