#include "Command.h"

//Displayed tasks indexes and TextManipulator object variables:
Manipulator* Command::_displayedTMPtr = NULL;
std::vector<int> Command::_displayedTasksIndexes;

Command::Command(Manipulator* todoTMPtr, Manipulator* doneTMPtr) {
	_todoTMPtr = todoTMPtr;
	_doneTMPtr = doneTMPtr;
}

Command::~Command(void) {
}

std::string Command::executeInput(std::string) {
	std::string virtualString;
	return virtualString;
}

std::string Command::undo(void) {
	std::string virtualString;
	return virtualString;
}

std::string Command::redo(void) {
	std::string virtualString;
	return virtualString;
}

//If keyword is not found, its associated vector element will be empty.
//If keyword is found but there is no associated param, its associated vector element will have 1 element of empty string
//Passed by reference input string will be modified to remaining string after extraction.
std::vector<std::vector<std::string>> Command::extractParamsForKeywords(std::string& input, std::vector<std::string> keywords) {
	//Check for dangling keyword at end of string, if true, append ending space to string
	bool isFound = false;
	for (unsigned int i = 0; i < keywords.size() && !isFound; i++) {
		std::string danglingKeyword;
		danglingKeyword = keywords[i].substr(0, keywords[i].size() - 1);
		if (input.find(danglingKeyword, input.size() - danglingKeyword.size()) != std::string::npos) {
			isFound = true;
			input += " ";
		}
	}

	std::vector<std::vector<std::string>> keywordsAndParams;
	std::vector<std::vector<int>> keywordsStartPos;
	std::vector<int> allStartPos;

	//Get start position of each occurrence of each keyword
	for (unsigned int i = 0; i < keywords.size(); i++) {
		int startSearchPos = 0;
		std::vector<int> startPos;
		int pos;

		pos = input.find(keywords[i].c_str(), startSearchPos, keywords[i].size());
		startPos.push_back(pos);
		startSearchPos = pos + 1;
		if (pos != std::string::npos) {
			allStartPos.push_back(pos);
		}

		while ((pos != std::string::npos) && ((unsigned int)startSearchPos < input.size())) {
			pos = input.find(keywords[i].c_str(), startSearchPos, keywords[i].size());
			if (pos != std::string::npos) {
				startPos.push_back(pos);
				allStartPos.push_back(pos);
				startSearchPos = pos + 1;
			}
		}

		keywordsStartPos.push_back(startPos);
	}

	//Extract param for each keyword by substr from start position of keyword + size of keyword +1 to start position of next keyword
	for (unsigned int i = 0; i < keywordsStartPos.size(); i++) {
		std::vector<std::string> params;
		for (unsigned int j = 0; j < keywordsStartPos[i].size(); j++) {
			if (keywordsStartPos[i][j] != std::string::npos) {
				int nextKeywordPos = input.size();
				for (unsigned int k = 0; k < allStartPos.size(); k++) {
					if (allStartPos[k] > keywordsStartPos[i][j] && allStartPos[k] < nextKeywordPos) {
						nextKeywordPos = allStartPos[k];
					}
				}

				std::string param;
				int paramLength;
				paramLength = nextKeywordPos - (keywordsStartPos[i][j] + keywords[i].size());
				if (paramLength > 0) {
					param = input.substr(keywordsStartPos[i][j] + keywords[i].size(), paramLength);
					params.push_back(param);
				}
				else {
					params.push_back("");
				}
			}
		}

		keywordsAndParams.push_back(params);
	}

	//Modify input string to remaining string after extraction
	if (!allStartPos.empty()) {
		std::sort(allStartPos.begin(), allStartPos.end());
		input = input.substr(0, allStartPos[0]);
	}

	return keywordsAndParams;
}

