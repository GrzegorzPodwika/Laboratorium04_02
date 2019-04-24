#include "pch.h"
#include "libONP.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
#include <Windows.h>
using namespace std;

void loadCorrectFileName(char *fileName)
{
	cin >> fileName;
	int nameLength = strlen(fileName);
	bool flag = false;

	for (int i = 1; i <= 3; i++)
	{
		if (i == 3) {
			cout << "Przekroczono limit prob wprowadzenia wlasciwej nazwy.";
			cin.ignore();
			exit(0);
		}

		for (int j = 0; j < nameLength; j++)
		{
			if (j <= nameLength - 4 && fileName[j] == '.' && fileName[j + 1] == 't' && fileName[j + 2] == 'x' && fileName[j + 3] == 't') {
				flag = true;
				break;
			}
		}

		if (flag)
			break;
		else {
			cout << "Bledna nazwa pliku! Podaj nazwe z rozszerzeniem .txt!" << endl;
			cin >> fileName;
			nameLength = strlen(fileName);
		}
	}
}

fstream createInputFile()
{
	char fileName[50];
	cout << "Podaj nazwe pliku do oczytu z rozszerzeniem .txt  ";
	loadCorrectFileName(fileName);
	bool flag = false;

	while (!flag) {

		fstream rFile(fileName, ios::in);

		if (rFile) {
			flag = true;
			cout << "Poprawnie wczytano plik...\n";
			//Sleep(1500);
			return rFile;
		}
		else {
			cout << "Nie ma pliku z taka nazwa, sprobuj ponownie!" << endl;
			loadCorrectFileName(fileName);
		}
	}
}

fstream createOutputFile()
{
	char fileName[50];
	cout << "Podaj nazwe pliku do zapisu z rozszerzeniem .txt  ";
	loadCorrectFileName(fileName);
	bool flag = false;

	while (!flag) {

		fstream rFile(fileName, ios::out);

		if (rFile) {
			flag = true;
			cout << "Poprawnie utworzono plik do zapisu...";
			//Sleep(1500);
			cout << endl;
			return rFile;
		}
		else {
			cout << "Nie mozna utworzyc pliku z taka nazwa, sprobuj ponownie!" << endl;
			loadCorrectFileName(fileName);
		}
	}
}

void reduceRedundantSigns(string &str)
{
	string tmp = "";
	int i{};

	while (str[i])
	{
		if (str[i] >= 'a' && str[i] <= 'z') 
		{																			
			tmp += str[i];					//jesli znak jest mala litera zostaje dodany do tymczasowego stringa
		}
		else if (str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '+' || str[i] == '-' || str[i] == '*' ||
			str[i] == '/' || str[i] == '%' || str[i] == '^' || str[i] == '~' || str[i] == '(' || str[i] == ')') 
		{
			tmp += str[i];					//jesli znak jest operatorem zostaje dodany do tymczasowego stringa
		}

		++i;
	}

	str = tmp;
}

bool isHighestPriority(char stackChar, char strChar)
{
	int scPrior{}, strcPrior{};

	//ustalenie priorytetu dla znaku na stosie
	if (stackChar == '=')
		scPrior = 0;
	if (stackChar == '<' || stackChar == '>')
		scPrior = 1;
	if (stackChar == '+' || stackChar == '-')
		scPrior = 2;
	if (stackChar == '*' || stackChar == '/' || stackChar == '%')
		scPrior = 3;
	if (stackChar == '^')
		scPrior = 4;
	if (stackChar == '~')
		scPrior = 5;

	//ustalenie priorytetu dla znaku z
	if (strChar == '=')
		strcPrior = 0;
	if (strChar == '<' || strChar == '>')
		strcPrior = 1;
	if (strChar == '+' || strChar == '-')
		strcPrior = 2;
	if (strChar == '*' || strChar == '/' || strChar == '%')
		strcPrior = 3;
	if (strChar == '^')
		strcPrior = 4;
	if (strChar == '~')
		strcPrior = 5;
	if (strChar == '(')
		strcPrior = 6;

	//dla znakow (= i =) lub (^ i ^) lub (~ i ~) program zwraca prawde zgodnie z konwencja konwersji na ONP, czyli zostawia te znaki na stosie
	if ((scPrior == 0 && strcPrior == 0) || (scPrior == 4 && strcPrior == 4) || (scPrior == 5 && strcPrior == 5))
		return true;
	else if (strcPrior > scPrior)				//jesli priorytet wchodzacego znaku jest > znaku na stosie to wchodzi na stos
		return true;
	else
		return false;							//zdjecie ze stosu
}

