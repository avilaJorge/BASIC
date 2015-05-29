/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
   // Replace this stub with your own code
	strings_.clear();
	statements_.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
	if (strings_.find(lineNumber) == strings_.end())
	{
		strings_.emplace(lineNumber, line);
		//TODO: Figure out how to emplace a Statement in statements_
	}
	else
		strings_.find(lineNumber)->second = line;
	
}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
	strings_.erase(strings_.find(lineNumber));
	//statements_.erase(statements_.find(lineNumber));
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
	statements_.emplace(lineNumber, stmt);
	//TODO:
	//strings_.emplace(lineNumber, stmt->toString());
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
		return 0;
}
