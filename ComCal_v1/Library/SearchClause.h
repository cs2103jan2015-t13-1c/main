#pragma once

#include "Exceptions.h"
#include "Task.h"

//Condition keywords string array, size and indexes:
static const int CONDITIONKEYWORDSARRAYSIZE = 3;
static const std::string CONDITIONKEYWORDSARRAY[CONDITIONKEYWORDSARRAYSIZE] = { " and ", " or ", " -- " };
static const int INDEX_AND = 0;
static const int INDEX_OR = 1;
static const int INDEX_EXCLUDE = 2;

//Search keywords string array, size and indexes:
static const int SEARCHKEYWORDSARRAYSIZE = 16;
static const std::string SEARCHKEYWORDSARRAY[SEARCHKEYWORDSARRAYSIZE] = { " .d ", " and.d ", " or.d ", " --.d ", " .s ", " and.s ", " or.s ", " --.s ", " .e ", " and.e ", " or.e ", " --.e ", " .l ", " and.l ", " or.l ", " --.l " };
static const int INDEX_SEARCHDESCRIPTION = 0;
static const int INDEX_SEARCHANDDESCRIPTION = 1;
static const int INDEX_SEARCHORDESCRIPTION = 2;
static const int INDEX_SEARCHEXCLUDEDESCRIPTION = 3;
static const int INDEX_SEARCHSTARTDATE = 4;
static const int INDEX_SEARCHANDSTARTDATE = 5;
static const int INDEX_SEARCHORSTARTDATE = 6;
static const int INDEX_SEARCHEXCLUDESTARTDATE = 7;
static const int INDEX_SEARCHENDDATE = 8;
static const int INDEX_SEARCHANDENDDATE = 9;
static const int INDEX_SEARCHORENDDATE = 10;
static const int INDEX_SEARCHEXCLUDEENDDATE = 11;
static const int INDEX_SEARCHLOCATION = 12;
static const int INDEX_SEARCHANDLOCATION = 13;
static const int INDEX_SEARCHORLOCATION = 14;
static const int INDEX_SEARCHEXCLUDELOCATION = 15;

enum Condition {
	NIL,
	AND,
	OR,
	EXCLUDE
};

class SearchClause {
private:
	/****************************************************************************************************
	Name: _searchKeywords
	Type: Vector of strings attribute
	Purpose: Holds recognised search attribute keywords (see SearchClause.cpp for constant string array declarations).
	****************************************************************************************************/
	std::vector<std::string> _searchKeywords;

	/****************************************************************************************************
	Name: _conditionKeywords
	Type: Vector of strings attribute
	Purpose: Holds recognised condition keywords (see SearchClause.cpp for constant string array declarations).
	****************************************************************************************************/
	std::vector<std::string> _conditionKeywords;

	/****************************************************************************************************
	Name: _searchKeywords
	Type: Vector of strings attribute
	Purpose: Holds search attributes specified in input search clause string.
	****************************************************************************************************/
	std::vector<std::string> _searchAttributes;

	/****************************************************************************************************
	Name: _searchContents
	Type: Vector of strings attribute
	Purpose: Holds search contents specified in input search clause string, each element relates to its respective
	index element in _searchAttributes vector of strings above.
	****************************************************************************************************/
	std::vector<std::string> _searchContents;

	/****************************************************************************************************
	Name: _searchCondition
	Type: Vector of Conditions attribute
	Purpose: Holds search conditions specified in input search clause string, each element relates to its respective
	index element in _searchAttributes vector of strings above.
	****************************************************************************************************/
	std::vector<Condition> _searchConditions;

	/****************************************************************************************************
	Name: _nestCondition
	Type: Condition attribute
	Purpose: Holds search condition for the following nested search statement.
	****************************************************************************************************/
	Condition _nestCondition;

	/************************************************************************************************************
	Name: extractParamsForKeywords
	Type: Method
	Purpose: Processes input string with given vector of keywords and extracts params for each keyword,
	Returns the params extracted as a vector of vector of strings, with the params extracted for each keyword
	as a vector of strings assigned to its corresponding index element
	eg. If element 0 of keyword vector is " `from ", then element 0 of return vector is vector of strings of
	all parameters for " `from " keyword.
	*************************************************************************************************************/
	std::vector<std::vector<std::string>> extractParamsForKeywords(std::string&, std::vector<std::string>);

	/************************************************************************************************************
	Name: processCondition
	Type: Method
	Purpose: Processes search condition based on the index int and attribute index int passed in, and pushes
	the processed Condition into _searchConditions vector of Conditions private attributes. This method is called
	to process the first condition of each search attribute in the search clause.
	*************************************************************************************************************/
	void processCondition(int, int);

	/************************************************************************************************************
	Name: processConditionKeywordsAndParams
	Type: Method
	Purpose: Processes search condition keywords and params based on input vector of vector of strings of condition
	keywords and associated params, and attribute string. This method is called to process the middle conditions of
	each search attribute in the search clause.
	*************************************************************************************************************/
	void processConditionKeywordsAndParams(std::vector<std::vector<std::string>>, std::string);

public:
	/************************************************************************************************************
	Name: SearchClause
	Type: Constructor
	Purpose: Processes input search clause string and accordingly furnishes private attributes.
	*************************************************************************************************************/
	SearchClause(std::string);

	~SearchClause(void);

	/************************************************************************************************************
	Name: getSearchAttributes
	Type: Method
	Purpose: Returns search attributes of the SearchClause object.
	*************************************************************************************************************/
	std::vector<std::string> getSearchAttributes(void);

	/************************************************************************************************************
	Name: getSearchContents
	Type: Method
	Purpose: Returns search contents of the SearchClause object.
	*************************************************************************************************************/
	std::vector<std::string> getSearchContents(void);

	/************************************************************************************************************
	Name: getSearchConditions
	Type: Method
	Purpose: Returns search conditions of the SearchClause object.
	*************************************************************************************************************/
	std::vector<Condition> getConditions(void);

	/************************************************************************************************************
	Name: getNestCondition
	Type: Method
	Purpose: Returns nest condition of the SearchClause object.
	*************************************************************************************************************/
	Condition getNestCondition(void);
};
