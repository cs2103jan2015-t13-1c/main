#pragma once

/**********************************************************************************************************
Name: Add
Type: Class
Purpose: Child class of Command parent class.
Responsible for executing create/add task into tasks database text file, when its executeInput API
is called by Logic class.
Its private attributes holds its parameter keywords and specified attributes of the task to be
created/added.
Private methods are functions used to support implementation of its API, for increased abstraction.
**********************************************************************************************************/

#include "Command.h"

class Add : public Command {
private:
	/****************************************************************************************************
	Name: _attributeKeywords
	Type: Vector of strings attribute
	Purpose: Holds recognised attribute keywords
	****************************************************************************************************/
	std::vector<std::string> _attributeKeywords;

	/****************************************************************************************************
	Name: _naturalKeywords
	Type: Method
	Purpose: Holds recognised natural keywords.
	****************************************************************************************************/
	std::vector<std::string> _naturalKeywords;
	std::string _description;
	time_t _startDateTime;
	time_t _endDateTime;
	std::string _location;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain specified task attributes and assigns them to the respective private
	attributes.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: processAttributesStyle
	Type: Method
	Purpose: Processes input string based on attribute keywords and assigns them to the respective private attributes.
	Returns bool value of whether input string has been processed - i.e. true if attribute keyword(s) is(are) found,
	false if no attribute keyword(s) is(are) found.
	****************************************************************************************************/
	bool processAttributesStyle(std::string);

	/****************************************************************************************************
	Name: processNaturalStyle
	Type: Method
	Purpose: Process input string based on natural keywords and assigns them to the respective private attributes.
	Called in process method if processAttributesStyle method returns false, i.e. input string is not attributes
	keyword based.
	****************************************************************************************************/
	void processNaturalStyle(std::string);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback with input added task to reflect successful addition of task and its task
	attributes.
	****************************************************************************************************/
	std::string prepareFeedback(Task);

	/****************************************************************************************************
	Name: prepareUndoFeedback
	Type: Method
	Purpose: Prepares undo feedback with deleted task to reflect successful deletion of task for undo of this
	instance of add.
	****************************************************************************************************/
	std::string prepareUndoFeedback(Task);

public:

	Add(Manipulator*, Manipulator*);
	~Add(void);

	/****************************************************************************************************
	Name:executeInput
	Type: Method
	Purpose: Executes input received - adds task with specified attributes in input string into todo task database,
	and returns feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);

	/****************************************************************************************************
	Name: undo
	Type: Method
	Purpose: Executes undo of this instance of add, and returns feedback string.
	****************************************************************************************************/
	std::string undo(void);

	/****************************************************************************************************
	Name: redo
	Type: Method
	Purpose: Executes redo of this instance of add, and returns feedback string.
	****************************************************************************************************/
	std::string redo(void);
};