bool isCorrectInfString(string str)
{
	int strSize = str.size();
	bool flag = true;
	int leftParentheseCounter{};				//licznik otwierajacych nawiasow (
	int rightParentheseCounter{};				//licznik zamykajacych nawiasow >

	for (int i = 0; i < strSize; i++)
	{
		//sprawdzenie czy nie wystepuja dwie litery obok siebie,np. ab
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			if (str[i + 1] != '\n' && str[i + 1] >= 'a' && str[i + 1] <= 'z')
			{
				flag = false;
				break;
			}
		}

		//sprawdzenie czy po znaku ) nie wystepuje operator inny niz ) lub koniec linii
		if (str[i] == ')')
		{
			if ((str[i + 1] != '\n') && (str[i + 1] == '=' || str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' ||
				str[i + 1] == '/' || str[i + 1] == '%' || str[i + 1] == '^' || str[i + 1] == '~' || str[i + 1] == '('))
			{
				flag = false;
				break;
			}
		}

		//sprawdzenie czy pewne operatory nie wystepuja obok siebie,np. ++
		if (str[i] == '=' || str[i] == '<' || str[i] == '>' || str[i] == '+' || str[i] == '-' || str[i] == '*' ||
			str[i] == '/' || str[i] == '%' || str[i] == '^')
		{
			if (str[i + 1] == '\n' || str[i + 1] == '=' || str[i + 1] == '<' || str[i + 1] == '>' || str[i + 1] == '+' || str[i + 1] == '-' || str[i + 1] == '*' ||
				str[i + 1] == '/' || str[i + 1] == '%' || str[i + 1] == '^')
			{
				flag = false;
				break;
			}
		}

		//sprawdzenie czy nawiasow jest taka sama ilosc
		if (str[i] == '(')
		{
			leftParentheseCounter++;
		}
		else if (str[i] == ')') {
			rightParentheseCounter++;
		}
	}

	if (leftParentheseCounter != rightParentheseCounter)
		flag = false;

	return flag;
}

string convertINFStringToONPString(string inStr)
{
	string outStr = "";			//przeksztalcone wyrazenie
	stack <char> signs;			//stos do operatorow, np. *, ^

	int i{}, tmp{};

	while (inStr[i])
	{
		//jesli znak ze stringa jest litera, dodac ja do wynikowego stringa
		if (inStr[i] >= 'a' && inStr[i] <= 'z')
		{
			outStr += inStr[i];
		}
		else {
			//jesli stos znakow pusty => push "pierwszy" znak
			if (signs.empty())
			{
				signs.push(inStr[i]);
			}
			else
			{
				//jesli wchodzacy znak jest zamykajacym nawiasem ')'
				if (inStr[i] == ')')
				{
					while (signs.empty() == false)
					{
						//dopoki nie natrafimy na nawias otwierajacy na stosie '(', dodawaj do wynikowego stringa znaki ze stosu, np. +,*
						if (signs.top() != '(') {
							outStr += signs.top();
							signs.pop();
						}
						else if (signs.top() == '(') {		//jesli natrafimy na nawias otwierajacy '(' sciagamy go ze stosu
							signs.pop();
							break;
						}
					}
				}
				else if (isHighestPriority(signs.top(), inStr[i]))		//jesli wchodzacy znak ma wyzszy priorytet od tego na stosie => push na stos
				{
					signs.push(inStr[i]);
				}
				else
				{
					//jesli wchodzacy znak ma nizszy priorytet to zdejmujemy ze stosu i dopisujemy do stringa, dopoki nie bedzie mial wiekszy priorytet
					while (signs.empty() == false && isHighestPriority(signs.top(), inStr[i]) != true) {
						outStr += signs.top();
						signs.pop();
					}
					signs.push(inStr[i]);		//jesli juz ma wiekszy => push na stos
				}
			}
		}

		tmp = i + 1;

		//jesli nastepny znak to NULL, czyli koniec stringa zdejmujemy reszte operatorow z stosu i dodajemy do stringa
		if (inStr[tmp] == '\0') {
			while (signs.empty() == false)
			{
				outStr += signs.top();
				signs.pop();
			}
		}

		++i;
	}

	return outStr;
}

int getONPPriority(char strChar)
{
	//ustalenie priorytetu znaku w notacji ONP
	if (strChar == '=')
	{
		return 0;
	}
	else if (strChar == '<' || strChar == '>')
	{
		return 1;
	}
	else if (strChar == '+' || strChar == '-')
	{
		return 2;
	}
	else if (strChar == '*' || strChar == '/' || strChar == '%')
	{
		return 3;
	}
	else if (strChar == '^')
	{
		return 4;
	}
	else if (strChar == '~')
	{
		return 5;
	}
	else if (strChar >= 'a' && strChar <= 'z')
		return 6;
	else
		return -1;
}

