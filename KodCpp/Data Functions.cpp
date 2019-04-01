#include <fstream>
#include <iostream>

#include "Header.h"

void setOutput(function *functionHead) {
	function *mainHead=functionHead;
	while (functionHead) {
		searchFunctions(functionHead->whereUsedHead, functionHead->name, mainHead);
		functionHead = functionHead->pNext;
	}
}

void searchFunctions(usedFunction *&whereUsedHead, std::string name, function *functionHead) {
	while (functionHead) {
		if (functionHead->name != name) {
			if (chkFunction(name, functionHead)) {
				//std::cout << "debug funkcja " << name << " jest uzyta w  " << functionHead->name << std::endl<<whereUsedHead<<std::endl;
				addToList(whereUsedHead, functionHead->name);
			}
		}
		functionHead=functionHead->pNext;
	}
}

bool chkFunction(std::string functionName,function *functionHead){
	usedFunction *head = functionHead->usedFunctionhead;
	while (head) {
		if (head->name == functionName) {
			return true;
		}
		head = head->pNext;
	}
	return false;
}

void printToFile(std::ofstream &ofile, function *outFunctionList) {
	variable *vhead;
	usedFunction *fhead;
	if (outFunctionList) {
		while (outFunctionList) {
			ofile << "Nazwa funkcji: " << outFunctionList->name << std::endl;
			vhead = outFunctionList->variablesHead;
			fhead = outFunctionList->whereUsedHead;
			if (ofile) {
				ofile << "Uzyte zmienne: " << std::endl;
				while (vhead) {
					if(vhead->type!="")
					ofile << "  -" << vhead->type << " " << vhead->name<< std::endl;
					vhead = vhead->pNext;
				}
			}
			else {
				ofile << "Brak zmiennych lokalnych" << std::endl;
			}
			if (fhead) {
				ofile << std::endl << "Funkcje, w ktorych uzyta:" << std::endl;
				while (fhead) {
					ofile << "  -" << fhead->name << std::endl;
					fhead = fhead->pNext;
				}
			}
			else {
				ofile << std::endl << "Funkcja, nie byla uzyta w zadnej innej" << std::endl;
			}
			ofile << std::endl << "**************************" <<std::endl;
			outFunctionList = outFunctionList->pNext;
		}
	}
}

void printToFile(std::vector<std::string> stringVector, std::ofstream &oFile) {
	oFile << "Znalezione cykle:" << std::endl;
	for (std::string s : stringVector) {
		oFile << "  " << s << std::endl;
	}
}

void functionUsage(function *functionHead) {
	function *saveHead = functionHead;
	while (functionHead) {
		usedFunction *usedFunBuff = functionHead->usedFunctionhead;
		while (usedFunBuff) {
			addToList(functionHead->functionsPointer, getUsedFun(usedFunBuff->name,saveHead));
			usedFunBuff = usedFunBuff->pNext;
		}
		functionHead = functionHead->pNext;
	}
}

function *getUsedFun(std::string name, function *functionHead) {
	while (functionHead) {
		if (functionHead->name == name) {
			return functionHead;
		}
		functionHead = functionHead->pNext;
	}
	return nullptr;
}

void printVector(std::vector<std::string> sVector) {
	for (std::string s : sVector) {
		std::cout << s << std::endl;
	}
}

void findAllCycles(function *fHead, std::vector<std::string> &globalVector) {
	while(fHead) {
		std::vector<std::string> cycleVector;
		cycleVector.clear();
		recursiveCycle(fHead, cycleVector,globalVector);
		fHead = fHead->pNext;
	}
}


void recursiveCycle(function *fHead, std::vector<std::string> cycleVector, std::vector<std::string> &globalVector) {
	if (isRepeated(fHead->name, cycleVector)) {
		cycleVector.push_back(fHead->name);
		globalVector.push_back(convertVectorToString(cycleVector));
	}
	else if(fHead->functionsPointer) {
		cycleVector.push_back(fHead->name);
		functionsPtr *buff = fHead->functionsPointer;
		while(buff){
			recursiveCycle(buff->fHead, cycleVector, globalVector);
			buff = buff->pNext;
		}
	}
}

bool isRepeated(std::string name, std::vector<std::string> cycleVector) {
	for(std::string s:cycleVector){
		if (s == name) {
			return true;
		}
	}
	return false;
}

std::string convertVectorToString(std::vector<std::string> sVector) {
	std::string output = "";
	for (std::string s : sVector) {
		output += s + " ";
	}
	return output;
}

bool findVariable(function *functionHead, std::string varString) {
	variable *varHead = functionHead->variablesHead;
	bool found = false;
	while (varHead) {
		std::string s = varHead->name;
		deleteSpace(s);
		if (s==varString) {
			found = true;
		}
		varHead = varHead->pNext;
	}
	return found;
}

void printSearchedVar(function *functionHead, std::string vString) {
	std::cout << "Funkcje, w ktorych znaleziono zmienna \"" << vString << "\" :" << std::endl;
	while (functionHead) {
		if (findVariable(functionHead, vString))
			std::cout << " -" << functionHead->name<<std::endl;
		functionHead = functionHead->pNext;
	}
}

void eraseType(function *&functionHead, std::string vType) {
	function *headBuff =functionHead;
	while (functionHead) {
		if(functionHead->variablesHead)
		deleteElement(functionHead->variablesHead, vType);
		functionHead = functionHead->pNext;
	}
	functionHead = headBuff;
}