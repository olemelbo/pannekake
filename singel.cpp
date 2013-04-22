//
//  singel.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "singel.h"
using namespace std;

Singel::Singel() {
    //Konstrukt�r uten parametere som ikke brukes
}

Singel::Singel(int romnr): Rom(romnr) {
    //Konstrukt�r med parameter romnr som ikke brukes
}

/** Metode som leser fra fil
 *  @param int romnr
 *  @param ifstream& infile
 */
Singel::Singel(int romnr, ifstream& infile): Rom(romnr, infile) {
    //Brukes ikke
}

//Destruktor
Singel::~Singel() {

}

/** Metode for � skrive til fil
 *  @param ostream* ut
 */
void Singel::skriv_til_fil(ostream* ut) {
	Rom::skriv_til_fil(ut);//skriver rommet til fil
}

/** Metode som viser inforasjon om rommet
 */
void Singel::display() {
	Rom::display();	//kj�rer rom sin display-funksjon
}