#pragma once

/**********************************************************************************************************
Name: Edit
Type: Class
Purpose: Child class of Command parent class.
Responsible for executing update/edit task in tasks database text file, when its executeInput API
is called by Logic class.
Its private attributes holds its parameter keywords, the specified task index, attribute codes
and new content for each attribute to be updated/edited.
Private methods are functions used to support implementation of its API, for increased abstraction.
**********************************************************************************************************/

#include "Command.h"

#include <sstream>

class Edit : public Command {
private:
	/****************************************************************************************************
	Name: _attributeKeywords
	Type: Vector of strings attribute
	Purpose: Holds recognised attribute keywords
	****************************************************************************************************/
	std::vector<std::string> _attributeKeywords;
	int _editTaskIndex;

	std::vector<std::string> _editAttributes;
	std::vector<std::string> _editContents;
	std::string _originalTaskLine;
	std::string _editedTaskLine;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain specified task index, attribute codes and new content for each
	attribute and pushes them into the respective vector of strings private attributes.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: processOriginal<type>String
	Type: Method
	Purpose: Processes time_t received to get existing <type> string, and returns this string.
	****************************************************************************************************/
	std::string processOriginalHourString(time_t);
	std::string processOriginalMinString(time_t);
	std::string processOriginalYearString(time_t);
	std::string processOriginalMonthString(time_t);
	std::string processOriginalMdayString(time_t);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback with _editedTaskLine string private attribute to reflect successful update/edition
	of task.
	****************************************************************************************************/
	std::string prepareFeedback(Task, Task);

public:
	Edit(Manipulator*, Manipulator*);
	~Edit(void);

	/****************************************************************************************************
	Name:executeInput
	Type: Method
	Purpose: Executes input received - assigns original task line to _originalTaskLine string private attribute,
	edits attributes of task with specified task index with specified new content, assigns edited task line to
	_editedTaskLine, and returns feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);

	/****************************************************************************************************
	Name: undo
	Type: Method
	Purpose: Executes undo of this instance of edit, and returns feedback string.
	****************************************************************************************************/
	std::string undo(void);

	/****************************************************************************************************
	Name: redo
	Type: Method
	Purpose: Executes redo of this instance of edit, and returns feedback string.
	****************************************************************************************************/
	std::string redo(void);
};

