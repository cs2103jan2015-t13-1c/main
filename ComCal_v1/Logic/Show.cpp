#include "Show.h"

Show::Show(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
	_type = 0;
	_startDateTime = 0;
	_TMUsed = NULL;
	_numFloating = 0;
	_numDeadlines = 0;
	_numSchedules = 0;
	_numDeadlinesTml = 0;
	_numSchedulesTml = 0;
}

Show::~Show(void){
}

std::string Show::executeInput(std::string userInput) {
	std::vector<Task> taskVector;
	std::string outputString;

	processInput(userInput);

	if (_type == SHOWTYPE_DONE_DEFAULT || _type == SHOWTYPE_DONE_DAY || _type == SHOWTYPE_DONE_WEEK) {
		_TMUsed = _doneTMPtr;
	}
	else if (_type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_TODO || _type == SHOWTYPE_DAY || _type == SHOWTYPE_WEEK) {
		_TMUsed = _todoTMPtr;
	}

	_TMUsed->sort();
	taskVector = _TMUsed->read();

	outputString = processVector(taskVector);

	storeDisplayed();

	return outputString;
}

void Show::processInput(std::string inputString){
	time_t dateTime = 0;
	time_t todayDateTime = 0;

	if (inputString.find("done", 0) != std::string::npos) {
		std::vector<std::string> keywordVector;
		std::vector<std::vector<std::string>> result2DVector;

		keywordVector.push_back("done ");
		result2DVector = extractParamsForKeywords(inputString, keywordVector);
		if (!inputString.empty()) {
			throw exceptionInputInvalidShowDone;
		} if (result2DVector[0].size() != 1) {
			throw exceptionInputRepeatAttributeKeywords;
		}

		inputString = result2DVector[0][0];

		if (inputString.empty()) {
			_type = SHOWTYPE_DONE_DEFAULT;
		}
		else if (inputString.find("week", 0) != std::string::npos) {
			_type = SHOWTYPE_DONE_WEEK;
		}
		else {
			_type = SHOWTYPE_DONE_DAY;
		}

	}
	else if (inputString.empty()) {
		_type = SHOWTYPE_DEFAULT;
	}
	else if (inputString.find("week", 0) != std::string::npos) {
		_type = SHOWTYPE_WEEK;
	}
	else if (inputString.find("todo", 0) != std::string::npos) {
		_type = SHOWTYPE_TODO;
	}
	else {
		_type = SHOWTYPE_DAY;
	}

	if (_type == SHOWTYPE_TODO) {
		dateTime = NULL;
	}
	else if (_type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_DONE_DEFAULT) {
		dateTime = processTime(TODAY, START, WEEK_PERMITTED);
	}
	else if (_type == SHOWTYPE_DAY || _type == SHOWTYPE_WEEK ||
		_type == SHOWTYPE_DONE_DAY || _type == SHOWTYPE_DONE_WEEK) {
		dateTime = processTime(inputString, START, WEEK_PERMITTED);
	}

	_startDateTime = dateTime;
}

std::string Show::processVector(std::vector<Task>& taskVector) {
	std::ostringstream outputStringStream;

	if (_type == SHOWTYPE_TODO || _type == SHOWTYPE_DEFAULT ||
		_type == SHOWTYPE_DONE_DEFAULT || _type == SHOWTYPE_DONE_DAY || _type == SHOWTYPE_DONE_WEEK) {
		outputStringStream << prepareAllFloatingOutput(taskVector) << std::endl;
	}

	if (_type == SHOWTYPE_TODO || _type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_DONE_DEFAULT) {
		outputStringStream << prepareAllDeadlineOutput(taskVector) << std::endl;
	}
	else {
		outputStringStream << prepareRestrictedDeadlineOutput(taskVector) << std::endl;
	}

	if (_type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_DAY || _type == SHOWTYPE_WEEK) {
		outputStringStream << prepareTimedOutput(taskVector);
	}

	if (_type == SHOWTYPE_DEFAULT) {
		outputStringStream << prepareTmlOutput(taskVector) << std::endl;
	}

	return outputStringStream.str();
}

