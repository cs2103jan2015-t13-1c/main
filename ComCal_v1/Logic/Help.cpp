#include "Help.h"

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