time_t Command::processTime(std::string userInput, bool isStart, bool isWeekPermitted) {
	assert(userInput != "");

	time_t timeT;

	for (unsigned int i = 0; i < userInput.size(); i++) {
		char c = userInput[i];
		userInput[i] = tolower(c);
	}

	bool processed = false;

	std::stringstream ss;
	ss << userInput;
	std::vector<std::string> inputs;
	std::string input;

	while (ss >> input) {
		inputs.push_back(input);
	}

	int hour = UNDEFINED;
	int min = UNDEFINED;
	int day = UNDEFINED;
	int thisNextLast = UNDEFINED;
	int mday = UNDEFINED;
	int month = UNDEFINED;
	int year = UNDEFINED;

	for (unsigned int i = 0; (i < inputs.size()) && (!processed); i++) {
		for (int j = 0; j < SIZE_TYPEKEYWORDSARRAY && (!processed); j++) {
			if (inputs[i] == TYPEKEYWORDS[j]) {
				if (j >= INDEX_TODAY && j <= INDEX_YESTERDAY) {
					inputs.erase(inputs.begin() + i);

					if (inputs.empty()) {
						processed = true;
					}
					else if (inputs.size() == 1) {
						if (isWeekPermitted) {
							throw exceptionInputInvalidTimeShowSearch;
						}
						if (inputs[0].size() != LENGTH_HOURINPUT + LENGTH_MININPUT) {
							throw exceptionInputInvalidTime;
						}

						if (inputs[0].find_first_not_of(INTS_POSITIVE) != std::string::npos) {
							throw exceptionInputInvalidTime;
						}

						hour = atoi((inputs[0].substr(0, LENGTH_HOURINPUT)).c_str());
						min = atoi((inputs[0].substr(LENGTH_HOURINPUT)).c_str());

						inputs.erase(inputs.begin());
						processed = true;
					}
					else {
						if (isWeekPermitted) {
							throw exceptionInputInvalidDateTimeShowSearch;
						}

						throw exceptionInputInvalidDateTimeAddEdit;
					}

					if (processed) {
						if (j == INDEX_TODAY) {
							timeT = getTodayTime(isStart, hour, min);
						}
						else if (j == INDEX_TOMORROW) {
							timeT = getTomorrowTime(isStart, hour, min);
						}
						else {
							timeT = getYesterdayTime(isStart, hour, min);
						}
					}
					else {
						if (isWeekPermitted) {
							throw exceptionInputInvalidDateTimeShowSearch;
						}

						throw exceptionInputInvalidDateTimeAddEdit;
					}
				}
				else if (j >= INDEX_MONDAY && j <= INDEX_SUNDAY) {
					day = j;
					inputs.erase(inputs.begin() + i);

					if (inputs.empty()) {
						processed = true;
					}
					else {
						for (unsigned int k = 0; k < (inputs.size()) && (!processed); k++) {
							for (int l = INDEX_THIS; (l <= INDEX_LAST) && (!processed); l++) {
								if (inputs[k] == THISNEXTLAST[l]) {
									thisNextLast = l;
									inputs.erase(inputs.begin() + k);

									if (inputs.empty()) {
										processed = true;
									}
									else if (inputs.size() == 1) {
										if (isWeekPermitted) {
											throw exceptionInputInvalidTimeShowSearch;
										}
										if (inputs[0].size() != LENGTH_HOURINPUT + LENGTH_MININPUT) {
											throw exceptionInputInvalidTime;
										}

										if (inputs[0].find_first_not_of(INTS_POSITIVE) != std::string::npos) {
											throw exceptionInputInvalidTime;
										}

										hour = atoi((inputs[0].substr(0, LENGTH_HOURINPUT)).c_str());
										min = atoi((inputs[0].substr(LENGTH_HOURINPUT)).c_str());

										inputs.erase(inputs.begin());
										processed = true;
									}
									else {
										if (isWeekPermitted) {
											throw exceptionInputInvalidDateTimeShowSearch;
										}

										throw exceptionInputInvalidDateTimeAddEdit;
									}
								}
							}
						}

						if (inputs.size() == 1 && (!processed)) {
							if (isWeekPermitted) {
								throw exceptionInputInvalidTimeShowSearch;
							}
							if (inputs[0].size() != LENGTH_HOURINPUT + LENGTH_MININPUT) {
								throw exceptionInputInvalidTime;
							}

							if (inputs[0].find_first_not_of(INTS_POSITIVE) != std::string::npos) {
								throw exceptionInputInvalidTime;
							}

							hour = atoi((inputs[0].substr(0, LENGTH_HOURINPUT)).c_str());
							min = atoi((inputs[0].substr(LENGTH_HOURINPUT)).c_str());

							inputs.erase(inputs.begin());
							processed = true;
						}
					}

					if (processed) {
						timeT = getDayTime(isStart, day, thisNextLast, hour, min);
					}
					else {
						if (isWeekPermitted) {
							throw exceptionInputInvalidDateTimeShowSearch;
						}

						throw exceptionInputInvalidDateTimeAddEdit;
					}
				}
				else if (j == INDEX_WEEK) {
					if (!isWeekPermitted) {
						throw exceptionInputInvalidDateTimeAddEdit;
					}

					inputs.erase(inputs.begin() + i);

					if (inputs.empty()) {
						processed = true;
					}
					else if (inputs.size() == 1) {
						for (int k = INDEX_THIS; (k <= INDEX_LAST) && (!processed); k++) {
							if (inputs[0] == THISNEXTLAST[k]) {
								thisNextLast = k;
								inputs.erase(inputs.begin());
								processed = true;
							}
						}

						for (int k = 0; (k < SIZE_SEPARATORSARRAY) && (!processed); k++) {
							if (inputs[0][POSITION_SEPARATOR1] == SEPARATORS[k] && inputs[0][POSITION_SEPARATOR2] == SEPARATORS[k]) {
								if (inputs[0].size() == LENGTH_MDAYINPUT + 1 + LENGTH_MONTHINPUT + 1 + LENGTH_YEARINPUT) {
									if (inputs[0].substr(0, LENGTH_MDAYINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
										throw exceptionInputInvalidDate;
									}

									if (inputs[0].substr(POSITION_SEPARATOR1 + 1, LENGTH_MONTHINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
										throw exceptionInputInvalidDate;
									}

									if (inputs[0].substr(POSITION_SEPARATOR2 + 1, LENGTH_YEARINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
										throw exceptionInputInvalidDate;
									}

									mday = atoi((inputs[0].substr(0, LENGTH_MDAYINPUT)).c_str());
									month = atoi((inputs[0].substr(POSITION_SEPARATOR1 + 1, LENGTH_MONTHINPUT)).c_str());
									year = atoi((inputs[0].substr(POSITION_SEPARATOR2 + 1, LENGTH_YEARINPUT)).c_str());

									inputs.erase(inputs.begin());
									processed = true;
								}
								else {
									throw exceptionInputInvalidDateTimeShowSearch;
								}
							}
						}
					}
					else {
						throw exceptionInputInvalidDateTimeShowSearch;
					}

					if (processed) {
						timeT = getWeekTime(thisNextLast, mday, month, year);
					}
					else {
						throw exceptionInputInvalidDateTimeShowSearch;
					}
				}
			}
		}
	}

	//Process specified date DD/MM/YY format
	if (!processed && inputs[0].size() == LENGTH_MDAYINPUT + 1 + LENGTH_MONTHINPUT + 1 + LENGTH_YEARINPUT) {
		for (int k = 0; (k < SIZE_SEPARATORSARRAY) && (!processed); k++) {
			if (inputs[0][POSITION_SEPARATOR1] == SEPARATORS[k] && inputs[0][POSITION_SEPARATOR2] == SEPARATORS[k]) {
				if (inputs[0].substr(0, LENGTH_MDAYINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
					throw exceptionInputInvalidDate;
				}

				if (inputs[0].substr(POSITION_SEPARATOR1 + 1, LENGTH_MONTHINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
					throw exceptionInputInvalidDate;
				}

				if (inputs[0].substr(POSITION_SEPARATOR2 + 1, LENGTH_YEARINPUT).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
					throw exceptionInputInvalidDate;
				}

				mday = atoi((inputs[0].substr(0, LENGTH_MDAYINPUT)).c_str());
				month = atoi((inputs[0].substr(POSITION_SEPARATOR1 + 1, LENGTH_MONTHINPUT)).c_str());
				year = atoi((inputs[0].substr(POSITION_SEPARATOR2 + 1, LENGTH_YEARINPUT)).c_str());

				inputs.erase(inputs.begin());

				if (inputs.empty()) {
					processed = true;
				}
				else if (inputs.size() == 1) {
					if (isWeekPermitted) {
						throw exceptionInputInvalidTimeShowSearch;
					}
					if (inputs[0].size() != LENGTH_HOURINPUT + LENGTH_MININPUT) {
						throw exceptionInputInvalidTime;
					}
					else {
						if (inputs[0].size() != LENGTH_HOURINPUT + LENGTH_MININPUT) {
							throw exceptionInputInvalidTime;
						}

						if (inputs[0].find_first_not_of(INTS_POSITIVE) != std::string::npos) {
							throw exceptionInputInvalidTime;
						}

						hour = atoi((inputs[0].substr(0, LENGTH_HOURINPUT)).c_str());
						min = atoi((inputs[0].substr(LENGTH_HOURINPUT)).c_str());

						inputs.erase(inputs.begin());
						processed = true;
					}
				}
				else {
					if (isWeekPermitted) {
						throw exceptionInputInvalidDateTimeShowSearch;
					}

					throw exceptionInputInvalidDateTimeAddEdit;
				}

				if (processed) {
					timeT = getDateTime(isStart, mday, month, year, hour, min);
				}
				else {
					if (isWeekPermitted) {
						throw exceptionInputInvalidDateTimeShowSearch;
					}

					throw exceptionInputInvalidDateTimeAddEdit;
				}
			}
		}
	}

	if (!processed || !inputs.empty()) {
		if (isWeekPermitted) {
			throw exceptionInputInvalidDateTimeShowSearch;
		}

		throw exceptionInputInvalidDateTimeAddEdit;
	}

	return timeT;
}

time_t Command::getTodayTime(bool isStart, int hour, int min){
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	tm structTimeT;

	localtime_s(&structTimeT, &timeNow);

	if (hour != UNDEFINED && min != UNDEFINED) {
		checkTimeValidity(hour, min);
		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;
	}
	else {
		if (isStart) {
			structTimeT.tm_hour = 0;
			structTimeT.tm_min = 0;
			structTimeT.tm_sec = 0;
		}
		else {
			structTimeT.tm_hour = 23;
			structTimeT.tm_min = 59;
			structTimeT.tm_sec = 0;
		}
	}

	timeT = mktime(&structTimeT);

	return timeT;
}

time_t Command::getYesterdayTime(bool isStart, int hour, int min){
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	time_t timeDesired = timeNow - SECONDS_DAY;

	tm structTimeT;

	localtime_s(&structTimeT, &timeDesired);

	if (hour != UNDEFINED && min != UNDEFINED) {
		checkTimeValidity(hour, min);
		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;
	}
	else {
		if (isStart) {
			structTimeT.tm_hour = 0;
			structTimeT.tm_min = 0;
			structTimeT.tm_sec = 0;
		}
		else {
			structTimeT.tm_hour = 23;
			structTimeT.tm_min = 59;
			structTimeT.tm_sec = 0;
		}
	}

	timeT = mktime(&structTimeT);

	return timeT;
}

time_t Command::getTomorrowTime(bool isStart, int hour, int min){
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	time_t timeDesired = timeNow + SECONDS_DAY;

	tm structTimeT;

	localtime_s(&structTimeT, &timeDesired);

	if (hour != UNDEFINED && min != UNDEFINED) {
		checkTimeValidity(hour, min);
		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;
	}
	else {
		if (isStart) {
			structTimeT.tm_hour = 0;
			structTimeT.tm_min = 0;
			structTimeT.tm_sec = 0;
		}
		else {
			structTimeT.tm_hour = 23;
			structTimeT.tm_min = 59;
			structTimeT.tm_sec = 0;
		}
	}

	timeT = mktime(&structTimeT);

	return timeT;
}

time_t Command::getDayTime(bool isStart, int day, int thisNextLast, int hour, int min) {
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	tm structTimeT;
	localtime_s(&structTimeT, &timeNow);

	int wdayToday;
	wdayToday = structTimeT.tm_wday - 1;

	if (wdayToday < 0) {
		wdayToday = 6;
	}

	int wdayDesiredDay;
	wdayDesiredDay = day - INDEX_MONDAY;

	int daysDifference;
	daysDifference = wdayDesiredDay - wdayToday;

	time_t desiredDayOfWeekTimeT;
	desiredDayOfWeekTimeT = timeNow + (daysDifference * SECONDS_DAY);

	time_t timeDesired;

	if (daysDifference < 0) {
		desiredDayOfWeekTimeT += SECONDS_WEEK;
	}

	if (thisNextLast == INDEX_NEXT) {
		timeDesired = desiredDayOfWeekTimeT + SECONDS_WEEK;
	}
	else if (thisNextLast == INDEX_LAST) {
		timeDesired = desiredDayOfWeekTimeT - SECONDS_WEEK;
	}
	else {
		timeDesired = desiredDayOfWeekTimeT;
	}

	localtime_s(&structTimeT, &timeDesired);

	if (hour != UNDEFINED && min != UNDEFINED) {
		checkTimeValidity(hour, min);
		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;
	}
	else {
		if (isStart) {
			structTimeT.tm_hour = 0;
			structTimeT.tm_min = 0;
			structTimeT.tm_sec = 0;
		}
		else {
			structTimeT.tm_hour = 23;
			structTimeT.tm_min = 59;
			structTimeT.tm_sec = 0;
		}
	}

	timeT = mktime(&structTimeT);

	return timeT;
}

time_t Command::getWeekTime(int thisNextLast, int mday, int month, int year) {
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	tm structTimeT;
	localtime_s(&structTimeT, &timeNow);

	time_t startOfWeekTimeT;
	time_t timeDesired;

	if (mday != UNDEFINED && month != UNDEFINED && year != UNDEFINED) {
		checkDateValidity(mday, month - 1, year);
		structTimeT.tm_year = 100 + year;
		structTimeT.tm_mon = month - 1;
		structTimeT.tm_mday = mday;
		structTimeT.tm_hour = 0;
		structTimeT.tm_min = 0;
		structTimeT.tm_sec = 0;

		timeDesired = mktime(&structTimeT);

		int wdaySpecifiedDate;
		wdaySpecifiedDate = structTimeT.tm_wday - 1;

		if (wdaySpecifiedDate < 0) {
			wdaySpecifiedDate = 6;
		}

		int daysDifference;
		daysDifference = -wdaySpecifiedDate;

		startOfWeekTimeT = timeDesired + (daysDifference * SECONDS_DAY);
	}
	else {
		int wdayToday;
		wdayToday = structTimeT.tm_wday - 1;

		if (wdayToday < 0) {
			wdayToday = 6;
		}

		int daysDifference;
		daysDifference = -wdayToday;

		startOfWeekTimeT = timeNow + (daysDifference * SECONDS_DAY);

		if (thisNextLast == INDEX_NEXT) {
			startOfWeekTimeT += SECONDS_WEEK;
		}
		else if (thisNextLast == INDEX_LAST) {
			startOfWeekTimeT -= SECONDS_WEEK;
		}
	}

	localtime_s(&structTimeT, &startOfWeekTimeT);

	structTimeT.tm_hour = 0;
	structTimeT.tm_min = 0;
	structTimeT.tm_sec = 0;

	timeT = mktime(&structTimeT);

	return timeT;
}

time_t Command::getDateTime(bool isStart, int mday, int month, int year, int hour, int min) {
	time_t timeT;

	time_t timeNow;
	time(&timeNow);

	tm structTimeT;

	localtime_s(&structTimeT, &timeNow);

	checkDateValidity(mday, month - 1, year);
	structTimeT.tm_year = 100 + year;
	structTimeT.tm_mon = month - 1;
	structTimeT.tm_mday = mday;

	if (hour != UNDEFINED && min != UNDEFINED) {
		checkTimeValidity(hour, min);
		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;
	}
	else {
		if (isStart) {
			structTimeT.tm_hour = 0;
			structTimeT.tm_min = 0;
			structTimeT.tm_sec = 0;
		}
		else {
			structTimeT.tm_hour = 23;
			structTimeT.tm_min = 59;
			structTimeT.tm_sec = 0;
		}
	}

	timeT = mktime(&structTimeT);

	return timeT;
}

//Prepare display format for a single task (for add and edit feedback)
std::string Command::prepareTaskDisplayAttributeBreakdown(Task task) {
	std::string taskDisplay = "";

	if (task.getDescription() != "") {
		std::string staticString = "";
		std::string wrappingString = "";
		staticString += DESCRIPTION + ":\t ";
		wrappingString = task.getDescription();
		taskDisplay += wrapText(POS_ATTRIBUTE_LINE, staticString, wrappingString) + "\n";
		//taskDisplay += DESCRIPTION + ":\t " + task.getDescription() + "\n";
	}

	if (task.getStartDateTime() > 0) {
		taskDisplay += STARTDATETIME + ": " + processTimeTToString(task.getStartDateTime()) + "\n";
	}

	if (task.getEndDateTime() > 0) {
		if (task.getCode() == TASKTYPECODE_DEADLINE) {
			taskDisplay += DEADLINE + ":\t " + processTimeTToString(task.getEndDateTime()) + "\n";
		}
		else {
			taskDisplay += ENDDATETIME + ":\t " + processTimeTToString(task.getEndDateTime()) + "\n";
		}
	}

	if (task.getLocation() != "") {
		std::string staticString = "";
		std::string wrappingString = "";
		staticString += LOCATION + ":\t ";
		wrappingString = task.getLocation();
		taskDisplay += wrapText(POS_ATTRIBUTE_LINE, staticString, wrappingString) + "\n";
		//taskDisplay += LOCATION + ":\t " + task.getLocation() + "\n";
	}

	return taskDisplay;
}

//Prepare display format for a single task (for delete, done and search feedback)
std::string Command::prepareTaskDisplayOneLine(Task task) {
	std::string taskDisplay = "";

	taskDisplay += getTaskType(task.getCode());

	taskDisplay += " (" + std::to_string(task.getIndex()) + "): ";

	if (task.getStartDateTime() > 0) {
		std::string startDateTimeString;
		startDateTimeString = processTimeTToString(task.getStartDateTime());
		if (task.getEndDateTime() > 0) {
			std::string endDateTimeString;
			endDateTimeString = processTimeTToString(task.getEndDateTime());
			if (startDateTimeString.substr(0, LENGTH_FEEDBACKDATESTRING) == endDateTimeString.substr(0, LENGTH_FEEDBACKDATESTRING)) {
				endDateTimeString = endDateTimeString.substr(endDateTimeString.size() - LENGTH_FEEDBACKTIMESTRING);
			}
			taskDisplay += startDateTimeString + " - " + endDateTimeString + ": ";
		}
		else {
			taskDisplay += startDateTimeString + ": ";
		}
	}
	else if (task.getEndDateTime() > 0) {
		std::string endDateTimeString;
		endDateTimeString = processTimeTToString(task.getEndDateTime());
		taskDisplay += endDateTimeString + ": ";
	}

	taskDisplay += task.getDescription();

	if (task.getLocation() != "") {
		taskDisplay += "; " + task.getLocation();
	}

	taskDisplay += "\n";

	return taskDisplay;
}

//Get task type name to furnish feedback
std::string Command::getTaskType(std::string typeCode) {
	std::string editedType;

	if (typeCode == TASKTYPECODE_TIMED || typeCode == TASKTYPECODE_PARTIALTIMED) {
		editedType = TASKTYPE_EVENT;
	}
	else if (typeCode == TASKTYPECODE_DEADLINE) {
		editedType = TASKTYPE_DEADLINE;
	}
	else {
		editedType = TASKTYPE_TASK;
	}

	return editedType;
}

std::string Command::processTimeTToString(time_t timeT) {
	assert(timeT > 0);

	tm timeTm;
	localtime_s(&timeTm, &timeT);
	char dateTimeString[50];
	strftime(dateTimeString, 50, "%a, %d %b %Y, %I:%M%p", &timeTm);

	return dateTimeString;
}

bool Command::checkStartEndTimeValidity(time_t startTime, time_t endTime) {
	bool startEndTimeValidity = true;

	if ((endTime > 0) && (startTime > endTime)) {
		startEndTimeValidity = false;
	}

	return startEndTimeValidity;
}

bool Command::checkDateValidity(int mday, int month, int year) {
	bool isValid = false;
	bool isLeapYear = false;

	if (month >= 0 && month <= 11) {
		switch (month) {
		case FEBRUARY:
			if (year % 4 == 0) {
				if (year % 100 == 0) {
					if (year % 400 == 0) {
						isLeapYear = true;
					}
				}
				else {
					isLeapYear = true;
				}
			}
			if (isLeapYear) {
				if (mday >= 1 && mday <= 29) {
					isValid = true;
				}
				else {
					throw exceptionInputMdayOutOfRangeLeapFeb;
				}
			}
			else {
				if (mday >= 1 && mday <= 28) {
					isValid = true;
				}
				else {
					throw exceptionInputMdayOutOfRangeNonLeapFeb;
				}
			}
			break;

		case APRIL:
		case JUNE:
		case SEPTEMBER:
		case NOVEMBER:
			if (mday >= 1 && mday <= 30) {
				isValid = true;
			}
			else {
				throw exceptionInputMdayOutOfRange30DayMonth;
			}
			break;

		default:
			if (mday >= 1 && mday <= 31) {
				isValid = true;
			}
			else {
				throw exceptionInputMdayOutOfRange31DayMonth;
			}
			break;
		}
	}
	else {
		throw exceptionInputMonthOutOfRange;
	}

	return isValid;

}

bool Command::checkTimeValidity(int hour, int min) {
	bool isValid = false;

	if (hour >= 0 && hour <= 23) {
		if (min >= 0 && min <= 59) {
			isValid = true;
		}
		else {
			throw exceptionInputMinOutOfRange;
		}
	}
	else {
		throw exceptionInputHourOutOfRange;
	}

	return isValid;
}

void Command::updateDisplayedTask(Manipulator* displayedTMPtr, std::vector<int> displayedTasksIndexes) {
	_displayedTMPtr = displayedTMPtr;
	_displayedTasksIndexes = displayedTasksIndexes;
}

std::vector<int> Command::getDisplayedTask(void){
	return _displayedTasksIndexes;
}
Manipulator* Command::getDisplayedTMPtr(void) {
	return _displayedTMPtr;
}

std::string Command::wrapText(unsigned int indentSize, std::string staticString, std::string wrapString) {
	unsigned int startIndex = 0;
	unsigned int runningIndex = 0;
	unsigned int spaceLeft;
	unsigned int spaceAfterIndent;
	const int FIRST_ELEMENT = 0;
	const int ONE_SPACE_SIZE = 1;
	std::string word;
	std::string displayString;
	std::string stringWithoutExtraSpace;
	std::string returnString;
	std::vector<std::string> wordVector;
	std::vector<std::string> vectorString;

	std::istringstream wrapStream(wrapString);

	assert(indentSize < CONSOLE_WIDTH);

	spaceAfterIndent = CONSOLE_WIDTH - indentSize;
	spaceLeft = spaceAfterIndent;
	returnString = staticString;

	while (wrapStream >> word) {
		wordVector.push_back(word);
	}

	while (wordVector.size() != 0) {

		while (wordVector.size() != 0 &&
			wordVector[FIRST_ELEMENT].size() + ONE_SPACE_SIZE <= spaceLeft) {
			displayString = displayString + wordVector[FIRST_ELEMENT] + " ";
			spaceLeft -= wordVector[FIRST_ELEMENT].size() + ONE_SPACE_SIZE;
			wordVector.erase(wordVector.begin());
		}

		if (wordVector.size() != 0 &&
			wordVector[FIRST_ELEMENT].size() >= spaceAfterIndent &&
			spaceLeft >= spaceAfterIndent / 2) {
			displayString = displayString + wordVector[FIRST_ELEMENT].substr(0, spaceLeft - 1) + " ";
			int charLeft = wordVector[FIRST_ELEMENT].size() - spaceLeft + 1;
			int startPos = spaceLeft - 2;
			wordVector[FIRST_ELEMENT] = wordVector[FIRST_ELEMENT].substr(startPos, charLeft);
		}

		displayString = displayString.substr(0, displayString.size() - 1);
		returnString = returnString + displayString + "\n";

		displayString = "";
		spaceLeft = CONSOLE_WIDTH - indentSize;
		for (unsigned int i = 0; i < indentSize; i++) {
			displayString = displayString + " ";
		}
	}

	returnString = returnString.substr(0, returnString.size() - 1);
	return returnString;
}

std::string Command::prepareHeader(std::string centreInput) {
	std::string headerString;
	int size;

	size = centreInput.size();

	headerString = " ";

	for (int i = 0; i < (CONSOLE_WIDTH - size - 6) / 2; i++) {
		headerString = headerString + "=";
	}

	headerString = headerString + "  " + centreInput + "  ";

	if (size % 2 == 1) {
		for (int i = 0; i <= (CONSOLE_WIDTH - size - 6) / 2; i++) {
			headerString = headerString + "=";
		}
	}
	else {
		for (int i = 0; i < (CONSOLE_WIDTH - size - 6) / 2; i++) {
			headerString = headerString + "=";
		}
	}

	headerString = headerString + "\n";

	return headerString;
}