std::string Show::prepareAllFloatingOutput(std::vector<Task>& taskVector) {
	int firstElement = 0;
	std::ostringstream outputStringStream;
	std::ostringstream bufferOutputStringStream;
	std::ostringstream headerOutputStringStream;
	std::string header;

	while (!taskVector.empty() && taskVector[firstElement].getCode() == TASKTYPECODE_FLOATING) {
		_taskIndexes.push_back(taskVector[firstElement].getIndex());
		bufferOutputStringStream << formatFloatingOutput(taskVector[firstElement]) << std::endl;
		taskVector.erase(taskVector.begin());
		_numFloating++;
	}

	if (_numFloating == 0) {
		bufferOutputStringStream << NO_FLOATING_ALL << std::endl;
	}

	if (_type == SHOWTYPE_DONE_DEFAULT || _type == SHOWTYPE_DONE_DAY || _type == SHOWTYPE_DONE_WEEK) {
		headerOutputStringStream << HEADER_DONE << HEADER_FLOATING << " (" << _numFloating << ")";
	}
	else {
		headerOutputStringStream << HEADER_FLOATING << " (" << _numFloating << ")";
	}

	header = prepareHeader(headerOutputStringStream.str());
	outputStringStream << header << bufferOutputStringStream.str();

	return outputStringStream.str();
}

std::string Show::formatFloatingOutput(Task task) {
	std::ostringstream staticOutputStringStream;
	std::ostringstream wrapOutputStringStream;
	std::string outputString;

	staticOutputStringStream << "(" << task.getIndex() << ")" << "\t";

	wrapOutputStringStream << task.getDescription();

	if (task.getLocation() != "") {
		wrapOutputStringStream << "; " << task.getLocation();
	}

	outputString = wrapText(POS_FLOATING_DEFAULT, staticOutputStringStream.str(), wrapOutputStringStream.str());

	return outputString;
}

std::string Show::prepareAllDeadlineOutput(std::vector<Task>& taskVector) {
	std::ostringstream bufferOutputStringStream;
	std::ostringstream headerOutputStringStream;
	std::ostringstream outputStringStream;
	std::string header;
	int vectorSize;

	vectorSize = taskVector.size();
	for (unsigned int i = 0; i < taskVector.size(); i++) {
		if (taskVector[i].getCode() == TASKTYPECODE_DEADLINE) {
			_taskIndexes.push_back(taskVector[i].getIndex());
			bufferOutputStringStream << formatDeadlineOutput(taskVector[i]) << std::endl;
			_numDeadlines++;
		}
	}

	if (_numDeadlines == 0) {
		bufferOutputStringStream << NO_DEADLINE_ALL << std::endl;
	}

	if (_type == SHOWTYPE_DONE_DEFAULT) {
		headerOutputStringStream << HEADER_DONE << HEADER_DEADLINE << " (" << _numDeadlines << ")";
	}
	else {
		headerOutputStringStream << HEADER_DEADLINE << " (" << _numDeadlines << ")";
	}

	header = prepareHeader(headerOutputStringStream.str());
	outputStringStream << header << bufferOutputStringStream.str();

	return outputStringStream.str();
}

std::string Show::prepareRestrictedDeadlineOutput(std::vector<Task> taskVector) {
	std::ostringstream outputStringStream;
	std::ostringstream bufferOutputStringStream;
	std::ostringstream headerOutputStringStream;
	std::string header;
	tm startDateTimetm;
	char dateString[50];

	if (_type == SHOWTYPE_DAY || _type == SHOWTYPE_DONE_DAY) {
		bufferOutputStringStream << prepareDeadlineDayOutput(taskVector, _startDateTime);
	}
	else if (_type == SHOWTYPE_WEEK || _type == SHOWTYPE_DONE_WEEK) {
		bufferOutputStringStream << prepareDeadlineWeekOutput(taskVector);
	}

	if (_type == SHOWTYPE_DONE_DAY || _type == SHOWTYPE_DONE_WEEK) {
		headerOutputStringStream << HEADER_DONE << HEADER_DEADLINE;
	}
	else {
		headerOutputStringStream << HEADER_DEADLINE;
	}

	if (_type == SHOWTYPE_DAY || _type == SHOWTYPE_DONE_DAY) {
		localtime_s(&startDateTimetm, &_startDateTime);
		strftime(dateString, 50, "%a %d/%m/%y ", &startDateTimetm);
		headerOutputStringStream << HEADER_FOR << dateString << " (" << _numDeadlines << ")";
	}
	else {
		headerOutputStringStream << HEADER_FOR << HEADER_THEWEEK << " (" << _numDeadlines << ")";
	}

	header = prepareHeader(headerOutputStringStream.str());

	outputStringStream << header << bufferOutputStringStream.str();

	return outputStringStream.str();
}

