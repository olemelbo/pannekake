//
//  suite.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "suite.h"

Suite::Suite() {
    //Konstruktør som ikke er i bruk
}

Suite::Suite(int romnr): Rom(romnr) {
    //Konstruktør med parameter romnr som ikke er i bruk
}

/** Metode for å lese fra fil
 *  @param int romnr
 *  @param iftrea &file
 */
Suite::Suite(int romnr, ifstream &file): Rom(romnr, file) {
    antall_senger = read_int(file);
    antall_kvadratmeter = read_int(file);
	beskrivelse = read_text(file);
}

//Destruktor
Suite::~Suite() {
    
}

/** Metode for å vise informason om rommet og romtypen
 */
void Suite::display() {
	Rom::display();	//viser informasjonen om rommet
	cout << "Antall senger: " << antall_senger << endl;
	cout << "Antall kvadratmeter: " << antall_kvadratmeter << endl;
	cout <<  beskrivelse << endl;
}

/** Metode for å skrive suiten til fil
 *  @param ostream* ut
 */
void Suite::skriv_til_fil(ostream* ut) {
	Rom::skriv_til_fil(ut);	//skriver rommet til fil
	*ut << antall_senger << "\n"
		<< antall_kvadratmeter << "\n"
		<< beskrivelse << "\n";
}