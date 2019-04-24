// lab04_02.cpp : Wtorek 11:00 Grzegorz Podwika


#include "pch.h"
#include "libONP.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stack>
using namespace std;

int main()
{
	fstream inFile = createInputFile();						//otwarcie pliku do odczytu
	fstream outFile = createOutputFile();					//otwarcie pliku do zapisu
	convertAndSaveExpressionsToFile(inFile, outFile);		//glowna funkcja konwertujaca i zapisujaca wyrazenia do pliku wynikowego

	inFile.close();
	outFile.close();
	return 0;
}


