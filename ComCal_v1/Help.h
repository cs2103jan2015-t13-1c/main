#pragma once
#include "Command.h"

class Help : public Command {
public:
	Help(Manipulator*, Manipulator*);
	~Help(void);

	/*
	Name:executeInput
	Type: Method
	Purpose: Executes input received - prepares string of help sheet based on specified command, and returns this
	string.
	*/
	std::string executeInput(std::string);
};
