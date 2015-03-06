#include "Manipulator.h"

Manipulator::Manipulator(std::string fileName) {
	_fileName = fileName;
}

Manipulator::~Manipulator(void) {
}

std::string Manipulator::getFileName(void) {
	return _fileName;
}

void Manipulator::write(std::vector<Task> taskVector) {
}

void Manipulator::append(Task task) {
}

std::vector<Task> Manipulator::read(void){
	std::vector<Task> taskVector;
	return taskVector;
}

void Manipulator::sort() {
}