std::string Show::prepareDeadlineDayOutput(std::vector<Task> taskVector, time_t referenceTime) {
	std::ostringstream outputStringStream;

	for (unsigned int i = 0; i < taskVector.size(); i++) {
		if (taskVector[i].getCode() == TASKTYPECODE_DEADLINE) {
			if (((long)taskVector[i].getEndDateTime() >= (long)referenceTime) &&
				((long)taskVector[i].getEndDateTime() < (long)referenceTime + SECONDS_DAY)) {
				_taskIndexes.push_back(taskVector[i].getIndex());
				outputStringStream << formatDeadlineOutput(taskVector[i]) << std::endl;
				_numDeadlines++;
			}
		}
	}
	if (_numDeadlines == 0 &&
		(_type == SHOWTYPE_DAY || _type == SHOWTYPE_DONE_DAY)) {
		outputStringStream << NO_DEADLINE_DAY << std::endl;
	}

	return outputStringStream.str();
}

std::string Show::prepareDeadlineWeekOutput(std::vector<Task> taskVector) {
	std::ostringstream outputStringStream;
	time_t referenceTime;
	std::string outputString;

	referenceTime = _startDateTime;

	for (int i = 0; i < 7; i++) {
		outputString = prepareDeadlineDayOutput(taskVector, referenceTime);
		outputStringStream << outputString;
		referenceTime = referenceTime + SECONDS_DAY;
	}

	if (_numDeadlines == 0) {
		outputStringStream << NO_DEADLINE_WEEK << std::endl;
	}

	return outputStringStream.str();
}

std::string Show::formatDeadlineOutput(Task task) {
	tm endDateTimetm;
	time_t endDateTime;
	char dateTimeString[50];
	char timeString[50];

	endDateTime = task.getEndDateTime();
	localtime_s(&endDateTimetm, &endDateTime);
	strftime(dateTimeString, 50, "%a, %d/%m/%y %I:%M%p", &endDateTimetm);
	strftime(timeString, 50, "%I:%M%p", &endDateTimetm);

	std::ostringstream staticOutputStringStream;
	std::ostringstream wrapOutputStringStream;
	std::string outputString;

	staticOutputStringStream << "(" << task.getIndex() << ")" << "\t";

	if (_type == SHOWTYPE_TODO || _type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_WEEK ||
		_type == SHOWTYPE_DONE_DEFAULT || _type == SHOWTYPE_DONE_WEEK) {
		staticOutputStringStream << dateTimeString << ": ";
	}
	else {
		staticOutputStringStream << timeString << ": ";
	}

	wrapOutputStringStream << task.getDescription();

	if (task.getLocation() != "") {
		wrapOutputStringStream << "; " << task.getLocation();
	}

	if (_type == SHOWTYPE_TODO || _type == SHOWTYPE_DEFAULT || _type == SHOWTYPE_WEEK ||
		_type == SHOWTYPE_DONE_DEFAULT || _type == SHOWTYPE_DONE_WEEK) {
		outputString = wrapText(POS_DEADLINES_DEFAULT, staticOutputStringStream.str(), wrapOutputStringStream.str());
	}
	else {
		outputString = wrapText(POS_DEADLINES_DAY, staticOutputStringStream.str(), wrapOutputStringStream.str());
	}
	return outputString;
}

