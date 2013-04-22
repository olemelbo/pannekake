//
//  regning.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "regning.h"
#include "listtool.h"
#include "utils.h"
#include <string>

using namespace std;

Regning::Regning() {
	// Denne skal ikke kjøres    
}

/**
 * Regning konstruktør
 * @param char* nvn		navnet på regningen
 * @param float total	totalsummen
 */ 
Regning::Regning(char* nvn, float total) : Text_element(nvn) {
    totalsum = total;
}

/**
 * Regning konstruktøren
 * @param char* nvn			navnet på regningen
 * @param ifstream  &file	filen
 */ 
Regning::Regning(char* nvn, ifstream &file): Text_element(nvn) {
    totalsum = read_int(file);	// Leser totalsummen fra fil.
}

Regning::~Regning() {
    
}
/**
 *	Skriver navnet og totalsummen til fil
 *	@param ostream* ut	filen
 */
void Regning::skriv_til_fil(ostream* ut) {
	*ut << text << "\n"
		<< totalsum << "\n";
}
/**
 *	Displayer navnet på regningen og totalsummen
 */
void Regning::display() {
    cout << text << ": " << totalsum << "\n";
}
/**
 *	Henter summen til regningen
 *	@return totalsum
 */
float Regning::hent_sum(){
	return totalsum;
}
