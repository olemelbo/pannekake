//
//  hotell.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
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

Hotell::Hotell(string fil) {
    
    ifstream infile(fil);
    if(infile.is_open()) {
        
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
        
        for(int i = 0; i < antall_fasciliteter; i++) {
            fasciliteter[i] = read_text(infile);
        }
        
        rom[SINGEL] = new List(Sorted);
        int antall_singel = read_int(infile);
        
        for(int i = 0; i < antall_singel; i++) {
            int romnr = read_int(infile);
            Singel* s = new Singel(romnr, infile);
            rom[SINGEL]->add(s);
        }
        
        rom[DOBBEL] = new List(Sorted);
        int antall_dobbel = read_int(infile);
        
        for(int i = 0; i < antall_dobbel; i++) {
            int romnr = read_int(infile);
            Dobbel* d = new Dobbel(romnr, infile);
            rom[DOBBEL]->add(d);
        }
        
        rom[SUITE] = new List(Sorted);
        int antall_suiter = read_int(infile);
        
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
    
}

void Hotell::les_fra_fil() {
    
}

void Hotell::skriv_til_fil(ostream* ut) {
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

	// Looper igjennom fasiliteter
    for(int i = 0; i < antall_fasciliteter; i++) {
		*ut << fasciliteter[i] << "\n";
	}
	
	int antall_singel = rom[SINGEL]->no_of_elements();
	*ut << antall_singel << "\n";

	for(int i = 1; i <= antall_singel; i++) {
		singel = (Singel*) rom[SINGEL]->remove_no(i);
		singel->skriv_til_fil(ut);
		rom[SINGEL]->add(singel);        
	}

	int antall_dobbel = rom[DOBBEL]->no_of_elements();
	*ut << antall_dobbel << "\n";
	for(int i=1; i <= antall_dobbel; i++) {
		dobbel = (Dobbel*) rom[DOBBEL]->remove_no(i);
		dobbel->skriv_til_fil(ut);
		rom[DOBBEL]->add(dobbel);
	}

	int antall_suiter = rom[SUITE]->no_of_elements();
	*ut << antall_suiter << "\n";
	for(int i=1; i <= antall_suiter; i++) {
		suite = (Suite*) rom[SUITE]->remove_no(i);
		suite->skriv_til_fil(ut);
		rom[SUITE]->add(suite);
	}
}

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

List* Hotell::get_rom(int romtype) {
	return rom[romtype];
}

Rom* Hotell::get_spesifikk_rom(int romnr) {
    for(int kat = 0; kat < ANTALL_ROMTYPER; kat++) {
        for(int j = 1; j <= get_rom(kat)->no_of_elements(); j++) {
            if(get_rom(kat)->in_list(romnr)) {
                Rom* r = (Rom*) get_rom(kat)->remove_no(j);
                get_rom(kat)->add(r);
                return r;
            }
        }
    }
    
    return NULL;
}

string Hotell::get_filnavn() {
	return filnavn;
}

Rom* Hotell::get_ledig_rom(int romtype) {
    
    int n = rom[romtype]->no_of_elements();
    int r = rand() % n + 1;
    int x = r;
    
    bool er_ledig = false;
    Rom* rommet;
    
    while(!er_ledig && x <= n) {
        rommet = (Rom*) rom[romtype]->remove_no(x);
        er_ledig = rommet->ledig(dagens_dato);
        rom[romtype]->add(rommet);
        x++;
    }
    
    if(!er_ledig) {
        for(int i = 1; i <= r; i++) {
            rommet = (Rom*) rom[romtype]->remove_no(i);
			er_ledig = rommet->ledig(dagens_dato);
            rom[romtype]->add(rommet);
        }
    }
    
    if(!er_ledig)
        return NULL;
    
    return rommet;
    
}

int Hotell::get_pris_seng(){
	return ekstra_seng_pris;
}

int Hotell::get_pris_frokost(){
	return frokost_pris;
}