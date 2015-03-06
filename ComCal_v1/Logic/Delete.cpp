#include "Delete.h"

Delete::Delete(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
}


Delete::~Delete(void) {
}

void Delete::process(std::string userInput) {
	if (userInput == "") {
		throw exceptionInputMissingTaskIndex;
	}

	std::vector<int> displayedTasksIndexes;
	displayedTasksIndexes = getDisplayedTask();

	std::stringstream ss;
	ss << userInput;

	std::string input;
	while (ss >> input) {
		if (!(input.find_first_not_of(INTS_POSITIVE) == std::string::npos)) {
			throw exceptionInputInvalidTaskIndex;
		}

		int deleteTaskIndex;
		deleteTaskIndex = atoi(input.c_str());

		bool isValid = false;
		for (unsigned int i = 0; i < displayedTasksIndexes.size() && !isValid; i++) {
			if (deleteTaskIndex == displayedTasksIndexes[i]) {
				isValid = true;
			}
		}

		if (!isValid) {
			throw exceptionInputInvalidTaskIndexOutOfRange;
		}

		_deleteTaskIndexes.push_back(deleteTaskIndex);
	}

	return;
}

std::string Delete::prepareFeedback(void) {
	std::string feedback = "Deleted the following:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _deletedTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_deletedTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Delete::executeInput(std::string userInput) {
	std::string feedbackString;
	std::vector<Task> contents;

	process(userInput);

	contents = getDisplayedTMPtr()->read();

	for (unsigned int i = 0; i < _deleteTaskIndexes.size(); i++) {
		if (contents[_deleteTaskIndexes[i]].getCode() == TASKTYPECODE_INVALID) {
			throw exceptionInputTaskAlreadyRemoved;
		}
		_deletedTasks.push_back(contents[_deleteTaskIndexes[i]]);
		contents[_deleteTaskIndexes[i]].setInvalid();
	}

	getDisplayedTMPtr()->write(contents);

	feedbackString = prepareFeedback();

	return feedbackString;
}

//@author A0080917B
std::string Delete::prepareUndoFeedback(void) {
	std::string feedback = "Added the following:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _deletedTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_deletedTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Delete::undo(void) {
	std::string feedbackString;
	std::vector<Task> deletedTasks = _deletedTasks;
	std::vector<Task> contents;

	contents = getDisplayedTMPtr()->read();

	for (unsigned int i = 0; i < deletedTasks.size(); i++) {
		bool isFound = false;
		for (unsigned int j = 0; j < contents.size() && !isFound; j++) {
			if (contents[j].getCode() == TASKTYPECODE_INVALID && contents[j].getDescription() == deletedTasks[i].getDescription() && contents[j].getStartDateTime() == deletedTasks[i].getStartDateTime() && contents[j].getEndDateTime() == deletedTasks[i].getEndDateTime() && contents[j].getLocation() == deletedTasks[i].getLocation()) {
				contents[j] = deletedTasks[i];
				isFound = true;
			}
		}
		if (!isFound) {
			contents.push_back(deletedTasks[i]);
		}
	}

	getDisplayedTMPtr()->write(contents);

	feedbackString = prepareUndoFeedback();

	return feedbackString;
}

std::string Delete::redo(void) {
	std::string feedbackString;
	std::vector<Task> deletedTasks = _deletedTasks;
	std::vector<Task> contents;

	contents = getDisplayedTMPtr()->read();

	for (unsigned int i = 0; i < deletedTasks.size(); i++) {
		bool isFound = false;
		for (unsigned int j = 0; j < contents.size() && !isFound; j++) {
			if (contents[j].getCode() != TASKTYPECODE_INVALID && contents[j].getDescription() == deletedTasks[i].getDescription() && contents[j].getStartDateTime() == deletedTasks[i].getStartDateTime() && contents[j].getEndDateTime() == deletedTasks[i].getEndDateTime() && contents[j].getLocation() == deletedTasks[i].getLocation()) {
				contents[j].setInvalid();
				isFound = true;
			}
		}
	}

	getDisplayedTMPtr()->write(contents);

	feedbackString = prepareFeedback();

	return feedbackString;
}
