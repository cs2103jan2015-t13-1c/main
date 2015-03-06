#include "Edit.h"

Edit::Edit(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
	_attributeKeywords.assign(ATTRIBUTEKEYWORDSARRAY, ATTRIBUTEKEYWORDSARRAY + ATTRIBUTEKEYWORDSARRAYSIZE);
}

Edit::~Edit(void) {
}

void Edit::process(std::string userInput) {
	if (userInput == "") {
		throw exceptionInputMissingEditTaskIndexAndParams;
	}

	std::vector<std::vector<std::string>> keywordsAndParams;

	std::stringstream ss;
	ss << userInput;

	std::string editTaskIndexString;
	ss >> editTaskIndexString;
	if (!(editTaskIndexString.find_first_not_of(INTS_POSITIVE) == std::string::npos)) {
		throw exceptionInputInvalidTaskIndex;
	}

	int editTaskIndex;
	editTaskIndex = atoi(editTaskIndexString.c_str());

	std::vector<int> displayedTasksIndexes;
	displayedTasksIndexes = getDisplayedTask();

	bool isValid = false;
	for (unsigned int i = 0; i < displayedTasksIndexes.size() && !isValid; i++) {
		if (editTaskIndex == displayedTasksIndexes[i]) {
			isValid = true;
		}
	}

	if (!isValid) {
		throw exceptionInputInvalidTaskIndexOutOfRange;
	}

	_editTaskIndex = editTaskIndex;

	std::string remainingParams;
	getline(ss, remainingParams);

	if (remainingParams == "") {
		throw exceptionInputMissingEditParams;
	}

	keywordsAndParams = extractParamsForKeywords(remainingParams, _attributeKeywords);

	for (unsigned int i = 0; i < keywordsAndParams.size(); i++) {
		if (!keywordsAndParams[i].empty()) {
			if (keywordsAndParams[i].size() > 1) {
				throw exceptionInputRepeatAttributeKeywords;
			}

			if (keywordsAndParams[i][0] == "") {
				throw exceptionInputMissingAttributeParam;
			}

			switch (i) {
			case INDEX_DESCRIPTION:
				_editAttributes.push_back(DESCRIPTION);
				break;
			case INDEX_STARTDATETIME:
				if (keywordsAndParams[i][0].size() == LENGTH_TIMEINPUT) {
					_editAttributes.push_back(STARTTIME);
				}
				else if (keywordsAndParams[i][0] != "-" && keywordsAndParams[i][0].substr(keywordsAndParams[i][0].size() - LENGTH_TIMEINPUT).find_first_not_of(INTS_POSITIVE) == std::string::npos) {
					_editAttributes.push_back(STARTDATETIME);
				}
				else {
					_editAttributes.push_back(STARTDATE);
				}
				break;
			case INDEX_ENDDATETIME:
				if (keywordsAndParams[i][0].size() == LENGTH_TIMEINPUT) {
					_editAttributes.push_back(ENDTIME);
				}
				else if (keywordsAndParams[i][0] != "-" && keywordsAndParams[i][0].substr(keywordsAndParams[i][0].size() - LENGTH_TIMEINPUT).find_first_not_of(INTS_POSITIVE) == std::string::npos) {
					_editAttributes.push_back(ENDDATETIME);
				}
				else {
					_editAttributes.push_back(ENDDATE);
				}
				break;
			case INDEX_LOCATION:
				_editAttributes.push_back(LOCATION);
				break;
			}

			if (keywordsAndParams[i][0] == "-") {
				keywordsAndParams[i][0] = "";
			}
			_editContents.push_back(keywordsAndParams[i][0]);
		}
	}

	if (_editAttributes.empty()) {
		throw exceptionInputInvalidAttributeKeyword;
	}

	if (remainingParams != "") {
		throw exceptionInputMissingAttributeKeyword;
	}

	return;
}

