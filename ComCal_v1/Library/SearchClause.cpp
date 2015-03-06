#include "SearchClause.h"

SearchClause::SearchClause(std::string searchClauseString) {
	_searchKeywords.assign(SEARCHKEYWORDSARRAY, SEARCHKEYWORDSARRAY + SEARCHKEYWORDSARRAYSIZE);
	_conditionKeywords.assign(CONDITIONKEYWORDSARRAY, CONDITIONKEYWORDSARRAY + CONDITIONKEYWORDSARRAYSIZE);

	bool isFound = false;
	for (unsigned int i = 0; i < _conditionKeywords.size() && !isFound; i++) {
		std::string keyword;
		keyword = _conditionKeywords[i];
		if (searchClauseString.find(keyword, searchClauseString.size() - keyword.size()) != std::string::npos) {
			isFound = true;
			searchClauseString = searchClauseString.substr(0, searchClauseString.size() - keyword.size());
		}
		else {
			std::string danglingKeyword;
			danglingKeyword = _conditionKeywords[i].substr(0, _conditionKeywords[i].size() - 1);
			if (searchClauseString.find(danglingKeyword, searchClauseString.size() - danglingKeyword.size()) != std::string::npos) {
				isFound = true;
				searchClauseString = searchClauseString.substr(0, searchClauseString.size() - danglingKeyword.size());
			}
		}

		if (isFound) {
			switch (i) {
			case INDEX_AND:
				_nestCondition = AND;
				break;
			case INDEX_OR:
				_nestCondition = OR;
				break;
			case INDEX_EXCLUDE:
				_nestCondition = EXCLUDE;
				break;
			}
		}
		else {
			_nestCondition = AND;
		}
	}

	std::vector<std::vector<std::string>> searchKeywordsAndParams;
	searchClauseString = " " + searchClauseString;
	searchKeywordsAndParams = extractParamsForKeywords(searchClauseString, _searchKeywords);

	if (searchClauseString != "") {
		std::string searchClauseStringChecker;
		std::stringstream searchClauseStringSS;
		searchClauseStringSS << searchClauseString;
		if (searchClauseStringSS >> searchClauseStringChecker) {
			std::vector<std::vector<std::string>> conditionKeywordsAndParams;
			conditionKeywordsAndParams = extractParamsForKeywords(searchClauseString, _conditionKeywords);
			std::stringstream searchClauseStringSS2;
			searchClauseStringSS2 << searchClauseString;
			if (searchClauseStringSS2 >> searchClauseStringChecker) {
				_searchAttributes.push_back(GENERAL);
				searchClauseString.erase(searchClauseString.begin());
				_searchContents.push_back(searchClauseString);
				_searchConditions.push_back(AND);
			}
			processConditionKeywordsAndParams(conditionKeywordsAndParams, GENERAL);
		}
	}

	for (unsigned int i = 0; i < searchKeywordsAndParams.size(); i++) {
		for (unsigned int j = 0; j < searchKeywordsAndParams[i].size(); j++) {
			if (searchKeywordsAndParams[i][j] == "") {
				throw exceptionInputMissingAttributeParam;
			}

			std::vector<std::vector<std::string>> conditionKeywordsAndParams;
			conditionKeywordsAndParams = extractParamsForKeywords(searchKeywordsAndParams[i][j], _conditionKeywords);

			if (i >= INDEX_SEARCHDESCRIPTION && i <= INDEX_SEARCHEXCLUDEDESCRIPTION) {
				_searchAttributes.push_back(DESCRIPTION);
				_searchContents.push_back(searchKeywordsAndParams[i][j]);
				processCondition(i, INDEX_SEARCHDESCRIPTION);

				processConditionKeywordsAndParams(conditionKeywordsAndParams, DESCRIPTION);
			}
			else if (i >= INDEX_SEARCHSTARTDATE && i <= INDEX_SEARCHEXCLUDESTARTDATE) {
				_searchAttributes.push_back(STARTDATE);
				_searchContents.push_back(searchKeywordsAndParams[i][j]);
				processCondition(i, INDEX_SEARCHSTARTDATE);

				processConditionKeywordsAndParams(conditionKeywordsAndParams, STARTDATE);
			}
			else if (i >= INDEX_SEARCHENDDATE && i <= INDEX_SEARCHEXCLUDEENDDATE) {
				_searchAttributes.push_back(ENDDATE);
				_searchContents.push_back(searchKeywordsAndParams[i][j]);
				processCondition(i, INDEX_SEARCHENDDATE);

				processConditionKeywordsAndParams(conditionKeywordsAndParams, ENDDATE);
			}
			else {
				_searchAttributes.push_back(LOCATION);
				_searchContents.push_back(searchKeywordsAndParams[i][j]);
				processCondition(i, INDEX_SEARCHLOCATION);

				processConditionKeywordsAndParams(conditionKeywordsAndParams, LOCATION);
			}
		}
	}
}


SearchClause::~SearchClause(void) {
}


