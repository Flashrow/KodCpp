#include <iostream>
#include <fstream> 
#include <string>

#include "Header.h"

void findFunctions(std::string filePath, function *&functionHead) {
	std::ifstream ifile;
	std::string buff="";
	std::string name="";
	std::string word = "";
	std::string line = "";
	int curlyBrackets = 0;
	int bracket = 0;
	bool isFunction = false;
	ifile.open(filePath);
	if(ifile.good())
	while (!ifile.eof()) {
		ifile >> word;
		if (ifile.fail())
			break;
		ignoreCode(word, ifile);
		if (word.find(";") < word.length()) {
			line = "";
			continue;
		}
			
		line += word+" ";
		if (line.find(")")<line.length()) {
			buff = line;
			line.erase(0, line.find(")")+1);
			line = deleteSpaceFromBeg(line);
			if (line[0]=='{'){
				line = buff;
				curlyBrackets++;
				functionDeclarationInfo(line,functionHead);
				functionBodyInfo(ifile, functionHead, curlyBrackets);
			line = "";
			}
			else {
				line = buff;
			}
		}
	}
	ifile.close();
}

void functionDeclarationInfo(std::string line, function *&functionHead) {
	line.erase(line.find(")"), std::string::npos);
	line = deleteSpaceFromBeg(line);
	std::string buffor = "";
	std::string name = "";
	std::string type = "";
	line.erase(0, line.find(" "));
	name = line.substr(0, line.find("("));
	name=deleteSpace(name);
	line.erase(0, line.find("(")+1);
	line += ", )";
	addToList(functionHead, name);
	while (line[0] != ')') {
		line = deleteSpaceFromBeg(line);
		if (line[0] == ')')
			break;
		name = line.substr(0, line.find(","));
		name = deleteSpaceFromBeg(name);
		name = deleteSpaceFromEnd(name);
		type = name.substr(0, name.find(" "));
		name.erase(0, name.find(" "));
		name = deleteSpaceFromBeg(name);
		addToList(functionHead->variablesHead, type, name);
		line.erase(0, line.find(",")+1);
	}
}

std::string deleteSpaceFromBeg(std::string &s) {
	while (s[0]==32) {
		s.erase(0, 1);
	}
	return s;
}

std::string deleteSpaceFromEnd(std::string &s) {
	while ((s.length() > 0)&&(s[s.length()-1] == 32)) {
		s.erase(s.length()-1, 1);
	}
	return s;
}

std::string deleteSpace(std::string &s) {
	while (s.find(" ")<s.length()) {
		s.erase(s.find(' '), 1);
	}
	return s;
}

void functionBodyInfo(std::ifstream &ifile, function *&functionHead, int &curlyBrackets ) {
	std::string word = "";
	std::string line="";
	std::string buff = "";
	while (curlyBrackets) {
		ifile >> word;
		ignoreCode(word, ifile);
		line += word +" ";
		
		if (word.find("if")<word.length()) {
			deleteSpaceFromBeg(word);
			if (word[0] == '{')
				word.erase(0, 1);
			if ((word.length() < 3) && (word.substr(0, 2) == "if")) {		// if (...)
				skipStatement(ifile, functionHead, line,0);
			}
			else if ((word.length() >= 3) && (word.substr(0, 3) == "if(")) {	// if(...)
				skipStatement(ifile, functionHead, line,1);
			}
		}
		else if (word.find("for") < word.length()) {
			deleteSpaceFromBeg(word);
			if (word[0] == '{')
				word.erase(0, 1);
			if ((word.length() < 4) && (word.substr(0, 3) == "for")) {		// for (...)
				skipStatement(ifile, functionHead,line, 0);
			}
			else if ((word.length() >= 4) && (word.substr(0, 4) == "for(")) {	// for(...)
				skipStatement(ifile, functionHead,line, 1);
			}
		}
		else if (word.find("while") < word.length()) {
			deleteSpaceFromBeg(word);
			if (word[0] == '{')
				word.erase(0, 1);
			if ((word.length() < 6) && (word.substr(0, 5) == "while")) {		// while (...)
				skipStatement(ifile, functionHead,line, 0);
			}
			else if ((word.length() >= 4) && (word.substr(0, 6) == "while(")) {	// while(...)
				line.erase(word.find("while") + 5, 1);
				skipStatement(ifile, functionHead,line, 1);
			}
		}
		else if (word.find("do") < word.length()) {
			deleteSpaceFromBeg(word);
			if (word[0] == '{')
				word.erase(0, 1);
			if ((word.length() < 3) && (word.substr(0, 2) == "do")) {		// do {...}while(...);
				line.erase(0, 2);
			}
			else if ((word.length() >= 3) && (word.substr(0, 3) == "do{")) {	// do{...}while(...);
				line.erase(0, 2);
			}
		}
		else if (word.find("switch") < word.length()) {

		}
		
		if (line.find(";") < line.length()) {
			deleteSpaceFromBeg(line);
			deleteSpaceFromEnd(line);
			functionLineInfo(line, functionHead);
			line.erase(0,line.find(";")+1);
		}
		if (line.find("{") < line.length()) {
			curlyBrackets++;
			line.erase(line.find("{"), 1);
		}
		if (line.find("}") < line.length()) {
			curlyBrackets--;
			line.erase(line.find("}"), 1);
		}
	}
}

