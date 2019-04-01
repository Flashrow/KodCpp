/** @file */
#pragma once
#include <string>
#include <iostream>
#include <vector>

//#**************************STRUKTURY******************************************

/**	Struktura reprezentuj¹ca zmienn¹
@param type typ zmiennej
@param name nazwa zmiennej
@param pNext wskaŸnik na nastêpn¹ strukturê
**/
struct variable {
	std::string type;
	std::string name;
	variable *pNext;
};

/**	Struktura reprezentuj¹ca nazwê wywo³anej funkcji
@param name nazwa wywo³anej funkcji
@param pNext wskaŸnik na nastêpn¹ strukturê
**/
struct usedFunction {
	std::string name;
	usedFunction *pNext;
};


struct function;
/** Struktura wskaŸników na funkcje
@param fHead wskaŸnik na strukturê funkcji
@param pNext wskaŸnik na nastêpn¹ strukturê
**/
struct functionsPtr {
	function* fHead;
	functionsPtr *pNext;
};

/** Struktura reprezentuj¹ca funkcjê
@param name nazwa funkcji
@param variablesHead wskaŸnik na listê u¿ytych zmiennych
@param usedFunctionhead wskaŸnik na listê funkcji wywo³anych wewn¹trz
@param whereUsedHead wskaŸnik na listê funkcji w których wywo³ana
@param functionsPointer WskaŸnik na listê wskaŸników na funkcje wywo³ywane wewn¹trz
@param pNext wskaŸnik na nastêpn¹ strukturê
**/
struct function {
	std::string name;
	variable *variablesHead;
	usedFunction *usedFunctionhead;
	usedFunction *whereUsedHead;
	functionsPtr *functionsPointer;
	function *pNext;
};

//#***************************OBS£UGA LIST***************************************

/**	Dodaje kolejny/pierwszy element do listy funkcji
@param[out] head WskaŸnik na g³owê listy funkcji
@param[in] name Nazwa funkcji
@param[in] vHead WskaŸnik na g³owê listy zmiennych u¿ytych w funkcji
@param uHead wskaŸnik na g³owê listy funkcji u¿ytych wewn¹trz
@param whereUsedHead wskaŸnik na g³owê listy funkcji, w których u¿yta
@param[in] fHead WskaŸnik na g³owê listy wskaŸników na funkcje wywo³ane wewn¹trz
**/
void addToList(function *&head, 
	std::string name, 
	variable *vHead=nullptr,
	usedFunction *uHead=nullptr,
	usedFunction *whereUsedHead=nullptr,
	functionsPtr *fHead=nullptr);

/**	Dodaje kolejny/pierwszy element do listy zmiennych
@param[out] vHead WskaŸnik na g³owê listy zmiennych
@param[in] type Nazwa typu zmiennej
@param[in] name Nazwa zmiennej
**/
void addToList(variable *&head, std::string type, std::string name);

/**	Dodaje kolejny/pierwszy element do listy wywo³anych funkcji
@param[out] uHead WskaŸnik na g³owê listy wywo³anych funkcji
@param[in]	name Nazwa funkcji
**/
void addToList(usedFunction *&head, std::string name);

/**Dodaje kolejny/pierwszy element do listy wskaŸników na funkcje
@param head wskaŸnik na g³owê listy wskaŸników
@param pointer funkcja do dodania
**/
void addToList(functionsPtr *&head, function *pointer);

/** Usuwa listê funkcji
@param head WskaŸnik na g³owê listy funkcji
**/
void deleteList(function *&head);

/** Usuwa listê zmiennych
@param head WskaŸnik na g³owê listy zmiennych
**/
void deleteList(variable *&head);

/** Usuwa listê wywo³anych funkcji
@param head WskaŸnik na g³owê listy wywo³anych funkcji
**/
void deleteList(usedFunction *&head);

/** Usuwa listê wskaŸników na funkcje
@param head g³owa listy
**/
void deleteList(functionsPtr *&head);

/** Usuwa podany typ z listy
@param head Lista, z której zostanie usuniêty element
@param typeString nazwa szukanego typu
**/
void deleteElement(variable *&head, std::string typeString);

/** Wypisuje listê funkcji z mo¿liwoœci¹ wyboru wypisywania poszczególnych sk³adników
@param head WskaŸnik na g³owê listy
**/
void printList(function *&head,
	bool printVariables = false,
	bool printUsedFunctions = false,
	bool printWhereUsed = false,
	bool printPointers = false);

/** Wypisuje listê zmiennych
@param head WskaŸnik na g³owê listy
**/
void printList(variable *&head);

