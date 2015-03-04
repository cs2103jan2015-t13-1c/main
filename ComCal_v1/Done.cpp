#include "pch.h"
#include "Done.h"

Done::Done(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
}

Done::~Done(void){
}

void Done::process(std::string userInput) {		//populate the vector of int with user inputs, eg. done 3, done 3, 4, 5
	if (userInput == "") {
		throw exceptionInputMissingTaskIndex;
	}

	std::vector<int> displayedTasksIndexes;
	displayedTasksIndexes = getDisplayedTask();

	std::stringstream ss;
	ss << userInput;

	std::string input;
	while (ss >> input) {
		if (!(input.find_first_not_of(INTS) == std::string::npos)) {
			throw exceptionInputInvalidTaskIndex;
		}

		int doneTaskIndex;
		doneTaskIndex = atoi(input.c_str());

		bool isValid = false;
		for (unsigned int i = 0; i < displayedTasksIndexes.size() && !isValid; i++) {
			if (doneTaskIndex == displayedTasksIndexes[i]) {
				isValid = true;
			}
		}

		if (!isValid) {
			throw exceptionInputInvalidTaskIndexOutOfRange;
		}

		_doneTaskIndexes.push_back(doneTaskIndex);
	}

	return;
}

std::string Done::prepareFeedback(void) {
	std::string feedback = "Marked the following done:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _doneTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_doneTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Done::executeInput(std::string inputString) {
	std::string feedbackString;
	std::vector<Task> contents;

	if (getDisplayedTMPtr() != _todoTMPtr) {
		throw exceptionInputInvalidDoneDisplayedTasks;
	}

	process(inputString);

	contents = _todoTMPtr->read();

	for (unsigned int i = 0; i < _doneTaskIndexes.size(); i++) {
		if (contents[_doneTaskIndexes[i]].getCode() == CODE_INVALID) {
			throw exceptionInputTaskAlreadyRemoved;
		}

		if (contents[_doneTaskIndexes[i]].getCode() == CODE_FLOATING || contents[_doneTaskIndexes[i]].getCode() == CODE_DEADLINE) {
			_doneTasks.push_back(contents[_doneTaskIndexes[i]]);
			contents[_doneTaskIndexes[i]].setInvalid();
		}
		else {
			throw exceptionInputInvalidDone;
		}
	}

	_todoTMPtr->write(contents);

	for (unsigned int i = 0; i < _doneTasks.size(); i++) {
		_doneTMPtr->append(_doneTasks[i]);
	}

	feedbackString = prepareFeedback();

	return feedbackString;
}

//@author A0080917B
std::string Done::prepareUndoFeedback(void) {
	std::string feedback = "Marked the following undone:\n";
	std::string tasksDisplay;

	for (unsigned int i = 0; i < _doneTasks.size(); i++) {
		tasksDisplay = prepareTaskDisplayOneLine(_doneTasks[i]);
		feedback += tasksDisplay;
	}

	return feedback;
}

std::string Done::undo(void) {
	std::string feedbackString;
	std::vector<Task> doneTasks = _doneTasks;
	std::vector<Task> todoContents;
	std::vector<Task> doneContents;

	todoContents = _todoTMPtr->read();
	doneContents = _doneTMPtr->read();

	for (unsigned int i = 0; i < doneTasks.size(); i++) {
		bool isFoundTodo = false;
		bool isFoundDone = false;
		for (unsigned int j = 0; j < todoContents.size() && !isFoundTodo; j++) {
			if (todoContents[j].getCode() == CODE_INVALID && todoContents[j].getDescription() == doneTasks[i].getDescription() && todoContents[j].getStartDateTime() == doneTasks[i].getStartDateTime() && todoContents[j].getEndDateTime() == doneTasks[i].getEndDateTime() && todoContents[j].getLocation() == doneTasks[i].getLocation()) {
				todoContents[j] = doneTasks[i];
				isFoundTodo = true;
			}
		}
		if (!isFoundTodo) {
			todoContents.push_back(doneTasks[i]);
		}

		for (unsigned int k = 0; k < doneContents.size() && !isFoundDone; k++) {
			if (doneContents[k].getCode() != CODE_INVALID && doneContents[k].getDescription() == doneTasks[i].getDescription() && doneContents[k].getStartDateTime() == doneTasks[i].getStartDateTime() && doneContents[k].getEndDateTime() == doneTasks[i].getEndDateTime() && doneContents[k].getLocation() == doneTasks[i].getLocation()) {
				doneContents[k].setInvalid();
				isFoundDone = true;
			}
		}
	}

	_todoTMPtr->write(todoContents);
	_doneTMPtr->write(doneContents);

	feedbackString = prepareUndoFeedback();

	return feedbackString;
}

std::string Done::redo(void) {
	std::string feedbackString;
	std::vector<Task> doneTasks = _doneTasks;
	std::vector<Task> todoContents;
	std::vector<Task> doneContents;

	todoContents = _todoTMPtr->read();
	doneContents = _doneTMPtr->read();

	for (unsigned int i = 0; i < doneTasks.size(); i++) {
		bool isFoundDone = false;
		bool isFoundTodo = false;
		for (unsigned int j = 0; j < doneContents.size() && !isFoundDone; j++) {
			if (doneContents[j].getCode() == CODE_INVALID && doneContents[j].getDescription() == doneTasks[i].getDescription() && doneContents[j].getStartDateTime() == doneTasks[i].getStartDateTime() && doneContents[j].getEndDateTime() == doneTasks[i].getEndDateTime() && doneContents[j].getLocation() == doneTasks[i].getLocation()) {
				doneContents[j] = doneTasks[i];
				isFoundDone = true;
			}
		}
		if (!isFoundDone) {
			doneContents.push_back(doneTasks[i]);
		}

		for (unsigned int k = 0; k < todoContents.size() && !isFoundTodo; k++) {
			if (todoContents[k].getCode() != CODE_INVALID && todoContents[k].getDescription() == doneTasks[i].getDescription() && todoContents[k].getStartDateTime() == doneTasks[i].getStartDateTime() && todoContents[k].getEndDateTime() == doneTasks[i].getEndDateTime() && todoContents[k].getLocation() == doneTasks[i].getLocation()) {
				todoContents[k].setInvalid();
				isFoundTodo = true;
			}
		}
	}

	_todoTMPtr->write(todoContents);
	_doneTMPtr->write(doneContents);

	feedbackString = prepareFeedback();

	return feedbackString;
}

