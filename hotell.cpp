//
//  hotell.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//	
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "listtool.h"
#include "hotell.h"
#include "utils.h"
#include <string>

using namespace std;

extern int dagens_dato;

Hotell::Hotell() {
    
}

/**
 * Hotell konstruktløren. Oppretter hotellet ved å lese inn fra fil.
 * @param string	fil
 * 
 */
Hotell::Hotell(string fil) {
    // Finner filen.
    ifstream infile(fil);
    if(infile.is_open()) { // Leser inn, mens filen er åpen.
        
        //Leser inn tekst
        navn        = read_text(infile);
        gateadresse = read_text(infile);
        postadresse = read_text(infile);
        mailadresse = read_text(infile);
        filnavn = read_text(infile);
        //Leser inn nummer
        telefon             = read_int(infile);
        fax                 = read_int(infile);
        frokost_pris        = read_int(infile);
        ekstra_seng_pris    = read_int(infile);
        antall_fasciliteter = read_int(infile);
        
		// Looper gjennom antall fasiliterer lagrer de i arrayen
        for(int i = 0; i < antall_fasciliteter; i++) {
            fasciliteter[i] = read_text(infile);
        }
        
		// Oppretter en liste for singel rom
        rom[SINGEL] = new List(Sorted);
        int antall_singel = read_int(infile);

        // Looper gjennom antall singel rom og lagrer de i rom arrayen,
        for(int i = 0; i < antall_singel; i++) {
            int romnr = read_int(infile);
            Singel* s = new Singel(romnr, infile);
            rom[SINGEL]->add(s);
        }
        
        // Oppretter en liste for dobbel rom.
		rom[DOBBEL] = new List(Sorted);
        int antall_dobbel = read_int(infile);
        // Looper gjennom antall dobbel rom og lagrer de i rom arrayen 
        for(int i = 0; i < antall_dobbel; i++) {
            int romnr = read_int(infile);
            Dobbel* d = new Dobbel(romnr, infile);
            rom[DOBBEL]->add(d);
		}
        
		// Oppretter en liste for suiter
        rom[SUITE] = new List(Sorted);
        int antall_suiter = read_int(infile);
        // Looper gjennom antall suiter og legger de til i rom arrayen.
		for(int i = 0; i < antall_suiter; i++) {
			int romnr = read_int(infile);
            Suite* s = new Suite(romnr, infile);
            rom[SUITE]->add(s);
		}
    } else {
        cout << "Kunne ikke lese filen.";
    }
    
 
}

Hotell::~Hotell() {
    for(int i = 0; i < ANTALL_ROMTYPER; i++) {
        for(int j = 1; j <= rom[i]->no_of_elements(); j++) {
            Rom* rom_for_sletting = (Rom*) rom[i]->remove();
            delete rom_for_sletting;
        }
    }
}
/**
 *	Skriver hotellet til fil
 *  @param ostream* ut
 */
void Hotell::skriv_til_fil(ostream* ut) {
	// Oppretter pekere til rom
	Singel* singel; 
	Dobbel* dobbel;
	Suite*	suite;

	*ut << navn << "\n"
	<< gateadresse << "\n"
	<< postadresse << "\n"
	<< mailadresse << "\n"
	<< filnavn <<	"\n"
	<< telefon << "\n" 
	<< fax << "\n"
	<< frokost_pris << "\n"
	<< ekstra_seng_pris << "\n"
	<< antall_fasciliteter << "\n";

	// Looper igjennom fasiliteter og skriver de til fil
    for(int i = 0; i < antall_fasciliteter; i++) {
		*ut << fasciliteter[i] << "\n";
	}
	
	// Skriver antall singel rom til fil
	int antall_singel = rom[SINGEL]->no_of_elements();
	*ut << antall_singel << "\n";
	// Looper igjennom en rom kategori og skriver den til fil.
	for(int i = 1; i <= antall_singel; i++) {
		singel = (Singel*) rom[SINGEL]->remove_no(i); // Henter rom fra rom listen
		singel->skriv_til_fil(ut);	// Skriver rommet til fil.
		rom[SINGEL]->add(singel);	// Legger rommet tilbake i listen.
	}
	// skriver antall dobbeletrom til fil
	int antall_dobbel = rom[DOBBEL]->no_of_elements();
	*ut << antall_dobbel << "\n";
	// Looper  gjennom antall dobbelt rom og skriver de til fil
	for(int i=1; i <= antall_dobbel; i++) {
		dobbel = (Dobbel*) rom[DOBBEL]->remove_no(i); // Henter rom fra listen
		dobbel->skriv_til_fil(ut); // Skriver rommet til fil.
		rom[DOBBEL]->add(dobbel); // Legger rommet tilbake i listen.
	}

	// Skriver antall suiter til fil
	int antall_suiter = rom[SUITE]->no_of_elements();
	*ut << antall_suiter << "\n";
	// Looper gjennom antall suiter og skriver de til fil
	for(int i=1; i <= antall_suiter; i++) {
		suite = (Suite*) rom[SUITE]->remove_no(i); // Henter rom fra listen
		suite->skriv_til_fil(ut); // Skriver rommet til fil.
		rom[SUITE]->add(suite); // Legger rommet tilbake i listen
	}
}

