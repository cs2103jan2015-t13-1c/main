#include "ComCalManager.h"
#include <msclr\marshal_cppstd.h>
#include <msclr\marshal.h>

#include "Functions.h"

ComCalManager::ComCalManager() {
	_tasks = new std::vector<Task*>();
}

ComCalManager::~ComCalManager() {
	delete _tasks;
}

System::String^ ComCalManager::deduceCommand(System::String^ userInputString) {
	System::String^ feedBackMessage;

	std::string userInput = convertStrTostr(userInputString);

	int space = userInput.find(" ");
	std::string function = toLowerCase(userInput.substr(0, space));
	std::string argument = userInput.substr(space + 1, userInput.length() - space - 1);

	if (function.compare("add") == 0) {
		feedBackMessage = convertstrToStr(addMainCom(argument));
	}

	return feedBackMessage;
}

// Converts System::String^ into std::string
std::string ComCalManager::convertStrTostr(System::String^ userInput) {
	std::string strInput;

	strInput = msclr::interop::marshal_as<std::string>(userInput);

	return strInput;
}

// Converts std::string into System::String^
System::String^ ComCalManager::convertstrToStr(std::string userInput) {
	System::String^ strInput;

	strInput = msclr::interop::marshal_as<System::String^>(userInput);

	return strInput;
}

// ----------------------------------------------------------------
// NONE OF THE FUNCTION BELOWS ARE IMPLEMENTED YET!!!
// ----------------------------------------------------------------

bool ComCalManager::isDateValid(std::string) {
	return true;
}

bool ComCalManager::isTimeValid(std::string) {
	return true;
}

bool ComCalManager::isDayValid(std::string) {
	return true;
}

bool ComCalManager::isClashing(std::string) {
	return true;
}

bool ComCalManager::isIndexValid(std::string) {
	return true;
}

std::vector<std::string> ComCalManager::readTextFileIntoVec(std::string) { //the argument passed should be the name of the text file
	std::vector<std::string> tasks;
	return tasks;
}

void ComCalManager::readVecIntoTextFile(std::vector<std::string>, std::string) { //the 2nd argument passed is name of textFile
}

std::string ComCalManager::addMainCom(std::string argument) {

	int d = argument.find(".d");
	int s = argument.find(".s");
	int e = argument.find(".e");
	int l = argument.find(".l");

	// TODO Assuming the user enters all of .d, .s, .e and .l for now.
	// Have to correct this later on
	std::string description = argument.substr(d + 3, s - d - 4);
	std::string startDate = argument.substr(s + 3, e - s - 4);
	std::string endDate = argument.substr(e + 3, l - e - 4);
	std::string location = argument.substr(l + 3, argument.length() - l - 3);

	Task* newTask = new Task(description, location, new Date(startDate), new Date(endDate));
	_tasks->push_back(newTask);

	return ("Added " + (*_tasks)[_tasks->size() - 1]->getDescription());
}

std::string ComCalManager::showMainCom(std::string) {
	return "";
}

std::string ComCalManager::deleteMainCom(std::string) {
	return "";
}

std::string ComCalManager::editMainCom(std::string) {
	return "";
}

std::string ComCalManager::undoMainCom(std::string) {
	return "";
}

std::string ComCalManager::redoMainCom(std::string) {
	return "";
}

std::string ComCalManager::searchMainCom(std::string) {
	return "";
}

bool ComCalManager::isAddFormatValid(std::string) {
	return true;
}

bool ComCalManager::isShowFormatValid(std::string) {
	return true;
}

bool ComCalManager::isDeleteFormatValid(std::string) {
	return true;
}

bool ComCalManager::isEditFormatValid(std::string) {
	return true;
}