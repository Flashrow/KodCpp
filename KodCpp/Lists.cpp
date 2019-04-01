
#include<iostream>
#include <string>

#include "Header.h"

using namespace std;

void addToList(function *&head, std::string name, variable *vHead, usedFunction *uHead, usedFunction *whereUsedHead, functionsPtr *fHead) {
	head = new function{name, vHead, uHead,whereUsedHead,fHead, head};
}

void addToList(variable *&head, std::string type, std::string name) {
	head = new variable{ type, name, head };
}

void addToList(usedFunction *&head, std::string name) {
	deleteSpace(name);
	head = new usedFunction{ name, head };
}

void addToList(functionsPtr *&head, function *pointer) {
	head = new functionsPtr{ pointer, head };
}

void printList(function *&head, bool printVariables, bool printUsedFunctions, bool printWhereUsed, bool printPointers) {
	if (head) {
		cout << head->name << endl;
		if (printVariables) {
			cout << "Variables:" << endl;
			printList(head->variablesHead);
			cout << endl;
		}
		if (printUsedFunctions) {
			cout << "Used functions: " << endl;
			printList(head->usedFunctionhead);
			cout << endl << endl;
		}
		if (printWhereUsed) {
			cout << "Where used: " << endl;
			printList(head->whereUsedHead);
			cout << endl << endl;
		}
		if (printPointers) {
			cout << "Functions pointers: " << endl;
			printList(head->functionsPointer);
			cout << endl << endl;
		}
		printList(head->pNext,printVariables,printUsedFunctions,printWhereUsed, printPointers);
	}
}

void printList(functionsPtr *head) {
	if (head) {
			cout <<"pointer: "<<head->fHead<<" name: "<< head->fHead->name << endl;
		printList(head->pNext);
	}
}

void printList(variable *&head) {
	if (head) {
		if(head->type.length())
		cout << head->type<<" "<< head->name << endl;
		printList(head->pNext);
	}
}

void printList(usedFunction *&head) {
	if (head) {
		if (head->name!="") {
			cout <<"  -"<< head->name << endl;
			printList(head->pNext);
		}
	}
}

void deleteList(function *&functionHead) {
	if (functionHead) {
		deleteList(functionHead->usedFunctionhead);
		functionHead->usedFunctionhead = nullptr;
		deleteList(functionHead->variablesHead);
		functionHead->variablesHead = nullptr;
		deleteList(functionHead->whereUsedHead);
		functionHead->whereUsedHead = nullptr;
		deleteList(functionHead->functionsPointer);
		functionHead->functionsPointer = nullptr;
		deleteList(functionHead->pNext);
		delete(functionHead);
		functionHead = nullptr;
	}
}

void deleteList(variable *&variableHead) {
	if (variableHead) {
		deleteList(variableHead->pNext);
		delete(variableHead);
		variableHead = nullptr;
	}
}

void deleteList(usedFunction *&usedFunHead) {
	if (usedFunHead) {
		deleteList(usedFunHead->pNext);
		delete(usedFunHead);
		usedFunHead= nullptr;
	}
}

void deleteList(functionsPtr *&head) {
	if (head) {
		deleteList(head->pNext);
		delete(head);
		head = nullptr;
	}
}

void deleteElement(variable *&head, std::string typeString) {
	variable *headB = head;	
	if (head->type.find(typeString) < headB->type.length()) {
		headB = head->pNext;
		delete(head);
		head = headB;
	}
	else {
		variable * headBefore = head;
		headB = head->pNext;
		while (headB) {
			if (headB->type.find(typeString) < headB->type.length()) {
				headBefore->pNext = headB->pNext;
				delete(headB);
				headB = headBefore->pNext;
			}
			else {
				headBefore = headB;
				headB = headB->pNext;
			}
		}
	}
}

function *findFunction(std::string name, function *head) {
	if (head) {
		if (head->name == name) {
			return head;
		}
		else {
			return findFunction(name, head->pNext);
		}
	}
	return nullptr;
}