string convertONPStringToINFString(string inStr)
{
	string outStr = "";				//wynikowy string
	string tmp = "";				//pomocniczy string1
	string tmp2 = "";				//pomocniczy string2
	stack <string> expStack;		//glowny stos dla wyrazen
	stack <int> prioritiesStack;	//stos dla priorytetow znakow

	int i{};

	while (inStr[i])
	{
		//jesli znak jest litera => push na stos, priorytet litery => push na stos priorytetow
		if (inStr[i] >= 'a' && inStr[i] <= 'z')
		{
			expStack.push({ inStr[i] });		
			prioritiesStack.push(getONPPriority(inStr[i]));
		}
		else {
			tmp = "";

			if (inStr[i] != '~') {
				//jesli stosy nie sa puste => obsluga bledow
				if (expStack.empty() == false && prioritiesStack.empty() == false) {
					//jesli priorytet znaku na stosie priorytetow jest <= priorytetu przychodzacego operatora (lewa galaz)
					if (prioritiesStack.top() <= getONPPriority(inStr[i]))
					{
						//tmp = (wyrazenie)
						tmp += '(';
						tmp += expStack.top();
						tmp += ')';
						expStack.pop();
					}
					else
					{
						//tmp = wyrazenie
						tmp = expStack.top();
						expStack.pop();
					}

					prioritiesStack.pop();
				}
				else
				{
					expStack.push("error");
					break;
				}

				//jesli stosy nie sa puste => obsluga bledow
				if (expStack.empty() == false && prioritiesStack.empty() == false) {
					//jesli priorytet znaku na stosie priorytetow jest < priorytetu przychodzacego operatora (prawa galaz)
					if (prioritiesStack.top() < getONPPriority(inStr[i])) {
						//tmp2 = (wyrazenie)znak(tmp)
						tmp2 = '(';
						tmp2 += expStack.top();
						tmp2 += ')';
						tmp2 += inStr[i];
						tmp2 += tmp;
						expStack.pop();
					}
					else
					{
						//tmp2 = wyrazenie znak tmp
						tmp2 = expStack.top();
						tmp2 += inStr[i];
						tmp2 += tmp;
						expStack.pop();
					}

					prioritiesStack.pop();
				}
				else
				{
					expStack.push("error");
					break;
				}
			}
			else
			{		
				// jesli znak jest '~'

				//jesli stosy nie sa puste => obsluga bledow
				if (expStack.empty() == false && prioritiesStack.empty() == false) {
					//jesli priorytet znaku na stosie priorytetow jest <= priorytetu przychodzacego operatora (lewa galaz)
					if (prioritiesStack.top() <= getONPPriority(inStr[i]))
					{	
						//tmp2 = ~(wyrazenie)
						tmp2 = inStr[i];
						tmp2 += '(';
						tmp2 += expStack.top();
						tmp2 += ')';
						expStack.pop();
					}
					else	//jesli priorytet znaku na stosie priorytetow jest < priorytetu przychodzacego operatora (prawa galaz)
					{
						//tmp2 = ~wyrazenie
						tmp2 = inStr[i];
						tmp2 += expStack.top();
						expStack.pop();
					}
				}
				else
				{
					expStack.push("error");
					break;
				}
			}

			expStack.push(tmp2);								//push na stos tmp2 czyli stringa wynikowego z jednego obiegu petli
			prioritiesStack.push(getONPPriority(inStr[i]));		//push na stos priorytetow priorytet przychodzacego znaku ,np. *,/
		}


		++i;
	}

	outStr = expStack.top();

	return outStr;

}

void convertAndSaveExpressionsToFile(std::fstream &iFile, std::fstream &oFile)
{
	int amountOfExpressions{};			
	string tmp = "";

	getline(iFile, tmp);
	amountOfExpressions = stoi(tmp);		//liczba wyrazen = skonwertowany string na int pierwszej linii z pliku

	string inStr = "";
	string subStr = "";
	string outStr = "";

	for (int i = 0; i < amountOfExpressions; i++, outStr = "")
	{
		getline(iFile, inStr);				//wczytywanie linii z wyrazeniem
		subStr = inStr.substr(0, 3);		//wpisanie do substringa czy jest to ONP czy INF
		reduceRedundantSigns(inStr);		//zredukowanie z wyrazenia niepoprawnych znakow

		if (subStr == "INF")
		{
			outStr += "ONP: ";
			bool flagCorrectInfString = isCorrectInfString(inStr);	//sprawdzenie czy wyrazenie infiksowe jest poprawne

			if (flagCorrectInfString)
			{
				outStr += convertINFStringToONPString(inStr);		//konwersja wyrazenia z INF do ONP
			}
			else
			{
				outStr += "error";
			}

			oFile << outStr << endl;
		}
		else {
			outStr += "INF: ";

			outStr += convertONPStringToINFString(inStr);			//konwersja wyrazenia z ONP do INF
			oFile << outStr << endl;
		}

	}
}