std::string Show::prepareTimedOutput(std::vector<Task>& taskVector) {
	std::ostringstream outputStringStream;
	std::ostringstream bufferOutputStringStream;
	std::ostringstream headerOutputStringStream;
	std::string header;

	if (_type == SHOWTYPE_DAY || _type == SHOWTYPE_DEFAULT) {
		bufferOutputStringStream << prepareTimedDayOutput(taskVector, _startDateTime);
	}
	else if (_type == SHOWTYPE_WEEK) {
		bufferOutputStringStream << prepareTimedWeekOutput(taskVector);
	}

	headerOutputStringStream << HEADER_TIMED << " (" << _numSchedules << ")";
	header = prepareHeader(headerOutputStringStream.str());
	outputStringStream << header << bufferOutputStringStream.str();

	return outputStringStream.str();
}

std::string Show::prepareTimedDayOutput(std::vector<Task>& taskVector, time_t referenceTime) {
	std::ostringstream outputStringStream;
	tm startDateTimetm;
	char dateString[50];

	localtime_s(&startDateTimetm, &referenceTime);
	strftime(dateString, 50, "%a %d/%m/%y", &startDateTimetm);

	outputStringStream << "~" << dateString << "~" << std::endl;

	for (unsigned int i = 0; i < taskVector.size(); i++) {
		if (taskVector[i].getCode() == TASKTYPECODE_TIMED) {
			if ((long)taskVector[i].getStartDateTime() < (long)referenceTime &&
				(long)taskVector[i].getEndDateTime() > (long)referenceTime) {
				_taskIndexes.push_back(taskVector[i].getIndex());
				outputStringStream << formatTimedOutput(taskVector[i], referenceTime) << std::endl;
				_numSchedules++;
			}
			else if ((long)taskVector[i].getStartDateTime() >= (long)referenceTime &&
				(long)taskVector[i].getStartDateTime() < (long)referenceTime + SECONDS_DAY) {
				_taskIndexes.push_back(taskVector[i].getIndex());
				outputStringStream << formatTimedOutput(taskVector[i], referenceTime) << std::endl;
				_numSchedules++;
			}

		}
		else if (taskVector[i].getCode() == TASKTYPECODE_PARTIALTIMED) {
			if ((long)taskVector[i].getStartDateTime() >= (long)referenceTime &&
				(long)taskVector[i].getStartDateTime() < (long)referenceTime + SECONDS_DAY) {
				_taskIndexes.push_back(taskVector[i].getIndex());
				outputStringStream << formatTimedOutput(taskVector[i], referenceTime) << std::endl;
				_numSchedules++;
			}
		}
	}

	if (_numSchedules == 0) {
		outputStringStream << NO_SCHEDULE_DAY << std::endl;
	}
	outputStringStream << std::endl;

	return outputStringStream.str();
}

std::string Show::prepareTimedWeekOutput(std::vector<Task>& taskVector) {
	std::ostringstream outputStringStream;
	time_t referenceTime;
	referenceTime = _startDateTime;

	for (int i = 0; i < 7; i++) {
		outputStringStream << prepareTimedDayOutput(taskVector, referenceTime);
		referenceTime = referenceTime + SECONDS_DAY;
	}

	return outputStringStream.str();
}

std::string Show::formatTimedOutput(Task task, time_t referenceTime) {
	tm endDateTimetm;
	time_t endDateTime;
	tm startDateTimetm;
	time_t startDateTime;
	char startTimeString[50];
	char endTimeString[50];
	char startDateTimeString[50];
	char endDateTimeString[50];

	std::ostringstream staticOutputStringStream;
	std::ostringstream wrapOutputStringStream;
	std::string outputString;

	startDateTime = task.getStartDateTime();
	localtime_s(&startDateTimetm, &startDateTime);
	endDateTime = task.getEndDateTime();
	localtime_s(&endDateTimetm, &endDateTime);

	strftime(startTimeString, 50, "%I:%M%p", &startDateTimetm);
	strftime(endTimeString, 50, "%I:%M%p", &endDateTimetm);
	strftime(startDateTimeString, 50, "!%d/%m/%y %I:%M%p", &startDateTimetm);
	strftime(endDateTimeString, 50, "!%d/%m/%y %I:%M%p", &endDateTimetm);

	staticOutputStringStream << "(" << task.getIndex() << ")" << "\t";

	if (task.getCode() == TASKTYPECODE_PARTIALTIMED) {
		staticOutputStringStream << "Starting  " << startTimeString << ": ";
	}
	else if ((long)task.getStartDateTime() <= (long)referenceTime ||
		(long)task.getEndDateTime() >= (long)referenceTime + SECONDS_DAY) {
		staticOutputStringStream << startDateTimeString << NOTIFICATION_SPANSOVERADAY << std::endl;
		staticOutputStringStream << "        " << endDateTimeString << ": ";
	}
	else {
		staticOutputStringStream << startTimeString << " - " << endTimeString << ": ";
	}

	wrapOutputStringStream << task.getDescription();

	if (task.getLocation() != "") {
		wrapOutputStringStream << "; " << task.getLocation();
	}

	outputString = wrapText(POS_TIMED_DAY, staticOutputStringStream.str(), wrapOutputStringStream.str());

	return outputString;
}

