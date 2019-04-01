/** @file */
#pragma once
#include <string>
#include <iostream>
#include <vector>

//#**************************STRUKTURY******************************************

/**	Struktura reprezentuj�ca zmienn�
@param type typ zmiennej
@param name nazwa zmiennej
@param pNext wska�nik na nast�pn� struktur�
**/
struct variable {
	std::string type;
	std::string name;
	variable *pNext;
};

/**	Struktura reprezentuj�ca nazw� wywo�anej funkcji
@param name nazwa wywo�anej funkcji
@param pNext wska�nik na nast�pn� struktur�
**/
struct usedFunction {
	std::string name;
	usedFunction *pNext;
};


struct function;
/** Struktura wska�nik�w na funkcje
@param fHead wska�nik na struktur� funkcji
@param pNext wska�nik na nast�pn� struktur�
**/
struct functionsPtr {
	function* fHead;
	functionsPtr *pNext;
};

/** Struktura reprezentuj�ca funkcj�
@param name nazwa funkcji
@param variablesHead wska�nik na list� u�ytych zmiennych
@param usedFunctionhead wska�nik na list� funkcji wywo�anych wewn�trz
@param whereUsedHead wska�nik na list� funkcji w kt�rych wywo�ana
@param functionsPointer Wska�nik na list� wska�nik�w na funkcje wywo�ywane wewn�trz
@param pNext wska�nik na nast�pn� struktur�
**/
struct function {
	std::string name;
	variable *variablesHead;
	usedFunction *usedFunctionhead;
	usedFunction *whereUsedHead;
	functionsPtr *functionsPointer;
	function *pNext;
};

//#***************************OBS�UGA LIST***************************************

/**	Dodaje kolejny/pierwszy element do listy funkcji
@param[out] head Wska�nik na g�ow� listy funkcji
@param[in] name Nazwa funkcji
@param[in] vHead Wska�nik na g�ow� listy zmiennych u�ytych w funkcji
@param uHead wska�nik na g�ow� listy funkcji u�ytych wewn�trz
@param whereUsedHead wska�nik na g�ow� listy funkcji, w kt�rych u�yta
@param[in] fHead Wska�nik na g�ow� listy wska�nik�w na funkcje wywo�ane wewn�trz
**/
void addToList(function *&head, 
	std::string name, 
	variable *vHead=nullptr,
	usedFunction *uHead=nullptr,
	usedFunction *whereUsedHead=nullptr,
	functionsPtr *fHead=nullptr);

/**	Dodaje kolejny/pierwszy element do listy zmiennych
@param[out] vHead Wska�nik na g�ow� listy zmiennych
@param[in] type Nazwa typu zmiennej
@param[in] name Nazwa zmiennej
**/
void addToList(variable *&head, std::string type, std::string name);

/**	Dodaje kolejny/pierwszy element do listy wywo�anych funkcji
@param[out] uHead Wska�nik na g�ow� listy wywo�anych funkcji
@param[in]	name Nazwa funkcji
**/
void addToList(usedFunction *&head, std::string name);

/**Dodaje kolejny/pierwszy element do listy wska�nik�w na funkcje
@param head wska�nik na g�ow� listy wska�nik�w
@param pointer funkcja do dodania
**/
void addToList(functionsPtr *&head, function *pointer);

/** Usuwa list� funkcji
@param head Wska�nik na g�ow� listy funkcji
**/
void deleteList(function *&head);

/** Usuwa list� zmiennych
@param head Wska�nik na g�ow� listy zmiennych
**/
void deleteList(variable *&head);

/** Usuwa list� wywo�anych funkcji
@param head Wska�nik na g�ow� listy wywo�anych funkcji
**/
void deleteList(usedFunction *&head);

/** Usuwa list� wska�nik�w na funkcje
@param head g�owa listy
**/
void deleteList(functionsPtr *&head);

/** Usuwa podany typ z listy
@param head Lista, z kt�rej zostanie usuni�ty element
@param typeString nazwa szukanego typu
**/
void deleteElement(variable *&head, std::string typeString);

/** Wypisuje list� funkcji z mo�liwo�ci� wyboru wypisywania poszczeg�lnych sk�adnik�w
@param head Wska�nik na g�ow� listy
**/
void printList(function *&head,
	bool printVariables = false,
	bool printUsedFunctions = false,
	bool printWhereUsed = false,
	bool printPointers = false);

/** Wypisuje list� zmiennych
@param head Wska�nik na g�ow� listy
**/
void printList(variable *&head);

/** Wypisuje list� wywo�anych funkcji
@param head Wska�nik na g�ow� listy
**/
void printList(usedFunction *&head);

