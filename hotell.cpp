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

using namespace std;

Hotell::Hotell() {
    
}

Hotell::Hotell(char* fil) {
    
    ifstream infile(fil);
    if(infile.is_open()) {
        
        //Leser inn tekst
        navn        = read_text(infile);
        gateadresse = read_text(infile);
        postadresse = read_text(infile);
        mailadresse = read_text(infile);
        
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

void Hotell::skriv_til_fil() {
    
}

void Hotell::display() {
    cout << navn;
}

