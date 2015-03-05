#pragma once

#include "Task.h"

#include <vector>
#include <fstream>
#include <algorithm> 
#include <ctime>

class Manipulator
{
protected:
	std::string _fileName;

public:
	Manipulator(std::string fileName);
	~Manipulator(void);

	std::string getFileName(void);

	virtual void append(Task);
	virtual void write(std::vector<Task>);
	virtual std::vector<Task> read(void);
	virtual void sort();
};