/** Wypisuje listê wywo³anych funkcji
@param head WskaŸnik na g³owê listy
**/
void printList(usedFunction *&head);

/** Wypisuje listê wskaŸników na funkcje
**/
void printList(functionsPtr *head);

/** Zwraca funkcjê szukan¹ po nazwie na liœcie funkcji
@param name Nazwa szukanej funkcji
@param head wskaŸnik na listê, w której szukaæ
**/
function *findFunction(std::string name, function *head);

//#*********************************FUNKCJE KOD C++**************************************

/** Wyszukuje w podanym pliku Ÿród³owym funkcje i zapisuje je na podanej liœcie
@param filePath Nazwa pliku z kodem
@param functionHead wskaŸnik na g³owê listy funkcji
**/
void findFunctions(std::string filePath, function *&functionHead);

/** Usuwa wszystkie spacje z podanego stringa
@param s String, z którego zostan¹ usuniête wszystkie spacje
**/
std::string deleteSpace(std::string &s);

/** Usuwa spacje z pocz¹tku podanego stringa: "___abc" -> "abc"
@param s String, z którego zostan¹ usuniête spacje
**/
std::string deleteSpaceFromBeg(std::string &s);

/** Usuwa spacje z koñca podanego stringa: "abc___" -> "abc"
@param s String, z którego zostan¹ usuniête spacje
**/
std::string deleteSpaceFromEnd(std::string &s);

/** Zczytuje informacje z podanego stringa, który zawiera deklaracje funkcji : funkcja(typ zmienna1, typ zmienna2...)
@param line String zawieraj¹cy deklaracje funkcji - nazwa i nawias
@param functionHead wskaŸnik na g³owê listy funkcji, do której zostan¹ dodane informacje z nag³ówka funkcji
**/
void functionDeclarationInfo(std::string line, function *&functionHead);

/**	Sprawdza cia³o funkcji, tzn miêdzy '{' '}' danej funkcji
@param ifile Zmienna pliku z którego pobierane s¹ dane
@param functionHead WskaŸnik na g³owê listy funkcji, do której zostan¹ dodane informacje znalezione w ciele danej funkcji
@param curlyBrackets Zmienna wskazuj¹ca na iloœæ otwartych nawiasów "{" minus iloœæ zamkniêtych nawiasów "}" - je¿eli == 0 to koniec cia³a funkcji
**/
void functionBodyInfo(std::ifstream &ifile, function *&functionHead, int &curlyBrackets);

/** Sprawdza informacje w jednej linii, tzn od poprzedniego koñca linii do œrednika ';'
@param line Podana linia kodu
@param functionHead WskaŸnik na g³owê listy funkcji, do której zostan¹ dodane informacje z danej linii
**/
void functionLineInfo(std::string line, function *&functionHead);

/** Iloœæ s³ów w linii, tzn iloœæ ci¹gów znaków, d³u¿szych od 0 z³o¿onych z liter, cyfr i dozwolonych znaków, funkcja ignoruje znaki specjalne
@param line String do policzenia iloœci s³ów
**/
int wordsInLine(std::string line);

/** Usuwa znaki specjalne(niedozwolone w nazwach) z podanego stringa i zastêpuje je spacj¹
@param line String, z którego zostan¹ usuniête znaki specjalne
**/
void removeSpecialCharacters(std::string &line);

/** Usuwa znaki specjalne(niedozwolone w nazwach) z pominiêciem nawiasów "(" i ")" z podanego stringa i zastêpuje je spacj¹
@param line String z którego zostan¹ usuniête znaki
**/
void leaveNamesAndBrackets(std::string &line);

/** Funkcja przechodzi deklaracje pêtl i zbiera z niej mo¿liwe informacje
@param ifile Zmienna pliku, z którego pobierane s¹ dane
@param functionHead WskaŸnik na g³owê listy funkcji, do której ewentualnie zostan¹ dopisane znalezione informacje
@param line String zawieraj¹cy przynajmniej pocz¹tek deklaracji pêtli for/while/ lub instrukcji warunkowej, np "for"/"for(..." lub ca³¹ deklaracje for(...){
@param brackets Zmienna prezentuj¹ca iloœæ nawiasów otwartych w stosunku do zamkniêtych, tzn. iloœæ"(" - iloœæ")"
**/
void skipStatement(std::ifstream &ifile,function *&functionHead, std::string &line, int brackets);

/** Zlicza nawiasy w podanym stringu, "(" -> +1 oraz ")"-> -1 , je¿eli iloœæ nawiasów siê wyzeruje, tzn bêdzie tyle samo otwartych co zamkniêtych to funkcja przerywa dzia³anie i zwraca 0
@param line String, w którym zostana zliczone nawiasy
**/
int countBrackets(std::string line);