std::string Edit::prepareFeedback(Task originalTask, Task editedTask){
	std::string feedback = "Edited ";
	std::string taskDisplay;

	std::string originalType;
	originalType = getTaskType(originalTask.getCode());

	std::string editedType;
	editedType = getTaskType(editedTask.getCode());

	for (unsigned int i = 0; i < _editAttributes.size(); i++) {
		if (editedType == TASKTYPE_DEADLINE) {
			if (_editAttributes[i] == ENDDATE) {
				_editAttributes[i] = DEADLINEDATE;
			}
			else if (_editAttributes[i] == ENDDATETIME) {
				_editAttributes[i] = DEADLINE;
			}
			else if (_editAttributes[i] == ENDTIME) {
				_editAttributes[i] = DEADLINETIME;
			}
		}

		feedback += _editAttributes[i];

		if (i == _editAttributes.size() - 2) {
			feedback += " and ";
		}
		else if (i == _editAttributes.size() - 1) {
			feedback += " ";
		}
		else {
			feedback += ", ";
		}
	}

	if (editedType == originalType) {
		feedback += "of " + editedType + " (" + std::to_string(_editTaskIndex) + "):\n";
	}
	else {
		feedback += "of " + originalType + " to " + editedType + " (" + std::to_string(_editTaskIndex) + "):\n";
	}

	taskDisplay = prepareTaskDisplayAttributeBreakdown(editedTask);

	feedback += taskDisplay;

	return feedback;
}

