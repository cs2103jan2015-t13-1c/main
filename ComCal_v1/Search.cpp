#include "pch.h"
#include "Search.h"

//Search task type strings:
const std::string TYPE_TODO = "todo";
const std::string TYPE_DONE = "done";

//Parentheses strings:
const std::string PARENTHESIS_OPEN = "{";
const std::string PARENTHESIS_CLOSE = "}";

//Time in seconds int:
const int SECONDS_DAY = 86400;

//Feedback message strings:
const std::string NO_RESULTS = "Your search returned no results.\n";
const std::string HEADER_RESULTS = "Your search returned the following results:\n";

//Time range connector keyword string:
const std::string TIMERANGEKEYWORD = " to ";

Search::Search(Manipulator* todoTMPtr, Manipulator* doneTMPtr) : Command(todoTMPtr, doneTMPtr) {
	_timeRangeKeywords.push_back(TIMERANGEKEYWORD);
}


Search::~Search(void) {
}

void Search::process(std::string userInput)	{
	std::string inputChecker;
	std::stringstream inputSS;
	inputSS << userInput;
	if (!(inputSS >> inputChecker)) {
		throw exceptionInputMissingSearchParams;
	}

	for (unsigned int i = 0; i < userInput.size(); i++) {
		char c = userInput[i];
		userInput[i] = tolower(c);
	}

	std::string type;
	std::stringstream ss;
	ss << userInput;
	ss >> type;
	std::string remainingParams;
	if (type == TYPE_TODO || type == TYPE_DONE) {
		if (type == TYPE_TODO) {
			_tMPtr = _todoTMPtr;
		}
		else if (type == TYPE_DONE) {
			_tMPtr = _doneTMPtr;
		}
		getline(ss, remainingParams);
	}
	else {
		_tMPtr = _todoTMPtr;
		remainingParams = userInput;
	}

	std::vector<std::string> searchClausesStrings;
	int level = 0;
	int pos;
	do {
		int openPos;
		int closePos;
		openPos = remainingParams.find(PARENTHESIS_OPEN);
		closePos = remainingParams.find(PARENTHESIS_CLOSE);

		if (openPos != std::string::npos && closePos != std::string::npos) {
			if (openPos < closePos) {
				pos = openPos;
				level++;
			}
			else {
				pos = closePos;
				level--;
			}
		}
		else if (openPos != std::string::npos) {
			pos = openPos;
			level++;
		}
		else if (closePos != std::string::npos) {
			pos = closePos;
			level--;
		}
		else {
			pos = std::string::npos;
		}

		if (level > 1) {
			throw exceptionInputSearchExceedPermittedNesting;
		}
		if (level < 0) {
			throw exceptionInputInvalidSearchParenthesesMatching;
		}

		std::string clauseString;
		std::string clauseStringChecker;
		if (pos == std::string::npos) {
			clauseString = remainingParams;
			clauseStringChecker = remainingParams;
		}
		else {
			clauseString = remainingParams.substr(0, pos);
			clauseStringChecker = remainingParams.substr(0, pos);
		}
		std::stringstream clauseStringSS;
		clauseStringSS << clauseStringChecker;
		if (clauseStringSS >> clauseStringChecker) {
			searchClausesStrings.push_back(clauseString);
		}

		remainingParams = remainingParams.substr(pos + 1);
	} while (pos != std::string::npos);

	if (level > 0) {
		throw exceptionInputInvalidSearchParenthesesMatching;
	}

	for (unsigned int i = 0; i < searchClausesStrings.size(); i++) {
		SearchClause searchClause(searchClausesStrings[i]);
		_searchClauses.push_back(searchClause);
	}
}

std::string Search::prepareFeedback(void) {
	std::string feedback;
	std::string tasksDisplay;

	std::vector<Task> taskVector;
	taskVector = _tMPtr->read();

	if (_taskIndexes.empty()) {
		feedback = NO_RESULTS;
	}
	else {
		feedback = HEADER_RESULTS;
		for (unsigned int i = 0; i < _taskIndexes.size(); i++) {
			Task task = taskVector[_taskIndexes[i]];
			tasksDisplay = prepareTaskDisplayOneLine(task);
			feedback += tasksDisplay;
		}
	}

	return feedback;
}

