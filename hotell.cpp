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
#include "hotell.h"
#include "utils.h"

using namespace std;

Hotell::Hotell() {
    
}

Hotell::Hotell(char* fil) {
    
    ifstream infile(fil);
    if(infile.is_open()) {
        
        char tmp[MAX_TEXT];
        
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