std::vector<std::vector<std::string>> SearchClause::extractParamsForKeywords(std::string& input, std::vector<std::string> keywords) {
	//Check for dangling keyword at end of string, if true, append ending space to string
	bool isFound = false;
	for (unsigned int i = 0; i < keywords.size() && !isFound; i++) {
		std::string danglingKeyword;
		danglingKeyword = keywords[i].substr(0, keywords[i].size() - 1);
		if (input.find(danglingKeyword, input.size() - danglingKeyword.size()) != std::string::npos) {
			isFound = true;
			input += " ";
		}
	}

	std::vector<std::vector<std::string>> keywordsAndParams;
	std::vector<std::vector<int>> keywordsStartPos;
	std::vector<int> allStartPos;

	//Get start position of each occurrence of each keyword
	for (unsigned int i = 0; i < keywords.size(); i++) {
		int startSearchPos = 0;
		std::vector<int> startPos;
		int pos;

		pos = input.find(keywords[i].c_str(), startSearchPos, keywords[i].size());
		startPos.push_back(pos);
		startSearchPos = pos + 1;
		if (pos != std::string::npos) {
			allStartPos.push_back(pos);
		}

		while ((pos != std::string::npos) && ((unsigned int)startSearchPos < input.size())) {
			pos = input.find(keywords[i].c_str(), startSearchPos, keywords[i].size());
			if (pos != std::string::npos) {
				startPos.push_back(pos);
				allStartPos.push_back(pos);
				startSearchPos = pos + 1;
			}
		}

		keywordsStartPos.push_back(startPos);
	}

	//Extract param for each keyword by substr from start position of keyword + size of keyword +1 to start position of next keyword
	for (unsigned int i = 0; i < keywordsStartPos.size(); i++) {
		std::vector<std::string> params;
		for (unsigned int j = 0; j < keywordsStartPos[i].size(); j++) {
			if (keywordsStartPos[i][j] != std::string::npos) {
				int nextKeywordPos = input.size();
				for (unsigned int k = 0; k < allStartPos.size(); k++) {
					if (allStartPos[k] > keywordsStartPos[i][j] && allStartPos[k] < nextKeywordPos) {
						nextKeywordPos = allStartPos[k];
					}
				}

				std::string param;
				int paramLength;
				paramLength = nextKeywordPos - (keywordsStartPos[i][j] + keywords[i].size());
				if (paramLength > 0) {
					param = input.substr(keywordsStartPos[i][j] + keywords[i].size(), paramLength);
					params.push_back(param);
				}
				else {
					params.push_back("");
				}
			}
		}

		keywordsAndParams.push_back(params);
	}

	//Modify input string to remaining string after extraction
	if (!allStartPos.empty()) {
		std::sort(allStartPos.begin(), allStartPos.end());
		input = input.substr(0, allStartPos[0]);
	}

	return keywordsAndParams;
}

void SearchClause::processCondition(int index, int attributeIndex) {
	int i = index - attributeIndex - 1;

	switch (i) {
	case -1:
	case INDEX_AND:
		_searchConditions.push_back(AND);
		break;
	case INDEX_OR:
		_searchConditions.push_back(OR);
		break;
	case INDEX_EXCLUDE:
		_searchConditions.push_back(EXCLUDE);
		break;
	}
}

void SearchClause::processConditionKeywordsAndParams(std::vector<std::vector<std::string>> conditionKeywordsAndParams, std::string attribute) {
	for (unsigned int i = 0; i < conditionKeywordsAndParams.size(); i++) {
		for (unsigned int j = 0; j < conditionKeywordsAndParams[i].size(); j++) {
			switch (i) {
			case INDEX_AND:
				if (conditionKeywordsAndParams[i][j] == "") {
					_nestCondition = AND;
				}
				else {
					_searchAttributes.push_back(attribute);
					_searchContents.push_back(conditionKeywordsAndParams[i][j]);
					_searchConditions.push_back(AND);
				}
				break;
			case INDEX_OR:
				if (conditionKeywordsAndParams[i][j] == "") {
					_nestCondition = OR;
				}
				else {
					_searchAttributes.push_back(attribute);
					_searchContents.push_back(conditionKeywordsAndParams[i][j]);
					_searchConditions.push_back(OR);
				}
				break;
			case INDEX_EXCLUDE:
				if (conditionKeywordsAndParams[i][j] == "") {
					_nestCondition = EXCLUDE;
				}
				else {
					_searchAttributes.push_back(attribute);
					_searchContents.push_back(conditionKeywordsAndParams[i][j]);
					_searchConditions.push_back(EXCLUDE);
				}
				break;
			}
		}
	}
}

std::vector<std::string> SearchClause::getSearchAttributes(void) {
	return _searchAttributes;
}

std::vector<std::string> SearchClause::getSearchContents(void) {
	return _searchContents;
}

std::vector<Condition> SearchClause::getConditions(void) {
	return _searchConditions;
}

Condition SearchClause::getNestCondition(void) {
	return _nestCondition;
}