std::string Edit::executeInput(std::string userInput) {
	std::string feedbackString;
	std::vector<Task> contents;

	process(userInput);

	contents = getDisplayedTMPtr()->read();

	std::string editTaskCode = contents[_editTaskIndex].getCode();
	if (editTaskCode == TASKTYPECODE_INVALID) {
		throw exceptionInputTaskAlreadyRemoved;
	}

	Task originalTask = contents[_editTaskIndex];
	_originalTaskLine = contents[_editTaskIndex].prepareLine();

	std::string editTaskDescription = contents[_editTaskIndex].getDescription();
	time_t editTaskStartDateTime = contents[_editTaskIndex].getStartDateTime();
	time_t editTaskEndDateTime = contents[_editTaskIndex].getEndDateTime();
	std::string editTaskLocation = contents[_editTaskIndex].getLocation();

	for (unsigned int i = 0; i < _editAttributes.size(); i++) {
		if (_editAttributes[i] == DESCRIPTION) {
			if (_editContents[i] == "") {
				throw exceptionInputInvalidEditRemoveDescription;
			}
			editTaskDescription = _editContents[i];
		}
		else if (_editAttributes[i] == STARTDATETIME) {
			time_t newTimeT;
			newTimeT = processTime(_editContents[i], START, WEEK_NOT_PERMITTED);
			editTaskStartDateTime = newTimeT;
		}
		else if (_editAttributes[i] == STARTDATE) {
			time_t newTimeT;
			if (_editContents[i] == "") {
				newTimeT = 0;
			}
			else {
				if (editTaskStartDateTime > 0) {
					std::string hourString;
					std::string minString;

					hourString = processOriginalHourString(editTaskStartDateTime);
					minString = processOriginalMinString(editTaskStartDateTime);

					_editContents[i] = _editContents[i] + " " + hourString + minString;
				}
				newTimeT = processTime(_editContents[i], START, WEEK_NOT_PERMITTED);
			}
			editTaskStartDateTime = newTimeT;
		}
		else if (_editAttributes[i] == STARTTIME) {
			if (editTaskStartDateTime > 0) {
				time_t newTimeT;

				std::string yearString;
				std::string monthString;
				std::string mdayString;

				yearString = processOriginalYearString(editTaskStartDateTime);
				monthString = processOriginalMonthString(editTaskStartDateTime);
				mdayString = processOriginalMdayString(editTaskStartDateTime);

				std::string newDateTimeString;
				newDateTimeString = mdayString + SEPARATORS[0] + monthString + SEPARATORS[0] + yearString + " " + _editContents[i];
				newTimeT = processTime(newDateTimeString, START, WEEK_NOT_PERMITTED);
				editTaskStartDateTime = newTimeT;
			}
			else if (editTaskEndDateTime > 0) {
				time_t newTimeT;

				std::string yearString;
				std::string monthString;
				std::string mdayString;

				yearString = processOriginalYearString(editTaskEndDateTime);
				monthString = processOriginalMonthString(editTaskEndDateTime);
				mdayString = processOriginalMdayString(editTaskEndDateTime);

				std::string newDateTimeString;
				newDateTimeString = mdayString + SEPARATORS[0] + monthString + SEPARATORS[0] + yearString + " " + _editContents[i];
				newTimeT = processTime(newDateTimeString, START, WEEK_NOT_PERMITTED);
				editTaskStartDateTime = newTimeT;
			}
			else {
				throw exceptionInputNoExistingDate;
			}
		}
		else if (_editAttributes[i] == ENDDATETIME) {
			time_t newTimeT;
			newTimeT = processTime(_editContents[i], END, WEEK_NOT_PERMITTED);
			editTaskEndDateTime = newTimeT;
		}
		else if (_editAttributes[i] == ENDDATE) {
			time_t newTimeT;
			if (_editContents[i] == "") {
				newTimeT = 0;
			}
			else {
				if (editTaskEndDateTime > 0) {
					std::string hourString;
					std::string minString;

					hourString = processOriginalHourString(editTaskEndDateTime);
					minString = processOriginalMinString(editTaskEndDateTime);

					_editContents[i] = _editContents[i] + " " + hourString + minString;
				}
				newTimeT = processTime(_editContents[i], END, WEEK_NOT_PERMITTED);
			}
			editTaskEndDateTime = newTimeT;
		}
		else if (_editAttributes[i] == ENDTIME) {
			if (editTaskEndDateTime > 0) {
				time_t newTimeT;

				std::string yearString;
				std::string monthString;
				std::string mdayString;

				yearString = processOriginalYearString(editTaskEndDateTime);
				monthString = processOriginalMonthString(editTaskEndDateTime);
				mdayString = processOriginalMdayString(editTaskEndDateTime);

				std::string newDateTimeString;
				newDateTimeString = mdayString + SEPARATORS[0] + monthString + SEPARATORS[0] + yearString + " " + _editContents[i];
				newTimeT = processTime(newDateTimeString, END, WEEK_NOT_PERMITTED);
				editTaskEndDateTime = newTimeT;
			}
			else if (editTaskStartDateTime > 0) {
				time_t newTimeT;

				std::string yearString;
				std::string monthString;
				std::string mdayString;

				yearString = processOriginalYearString(editTaskStartDateTime);
				monthString = processOriginalMonthString(editTaskStartDateTime);
				mdayString = processOriginalMdayString(editTaskStartDateTime);

				std::string newDateTimeString;
				newDateTimeString = mdayString + SEPARATORS[0] + monthString + SEPARATORS[0] + yearString + " " + _editContents[i];
				newTimeT = processTime(newDateTimeString, END, WEEK_NOT_PERMITTED);
				editTaskEndDateTime = newTimeT;
			}
			else {
				throw exceptionInputNoExistingDate;
			}
		}
		else {
			editTaskLocation = _editContents[i];
		}
	}

	for (unsigned int i = 0; i < contents.size(); i++) {
		if (contents[i].getCode() != TASKTYPECODE_INVALID && contents[i].getDescription() == editTaskDescription && contents[i].getStartDateTime() == editTaskStartDateTime && contents[i].getEndDateTime() == editTaskEndDateTime && contents[i].getLocation() == editTaskLocation) {
			throw exceptionInputIdenticalTaskPresent;
		}
	}

	if (!checkStartEndTimeValidity(editTaskStartDateTime, editTaskEndDateTime)) {
		throw exceptionInputStartLaterThanEndTime;
	}

	Task editedTask(editTaskDescription, editTaskStartDateTime, editTaskEndDateTime, editTaskLocation);

	contents[_editTaskIndex] = editedTask;

	getDisplayedTMPtr()->write(contents);

	_editedTaskLine = editedTask.prepareLine();

	feedbackString = prepareFeedback(originalTask, editedTask);

	return feedbackString;
}

