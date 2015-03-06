#include "Add.h"

Add::Add(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
	_attributeKeywords.assign(ATTRIBUTEKEYWORDSARRAY, ATTRIBUTEKEYWORDSARRAY + ATTRIBUTEKEYWORDSARRAYSIZE);
	_naturalKeywords.assign(NATURALKEYWORDSARRAY, NATURALKEYWORDSARRAY + NATURALKEYWORDSARRAYSIZE);
	_description = "";
	_startDateTime = NO_TIME;
	_endDateTime = NO_TIME;
	_location = "";
}


Add::~Add(void){
}

void Add::process(std::string userInput) {
	bool isProcessed = false;

	if (userInput == "") {
		throw exceptionInputMissingAddParams;
	}

	isProcessed = processAttributesStyle(userInput);

	if (!isProcessed) {
		processNaturalStyle(userInput);
	}

	return;
}

bool Add::processAttributesStyle(std::string userInput) {
	bool isProcessed = false;
	bool isStartDateDefined = false;

	std::vector<std::vector<std::string>> keywordsAndParams;

	userInput = " " + userInput;
	keywordsAndParams = extractParamsForKeywords(userInput, _attributeKeywords);

	for (unsigned int i = 0; i < keywordsAndParams.size(); i++) {
		if (!keywordsAndParams[i].empty()) {
			if (keywordsAndParams[i].size() > 1) {
				throw exceptionInputRepeatAttributeKeywords;
			}

			if (keywordsAndParams[i][0] == "") {
				throw exceptionInputMissingAttributeParam;
			}

			isProcessed = true;

			switch (i) {
			case INDEX_DESCRIPTION:
				_description = keywordsAndParams[i][0];
				break;
			case INDEX_STARTDATETIME:
				isStartDateDefined = true;
				_startDateTime = processTime(keywordsAndParams[i][0], START, WEEK_NOT_PERMITTED);
				break;
			case INDEX_ENDDATETIME:
			{
				std::string endDateTimeString;

				if (isStartDateDefined && keywordsAndParams[i][0].size() == LENGTH_TIMEINPUT) {
					std::string startDateTimeString = keywordsAndParams[INDEX_STARTDATETIME][0];
					std::string startDateString;
					if (startDateTimeString.substr(startDateTimeString.size() - LENGTH_TIMEINPUT).find_first_not_of(INTS_POSITIVE) == std::string::npos) {
						startDateString = startDateTimeString.substr(0, startDateTimeString.size() - LENGTH_TIMEINPUT);
					}
					else {
						startDateString = startDateTimeString;
					}

					endDateTimeString = startDateString + " " + keywordsAndParams[i][0];
				}
				else {
					endDateTimeString = keywordsAndParams[i][0];
				}

				_endDateTime = processTime(endDateTimeString, END, WEEK_NOT_PERMITTED);

				if (!checkStartEndTimeValidity(_startDateTime, _endDateTime)) {
					throw exceptionInputStartLaterThanEndTime;
				}
				break;
			}
			case INDEX_LOCATION:
				_location = keywordsAndParams[i][0];
				break;
			}
		}
	}

	if (isProcessed) {
		if (userInput != "") {
			throw exceptionInputMissingAttributeKeyword;
		}

		if (keywordsAndParams[INDEX_DESCRIPTION].empty()) {
			throw exceptionInputMissingDescription;
		}
	}

	return isProcessed;
}

