/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */
#include "program.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
	clear();
}

void Program::clear() {
   // Replace this stub with your own code
	if (!statements_.empty())
	{
		strings_.clear();
		for (auto statement : statements_)
		{
			delete &statement;
		}
		statements_.clear();
	}
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
	if (strings_.find(lineNumber) == strings_.end())
	{
		strings_.emplace(lineNumber, line);
	}
	else
		strings_.find(lineNumber)->second = line;
	
}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
	if (strings_.find(lineNumber) != strings_.end())
	{
		strings_.erase(strings_.find(lineNumber));
		delete statements_.find(lineNumber)->second;
		statements_.erase(statements_.find(lineNumber));
	}
}

string Program::getSourceLine(int lineNumber) {
   // Replace this stub with your own code
	auto it = strings_.find(lineNumber);
	if (it != strings_.end())
		return it->second;
	else
		return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code

	if (statements_.find(lineNumber) == statements_.end())
	{
		statements_.emplace(lineNumber, stmt);
	}
	else
		statements_.find(lineNumber)->second = stmt;

}

Statement *Program::getParsedStatement(int lineNumber) {
   // Replace this stub with your own code
	auto it = statements_.find(lineNumber);
	if (it != statements_.end())
		return it->second;
	else
		return NULL;
}

int Program::getFirstLineNumber() {
	// Replace this stub with your own code
	if (!strings_.empty())
		return strings_.begin()->first;
	else
		return -1;     
}

int Program::getNextLineNumber(int lineNumber) {
	// Replace this stub with your own code
	auto it = strings_.upper_bound(lineNumber);
	if (it != strings_.end())
		return it->first;
	else
		return -1;
}
