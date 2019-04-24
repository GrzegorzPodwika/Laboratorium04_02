#ifndef LIBONP_H
#define LIBONP_H

#include <fstream>

/*
Funkcja pomocnicza wczytujaca poprawna nazwe pliku
@param fileName nazwa pliku do wczytania
*/
void loadCorrectFileName(char *fileName);

/*
Funkcja tworzaca strumien do wczytywania wlasciwego pliku
@return wczytany plik z dysku
*/
std::fstream createInputFile();

/*
Funkcja tworzaca strumien do zapisu wlasciwego pliku
@return plik do zapisu
*/
std::fstream createOutputFile();

/*
Funkcja redukujaca nadmiarowe znaki ze stringa, np. spacje, kropki
@param str przesylany string do zredukowania
*/
void reduceRedundantSigns(std::string &str);

/*
Funkcja sprawdzajaca czy znak ze stringa w notacji INF ma wyzszy priorytet niz ten na stosie
@param stackChar znak znajdujacy sie na stosie
@param strChar znak z stringa do sprawdzenia priorytetu
@return true jesli ma wyzszy priorytet, false w przeciwnym wypadku
*/
bool isHighestPriority(char stackChar, char strChar);

/*
Funkcja sprawdzajaca poprawnosc wyrazenia w postaci infiksowej
@param str przeslany string do sprawdzenia
@return true jesli wyrazenie jest poprawne, flase w przeciwnym wypadku
*/
bool isCorrectInfString(std::string str);

/*
Funkcja konwertujaca wyrazenie w postaci infiksowej do postaci ONP
@param inStr wyrazenie wejsciowe (string) w postaci infiksowej
@return wyrazenie (string) w postaci ONP
*/
std::string convertINFStringToONPString(std::string inStr);

/*
Funkcja zwracajaca priorytet przyslanego znaku w notacji ONP
@param strChar znak ktorego priorytet chcemy ustalic
@return liczba calkowita imitujaca priorytet znaku
*/
int getONPPriority(char strChar);

/*
Funkcja konwertujaca wyrazenie w postaci ONP do postaci infiksowej
@param inStr wyrazenie wejsciowe (string) w postaci ONP
@return wyrazenie (string) w postaci infiksowej
*/
std::string convertONPStringToINFString(std::string inStr);

/*
Glowna funkcja grupujaca funkcje obliczajace wyrazenia i zapisujaca do pliku wynikowego
@param iFile wczytany plik
@param oFile plik do zapisu
*/
void convertAndSaveExpressionsToFile(std::fstream &iFile, std::fstream &oFile);

#endif // !LIBONP_H