/** Wypisuje list� wska�nik�w na funkcje
**/
void printList(functionsPtr *head);

/** Zwraca funkcj� szukan� po nazwie na li�cie funkcji
@param name Nazwa szukanej funkcji
@param head wska�nik na list�, w kt�rej szuka�
**/
function *findFunction(std::string name, function *head);

//#*********************************FUNKCJE KOD C++**************************************

/** Wyszukuje w podanym pliku �r�d�owym funkcje i zapisuje je na podanej li�cie
@param filePath Nazwa pliku z kodem
@param functionHead wska�nik na g�ow� listy funkcji
**/
void findFunctions(std::string filePath, function *&functionHead);

/** Usuwa wszystkie spacje z podanego stringa
@param s String, z kt�rego zostan� usuni�te wszystkie spacje
**/
std::string deleteSpace(std::string &s);

/** Usuwa spacje z pocz�tku podanego stringa: "___abc" -> "abc"
@param s String, z kt�rego zostan� usuni�te spacje
**/
std::string deleteSpaceFromBeg(std::string &s);

/** Usuwa spacje z ko�ca podanego stringa: "abc___" -> "abc"
@param s String, z kt�rego zostan� usuni�te spacje
**/
std::string deleteSpaceFromEnd(std::string &s);

/** Zczytuje informacje z podanego stringa, kt�ry zawiera deklaracje funkcji : funkcja(typ zmienna1, typ zmienna2...)
@param line String zawieraj�cy deklaracje funkcji - nazwa i nawias
@param functionHead wska�nik na g�ow� listy funkcji, do kt�rej zostan� dodane informacje z nag��wka funkcji
**/
void functionDeclarationInfo(std::string line, function *&functionHead);

/**	Sprawdza cia�o funkcji, tzn mi�dzy '{' '}' danej funkcji
@param ifile Zmienna pliku z kt�rego pobierane s� dane
@param functionHead Wska�nik na g�ow� listy funkcji, do kt�rej zostan� dodane informacje znalezione w ciele danej funkcji
@param curlyBrackets Zmienna wskazuj�ca na ilo�� otwartych nawias�w "{" minus ilo�� zamkni�tych nawias�w "}" - je�eli == 0 to koniec cia�a funkcji
**/
void functionBodyInfo(std::ifstream &ifile, function *&functionHead, int &curlyBrackets);

/** Sprawdza informacje w jednej linii, tzn od poprzedniego ko�ca linii do �rednika ';'
@param line Podana linia kodu
@param functionHead Wska�nik na g�ow� listy funkcji, do kt�rej zostan� dodane informacje z danej linii
**/
void functionLineInfo(std::string line, function *&functionHead);

/** Ilo�� s��w w linii, tzn ilo�� ci�g�w znak�w, d�u�szych od 0 z�o�onych z liter, cyfr i dozwolonych znak�w, funkcja ignoruje znaki specjalne
@param line String do policzenia ilo�ci s��w
**/
int wordsInLine(std::string line);

/** Usuwa znaki specjalne(niedozwolone w nazwach) z podanego stringa i zast�puje je spacj�
@param line String, z kt�rego zostan� usuni�te znaki specjalne
**/
void removeSpecialCharacters(std::string &line);

/** Usuwa znaki specjalne(niedozwolone w nazwach) z pomini�ciem nawias�w "(" i ")" z podanego stringa i zast�puje je spacj�
@param line String z kt�rego zostan� usuni�te znaki
**/
void leaveNamesAndBrackets(std::string &line);

/** Funkcja przechodzi deklaracje p�tl i zbiera z niej mo�liwe informacje
@param ifile Zmienna pliku, z kt�rego pobierane s� dane
@param functionHead Wska�nik na g�ow� listy funkcji, do kt�rej ewentualnie zostan� dopisane znalezione informacje
@param line String zawieraj�cy przynajmniej pocz�tek deklaracji p�tli for/while/ lub instrukcji warunkowej, np "for"/"for(..." lub ca�� deklaracje for(...){
@param brackets Zmienna prezentuj�ca ilo�� nawias�w otwartych w stosunku do zamkni�tych, tzn. ilo��"(" - ilo��")"
**/
void skipStatement(std::ifstream &ifile,function *&functionHead, std::string &line, int brackets);

/** Zlicza nawiasy w podanym stringu, "(" -> +1 oraz ")"-> -1 , je�eli ilo�� nawias�w si� wyzeruje, tzn b�dzie tyle samo otwartych co zamkni�tych to funkcja przerywa dzia�anie i zwraca 0
@param line String, w kt�rym zostana zliczone nawiasy
**/
int countBrackets(std::string line);