std::string Search::executeInput(std::string inputString) {
	std::string feedbackString;

	process(inputString);

	_tMPtr->sort();

	std::vector<Task> taskVector;
	taskVector = _tMPtr->read();
	for (unsigned int i = 0; i < taskVector.size(); i++) {
		_taskIndexes.push_back(i);
	}
	std::vector<int> excludeClauseTaskIndexes;
	bool isFirst = true;
	for (unsigned int i = 0; i < _searchClauses.size(); i++) {
		if (!_searchClauses[i].getSearchAttributes().empty()) {
			std::vector<int> processedClauseTaskIndexes;
			processedClauseTaskIndexes = executeClause(_searchClauses[i]);

			Condition condition;
			if (i == 0) {
				condition = NIL;
			}
			else {
				condition = _searchClauses[i - 1].getNestCondition();
			}

			switch (condition) {
			case NIL:
				_taskIndexes = processedClauseTaskIndexes;
				isFirst = false;
			case AND:
				if (isFirst) {
					_taskIndexes = processedClauseTaskIndexes;
					isFirst = false;
				}
				else if (!_taskIndexes.empty()) {
					std::vector<int> intermediateClauseTaskIndexes;
					for (unsigned int j = 0; j < processedClauseTaskIndexes.size(); j++) {
						for (unsigned int k = 0; k < _taskIndexes.size() && processedClauseTaskIndexes[j] >= _taskIndexes[k]; k++) {
							if (_taskIndexes[k] == processedClauseTaskIndexes[j]) {
								intermediateClauseTaskIndexes.push_back(processedClauseTaskIndexes[j]);
							}
						}
					}
					_taskIndexes = intermediateClauseTaskIndexes;
				}
				break;
			case OR:
				if (isFirst) {
					_taskIndexes = processedClauseTaskIndexes;
					isFirst = false;
				}
				else {
					for (unsigned int j = 0; j < processedClauseTaskIndexes.size(); j++) {
						bool isFound = false;
						unsigned int k = 0;
						while (k < _taskIndexes.size() && processedClauseTaskIndexes[j] >= _taskIndexes[k]) {
							if (_taskIndexes[k] == processedClauseTaskIndexes[j]) {
								isFound = true;
							}
							k++;
						}
						if (!isFound) {
							_taskIndexes.insert(_taskIndexes.begin() + k, processedClauseTaskIndexes[j]);
						}
					}
				}
				break;
			case EXCLUDE:
				for (unsigned int j = 0; j < processedClauseTaskIndexes.size(); j++) {
					excludeClauseTaskIndexes.push_back(processedClauseTaskIndexes[j]);
				}
				break;
			}
		}
	}

	if (!excludeClauseTaskIndexes.empty()) {
		for (unsigned int i = 0; i < excludeClauseTaskIndexes.size(); i++) {
			for (unsigned int j = 0; j < _taskIndexes.size() && excludeClauseTaskIndexes[i] >= _taskIndexes[j]; j++) {
				if (_taskIndexes[j] == excludeClauseTaskIndexes[i]) {
					_taskIndexes.erase(_taskIndexes.begin() + j);
				}
			}
		}
	}

	updateDisplayedTask(_tMPtr, _taskIndexes);

	feedbackString = prepareFeedback();

	return feedbackString;
}

