/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

PrintStmt::PrintStmt(TokenScanner& scanner)
{
	exp_ = readE(scanner, 0);
	if (scanner.hasMoreTokens()){
		error("Extraneous token " + scanner.nextToken());
	}
}

PrintStmt::~PrintStmt()
{
	delete exp_;
}

void PrintStmt::execute(EvaluationContext& context)
{
	cout << exp_->eval(context) << endl;
}

RemStmt::RemStmt(TokenScanner& scanner)
{
	while (scanner.hasMoreTokens())
	{
		comment_ += scanner.nextToken();
	}
}

LetStmt::LetStmt(TokenScanner& scanner)
{
	name_ = scanner.nextToken(); //store variable name in name_
	scanner.nextToken(); // toss out the assignment operator
	exp_ = readE(scanner, 0); //store expression to be assigned to name_
	if (scanner.hasMoreTokens()){
		error("Extraneous token " + scanner.nextToken());
	}
}

LetStmt::~LetStmt()
{
	delete exp_;
}

void LetStmt::execute(EvaluationContext& context)
{
	context.setValue(name_, exp_->eval(context));
}

InputStmt::InputStmt(TokenScanner& scanner)
{
	name_ = scanner.nextToken(); //store variable name in name_
	if (scanner.hasMoreTokens()){
		error("Extraneous token " + scanner.nextToken());
	}
}

InputStmt::~InputStmt()
{
	delete exp_;
}

void InputStmt::execute(EvaluationContext& context)
{
	cout << " ? ";					//Print ? indicating ready for input
	getline(cin, input_);			//Get the entire input line
	TokenScanner inputScanner;
	inputScanner.ignoreWhitespace();
	inputScanner.scanNumbers();
	inputScanner.scanStrings();
	inputScanner.setInput(input_);  //Use token scanner to parse statement by passing in to readE

	exp_ = readE(inputScanner, 0);
	if (inputScanner.hasMoreTokens()){
		error("Extraneous token " + inputScanner.nextToken());
	}

	context.setValue(name_, exp_->eval(context)); //Set the value of the variable
}

GotoStmt::GotoStmt(TokenScanner& scanner)
{
	try {
		lineNumber_ = stoi(scanner.nextToken());
	} catch (ErrorException & ex) {
		cerr << "Error: " << ex.getMessage() << endl;
	}
	if (scanner.hasMoreTokens()){
		error("Extraneous token " + scanner.nextToken());
	}
}

GotoStmt::~GotoStmt()
{

}

void GotoStmt::execute(EvaluationContext& context)
{
	context.setCurrentLine(lineNumber_);
}

IfStmt::IfStmt(TokenScanner& scanner)
{
	exp1_ = readE(scanner, 0); //Store the first expression 
	operator_ = scanner.nextToken();
	if (operator_ != "<" && operator_ != ">" && operator_ != "=")
	{
		error("Invalid operator, will set to default: =");
		operator_ = "=";
	}
	exp2_ = readE(scanner, 0);
	if (scanner.nextToken() != "THEN")
	{
		error("Invalid Expression, this IF Statement will do nothing.");
		lineNumber_ = -1;
	}
	else
	{
		try {
			lineNumber_ = stoi(scanner.nextToken());
		}
		catch (ErrorException & ex) {
			cerr << "Error: " << ex.getMessage() << endl;
		}
	}
}

IfStmt::~IfStmt()
{
	delete exp1_;
	delete exp2_;
}

void IfStmt::execute(EvaluationContext& context)
{
	if (operator_ == "<")
		result_ = (exp1_->eval(context) < exp2_->eval(context));
	else if (operator_ == ">")
		result_ = (exp1_->eval(context) > exp2_->eval(context));
	else if (operator_ == "=")
		result_ = (exp1_->eval(context) == exp2_->eval(context));

	if (result_ && lineNumber_ != -1)
		context.setCurrentLine(lineNumber_);
}

void EndStmt::execute(EvaluationContext& context)
{
	context.setCurrentLine(-1);
}