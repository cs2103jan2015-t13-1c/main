#include "pch.h"
#include "Help.h"

//Command strings:
const std::string COMMAND_ADD = "add";
const std::string COMMAND_SHOW = "show";
const std::string COMMAND_EDIT = "edit";
const std::string COMMAND_DELETE = "del";
const std::string COMMAND_DONE = "done";
const std::string COMMAND_UNDONE = "undone";
const std::string COMMAND_SEARCH = "search";

Help::Help(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
}

Help::~Help(void) {
}

std::string Help::executeInput(std::string userInput) {
	std::string feedback;

	if (userInput == COMMAND_ADD) {
		feedback = INPUTHELP_ADD + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_SHOW) {
		feedback = INPUTHELP_SHOW + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_EDIT) {
		feedback = INPUTHELP_EDIT + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_DELETE) {
		feedback = INPUTHELP_DEL + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_DONE) {
		feedback = INPUTHELP_DONE + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_UNDONE) {
		feedback = INPUTHELP_UNDONE + LINESPACING_DOUBLE;
	}
	else if (userInput == COMMAND_SEARCH) {
		feedback = INPUTHELP_SEARCH + LINESPACING_DOUBLE;
	}
	else {
		throw exceptionInputInvalidHelpCommand;
	}

	return feedback;
}