void Add::processNaturalStyle(std::string userInput) {
	bool isProcessed = false;

	std::vector<std::vector<std::string>> keywordsAndParams;
	keywordsAndParams = extractParamsForKeywords(userInput, _naturalKeywords);

	for (unsigned int i = 0; i < keywordsAndParams.size(); i++) {
		if (!keywordsAndParams[i].empty()) {
			if (keywordsAndParams[i].size() > 1) {
				throw exceptionInputRepeatNaturalKeywords;
			}

			if (keywordsAndParams[i][0] == "") {
				throw exceptionInputMissingNaturalParam;
			}
		}
	}

	//description
	if (userInput == "") {
		throw exceptionInputMissingDescription;
	}
	_description = userInput;

	std::string dateTimeString;
	//on without or with from and to
	if (!isProcessed && !keywordsAndParams[INDEX_ON].empty()) {
		//Cannot have by
		if (!keywordsAndParams[INDEX_BY].empty()) {
			throw exceptionInputInvalidNaturalKeywordsCombination;
		}
		//on without from and to
		if (keywordsAndParams[INDEX_FROM].empty() && keywordsAndParams[INDEX_TO].empty()) {
			dateTimeString = keywordsAndParams[INDEX_ON][0];
			_startDateTime = processTime(dateTimeString, START, WEEK_NOT_PERMITTED);
			isProcessed = true;
		}
		//on with from and to
		else if (!keywordsAndParams[INDEX_FROM].empty() && !keywordsAndParams[INDEX_TO].empty()) {
			dateTimeString = keywordsAndParams[INDEX_ON][0] + " " + keywordsAndParams[INDEX_FROM][0];
			_startDateTime = processTime(dateTimeString, START, WEEK_NOT_PERMITTED);
			dateTimeString = keywordsAndParams[INDEX_ON][0] + " " + keywordsAndParams[INDEX_TO][0];
			_endDateTime = processTime(dateTimeString, END, WEEK_NOT_PERMITTED);
			if (!checkStartEndTimeValidity(_startDateTime, _endDateTime)) {
				throw exceptionInputStartLaterThanEndTime;
			}
			isProcessed = true;
		}
		else {
			if (keywordsAndParams[INDEX_FROM].empty()) {
				throw exceptionInputMissingStartTime;
			}
			if (keywordsAndParams[INDEX_TO].empty()) {
				throw exceptionInputMissingEndTime;
			}
		}
	}

	//from and to
	if (!isProcessed && (!keywordsAndParams[INDEX_FROM].empty() || !keywordsAndParams[INDEX_TO].empty())) {
		//Cannot have by
		if (!keywordsAndParams[INDEX_BY].empty()) {
			throw exceptionInputInvalidNaturalKeywordsCombination;
		}

		if (keywordsAndParams[INDEX_FROM].empty()) {
			throw exceptionInputMissingStartTime;
		}
		if (keywordsAndParams[INDEX_TO].empty()) {
			throw exceptionInputMissingEndTime;
		}

		dateTimeString = keywordsAndParams[INDEX_FROM][0];
		_startDateTime = processTime(dateTimeString, START, WEEK_NOT_PERMITTED);
		dateTimeString = keywordsAndParams[INDEX_TO][0];
		_endDateTime = processTime(dateTimeString, END, WEEK_NOT_PERMITTED);
		if (!checkStartEndTimeValidity(_startDateTime, _endDateTime)) {
			throw exceptionInputStartLaterThanEndTime;
		}

		isProcessed = true;
	}

	//by
	if (!isProcessed && !keywordsAndParams[INDEX_BY].empty()) {
		dateTimeString = keywordsAndParams[INDEX_BY][0];
		_endDateTime = processTime(dateTimeString, END, WEEK_NOT_PERMITTED);
		isProcessed = true;
	}

	//location
	if (!keywordsAndParams[INDEX_IN].empty()) {
		_location = keywordsAndParams[INDEX_IN][0];
	}
}

std::string Add::prepareFeedback(Task addedTask) {
	std::string feedback = "Added ";
	std::string type;
	std::string taskDisplay;

	type = getTaskType(addedTask.getCode());

	feedback += type + ":\n";

	taskDisplay = prepareTaskDisplayAttributeBreakdown(addedTask);

	feedback += taskDisplay;

	return feedback;
}

std::string Add::prepareUndoFeedback(Task deletedTask) {
	std::string feedback = "Deleted ";
	std::string taskDisplay;
	std::string type;

	type = getTaskType(deletedTask.getCode());

	feedback += type + ":\n";

	taskDisplay = prepareTaskDisplayAttributeBreakdown(deletedTask);

	feedback += taskDisplay;

	return feedback;
}

std::string Add::executeInput(std::string userInput) {
	std::string feedbackString;

	process(userInput);

	std::vector<Task> contents;
	contents = _todoTMPtr->read();

	for (unsigned int i = 0; i < contents.size(); i++) {
		if (contents[i].getCode() != TASKTYPECODE_INVALID && contents[i].getDescription() == _description && contents[i].getStartDateTime() == _startDateTime && contents[i].getEndDateTime() == _endDateTime && contents[i].getLocation() == _location) {
			throw exceptionInputIdenticalTaskPresent;
		}
	}

	Task addTask(_description, _startDateTime, _endDateTime, _location);

	_todoTMPtr->append(addTask);

	feedbackString = prepareFeedback(addTask);

	return feedbackString;
}

std::string Add::undo(void) {
	std::string feedbackString;

	std::vector<Task> contents;
	contents = _todoTMPtr->read();

	bool isFound = false;
	int addedTaskIndex = NO_INDEX;
	for (unsigned int i = 0; i < contents.size() && !isFound; i++) {
		if (contents[i].getCode() != TASKTYPECODE_INVALID && contents[i].getDescription() == _description && contents[i].getStartDateTime() == _startDateTime && contents[i].getEndDateTime() == _endDateTime && contents[i].getLocation() == _location) {
			addedTaskIndex = i;
			isFound = true;
		}
	}
	Task deletedTask = contents[addedTaskIndex];

	contents[addedTaskIndex].setInvalid();

	_todoTMPtr->write(contents);

	feedbackString = prepareUndoFeedback(deletedTask);

	return feedbackString;
}

std::string Add::redo(void) {
	std::string feedbackString;

	Task addTask(_description, _startDateTime, _endDateTime, _location);

	std::vector<Task> contents;
	contents = _todoTMPtr->read();

	bool isFound = false;
	for (unsigned int i = 0; i < contents.size() && !isFound; i++) {
		if (contents[i].getCode() == TASKTYPECODE_INVALID && contents[i].getDescription() == _description && contents[i].getStartDateTime() == _startDateTime && contents[i].getEndDateTime() == _endDateTime && contents[i].getLocation() == _location) {
			contents[i] = addTask;
			isFound = true;
		}
	}
	if (!isFound) {
		contents.push_back(addTask);
	}

	_todoTMPtr->write(contents);

	feedbackString = prepareFeedback(addTask);

	return feedbackString;
}
