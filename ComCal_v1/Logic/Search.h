#pragma once

/**********************************************************************************************************
Name: Search
Type: Class
Purpose: Child class of Command parent class.
Responsible for executing searching task in tasks database text file.
Its private attributes holds its parameter keywords, the specified task index, attribute codes
and search content for each attribute to be searched.
**********************************************************************************************************/

#include "Command.h"
#include "SearchClause.h"

//Search task type strings:
static const std::string TYPE_TODO = "todo";
static const std::string TYPE_DONE = "done";

//Parentheses strings:
static const std::string PARENTHESIS_OPEN = "{";
static const std::string PARENTHESIS_CLOSE = "}";

//Search feedback message strings:
static const std::string NO_RESULTS = "Your search returned no results.\n";
static const std::string HEADER_RESULTS = "Your search returned the following results:\n";

//Time range connector keyword string:
static const std::string TIMERANGEKEYWORD = " to ";

class Search : public Command {
private:
	/****************************************************************************************************
	Name: _timeRangeKeywords
	Type: Vector of strings attribute
	Purpose: Holds recognised time range keywords
	****************************************************************************************************/
	std::vector<std::string> _timeRangeKeywords;

	/****************************************************************************************************
	Name: _tMPtr
	Type: Manipulator pointer attribute
	Purpose: Holds the Manipulator pointer with the task file to search from.
	****************************************************************************************************/
	Manipulator* _tMPtr;

	/****************************************************************************************************
	Name: _searchClauses
	Type: Vector of SearchClause attribute
	Purpose: Holds SearchClause objects of Search object.
	****************************************************************************************************/
	std::vector<SearchClause> _searchClauses;

	/****************************************************************************************************
	Name: _taskIndexes
	Type: Vector of int attribute
	Purpose: Holds task indexes of search results.
	****************************************************************************************************/
	std::vector<int> _taskIndexes;

	/****************************************************************************************************
	Name: process
	Type: Method
	Purpose: Processes input string to obtain task file to search from and assign Manipulator pointer private
	attribute, and formulate SearchClause objects and push into vector of SearchClause private attribute.
	****************************************************************************************************/
	void process(std::string);

	/****************************************************************************************************
	Name: processSearchDateRange
	Type: Method
	Purpose: Processes input string to obtain search date range, and assigns the start and end time_t values
	to the first and second reference time_t variables passed in.
	****************************************************************************************************/
	void processSearchDateRange(std::string, time_t&, time_t&);

	/****************************************************************************************************
	Name: executeClause
	Type: Method
	Purpose: Executes input search clause and returns vector of int task indexes search results. This method
	is called in executeInput API's for loop iteration of _searchClause private attribute to execute each
	SearchClause.
	****************************************************************************************************/
	std::vector<int> executeClause(SearchClause);

	/****************************************************************************************************
	Name: prepareFeedback
	Type: Method
	Purpose: Prepares feedback of search results with _taskIndexes private attribute.
	****************************************************************************************************/
	std::string prepareFeedback();

public:
	Search(Manipulator*, Manipulator*);
	~Search(void);

	/****************************************************************************************************
	Name: executeInput
	Type: Method
	Purpose: Executes input received - searches specified task file with search statements and conditions,
	and returns feedback string.
	****************************************************************************************************/
	std::string executeInput(std::string);
};
