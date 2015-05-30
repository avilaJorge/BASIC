/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
//#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
#include "error.h"
using namespace std;


/* Function prototypes */

void processLine(string line, Program & program, EvaluationContext& context);

/* Main program */

int main() {
	EvaluationContext context;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, context);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvaluationContext& context) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.scanStrings();
   scanner.setInput(line);
   //Expression *exp = parseExp(scanner);
   //int value = exp->eval(state);
   //cout << getLineNumber(line) << endl;
   //delete exp;
   string token = scanner.nextToken();
   if (scanner.getTokenType(token) == WORD)
   {
	   if (token == "LIST")
	   {
		   if (program.getFirstLineNumber() != -1)
		   {
			   int lineNumber = program.getFirstLineNumber();
			   while (lineNumber != -1)
			   {
				   cout << program.getSourceLine(lineNumber) << endl;
				   lineNumber = program.getNextLineNumber(lineNumber);
			   }
		   }
	   }
	   else if (token == "CLEAR")
	   {
		   program.clear();
	   }
	   else if (token == "RUN")
	   {
		   int currentLine = program.getFirstLineNumber();
		   context.setCurrentLine(currentLine);
		   if (currentLine != -1)
		   {
			   while (currentLine != -1)
			   {
				   program.getParsedStatement(currentLine)->execute(context);
				   if (currentLine == context.getCurrentLine())
				   {
					   context.setCurrentLine(program.getNextLineNumber(currentLine));
					   currentLine = context.getCurrentLine();
				   }
				   else
					   currentLine = context.getCurrentLine();
			   }
		   }
	   }
   }
   else if (scanner.getTokenType(token) == NUMBER)
   {
	   int lineNumber = stoi(token);
	   if (scanner.hasMoreTokens())
	   {
		   program.setParsedStatement(lineNumber, parseStatement(scanner));
		   program.addSourceLine(lineNumber, line);
	   }
	   else
	   {
		   program.removeSourceLine(lineNumber);
	   }
   }
   else
	   error("Invalid input");
}