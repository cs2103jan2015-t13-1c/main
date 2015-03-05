#include "Task.h"

Task::Task(std::string taskString) {
	_index = NO_INDEX;

	initialise(taskString);
}

Task::Task(int taskIndex, std::string taskString) {
	_index = taskIndex;

	initialise(taskString);
}

void Task::initialise(std::string taskString) {
	int firstTab = getTabPosition(taskString, 0);
	int secondTab = getTabPosition(taskString, firstTab + 1);
	int thirdTab = getTabPosition(taskString, secondTab + 1);
	int fourthTab = getTabPosition(taskString, thirdTab + 1);

	if (firstTab == END_OF_STRING ||
		secondTab == END_OF_STRING ||
		thirdTab == END_OF_STRING ||
		fourthTab == END_OF_STRING) {
		throw exceptionTaskInvalidStringFormat;
	}

	std::string extractedString;
	time_t timeValue;

	extractedString = taskString.substr(0, 3);
	if (!checkTaskCodeValidity(extractedString)) {
		throw exceptionTaskInvalidTypeCode;
	}
	_code = extractedString;

	extractedString = taskString.substr(firstTab + 1, secondTab - firstTab - 1);
	if (extractedString == "") {
		throw exceptionTaskIncorrectEmptyAttributeSymbol;
	}
	else if (extractedString == SYMBOL_EMPTYATTRIBUTE) {
		throw exceptionTaskNoDescription;
	}
	else {
		_description = extractedString;
	}

	extractedString = taskString.substr(secondTab + 1, thirdTab - secondTab - 1);
	timeValue = getTimeT(extractedString);
	_startDateTime = timeValue;

	extractedString = taskString.substr(thirdTab + 1, fourthTab - thirdTab - 1);
	timeValue = getTimeT(extractedString);
	_endDateTime = timeValue;

	extractedString = taskString.substr(fourthTab + 1, taskString.size() - fourthTab - 1);
	if (extractedString == "") {
		throw exceptionTaskIncorrectEmptyAttributeSymbol;
	}
	else if (extractedString == SYMBOL_EMPTYATTRIBUTE) {
		_location = "";
	}
	else {
		_location = extractedString;
	}

	bool isCorrect = false;
	if (_code == TASKTYPECODE_INVALID) {
		isCorrect = true;
	}
	else if (_startDateTime > 0 && _endDateTime > 0) {
		isCorrect = (_code == TASKTYPECODE_TIMED);
	}
	else if (_startDateTime > 0 && _endDateTime == 0) {
		isCorrect = (_code == TASKTYPECODE_PARTIALTIMED);
	}
	else if (_endDateTime > 0 && _startDateTime == 0) {
		isCorrect = (_code == TASKTYPECODE_DEADLINE);
	}
	else {
		isCorrect = (_code == TASKTYPECODE_FLOATING);
	}

	if (!isCorrect) {
		throw exceptionTaskIncorrectTaskTypeCode;
	}
}

Task::Task(std::string description, time_t startDateTime, time_t endDateTime, std::string location) {
	_index = NO_INDEX;
	_description = description;
	_startDateTime = startDateTime;
	_endDateTime = endDateTime;
	_location = location;

	if (startDateTime > 0 && endDateTime > 0) {
		_code = TASKTYPECODE_TIMED;
	}
	else if (startDateTime > 0) {
		_code = TASKTYPECODE_PARTIALTIMED;
	}
	else if (endDateTime > 0) {
		_code = TASKTYPECODE_DEADLINE;
	}
	else {
		_code = TASKTYPECODE_FLOATING;
	}
}

Task::~Task(void) {
}

int Task::getTabPosition(std::string taskString, unsigned int startPosition) {
	int checkerPosition;

	if (startPosition >= taskString.size()) {
		return END_OF_STRING;
	}

	for (checkerPosition = startPosition; taskString[checkerPosition] != '\t'; checkerPosition++) {
		if ((unsigned)checkerPosition >= taskString.size()) {
			return END_OF_STRING;
		}
	}

	return checkerPosition;
}

int Task::getIndex(void) {
	return _index;
}

std::string Task::getCode(void) {
	return _code;
}

std::string Task::getDescription(void) {
	return _description;
}

time_t Task::getStartDateTime(void) {
	return _startDateTime;
}

time_t Task::getEndDateTime(void) {
	return _endDateTime;
}

std::string Task::getLocation(void) {
	return _location;
}

std::string Task::prepareLine(void) {
	std::string taskLine;
	std::string descriptionString;
	std::string startDateTimeString;
	std::string endDateTimeString;
	std::string locationString;

	if (_description == "") {
		descriptionString = "-";
	}
	else {
		descriptionString = _description;
	}

	tm timeStruct;
	char startDateTimeCharString[50];
	char endDateTimeCharString[50];

	if (_startDateTime == NO_TIME) {
		startDateTimeString = SYMBOL_EMPTYATTRIBUTE;
	}
	else {
		time_t startDateTime = _startDateTime;
		localtime_s(&timeStruct, &startDateTime);
		strftime(startDateTimeCharString, 50, "%d/%m/%y %H%M", &timeStruct);
		startDateTimeString = startDateTimeCharString;
	}

	if (_endDateTime == NO_TIME) {
		endDateTimeString = SYMBOL_EMPTYATTRIBUTE;
	}
	else {
		time_t endDateTime = _endDateTime;
		localtime_s(&timeStruct, &endDateTime);
		strftime(endDateTimeCharString, 50, "%d/%m/%y %H%M", &timeStruct);
		endDateTimeString = endDateTimeCharString;
	}

	if (_location == "") {
		locationString = SYMBOL_EMPTYATTRIBUTE;
	}
	else {
		locationString = _location;
	}

	taskLine = _code + "\t" + descriptionString + "\t" + startDateTimeString + "\t" + endDateTimeString + "\t" + locationString;

	return taskLine;
}