//#*********************************FUNKCJE DO PRZETWARZANIA ZEBRANYCH INFORMACJI**************************************

/** Dopisuje dla ka¿dej funkcji w podanej liœcie funkcje, w których jest u¿yta
@param functionHead wskaŸnik na domyœln¹ g³owê listy funkcji
**/
void setOutput(function *functionHead);

/** Wypisuje listê do pliku
@param ofile zmienna pliku, do którego zostanie wypisana lista
@outFunctionList wskaŸnik na g³owê listy
**/
void printToFile(std::ofstream &ofile, function *outFunctionList);

/** Wypisuje do pliku wektor
**/
void printToFile(std::vector<std::string> stringVector, std::ofstream &oFile);

/** Je¿eli wykryje znaki '//' to pomija komentarz
@param word S³owo do sprawdzenia
@param ifile Plik, z którego pobierane s¹ dane
**/
void ignoreCode(std::string &word, std::ifstream &ifile);

/** Sprawdza czy podana funkcja jest na liœcie funkcji u¿ytych
@param functionName funckja do sprawdzenia
@param functionHead WskaŸnik na g³owê listy funkcji
**/
bool chkFunction(std::string functionName, function *functionHead);

/** Wyszukuje gdzie by³a u¿yta podana funkcja i dopisuje do podanej listy nazwê funckji, w której by³a u¿yta
@param outFunctionList Lista, do której zostan¹ dopisane znalezione funkcje
@param name Nazwa funkcji, której u¿ycie w œrodku innej jest poszukiwane
@param functionHead WskaŸnik na domyœln¹ g³owê listy funkcji
**/
void searchFunctions(usedFunction *&outFunctionList, std::string name, function *functionHead);

/** Uzupe³nia listê wskaŸników na funkcje wywo³ywane dla danej funkcji
@param functionHead lista, która bêdzie przerobiona na strukturê umo¿liwiaj¹c¹ wyszukanie cykli
**/
void functionUsage(function *functionHead);

/** Zwraca wskaŸnik na strukturê funkcji
@param name Nazwa szukanej funkcji
@param functionHead Lista funkcji
**/
function *getUsedFun(std::string name, function *functionHead);

/** Wypisuje wektor stringów
**/
void printVector(std::vector<std::string> sVector);

/** Szuka cyklów w wywo³aniach funkcji i wpisuje je do podanego wektora
@param fHead G³owa listy funkcji do znalezienia cyklów
@param globalVector Wektor, do którego zostan¹ wpisane wszystkie znalezione cykle
**/
void findAllCycles(function *fHead, std::vector<std::string> &globalVector);

/**Rekurencyjnie symuluje wywo³ywanie kolejnych funkcji, jednoczeœnie sprawdzaj¹c czy nie utworzy³ siê cykl,
je¿eli istnieje cykl to dopisuje go do g³ównego wektora stringów
@param fHead WskaŸnik na funkcje, dla której zostanie przeprowadzona symulacja wywo³añ funkcji
@param cycleVector Wektor dostêpny 'lokalnie' w danym przejœciu rekurencyjnym, s³u¿y do sprawdzenia czy istnieje cykl na danej linii rekurencyjnej
@param globalVector Wektor stringów, do którego zostanie dopisany kompletny cykl, je¿eli zostanie wykryty
**/
void recursiveCycle(function *fHead, std::vector<std::string> cycleVector, std::vector<std::string> &globalVector);

/** Zamienia wektor stringów na pojedyñczy string, s³owa oddzielone spacjami
**/
std::string convertVectorToString(std::vector<std::string> sVector);

/** Wyszukuje podanej zmiennej w liœcie funkcji
@param functionHead Lista funkcji
@param varString wyszukiwana zmienna
**/
bool findVariable(function *functionHead, std::string varString);

/** Wypisuje na ekran funkcje, w których znaleziono podan¹ zmienn¹
@param functionHead Lista funkcji
@param vString Szukana zmienna
**/
void printSearchedVar(function *functionHead, std::string vString);

/** Usuwa z listy funkcji wszystkie zmienne podanego typu
@param functionHead Lista funkcji
@param vType Typ do usuniêcia
**/
void eraseType(function *&functionHead, std::string vType);

/** Sprawdza czy podana funkcja ju¿ siê znajduje w wektorze, tzn. czy nie powsta³ cykl
@param name Nazwa funkcji do wyszukania
@param cycleVector Wektor z tokiem wywo³añ funkcji w danej linii rekurencji
**/
bool isRepeated(std::string name, std::vector<std::string> cycleVector);