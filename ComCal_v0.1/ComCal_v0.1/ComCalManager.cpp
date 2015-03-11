#include "ComCalManager.h"

ComCalManager::ComCalManager(){
}

ComCalManager::~ComCalManager(){
}

System::String^ ComCalManager::deduceCommand(System::String^){

	System::String^ feedBackMessage;

	return feedBackMessage;
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

std::string ComCalManager::addMainCom(std::string) {
	return "";
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