/**
 * Displayer hotellet på skjermen.
 */ 
void Hotell::display() {
    cout << navn << endl;
	cout << gateadresse << endl;
	cout << postadresse << endl;
	cout << mailadresse << endl;
	cout << "Filnavn: " << filnavn << endl;
	cout << telefon << endl;
	cout << fax << endl;
	cout << frokost_pris << endl;
	cout << ekstra_seng_pris << endl;
	cout << "Fasiliteter: " << endl;
	for(int i = 0; i < antall_fasciliteter; i++) {
		cout << " - " <<  fasciliteter[i] << endl;
	}
}

/** 
 *	Henter rom innenfor en kategori fra hotellet.
 *	@param int romtype
 *	@return List* romtype.
 */
List* Hotell::get_rom(int romtype) {
	return rom[romtype];
}

/**
 *	Henter et spesifikt rom fra hotellet.
 *	@param int romnr
 *	@return Rom* r;
 */
Rom* Hotell::get_spesifikk_rom(int romnr) {
	// Looper igjennom antall rom typer
    for(int kat = 0; kat < ANTALL_ROMTYPER; kat++) {
		// Looper gjennom alle rom innen for en kategori
        for(int j = 1; j <= get_rom(kat)->no_of_elements(); j++) {
			// Sjekker om romnummeret er i listen av rom
            if(get_rom(kat)->in_list(romnr)) {
                Rom* r = (Rom*) get_rom(kat)->remove_no(j); // Henter ut rommet
                get_rom(kat)->add(r); // Legger det tilbake i kategorien
                return r; // returnerer rommet.
            }
        }
    }
    
    return NULL;
}

string Hotell::get_filnavn() {
	return filnavn; // returner filnavnet til hotellet.
}

/**
 *	Henter ut et (random) hotell rom fra listen over hotell rom.
 *
 */

Rom* Hotell::get_ledig_rom(int romtype, int ankomst, int avreise) {
    
    int n = rom[romtype]->no_of_elements();
    int r = rand() % n + 1;
    int x = r;
    
    bool er_ledig = false;
    Rom* rommet;
    
    while(!er_ledig && x <= n) {
        rommet = (Rom*) rom[romtype]->remove_no(x);
        er_ledig = rommet->ledig(ankomst, avreise);
        rom[romtype]->add(rommet);
        x++;
    }
    
    if(!er_ledig) {
        for(int i = 1; i <= r; i++) {
            rommet = (Rom*) rom[romtype]->remove_no(i);
			er_ledig = rommet->ledig(ankomst, avreise);
            rom[romtype]->add(rommet);
        }
    }
    
    if(!er_ledig)
        return NULL;
    
    return rommet;	// Returnerer rommet.
    
}

int Hotell::get_pris_seng(){
	return ekstra_seng_pris;	// Returnerer prisene paa ekstra seng
}

int Hotell::get_pris_frokost(){
	return frokost_pris;	/// Returnerer prisen på frokost
}