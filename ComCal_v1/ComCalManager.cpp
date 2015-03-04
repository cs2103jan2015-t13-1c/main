#include "pch.h"
#include "ComCalManager.h"

ComCalManager::ComCalManager(){
	std::string todoFileName;
	std::string doneFileName;

	//if (numOfArg == NOFILENAMEENTERED) {
		todoFileName = FILENAME_TODODEFAULT;
		doneFileName = FILENAME_DONEDEFAULT;
	/*}
	else if (numOfArg == TODOFILENAMEENTERED) {
		todoFileName = argVector[1];
		doneFileName = FILENAME_DONEDEFAULT;
	}
	else {
		todoFileName = argVector[1];
		doneFileName = argVector[2];
	}*/

	Manipulator* todoTMPtr;
	Manipulator* doneTMPtr;
	Logic* logPtr;

	todoTMPtr = new TextManipulator(todoFileName);
	doneTMPtr = new TextManipulator(doneFileName);

	prestartCheck(todoTMPtr);
	prestartCheck(doneTMPtr);
	printWelcomeMessage(todoFileName, doneFileName);

	logPtr = new Logic(todoTMPtr, doneTMPtr);

	run(logPtr);

	delete todoTMPtr;
	delete doneTMPtr;
	delete logPtr;

	//system("pause");

	return;
}

ComCalManager::~ComCalManager(){
}

Platform::String^ ComCalManager::deduceCommand(Platform::String^){

	Platform::String^ feedBackMessage;

	return feedBackMessage;
}

void ComCalManager::run(Logic* logPtr) {
	_logPtr = logPtr;
	std::string userInput;
	std::string output;
	bool isTerminate;

	do {
		try {
			userInput = read();
			isTerminate = _logPtr->executeCommand(userInput, output);
			printOutput(output);
		}
		catch (std::exception& exception) {
			std::cout << exception.what() << std::endl << std::endl;
			if (exception.what() == TASKERROR_INVALIDSTRINGFORMAT || exception.what() == TASKERROR_INVALIDTYPECODE || exception.what() == TASKERROR_INCORRECTEMPTYATTRIBUTESYMBOL || exception.what() == TASKERROR_NODESCRIPTION || exception.what() == TASKERROR_INVALIDDATETIME || exception.what() == TASKERROR_INVALIDDATE || exception.what() == TASKERROR_INVALIDTIME || exception.what() == TASKERROR_INCORRECTTYPECODE || exception.what() == TASKERROR_MDAYOUTOFRANGELEAPFEB || exception.what() == TASKERROR_MDAYOUTOFRANGENONLEAPFEB || exception.what() == TASKERROR_MDAYOUTOFRANGE30DAYMONTH || exception.what() == TASKERROR_MDAYOUTOFRANGE31DAYMONTH || exception.what() == TASKERROR_MONTHOUTOFRANGE || exception.what() == TASKERROR_HOUROUTOFRANGE || exception.what() == TASKERROR_MINOUTOFRANGE) {
				std::cout << "TEXT FILE IS CORRUPTED. PLEASE CHECK ActivityLog.txt FOR DETAILS." << std::endl;
				isTerminate = true;
			}
			else {
				isTerminate = false;
			}
		}
	} while (!isTerminate);

	return;
}

std::string ComCalManager::read(void) {
	std::string userInput;

	getline(std::cin, userInput);

	if (userInput == "") {
		throw exceptionInputNoCommand;
	}

	return userInput;
}

void ComCalManager::printOutput(std::string output) {
	std::cout << output << std::endl;
}

void ComCalManager::prestartCheck(Manipulator* tmPtr) {
	std::ofstream logFile;
	time_t timeNow;
	tm timeNowtm;
	time(&timeNow);
	char timeString[50];

	localtime_s(&timeNowtm, &timeNow);
	strftime(timeString, 50, "%a, %d %b %Y, %I:%M%p", &timeNowtm);

	logFile.open(FILENAME_LOGDEFAULT, std::ios::app);
	logFile << "\nPre-start Check for " << tmPtr->getFileName() << " started on: " << timeString << std::endl;

	try {
		tmPtr->sort();
		logFile << "Pre-start Check completed with no error\n." << std::endl;
		logFile.close();
	}
	catch (std::exception& exception) {
		std::cout << "PRE-START CHECK FAILED. " << tmPtr->getFileName() << " IS CORRUPTED. PLEASE CHECK ActivityLog.txt FOR DETAILS." << std::endl;
		logFile << "PRE-START CHECK FAILED. SEE ABOVE FOR DETAILS.\n" << std::endl;

		logFile.close();

		//system("pause");
		exit(0);
	}
}

void ComCalManager::printWelcomeMessage(std::string todoFileName, std::string doneFileName) {
	char buffer[255];
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
