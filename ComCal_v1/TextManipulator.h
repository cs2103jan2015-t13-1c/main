#pragma once

/**********************************************************************************************************
Name: TextManipulator
Type: Child Class of Manipulator
Purpose: Responsible for interacting, manipulating and maintaining the .txt files database - which includes
appending and writing contents, reading contents from, and sorting contents in the files.
The sorting order is as follows:
1) All floating tasks on top
2) All other tasks sorted by start date/time then end date/time for timed, start date/time for
partial-timed, and deadline date/time for deadline tasks.
Preconditions: Assumes input task object is correctly furnished with the correct task attributes.
Postconditions: append, write, read and sort APIs perform its desired functions:
(1) append - Appends a task line string to the end of the .txt file and saves it.
(2) write - Overwrites contents in the .txt file with task line strings of the input vector of task objects and saves it.
(3) read - Read contents from the .txt file and returns them as a vector of task objects.
(4) sort - Sort contents in the .txt file by the sorting order above.
**********************************************************************************************************/

#include "Manipulator.h"

class TextManipulator : public Manipulator
{
private:
	static bool compareTime(Task, Task);
	static long assignFirstTimePriority(Task);
	static long assignSecondTimePriority(Task);

public:
	TextManipulator(std::string fileName);
	~TextManipulator(void);

	void append(Task);
	void write(std::vector<Task>);
	std::vector<Task> read(void);
	void sort();
};

