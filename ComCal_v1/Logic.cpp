#include "pch.h"
#include "Logic.h"

//Command strings:
const std::string COMMAND_ADD = "add";
const std::string COMMAND_SHOW = "show";
const std::string COMMAND_EDIT = "edit";
const std::string COMMAND_DELETE = "del";
const std::string COMMAND_EXIT = "exit";
const std::string COMMAND_DONE = "done";
const std::string COMMAND_UNDONE = "undone";
const std::string COMMAND_UNDO = "undo";
const std::string COMMAND_REDO = "redo";
const std::string COMMAND_SEARCH = "search";
const std::string COMMAND_HELP = "help";

//Thank you message string:
const std::string MESSAGE_THANKYOU = "Thank you for using TAC, do come back soon! Good bye!";

Logic::Logic(Manipulator* todoTMPtr, Manipulator* doneTMPtr) {
	_todoTMPtr = todoTMPtr;
	_doneTMPtr = doneTMPtr;
}

Logic::~Logic(void) {
}

bool Logic::executeCommand(std::string userInput, std::string& output){
	CommandType commandType;
	bool isTerminate = false;
	std::string errorString;

	commandType = extractCommand(userInput);

	Command* command;

	switch (commandType) {
	case ADD:
	{
		command = new Add(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		_commandHistory.push(command);
		break;
	}
	case SHOW:
	{
		command = new Show(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		break;
	}
	case EDIT:
	{
		command = new Edit(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		_commandHistory.push(command);
		break;
	}
	case DEL:
	{
		command = new Delete(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		_commandHistory.push(command);
		break;
	}
	case DONE:
	{
		command = new Done(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		_commandHistory.push(command);
		break;
	}
	case UNDONE:
	{
		command = new Undone(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		_commandHistory.push(command);
		break;
	}
	case UNDO:
	{
		if (userInput != "") {
			throw exceptionInputInvalidUndoParam;
		}
		if (_commandHistory.empty()) {
			throw exceptionInputInvalidUndo;
		}
		Command* undoCommand = _commandHistory.top();
		output = undoCommand->undo();
		_commandHistory.pop();
		_undoHistory.push(undoCommand);
		break;
	}
	case REDO:
	{
		if (userInput != "") {
			throw exceptionInputInvalidRedoParam;
		}
		if (_undoHistory.empty()) {
			throw exceptionInputInvalidRedo;
		}
		Command* redoCommand = _undoHistory.top();
		output = redoCommand->redo();
		_undoHistory.pop();
		_commandHistory.push(redoCommand);
		break;
	}
	case SEARCH:
	{
		command = new Search(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		break;
	}
	case HELP:
	{
		command = new Help(_todoTMPtr, _doneTMPtr);
		output = command->executeInput(userInput);
		break;
	}
	default:
		while (!_commandHistory.empty()) {
			delete _commandHistory.top();
			_commandHistory.pop();
		}
		while (!_undoHistory.empty()) {
			delete _undoHistory.top();
			_undoHistory.pop();
		}
		output = MESSAGE_THANKYOU;
		isTerminate = true;
	}

	return isTerminate;
}

CommandType Logic::extractCommand(std::string& userInput) {
	CommandType commandType;
	unsigned int lengthOfCommand;
	unsigned int lengthOfRemainingString;
	std::string commandString;
	std::string errorString = "";

	lengthOfCommand = getSpacePosition(userInput);

	commandString = userInput.substr(0, lengthOfCommand);

	for (unsigned int i = 0; i < commandString.size(); i++) {
		char c = commandString[i];
		commandString[i] = tolower(c);
	}

	if (commandString == COMMAND_ADD) {
		commandType = ADD;
	}
	else if (commandString == COMMAND_SHOW) {
		commandType = SHOW;
	}
	else if (commandString == COMMAND_EDIT) {
		commandType = EDIT;
	}
	else if (commandString == COMMAND_DELETE) {
		commandType = DEL;
	}
	else if (commandString == COMMAND_DONE) {
		commandType = DONE;
	}
	else if (commandString == COMMAND_UNDONE) {
		commandType = UNDONE;
	}
	else if (commandString == COMMAND_UNDO) {
		commandType = UNDO;
	}
	else if (commandString == COMMAND_REDO) {
		commandType = REDO;
	}
	else if (commandString == COMMAND_SEARCH) {
		commandType = SEARCH;
	}
	else if (commandString == COMMAND_HELP) {
		commandType = HELP;
	}
	else if (commandString == COMMAND_EXIT) {
		commandType = EXIT;
	}
	else {
		throw exceptionInputInvalidCommand;
	}


	if (userInput.size() > lengthOfCommand) {
		lengthOfRemainingString = userInput.size() - lengthOfCommand - 1;
		userInput = userInput.substr(lengthOfCommand + 1, lengthOfRemainingString);
	}
	else {
		userInput = "";
	}

	return commandType;
}

int Logic::getSpacePosition(std::string input) {
	unsigned int spacePosition = 0;
	char ch = input[spacePosition];

	while (ch != ' ') {
		spacePosition++;
		if (spacePosition >= input.size()) {
			return spacePosition;
		}
		ch = input[spacePosition];
	}

	return spacePosition;
}