std::string Show::prepareTmlOutput(std::vector<Task> taskVector) {
	std::ostringstream outputStringStream;
	std::string header;
	long startTimeTml = (long)_startDateTime + SECONDS_DAY;
	time_t earliestTime = startTimeTml;
	tm earliestTimetm;
	char earliestTimeString[50];

	for (unsigned int i = 0; i < taskVector.size(); i++) {

		if (taskVector[i].getCode() == TASKTYPECODE_DEADLINE &&
			taskVector[i].getEndDateTime() >= startTimeTml && taskVector[i].getEndDateTime() < startTimeTml + SECONDS_DAY) {
			_numDeadlinesTml++;
		}
		else if (taskVector[i].getCode() == TASKTYPECODE_PARTIALTIMED &&
			taskVector[i].getStartDateTime() >= startTimeTml && taskVector[i].getStartDateTime() < startTimeTml + SECONDS_DAY) {
			_numSchedulesTml++;
			if (_numSchedulesTml == 1) {
				earliestTime = taskVector[i].getStartDateTime();
			}
		}
		else if (taskVector[i].getCode() == TASKTYPECODE_TIMED &&
			taskVector[i].getStartDateTime() < startTimeTml && taskVector[i].getEndDateTime() >= startTimeTml) {
			_numSchedulesTml++;
			if (_numSchedulesTml == 1) {
				earliestTime = startTimeTml;
			}
		}
		else if (taskVector[i].getCode() == TASKTYPECODE_TIMED &&
			taskVector[i].getStartDateTime() >= startTimeTml && taskVector[i].getStartDateTime() < startTimeTml + SECONDS_DAY) {
			_numSchedulesTml++;
			if (_numSchedulesTml == 1) {
				earliestTime = taskVector[i].getStartDateTime();
			}
		}
	}


	localtime_s(&earliestTimetm, &earliestTime);
	strftime(earliestTimeString, 50, "%I:%M%p", &earliestTimetm);

	header = prepareHeader(HEADER_TOMMORROW);
	outputStringStream << header;
	outputStringStream << FOOTER_YOU_HAVE << _numDeadlinesTml << FOOTER_DEADLINES_AND << _numSchedulesTml << FOOTER_EVENTS_TML << std::endl;

	if (_numSchedulesTml != 0) {
		outputStringStream << FOOTER_YOUR_EVENT_STARTS << earliestTimeString << std::endl;
	}

	return outputStringStream.str();
}

void Show::storeDisplayed(void){
	removeDuplicatedTaskIndexes();
	sort(_taskIndexes.begin(), _taskIndexes.end());
	updateDisplayedTask(_TMUsed, _taskIndexes);
}

void Show::removeDuplicatedTaskIndexes(void) {
	for (unsigned int i = 0; i < _taskIndexes.size(); i++) {
		for (unsigned int j = i + 1; j < _taskIndexes.size(); j++) {
			if (_taskIndexes[i] == _taskIndexes[j]) {
				std::vector<int>::iterator iter = _taskIndexes.begin() + j;
				_taskIndexes.erase(iter);
			}
		}
	}
}
