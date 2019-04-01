#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Header.h"

using namespace std;

//prze³¹czniki: 
//-fin plik wejœciowy
//-ffun plik wyjœciowy z funkcjami
//-fcykl plik wyjœciowy z wszystkimi cyklami
//-zm nazwa zmiennej, dla której wypisaæ wszystkie funkcje, w których jest u¿yta
//-typ nazwa typu, dla którego zostan¹ usuniête wszystkie lokalne
int main(int argc, char *argv[]) {
	{
	string iPath = "";
	string oPath = "";
	string cyclePath = "";
	string varName = "";
	string typeToDelete = "";
	ifstream ifile;
	ofstream ofile;
	ofstream cycleFile;
	function *functionHead = nullptr;

	for (int i = 1; i < argc - 1; i++) {
		if (strcmp(argv[i], "-fin") == 0)
			iPath = argv[i + 1];

		if (strcmp(argv[i], "-ffun") == 0)
			oPath = argv[i + 1];

		if (strcmp(argv[i], "-fcykl") == 0)
			cyclePath = argv[i + 1];

		if (strcmp(argv[i], "-zm") == 0)
			varName = argv[i + 1];

		if (strcmp(argv[i], "-typ") == 0)
			typeToDelete = argv[i + 1];
	}

	//iPath = "test.txt";
	//oPath = "wynik.txt";
	//cyclePath = "cykle.txt";
	//typeToDelete = "int";
	//varName = "a";

	if (iPath != "") {
		ifile.open(iPath);
		if (!ifile.good()) {
			cout << "B³¹d, nie mo¿na u¿yæ tego pliku wejœciowego!" << endl;
			cin.get();
			return 0;
		}
	}
	else {
		cout << "Nie podano sciezki do pliku wejsciowego!" << endl;
	}
	if (oPath != "") {
		ofile.open(oPath);
		if (!ofile.good()) {
			cout << "B³¹d, nie mo¿na u¿yæ tego pliku wyjœciowego!" << endl;
			cin.get();
			return 0;
		}
	}
	else {
		cout << "Nie podano sciezki do pliku wyjsciowego!" << endl;
	}

	findFunctions(iPath, functionHead);	//zbieranie danych z funkcji
	ifile.close();

	if (varName != "") {
		printSearchedVar(functionHead, varName);
	}

	if (typeToDelete != "") {
		eraseType(functionHead, typeToDelete);				//usuwanie podanego typu z wyniku
	}

	setOutput(functionHead);
	printToFile(ofile, functionHead);	//wypisywanie podstawowych informacji do g³ównego pliku wyjsciowego
	ofile.close();

	functionUsage(functionHead);
	//printList(functionHead, false, true, false, true);

	if (cyclePath != "") {					//szukanie i wypisywanie cykli
		cycleFile.open(cyclePath);
		if (cycleFile.good()) {
			vector<string> foundCycles;
			findAllCycles(functionHead, foundCycles);
			convertVectorToString(foundCycles);
			printToFile(foundCycles, cycleFile);
			cycleFile.close();
		}
		else {
			cout << "Nie mo¿na u¿yæ tej œcie¿ki do pliku dla wypisania cykli" << endl;
		}
	}


	cout << endl << "Koniec programu";
	deleteList(functionHead);
	cin.get();
}
	_CrtDumpMemoryLeaks();
	return 0;
}

