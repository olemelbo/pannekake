//
//  utils.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "utils.h"
#include "coen.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

/** Metode for å lese inn en tekst fra fil
 *  @param ifstream& file
 *  @return string tmp
 */
string read_text(ifstream& file) {
    string tmp;
    getline(file, tmp);	//henter linje fra fil
    
    //Fjerner newline for MAC OSX
    if(*tmp.rbegin() == '\r')
        tmp.erase(tmp.length() - 1);
    
    return tmp;
}

/** Metode for å lese inn et tall fra fil
 *  @param ifstream& file
 *  @return int tmp
 */
int read_int(ifstream& file) {
    string tmp;
    getline(file, tmp);
    return stoi(tmp);
}

/** Metode for å lese inn en float fra keyboard
 *  @param string promt		informasjonstekst
 *  @return float result
 */
float read_float(string promt) {
	cout << endl << promt << ": ";
	string result;
    getline(cin,result);
	return atof(result.c_str());
}

/** Metode for å lese inn en float fra fil
 *  @param ifstream& file
 *  @return float tmp
 */
float read_float(ifstream& file) {
	string tmp;
	getline(file, tmp);
	return atof(tmp.c_str());
}

/** Metode for å lese inn en int fra keyboard
 *  @param string promt		informasjonstekst
 *  @return int r
 */
int read_int(string promt) {
	cout << endl << promt << ": ";
	string result;
    getline(cin,result);
	if ( !isdigit(result[0]) ) {
		return -1;
	}
	else{//dersom det ble skrevet inn et tall
		int r = stoi(result);
		return r;
	}
}

/** Metode for å lese inn en char fra keyboard
 *  @param string promt		informasjonstekst
 *  @return char cmd
 */
char read_char(string promt) {
	cout << endl << promt << ": ";

    char cmd;
    char* tmp;
    tmp = new char(1);
	
    //Leser input
    string str;
    getline(cin, str);
    
    const char* c = str.c_str();
    strcpy(tmp, c);
    cmd = *tmp;
    
    //delete(tmp);
    
    return toupper(cmd);
}

/** Metode for å lese inn en bool fra fil
 *  @param ifstream& file
 *  @return bool
 */
bool read_bool(ifstream &file) {
    int test = read_int(file); //leser inn 1 eller 0
    return test > 0 ? true : false;
}

/** Metode for å konvertere en string til int
 *  @param string temp
 *  @return int temp
 */
int convert_to_int(string temp ) {
	return stoi(temp);
}

/** Metode for å lese inn en string fra keyboard
 *  @param string promt
 *  @return string result
 */
string getln(string promt) {
    cout << endl << promt << ": ";
	string result;
    getline(cin,result);
    return result;
}

/** Metode som overloader funksjonen getln(string promt)
 *  @param string promt		informasjonstekst
 *  @param int i
 *  @return string result
 */
string getln(string promt, int i) {
    cout << promt << " " << i << ": " << endl;
	string result;
    getline(cin,result);
    return result;
}

/** Metode for å konvertere en string til char*
 *  @param string str
 *  @return char* writable
 */
 char * convert_string_to_char(string str) {
	char * writable = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0';
	
	delete[] writable;
	return writable;
 }

 /** Metode for å teste om brukeren har trykket enter på keyboardet
  *  @param string temp
  *  @return bool
  */
bool did_the_user_press_enter(string temp) {
	if(temp.empty())
		return true;
	return false;
}

/** Metode for å sjekke om ankomst-datoen som er blitt tastet inn er gyldig
 *  @param int ankomst
 *  @param int avreise
 *  @param int dagens_dato
 *  @return bool
 */
bool gyldig_ankomst(int ankomst, int avreise, int dagens_dato) {
	if((ankomst >= dagens_dato) && (ankomst < avreise) ) 
		return true;
	return false;
}

/** Metode for å teste om reservasjonen ikke inneholder noen beboere
 *  @param string temp
 *  @param int counter	antall beboeres
 */
bool ingen_beboere(string temp, int counter){
						//dersom brukeren trykket enter og ingen beboere er registrert
	if((temp.empty()) && (counter == 0))	
		return true;	//ingen beboere
						//dersom brukeren trykket enter og 1 eller fler beboere er registrert
	if((temp.empty()) && (counter > 0))		
		return false;	//beboere
	return true;	//ellers true
}