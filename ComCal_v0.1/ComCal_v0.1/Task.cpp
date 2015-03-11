#include "Task.h"

Task::Task(std::string description, std::string location, int startDay, int startMonth, int startYear, int startTime, int endDay, int endMonth, int endYear, int endTime) {
	_description = description;
	_location = location;
	_startDate = new Date(startDay, startMonth, startYear, startTime);
	_endDate = new Date(endDay, endMonth, endYear, endTime);
}

Task::Task(std::string description, std::string location, Date* startDate, Date* endDate) {
	_description = description;
	_location = location;
	_startDate = startDate;
	_endDate = endDate;
}

Task::~Task() {
	if (_startDate != NULL) {
		delete _startDate;
	}

	if (_endDate != NULL) {
		delete _endDate;
	}
}

std::string Task::getDescription() {
	return _description;
}