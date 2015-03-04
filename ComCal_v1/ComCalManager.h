#pragma once

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
#include "Exception.h"

#include "Windows.h"
#include <string>
#include <iostream>
#include <ctime>

//Default file names constant string declarations:
const std::string FILENAME_TODODEFAULT = "TAC_todo.txt";
const std::string FILENAME_DONEDEFAULT = "TAC_done.txt";

//Default log file name constant string declarations:
const std::string FILENAME_LOGDEFAULT = "ActivityLog.txt";

//Number of file name arguments constant int declarations:
const int NOFILENAMEENTERED = 1;
const int TODOFILENAMEENTERED = 2;

//Welcome messages constant string declarations:
const std::string MESSAGE_WELCOME = "Welcome to TAC - your friendly Todo Assistant!\n";
const std::string MESSAGE_TODODEFAULTFILENAMECONFIRMATION = "Working on default todo file: " + FILENAME_TODODEFAULT;
const std::string MESSAGE_DONEDEFAULTFILENAMECONFIRMATION = ", and default done file: " + FILENAME_DONEDEFAULT;
const std::string MESSAGE_TODOSPECIFIEDFILENAMECONFIRMATION = "Working on specified todo file: \"%s\"";
const std::string MESSAGE_DONESPECIFIEDFILENAMECONFIRMATION = ", and specified done file: \"%s\"";

ref class ComCalManager sealed
{
public:
	ComCalManager();	

	//1) This function will deduce the mainCom and call that specific function
	//2) The String^ here will be converted to a normal c++ string the passed to the mainCom functions
	//3) A String^ class as a message that will be reflected on the feedback.
	Platform::String^ deduceCommand(Platform::String^); 

private:
	Logic* _logPtr;

	void prestartCheck(Manipulator*);
	void printWelcomeMessage(std::string, std::string);
	void run(Logic*);
	std::string read();
	void printOutput(std::string);

	std::vector<int> indexInUse; //used to store all the index in use
	~ComCalManager();

	//------------------------------------Standalone Functions------------------------------------------
	//1) Standalone functions that might be useful to other mainComs
	//   probably some bool function to check some stuff
	bool isDateValid(std::string);
	bool isTimeValid(std::string);
	bool isDayValid(std::string);
	bool isClashing(std::string);
	bool isIndexValid(std::string);

	std::vector<std::string> readTextFileIntoVec(std::string); //the argument passed should be the name of the text file
	void readVecIntoTextFile(std::vector<std::string>, std::string); //the 2nd argument passed is name of textFile


	//------------------------------------Main Functions------------------------------------------------
	//1) All the main functions with string should return to the UI a message for the feedback history
	//   so that it can be binded to the "FeedBack" textblock in the UI, a simple 'cout' from the function
	//   class itself isn't possible to my knowledge
	//2) The public deduceCommand fx will pass the input string to these main commands below
	//3) The arguments passed in the mainComs will be without the command itself eg. "add stuff" -> "stuff"

	std::string addMainCom(std::string);
	std::string showMainCom(std::string);
	std::string deleteMainCom(std::string);
	std::string editMainCom(std::string);
	std::string undoMainCom(std::string);
	std::string redoMainCom(std::string);
	std::string searchMainCom(std::string);


	//---------------------------------Main Sub-Functions-----------------------------------------------
	//1) Below will be all the sub-functions that will be used by the MainCom functions
	//2) Add whatever function you want but it should only deal with that specific mainCom you want to handle

	//sub-functions for addMainCom
	bool isAddFormatValid(std::string);

	//sub-functions for showMainCom
	bool isShowFormatValid(std::string);

	//sub-functions for deleteMainCom
	bool isDeleteFormatValid(std::string);

	//sub-functions for editMainCom
	bool isEditFormatValid(std::string);

	//sub-functions for undoMainCom

	//sub-functions for redoMainCom

};


