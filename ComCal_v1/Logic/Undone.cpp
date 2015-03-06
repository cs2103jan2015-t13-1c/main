#include "Undone.h"

Undone::Undone(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
}

Undone::~Undone(void){
}

void Undone::process(std::string userInput) {		//populate the vector of int with user inputs, eg. done 3, done 3, 4, 5
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

		int undoneTaskIndex;
		undoneTaskIndex = atoi(input.c_str());

		bool isValid = false;
		for (unsigned int i = 0; i < displayedTasksIndexes.size() && !isValid; i++) {
			if (undoneTaskIndex == displayedTasksIndexes[i]) {
				isValid = true;
			}
		}

		if (!isValid) {
			throw exceptionInputInvalidTaskIndexOutOfRange;
		}

		_undoneTaskIndexes.push_back(undoneTaskIndex);
	}

	return;
}

std::string Undone::prepareFeedback(void) {
	std::string feedback = "Marked the following undone:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _undoneTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_undoneTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Undone::executeInput(std::string inputString) {
	std::string feedbackString;
	std::vector<Task> contents;

	if (getDisplayedTMPtr() != _doneTMPtr) {
		throw exceptionInputInvalidUndoneDisplayedTasks;
	}

	process(inputString);

	contents = _doneTMPtr->read();

	for (unsigned int i = 0; i < _undoneTaskIndexes.size(); i++) {
		if (contents[_undoneTaskIndexes[i]].getCode() == TASKTYPECODE_INVALID) {
			throw exceptionInputTaskAlreadyRemoved;
		}

		_undoneTasks.push_back(contents[_undoneTaskIndexes[i]]);
		contents[_undoneTaskIndexes[i]].setInvalid();
	}

	_doneTMPtr->write(contents);

	for (unsigned int i = 0; i < _undoneTasks.size(); i++) {
		_todoTMPtr->append(_undoneTasks[i]);
	}

	feedbackString = prepareFeedback();

	return feedbackString;
}

//@author A0080917B
std::string Undone::prepareUndoFeedback(void) {
	std::string feedback = "Marked the following done:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _undoneTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_undoneTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Undone::undo(void) {
	std::string feedbackString;
	std::vector<Task> undoneTasks = _undoneTasks;
	std::vector<Task> todoContents;
	std::vector<Task> doneContents;

	todoContents = _todoTMPtr->read();
	doneContents = _doneTMPtr->read();

	for (unsigned int i = 0; i < undoneTasks.size(); i++) {
		bool isFoundDone = false;
		bool isFoundTodo = false;
		for (unsigned int j = 0; j < doneContents.size() && !isFoundDone; j++) {
			if (doneContents[j].getCode() == TASKTYPECODE_INVALID && doneContents[j].getDescription() == undoneTasks[i].getDescription() && doneContents[j].getStartDateTime() == undoneTasks[i].getStartDateTime() && doneContents[j].getEndDateTime() == undoneTasks[i].getEndDateTime() && doneContents[j].getLocation() == undoneTasks[i].getLocation()) {
				doneContents[j] = undoneTasks[i];
				isFoundDone = true;
			}
		}
		if (!isFoundDone) {
			doneContents.push_back(undoneTasks[i]);
		}

		for (unsigned int k = 0; k < todoContents.size() && !isFoundTodo; k++) {
			if (todoContents[k].getCode() != TASKTYPECODE_INVALID && todoContents[k].getDescription() == undoneTasks[i].getDescription() && todoContents[k].getStartDateTime() == undoneTasks[i].getStartDateTime() && todoContents[k].getEndDateTime() == undoneTasks[i].getEndDateTime() && todoContents[k].getLocation() == undoneTasks[i].getLocation()) {
				todoContents[k].setInvalid();
				isFoundTodo = true;
			}
		}
	}

	_todoTMPtr->write(todoContents);
	_doneTMPtr->write(doneContents);

	feedbackString = prepareUndoFeedback();

	return feedbackString;
}

std::string Undone::redo(void) {
	std::string feedbackString;
	std::vector<Task> undoneTasks = _undoneTasks;
	std::vector<Task> todoContents;
	std::vector<Task> doneContents;

	todoContents = _todoTMPtr->read();
	doneContents = _doneTMPtr->read();

	for (unsigned int i = 0; i < undoneTasks.size(); i++) {
		bool isFoundTodo = false;
		bool isFoundDone = false;
		for (unsigned int j = 0; j < todoContents.size() && !isFoundTodo; j++) {
			if (todoContents[j].getCode() == TASKTYPECODE_INVALID && todoContents[j].getDescription() == undoneTasks[i].getDescription() && todoContents[j].getStartDateTime() == undoneTasks[i].getStartDateTime() && todoContents[j].getEndDateTime() == undoneTasks[i].getEndDateTime() && todoContents[j].getLocation() == undoneTasks[i].getLocation()) {
				todoContents[j] = undoneTasks[i];
				isFoundTodo = true;
			}
		}
		if (!isFoundTodo) {
			todoContents.push_back(undoneTasks[i]);
		}

		for (unsigned int k = 0; k < doneContents.size() && !isFoundDone; k++) {
			if (doneContents[k].getCode() != TASKTYPECODE_INVALID && doneContents[k].getDescription() == undoneTasks[i].getDescription() && doneContents[k].getStartDateTime() == undoneTasks[i].getStartDateTime() && doneContents[k].getEndDateTime() == undoneTasks[i].getEndDateTime() && doneContents[k].getLocation() == undoneTasks[i].getLocation()) {
				doneContents[k].setInvalid();
				isFoundDone = true;
			}
		}
	}

	_todoTMPtr->write(todoContents);
	_doneTMPtr->write(doneContents);

	feedbackString = prepareFeedback();

	return feedbackString;
}