bool Task::checkTaskCodeValidity(std::string taskCode) {
	bool isValid = false;

	if (taskCode == TASKTYPECODE_INVALID || taskCode == TASKTYPECODE_FLOATING || taskCode == TASKTYPECODE_TIMED || taskCode == TASKTYPECODE_PARTIALTIMED || taskCode == TASKTYPECODE_DEADLINE) {
		isValid = true;
	}

	return isValid;
}

time_t Task::getTimeT(std::string dateTimeString) {
	time_t timeT;

	if (dateTimeString == "") {
		throw exceptionTaskIncorrectEmptyAttributeSymbol;
	}

	if (dateTimeString == "-") {
		timeT = 0;
	}
	else {
		if (dateTimeString.size() != LENGTH_STORAGEDATESTRING || dateTimeString[POSITION_DATESEPARATOR1] != '/' || dateTimeString[POSITION_DATESEPARATOR2] != '/' || dateTimeString[POSITION_DATETIMESEPARATOR] != ' ') {
			throw exceptionTaskInvalidDateTime;
		}

		int mday;
		int month;
		int year;
		int hour;
		int min;

		if (dateTimeString.substr(0, LENGTH_STORAGEMDAYSTRING).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
			throw exceptionTaskInvalidDate;
		}

		if (dateTimeString.substr(POSITION_DATESEPARATOR1 + 1, LENGTH_STORAGEMONTHSTRING).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
			throw exceptionTaskInvalidDate;
		}

		if (dateTimeString.substr(POSITION_DATESEPARATOR2 + 1, LENGTH_STORAGEYEARSTRING).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
			throw exceptionTaskInvalidDate;
		}

		if (dateTimeString.substr(POSITION_DATETIMESEPARATOR + 1, LENGTH_STORAGEHOURSTRING).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
			throw exceptionTaskInvalidTime;
		}

		if (dateTimeString.substr(POSITION_DATETIMESEPARATOR + 1 + LENGTH_STORAGEHOURSTRING).find_first_not_of(INTS_POSITIVE) != std::string::npos) {
			throw exceptionTaskInvalidTime;
		}

		mday = atoi(dateTimeString.substr(0, LENGTH_STORAGEMDAYSTRING).c_str());
		month = atoi(dateTimeString.substr(POSITION_DATESEPARATOR1 + 1, LENGTH_STORAGEMONTHSTRING).c_str());
		year = atoi(dateTimeString.substr(POSITION_DATESEPARATOR2 + 1, LENGTH_STORAGEYEARSTRING).c_str());
		hour = atoi(dateTimeString.substr(POSITION_DATETIMESEPARATOR + 1, LENGTH_STORAGEHOURSTRING).c_str());
		min = atoi(dateTimeString.substr(POSITION_DATETIMESEPARATOR + 1 + LENGTH_STORAGEHOURSTRING).c_str());

		checkDateTimeValidity(mday, month - 1, year, hour, min);

		time_t timeNow;
		time(&timeNow);

		tm structTimeT;

		localtime_s(&structTimeT, &timeNow);

		structTimeT.tm_year = 100 + year;
		structTimeT.tm_mon = month - 1;
		structTimeT.tm_mday = mday;

		structTimeT.tm_hour = hour;
		structTimeT.tm_min = min;
		structTimeT.tm_sec = 0;

		timeT = mktime(&structTimeT);
	}

	return timeT;
}

void Task::checkDateTimeValidity(int mday, int month, int year, int hour, int min) {
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
					throw exceptionTaskMdayOutOfRangeLeapFeb;
				}
			}
			else {
				if (mday >= 1 && mday <= 28) {
					isValid = true;
				}
				else {
					throw exceptionTaskMdayOutOfRangeNonLeapFeb;
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
				throw exceptionTaskMdayOutOfRange30DayMonth;
			}
			break;

		default:
			if (mday >= 1 && mday <= 31) {
				isValid = true;
			}
			else {
				throw exceptionTaskMdayOutOfRange31DayMonth;
			}
			break;
		}
	}
	else {
		throw exceptionTaskMonthOutOfRange;
	}

	if (hour >= 0 && hour <= 23) {
		if (min >= 0 && min <= 59) {
			isValid = true;
		}
		else {
			throw exceptionTaskMinOutOfRange;
		}
	}
	else {
		throw exceptionTaskHourOutOfRange;
	}

	return;
}

void Task::setInvalid() {
	_code = TASKTYPECODE_INVALID;
}
