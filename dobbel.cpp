//
//  dobbel.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "dobbel.h"
#include "utils.h"

Dobbel::Dobbel() {
    
}

Dobbel::Dobbel(int romnr) : Rom(romnr) {
    
}

/**
 *	Dobbeltrom konstrukt�ren.
 *	Sender romnummer opptil rom. 
 *	@param int romnr	romnummret
 *	@param ifstream &file 
 */
Dobbel::Dobbel(int romnr, ifstream &file): Rom(romnr, file) {
    ekstra_seng = read_bool(file); //Setter status p� ekstraseng
}

Dobbel::~Dobbel() {
    
}

/**
 *	Skriver dobbeltrommet til fil
 *	@param ostream* ut
 */
void Dobbel::skriv_til_fil(ostream* ut) {
	Rom::skriv_til_fil(ut);	// Kj�rer rom sin skriv ut metode.
	*ut << ekstra_seng << "\n";
}