void functionLineInfo(std::string line, function *&functionHead) {
	deleteSpaceFromBeg(line);
	deleteSpaceFromEnd(line);
	std::string type = "";
	std::string name = "";
	if ((line.find("(") < line.length()) && (line.find(")") < line.length())) {  //podejrzenie funkcji
		leaveNamesAndBrackets(line);
		deleteSpaceFromBeg(line);
		deleteSpaceFromEnd(line);
		while (line.find("(") < line.length()) {
			line.erase(line.find_last_of("("), std::string::npos);
			if (line.find("(") < line.length()) {									//functionA(functionB(FunctionC(...)));
				name = line.substr(line.find_last_of("(") + 1, std::string::npos);
				deleteSpaceFromEnd(line);
				while (name.find(" ") < name.length()) {
					name.erase(0, name.find(" ") + 1);
				}
				if (line.length() > 0)
				addToList(functionHead->usedFunctionhead, name);
			}
			else {																	//function();
				deleteSpaceFromEnd(line);
				while (line.find(" ") < line.length()) {
					line.erase(0, line.find(" ") + 1);
				}
				if(line.length()>0)
				addToList(functionHead->usedFunctionhead, line);
			}
		}
	}
	else {																		// linia bez nawiasów == bez funkcji
		if (line.find("=") < line.length()) {
			line.erase(line.find("="), std::string::npos);
			line += ";";
		}
		deleteSpaceFromEnd(line);

		if (wordsInLine(line) == 2) {
			if ((line.substr(0, line.find(" ")) != "case") && (line.substr(0, line.find(" ")) != "return")) {
				name = line.substr(line.find(" "), std::string::npos);
				while ((name[name.length() - 1] == ';') || (name[name.length() - 1] == ' ')) {
					name.erase(name.length() - 1, 1);
				}
				addToList(functionHead->variablesHead, line.substr(0, line.find(" ")), name);
			}
		}
		else if(line.find(",")<line.length()){
			line.insert(line.length() - 1, ",");
			type = line.substr(0, line.find(" "));
			line.erase(0, line.find(" ") + 1);
			deleteSpaceFromBeg(line);
			while (line.find(",") < line.length()) {
				name = line.substr(0, line.find(","));
				while ((name[name.length() - 1] == ';') || (name[name.length() - 1] == ' ')) {
					name.erase(name.length() - 1, 1);
				}
				addToList(functionHead->variablesHead, type, name);
				line.erase(0, line.find(",")+1);
			}
		}
	}
}

void leaveNamesAndBrackets(std::string &line) {
	for (int i = 0; i < line.length(); i++) {
		if (!(((line[i] > 47) && (line[i] < 58)) 
			|| ((line[i] > 64) && (line[i] < 91))
			|| ((line[i] > 96) && (line[i] < 123)) 
			|| (line[i] == '_') || (line[i] == '$') 
			|| (line[i] == '(') || (line[i] == ')'))) {
			line.replace(i, 1, " ");
		}
	}
	deleteSpaceFromBeg(line);
	deleteSpaceFromEnd(line);
}

void removeSpecialCharacters(std::string &line) {
	for (int i = 0; i < line.length(); i++) {
		if (!(((line[i]>47)&&(line[i]<58)) 
			|| ((line[i] > 64) && (line[i] < 91)) 
			|| ((line[i] > 96) && (line[i] < 123)) 
			|| (line[i]=='_') || (line[i]=='$'))) {
			line.replace(i, 1, " ");
		}
	}
	deleteSpaceFromBeg(line);
	deleteSpaceFromEnd(line);
}

int wordsInLine(std::string line) {
	removeSpecialCharacters(line);
	deleteSpaceFromBeg(line);
	deleteSpaceFromEnd(line);
	int count=0;
	if(line[0])
	count=1;
	while (line.find(" ") < line.length()) {
		line.erase(0, line.find(" ")+1);
		count++;
	}
	return count;
}

void skipStatement(std::ifstream &ifile, function *&functionHead, std::string &line, int brackets) {
	std::string inside = "";
	std::string word = "";
	if (!brackets) {										//if/for/while (...)  <-spacja miedzy if/for/while a nawiasem '('
		ifile >> word;
		ignoreCode(word, ifile);
		line += word+" ";
	}
	brackets = countBrackets(line);
	 while(brackets){										//kompletowanie ca³ej deklaracji - a¿ nawiasy siê wyzeruj¹
		 ifile >> word;
		 ignoreCode(word, ifile);
		 line += word + " ";
		// std::cout << "debug2 " << line << std::endl;
		 brackets = countBrackets(line);
	 }
	 inside = line;
	 
	 if(inside.find("(")<inside.length())
	 inside.erase(0, inside.find("("));
	 if(inside.find_last_not_of(")") < inside.length())
	 inside.erase(inside.find_last_not_of(")")-1, std::string::npos);			//zawartoœæ nawiasów z deklaracji
	 functionLineInfo(inside, functionHead);
	 if (line.find(")") < line.length())
		 line.erase(0, line.find_last_of(")") + 1);
}


int countBrackets(std::string line) {
int brackets = 0;
bool check = false;
	for (int i = 0; i < line.length(); i++) {
		if (line[i] == '(') {
			brackets++;
		}
		else if (line[i] == ')') {
			brackets--;
		}
		if (brackets > 0)
			check = true;

		if (check) {
			if (brackets==0)
				break;
		}
	}
return brackets;
}

void ignoreCode(std::string &word, std::ifstream &ifile) {
	std::string line = word;
	char c = {};
	if (line.find("//") < line.length()) {
		while ((c != 10) || (c!=13)) {
			ifile >> c;
		}
	}
	word = line.substr(0, line.find("//"));
}