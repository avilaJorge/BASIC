#pragma once

#include "exp.h"
#include "statement.h"

/*
* Function: parseExp
* Usage: Expression *exp = parseExp(scanner);
* -------------------------------------------
* Parses an expression by reading tokens from the scanner, which must
* be provided by the client.  The scanner should be set to ignore
* whitespace and to scan numbers.
*/

Expression *parseExp(TokenScanner & scanner);

/*
* Function: readE
* Usage: Expression *exp = readE(scanner, prec);
* ----------------------------------------------
* Returns the next expression from the scanner involving only operators
* whose precedence is at least prec.  The prec argument is optional and
* defaults to 0, which means that the function reads the entire expression.
*/

Expression *readE(TokenScanner & scanner, int prec = 0);

/*
* Function: readT
* Usage: Expression *exp = readT(scanner);
* ----------------------------------------
* Returns the next individual term, which is either a constant, an
* identifier, or a parenthesized subexpression.
*/

Expression *readT(TokenScanner & scanner);

/*
* Function: precedence
* Usage: int prec = precedence(token);
* ------------------------------------
* Returns the precedence of the specified operator token.  If the token
* is not an operator, precedence returns 0.
*/

int precedence(std::string token);

/*
* Function parseStatement
* Usage: Statment *stmt = parseStatement(scanner);
* ------------------------------------
* Parses a Statement by reading tokens from the scanner, which must
* be provided by the client.  The scanner should be set to ignore
* whitespace and to scan numbers.
*/
Statement* parseStatement(TokenScanner& scanner);