//#*********************************FUNKCJE DO PRZETWARZANIA ZEBRANYCH INFORMACJI**************************************

/** Dopisuje dla ka�dej funkcji w podanej li�cie funkcje, w kt�rych jest u�yta
@param functionHead wska�nik na domy�ln� g�ow� listy funkcji
**/
void setOutput(function *functionHead);

/** Wypisuje list� do pliku
@param ofile zmienna pliku, do kt�rego zostanie wypisana lista
@outFunctionList wska�nik na g�ow� listy
**/
void printToFile(std::ofstream &ofile, function *outFunctionList);

/** Wypisuje do pliku wektor
**/
void printToFile(std::vector<std::string> stringVector, std::ofstream &oFile);

/** Je�eli wykryje znaki '//' to pomija komentarz
@param word S�owo do sprawdzenia
@param ifile Plik, z kt�rego pobierane s� dane
**/
void ignoreCode(std::string &word, std::ifstream &ifile);

/** Sprawdza czy podana funkcja jest na li�cie funkcji u�ytych
@param functionName funckja do sprawdzenia
@param functionHead Wska�nik na g�ow� listy funkcji
**/
bool chkFunction(std::string functionName, function *functionHead);

/** Wyszukuje gdzie by�a u�yta podana funkcja i dopisuje do podanej listy nazw� funckji, w kt�rej by�a u�yta
@param outFunctionList Lista, do kt�rej zostan� dopisane znalezione funkcje
@param name Nazwa funkcji, kt�rej u�ycie w �rodku innej jest poszukiwane
@param functionHead Wska�nik na domy�ln� g�ow� listy funkcji
**/
void searchFunctions(usedFunction *&outFunctionList, std::string name, function *functionHead);

/** Uzupe�nia list� wska�nik�w na funkcje wywo�ywane dla danej funkcji
@param functionHead lista, kt�ra b�dzie przerobiona na struktur� umo�liwiaj�c� wyszukanie cykli
**/
void functionUsage(function *functionHead);

/** Zwraca wska�nik na struktur� funkcji
@param name Nazwa szukanej funkcji
@param functionHead Lista funkcji
**/
function *getUsedFun(std::string name, function *functionHead);

/** Wypisuje wektor string�w
**/
void printVector(std::vector<std::string> sVector);

/** Szuka cykl�w w wywo�aniach funkcji i wpisuje je do podanego wektora
@param fHead G�owa listy funkcji do znalezienia cykl�w
@param globalVector Wektor, do kt�rego zostan� wpisane wszystkie znalezione cykle
**/
void findAllCycles(function *fHead, std::vector<std::string> &globalVector);

/**Rekurencyjnie symuluje wywo�ywanie kolejnych funkcji, jednocze�nie sprawdzaj�c czy nie utworzy� si� cykl,
je�eli istnieje cykl to dopisuje go do g��wnego wektora string�w
@param fHead Wska�nik na funkcje, dla kt�rej zostanie przeprowadzona symulacja wywo�a� funkcji
@param cycleVector Wektor dost�pny 'lokalnie' w danym przej�ciu rekurencyjnym, s�u�y do sprawdzenia czy istnieje cykl na danej linii rekurencyjnej
@param globalVector Wektor string�w, do kt�rego zostanie dopisany kompletny cykl, je�eli zostanie wykryty
**/
void recursiveCycle(function *fHead, std::vector<std::string> cycleVector, std::vector<std::string> &globalVector);

/** Zamienia wektor string�w na pojedy�czy string, s�owa oddzielone spacjami
**/
std::string convertVectorToString(std::vector<std::string> sVector);

/** Wyszukuje podanej zmiennej w li�cie funkcji
@param functionHead Lista funkcji
@param varString wyszukiwana zmienna
**/
bool findVariable(function *functionHead, std::string varString);

/** Wypisuje na ekran funkcje, w kt�rych znaleziono podan� zmienn�
@param functionHead Lista funkcji
@param vString Szukana zmienna
**/
void printSearchedVar(function *functionHead, std::string vString);

/** Usuwa z listy funkcji wszystkie zmienne podanego typu
@param functionHead Lista funkcji
@param vType Typ do usuni�cia
**/
void eraseType(function *&functionHead, std::string vType);

/** Sprawdza czy podana funkcja ju� si� znajduje w wektorze, tzn. czy nie powsta� cykl
@param name Nazwa funkcji do wyszukania
@param cycleVector Wektor z tokiem wywo�a� funkcji w danej linii rekurencji
**/
bool isRepeated(std::string name, std::vector<std::string> cycleVector);