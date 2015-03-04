/***********************************************************************************************************************************************
This Main.cpp file contains the main function, which is the entry point of the ComCal program, and serves as the program's initialiser.
ComCal is a CLI input coupled with GUI display program that enables users to manage their tasks more efficiently and effectively.
It's simple database of .txt files enables advanced users to more easily and conveniently edit their tasks directly in the database.
ComCal has the following task management functionalities:
1) (Create) add <task>: Enables users to add a task to their task list in the .txt files.
2) (Retrieve) show <type> <date/time>: Enables users to display tasks from the .txt files tasks list based on <type> and <date/time> specified.
3) (Update) edit <task index> <attribute> <new content>: Enables users to edit an attribute of a task in the .txt files tasks list.
4) (Delete) del <task index>: Enables users to delete a task from the .txt files tasks list.
5) (Done/Undone) done/undo <task index>: Enables users to mark a task from the .txt files tasks list as complete/incomplete.
6) (Undo/Redo) undo/redo: Enables users to undo/redo last action performed/undone.
7) (Search) search <attribute> <content>: Enables user to search for a task from the .txt files tasks list either by wildcard(without specifying any attribute) or by attribute and content specified.
*************************************************************************************************************************************************/

#include "Manipulator.h"
#include "Logic.h"
#include "ComCalManager.h"
#include "Exception.h"

#include <string>
#include <iostream>
#include <fstream>

//Default file names:
const std::string FILENAME_TODODEFAULT = "TAC_todo.txt";
const std::string FILENAME_ARCHIVEDEFAULT = "TAC_archive.txt";
const std::string FILENAME_DONEDEFAULT = "TAC_done.txt";

//Default log file name:
const std::string FILENAME_LOGDEFAULT = "ActivityLog.txt";

//Number of file name arguments:
const int NOFILENAMEENTERED = 1;
const int TODOFILENAMEENTERED = 2;

//Feedback messages:
const std::string MESSAGE_WELCOME = "Welcome to TAC - your friendly Todo Assistant!\n";
const std::string MESSAGE_TODODEFAULTFILENAMECONFIRMATION = "Working on default todo file: " + FILENAME_TODODEFAULT;
const std::string MESSAGE_DONEDEFAULTFILENAMECONFIRMATION = ", and default done file: " + FILENAME_DONEDEFAULT;
const std::string MESSAGE_TODOSPECIFIEDFILENAMECONFIRMATION = "Working on specified todo file: \"%s\"";
const std::string MESSAGE_DONESPECIFIEDFILENAMECONFIRMATION = ", and specified done file: \"%s\"";

char buffer[255];

void main(int numOfArg, char* argVector[]) {
	std::string todoFileName;
	//std::string archiveFileName;
	std::string doneFileName;

	if (numOfArg == NOFILENAMEENTERED) {
		todoFileName = FILENAME_TODODEFAULT;
		doneFileName = FILENAME_DONEDEFAULT;
	}
	else if (numOfArg == TODOFILENAMEENTERED) {
		todoFileName = argVector[1];
		doneFileName = FILENAME_DONEDEFAULT;
	}
	else {
		todoFileName = argVector[1];
		doneFileName = argVector[2];
	}

	Manipulator* todoTMPtr;
	Manipulator* archiveTMPtr;
	Manipulator* doneTMPtr;
	Logic* logPtr;

	todoTMPtr = new TextManipulator(todoFileName);
	//archiveTMPtr = new TextManipulator(archiveFileName);
	doneTMPtr = new TextManipulator(doneFileName);

	prestartCheck(todoTMPtr);
	//prestartCheck(archiveTMPtr);
	prestartCheck(doneTMPtr);
	printWelcomeMessage(todoFileName, doneFileName);

	logPtr = new Logic(todoTMPtr, doneTMPtr);
	ComCalManager CCM();

	CCM.run(logPtr);

	delete todoTMPtr;
	delete doneTMPtr;
	delete logPtr;

	//system("pause");

	return;
}

void printWelcomeMessage(std::string todoFileName, std::string doneFileName) {
	std::cout << MESSAGE_WELCOME;
	std::string output;

	if (todoFileName != FILENAME_TODODEFAULT) {
		sprintf_s(buffer, MESSAGE_TODOSPECIFIEDFILENAMECONFIRMATION.c_str(), todoFileName);
	}
	output = buffer;
	std::cout << "[" << output;

	if (doneFileName != FILENAME_DONEDEFAULT) {
		sprintf_s(buffer, MESSAGE_DONESPECIFIEDFILENAMECONFIRMATION.c_str(), doneFileName);
	}
	output = buffer;
	std::cout << output << "]\n\n";

	return;
}

void prestartCheck(Manipulator* tMPtr) {
	std::ofstream logFile;
	time_t timeNow;
	tm timeNowtm;
	time(&timeNow);
	char timeString[50];

	localtime_s(&timeNowtm, &timeNow);
	strftime(timeString, 50, "%a, %d %b %Y, %I:%M%p", &timeNowtm);

	logFile.open(FILENAME_LOGDEFAULT, std::ios::app);
	logFile << "\nPre-start Check for " << tMPtr->getFileName() << " started on: " << timeString << std::endl;

	try {
		tMPtr->sort();
		logFile << "Pre-start Check completed with no error\n." << std::endl;
		logFile.close();
	}
	catch (std::exception& exception) {
		std::cout << "PRE-START CHECK FAILED. " << tMPtr->getFileName() << " IS CORRUPTED. PLEASE CHECK ActivityLog.txt FOR DETAILS." << std::endl;
		logFile << "PRE-START CHECK FAILED. SEE ABOVE FOR DETAILS.\n" << std::endl;

		logFile.close();

		//system("pause");
		exit(0);
	}
}