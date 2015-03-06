#include "TextManipulator.h"

TextManipulator::TextManipulator(std::string fileName) : Manipulator(fileName) {
}

TextManipulator::~TextManipulator(void) {
}

void TextManipulator::write(std::vector<Task> taskVector) {
	std::ofstream outFile;

	outFile.open(_fileName, std::ios::trunc);

	for (unsigned int i = 0; i < taskVector.size(); i++) {
		outFile << taskVector[i].prepareLine() << std::endl;
	}

	outFile.close();
}

void TextManipulator::append(Task task) {
	std::ofstream outFile;

	outFile.open(_fileName, std::ios::app);

	outFile << task.prepareLine() << std::endl;

	outFile.close();
}

std::vector<Task> TextManipulator::read(void){
	std::string sentence;
	std::ifstream inFile;
	std::vector<Task> taskVector;
	int taskIndex = 0;

	inFile.open(_fileName);

	try {
		while (getline(inFile, sentence)) {
			Task task(taskIndex, sentence);
			taskVector.push_back(task);
			taskIndex++;
		}
	}
	catch (std::exception& exception) {
		std::ofstream logFile;

		logFile.open("ActivityLog.txt", std::ios_base::out | std::ios_base::app);
		logFile << exception.what() << std::endl;
		logFile << "ERROR OCCURRED AT INDEX (" << taskIndex << ")" << std::endl;
		logFile.close();

		throw;
	}

	inFile.close();

	return taskVector;
}

void TextManipulator::sort() {
	std::vector<Task> taskVector;

	taskVector = read();
	unsigned int i = 0;
	while (i < taskVector.size()) {
		if (taskVector[i].getCode() == TASKTYPECODE_INVALID) {
			taskVector.erase(taskVector.begin() + i);
		}
		else {
			i++;
		}
	}

	if (!taskVector.empty()) {
		std::stable_sort(taskVector.begin(), taskVector.end(), compareTime);
		write(taskVector);
	}
}

bool TextManipulator::compareTime(Task task1, Task task2) {
	if (assignFirstTimePriority(task1) < assignFirstTimePriority(task2)) {
		return true;
	}
	else if (assignFirstTimePriority(task1) > assignFirstTimePriority(task2)) {
		return false;
	}
	else if (task1.getCode() == TASKTYPECODE_TIMED && task2.getCode() == TASKTYPECODE_TIMED) {
		return assignSecondTimePriority(task1) < assignSecondTimePriority(task2);
	}
	else {
		return false;
	}
}

long TextManipulator::assignFirstTimePriority(Task task) {
	if (task.getCode() == TASKTYPECODE_DEADLINE) {
		return (long)task.getEndDateTime();
	}
	else {
		return (long)task.getStartDateTime();
	}
}

long TextManipulator::assignSecondTimePriority(Task task) {
	return (long)task.getEndDateTime();
}
