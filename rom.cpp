//
//  rom.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#include "rom.h"
#include <fstream>
#include "utils.h"
#include "reservasjon.h"
#include "timer.h"

using namespace std;

extern Timer timer;

Rom::Rom() {
    
}

/** 
 * Rom konstruktør, sender romnummer til Num_element. 
 * Så rommet blir sortert etter romnummer.
 * @param int romnr		romnummret
 */ 
Rom::Rom(int romnr): Num_element(romnr) {
    
}
/**
 *	Rom konstruktøren, sender romnummer til Num_element
 *	@param int romnr	romnummeret
 *	@param ifstream &file
 */
Rom::Rom(int romnr, ifstream &file): Num_element(romnr) {
    ant_senger = read_int(file);	// Leser inn antall senger
    frokost_inkludert = read_bool(file);	// Leser inn frokost inkludert
    reservasjoner = new List(Sorted);	// Oppretter en liste med reservasjoner
    int antall_reservasjoner = read_int(file);	// Leser inn antall reservasjoner
    for (int i = 0; i < antall_reservasjoner; i++) {
        int ankomst = read_int(file);	// Leser inn ankomst dato.
        Reservasjon* res = new Reservasjon(ankomst, file);	// Oppretter en ny reservasjon
        reservasjoner->add(res);	// Legger reservasjonen til i listen over reservasjoner
    }
}

Rom::~Rom() {
    delete reservasjoner;  //Frigir minne fra heap.
}

/**
 *	Skriver rommet til fil.
 *	@param ostream* ut
 */
void Rom::skriv_til_fil(ostream* ut) {
	
    *ut << number << "\n"
        << ant_senger << "\n"
        << frokost_inkludert << "\n"
        << reservasjoner->no_of_elements() << "\n";
    
    Reservasjon* temp;
    // Looper igjennom antall reservasjoner
	for (int i = 1;  i <= reservasjoner->no_of_elements();  i++)  {
		temp = (Reservasjon*) reservasjoner->remove_no(i);	// Henter ut en reservasjon
		temp->skriv_til_fil(ut);		// Skriver reservasjonen til fil
		reservasjoner->add(temp);	// Legger reservasjonen tilbake i listen
	}

}
/**
 *	Displayer rommet.
 */
void Rom::display() {
	cout << "Romnummer: " << number << endl;
	cout << "Antall senger: " << ant_senger << endl;
	if(frokost_inkludert) {
		cout << "Frokost er inkludert" <<endl;
	} else {
		cout << "Frokost er ikke inkludert " << endl;
	}
}

/**
 *	Sjekker om rommet er ledig 
 */
bool Rom::ledig(int ankomst) {
	// Henter ut antall reservasjoner
    int antall_reservasjoner = reservasjoner->no_of_elements();
    bool ledig = true;
    // Looper gjennom alle reservasjoner
    for(int i = 0; i < antall_reservasjoner; i++) {
		// Henter ut en reservasjon
        Reservasjon* reservasjon = (Reservasjon*) reservasjoner->remove_no(i);
        // Sjekker om tidsperioden er ledig.
		if(ankomst > reservasjon->getAnkomstDato() && ankomst < reservasjon->getAvreiseDato()) {
            ledig = false;
        }
		// Legger reservasjonen tilbake i listen med reservasjoner
        reservasjoner->add(reservasjon);
    }
    
    return ledig;	// Retunerer true eller false.
}

/**
 *	Sjekker om rom er ledig i en tidsperiode
 *	@param int ankomst		ankomstdato
 *	@param int avreise		avreisedato
 *	@return bool			retunerer om perioden er ledig eller ikke
 */
bool Rom::ledig(int ankomst, int avreise) {
	Reservasjon* reservasjon;
	// Antall reservasjoner
	int antall_reservasjoner = reservasjoner->no_of_elements();
	for(int j = 1; j <= antall_reservasjoner; j++) {
		reservasjon = (Reservasjon*) reservasjoner->remove_no(j);	// Henter ut en reservasjon
		// Sjekker om perioden er ledig
		if(ankomst <= reservasjon->getAvreiseDato() && avreise >= reservasjon->getAnkomstDato())	
            return false;
		// Legger reservasjonen tilbake i listen over reservasjoner
        reservasjoner->add(reservasjon);
	}
    
    return true;
    
}

/**
 * Returnerer romnummretet
 * @return int number romnummer
 */
int Rom::getRomNummer() {
	return number;
}

/**
 *	Retunerer listen med rom
 *	@return reservasjoner
 */
List* Rom::get_reservasjoner() {
    return reservasjoner;
}