std::string Edit::processOriginalHourString(time_t timeT) {
	std::string hourString;

	tm timeTM;
	localtime_s(&timeTM, &timeT);

	hourString = std::to_string(timeTM.tm_hour);
	if (hourString.size() != LENGTH_HOURINPUT) {
		hourString = leadingZero + hourString;
	}

	return hourString;
}

std::string Edit::processOriginalMinString(time_t timeT) {
	std::string minString;

	tm timeTM;
	localtime_s(&timeTM, &timeT);

	minString = std::to_string(timeTM.tm_min);
	if (minString.size() != LENGTH_MININPUT) {
		minString = leadingZero + minString;
	}

	return minString;
}

std::string Edit::processOriginalYearString(time_t timeT) {
	std::string yearString;

	tm timeTM;
	localtime_s(&timeTM, &timeT);

	yearString = std::to_string(timeTM.tm_year - 100);
	if (yearString.size() != LENGTH_YEARINPUT) {
		yearString = leadingZero + yearString;
	}

	return yearString;
}

std::string Edit::processOriginalMonthString(time_t timeT) {
	std::string monthString;

	tm timeTM;
	localtime_s(&timeTM, &timeT);

	monthString = std::to_string(timeTM.tm_mon + 1);
	if (monthString.size() != LENGTH_MONTHINPUT) {
		monthString = leadingZero + monthString;
	}

	return monthString;
}

std::string Edit::processOriginalMdayString(time_t timeT) {
	std::string mdayString;

	tm timeTM;
	localtime_s(&timeTM, &timeT);

	mdayString = std::to_string(timeTM.tm_mday);
	if (mdayString.size() != LENGTH_MONTHINPUT) {
		mdayString = leadingZero + mdayString;
	}

	return mdayString;
}


std::string Edit::undo(void) {
	std::string feedbackString;

	Task editedTask(_editedTaskLine);

	Task originalTask(_originalTaskLine);

	std::vector<Task> contents;
	contents = getDisplayedTMPtr()->read();

	bool isFound = false;
	for (unsigned int i = 0; i < contents.size() && !isFound; i++) {
		if (contents[i].getCode() != TASKTYPECODE_INVALID && contents[i].getDescription() == editedTask.getDescription() && contents[i].getStartDateTime() == editedTask.getStartDateTime() && contents[i].getEndDateTime() == editedTask.getEndDateTime() && contents[i].getLocation() == editedTask.getLocation()) {
			isFound = true;
			contents[i] = originalTask;
		}
	}

	getDisplayedTMPtr()->write(contents);

	feedbackString = prepareFeedback(editedTask, originalTask);

	return feedbackString;
}

std::string Edit::redo(void) {
	std::string feedbackString;

	Task editedTask(_editedTaskLine);

	Task originalTask(_originalTaskLine);

	std::vector<Task> contents;
	contents = getDisplayedTMPtr()->read();

	bool isFound = false;
	for (unsigned int i = 0; i < contents.size() && !isFound; i++) {
		if (contents[i].getCode() != TASKTYPECODE_INVALID && contents[i].getDescription() == originalTask.getDescription() && contents[i].getStartDateTime() == originalTask.getStartDateTime() && contents[i].getEndDateTime() == originalTask.getEndDateTime() && contents[i].getLocation() == originalTask.getLocation()) {
			isFound = true;
			contents[i] = editedTask;
		}
	}

	getDisplayedTMPtr()->write(contents);

	feedbackString = prepareFeedback(originalTask, editedTask);

	return feedbackString;
}