std::vector<int> Search::executeClause(SearchClause searchClause) {
	std::vector<std::string> searchAttributes = searchClause.getSearchAttributes();
	std::vector<std::string> searchContents = searchClause.getSearchContents();
	std::vector<Condition> searchConditions = searchClause.getConditions();

	std::vector<std::vector<int>> clauseTaskIndexes;

	std::vector<Task> taskVector;
	taskVector = _tMPtr->read();
	for (unsigned int i = 0; i < searchAttributes.size(); i++) {
		std::vector<int> conditionTaskIndexes;
		for (unsigned int j = 0; j < taskVector.size(); j++) {
			if (searchAttributes[i] == GENERAL) {
				std::string searchDescriptionString = taskVector[j].getDescription();
				std::string searchLocationString = taskVector[j].getLocation();

				for (unsigned int k = 0; k < searchDescriptionString.size(); k++) {
					char c = searchDescriptionString[k];
					searchDescriptionString[k] = tolower(c);
				}
				for (unsigned int k = 0; k < searchLocationString.size(); k++) {
					char c = searchLocationString[k];
					searchLocationString[k] = tolower(c);
				}

				if (searchDescriptionString.find(searchContents[i]) != std::string::npos || searchLocationString.find(searchContents[i]) != std::string::npos) {
					conditionTaskIndexes.push_back(j);
				}
			}
			else if (searchAttributes[i] == DESCRIPTION) {
				std::string searchString = taskVector[j].getDescription();
				for (unsigned int k = 0; k < searchString.size(); k++) {
					char c = searchString[k];
					searchString[k] = tolower(c);
				}
				if (searchString.find(searchContents[i]) != std::string::npos) {
					conditionTaskIndexes.push_back(j);
				}
			}
			else if (searchAttributes[i] == STARTDATE || searchAttributes[i] == ENDDATE) {
				time_t startDateRangeTime;
				time_t endDateRangeTime;
				processSearchDateRange(searchContents[i], startDateRangeTime, endDateRangeTime);

				time_t taskTime;
				if (searchAttributes[i] == STARTDATE) {
					taskTime = taskVector[j].getStartDateTime();
				}
				else {
					taskTime = taskVector[j].getEndDateTime();
				}
				if (taskTime >= startDateRangeTime && taskTime <= endDateRangeTime) {
					conditionTaskIndexes.push_back(j);
				}
			}
			else if (searchAttributes[i] == LOCATION) {
				std::string searchString = taskVector[j].getLocation();
				for (unsigned int k = 0; k < searchString.size(); k++) {
					char c = searchString[k];
					searchString[k] = tolower(c);
				}
				if (searchString.find(searchContents[i]) != std::string::npos) {
					conditionTaskIndexes.push_back(j);
				}
			}
		}
		clauseTaskIndexes.push_back(conditionTaskIndexes);
	}

	std::vector<int> processedClauseTaskIndexes;
	for (unsigned int i = 0; i < taskVector.size(); i++) {
		processedClauseTaskIndexes.push_back(i);
	}
	std::vector<int> excludeClauseTaskIndexes;
	bool isFirst = true;
	for (unsigned int i = 0; i < clauseTaskIndexes.size(); i++) {
		switch (searchConditions[i]) {
		case AND:
			if (isFirst) {
				processedClauseTaskIndexes = clauseTaskIndexes[i];
				isFirst = false;
			}
			else {
				std::vector<int> intermediateClauseTaskIndexes;
				for (unsigned int j = 0; j < clauseTaskIndexes[i].size(); j++) {
					for (unsigned int k = 0; k < processedClauseTaskIndexes.size() && clauseTaskIndexes[i][j] >= processedClauseTaskIndexes[k]; k++) {
						if (processedClauseTaskIndexes[k] == clauseTaskIndexes[i][j]) {
							intermediateClauseTaskIndexes.push_back(clauseTaskIndexes[i][j]);
						}
					}
				}
				processedClauseTaskIndexes = intermediateClauseTaskIndexes;
			}
			break;
		case OR:
			if (isFirst) {
				processedClauseTaskIndexes = clauseTaskIndexes[i];
				isFirst = false;
			}
			else {
				for (unsigned int j = 0; j < clauseTaskIndexes[i].size(); j++) {
					bool isFound = false;
					unsigned int k = 0;
					while (k < processedClauseTaskIndexes.size() && clauseTaskIndexes[i][j] >= processedClauseTaskIndexes[k]) {
						if (processedClauseTaskIndexes[k] == clauseTaskIndexes[i][j]) {
							isFound = true;
						}
						k++;
					}
					if (!isFound) {
						processedClauseTaskIndexes.insert(processedClauseTaskIndexes.begin() + k, clauseTaskIndexes[i][j]);
					}
				}
			}
			break;
		case EXCLUDE:
			for (unsigned int j = 0; j < clauseTaskIndexes[i].size(); j++) {
				excludeClauseTaskIndexes.push_back(clauseTaskIndexes[i][j]);
			}
			break;
		}
	}

	if (!excludeClauseTaskIndexes.empty()) {
		for (unsigned int i = 0; i < excludeClauseTaskIndexes.size(); i++) {
			for (unsigned int j = 0; j < processedClauseTaskIndexes.size() && excludeClauseTaskIndexes[i] >= processedClauseTaskIndexes[j]; j++) {
				if (processedClauseTaskIndexes[j] == excludeClauseTaskIndexes[i]) {
					processedClauseTaskIndexes.erase(processedClauseTaskIndexes.begin() + j);
				}
			}
		}
	}

	return processedClauseTaskIndexes;
}

void Search::processSearchDateRange(std::string input, time_t& startDateRangeTime, time_t& endDateRangeTime) {
	std::string startDateRangeString = input;

	std::vector<std::vector<std::string>> endDateRangeString;
	endDateRangeString = extractParamsForKeywords(startDateRangeString, _timeRangeKeywords);
	startDateRangeTime = processTime(startDateRangeString, START, WEEK_PERMITTED);
	if (endDateRangeString[0].empty()) {
		if (startDateRangeString.find("week") != std::string::npos) {
			endDateRangeTime = startDateRangeTime + (SECONDS_DAY * 7);
		}
		else {
			endDateRangeTime = startDateRangeTime + SECONDS_DAY;
		}
	}
	else {
		if (endDateRangeString.size() > 1) {
			throw exceptionInputRepeatTimeRangeKeywords;
		}
		if (endDateRangeString[0][0].find("week") != std::string::npos) {
			endDateRangeTime = processTime(endDateRangeString[0][0], START, WEEK_PERMITTED) + (SECONDS_DAY * 7);
		}
		else {
			endDateRangeTime = processTime(endDateRangeString[0][0], END, WEEK_PERMITTED);
		}
		if (endDateRangeTime < startDateRangeTime) {
			throw exceptionInputStartLaterThanEndTime;
		}
	}
}

