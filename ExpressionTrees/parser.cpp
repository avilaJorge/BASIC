#include "parser.h"

using namespace std;

Expression* parseExp(TokenScanner& scanner) {
	Expression *exp = readE(scanner, 0);
	if (scanner.hasMoreTokens()) {
		error("Unexpected token \"" + scanner.nextToken() + "\"");
	}
	return exp;
}

Expression* readE(TokenScanner& scanner, int prec) {
	Expression *exp = readT(scanner);
	string token;
	bool done = false;

	while (!done && scanner.hasMoreTokens())
	{
		token = scanner.nextToken();
		int tprec = precedence(token);
		if (tprec <= prec)
		{
			done = true;
			scanner.saveToken(token);
		}
		else
		{
			Expression *rhs = readE(scanner, tprec);
			exp = new CompoundExp(token, exp, rhs);
		}
	}
	return exp;
}

Expression* readT(TokenScanner& scanner) {
	string token = scanner.nextToken();
	TokenType type = scanner.getTokenType(token);
	if (type == WORD) return new IdentifierExp(token);
	if (type == NUMBER) return new ConstantExp(stringToInteger(token));
	if (token != "(") error("Illegal term in expression");
	Expression *exp = readE(scanner, 0);
	if (scanner.nextToken() != ")") {
		error("Unbalanced parentheses in expression");
	}
	return exp;
}

int precedence(std::string token) {
	//if (token == "=") return 1; REMOVED: Since BASIC does not allow embedded assignments
	if (token == "+" || token == "-") return 2;
	if (token == "*" || token == "/") return 3;
	return 0;

}

Statement* parseStatement(TokenScanner& scanner)
{
	string statementType = scanner.nextToken();
	if (statementType == "PRINT") return new PrintStmt(scanner);
	if (statementType == "REM") return new RemStmt(scanner);
	if (statementType == "LET") return new LetStmt(scanner);
	if (statementType == "INPUT") return new InputStmt(scanner);
	if (statementType == "GOTO") return new GotoStmt(scanner);
	if (statementType == "IF") return new IfStmt(scanner);
	if (statementType == "END") return new EndStmt(scanner);
	if (scanner.hasMoreTokens()) {
		error("Unexpected token \"" + scanner.nextToken() + "\"" + ", will return EndStmt");
	}
	return new EndStmt(scanner);

}