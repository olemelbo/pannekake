//
//  hotell.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "hotell.h"

using namespace std;

Hotell::Hotell() {
    
}

Hotell::Hotell(char* fil) {
    
    ifstream infile(fil);
    if(infile.is_open()) {
        
        char tmp[MAX_TEXT];
        
        //Henter antallet leger og konverterer
        infile.getline(navn, MAX_TEXT);
        infile.getline(gateadresse, MAX_TEXT);
        infile.getline(postadresse, MAX_TEXT);
        infile.getline(mailadresse, MAX_TEXT);
        
        infile.getline(tmp, MAX_TEXT);
        telefon = atoi(tmp);
        
        infile.getline(tmp, MAX_TEXT);
        fax = atoi(tmp);
        
        infile.getline(tmp, MAX_TEXT);
        frokost_pris = atoi(tmp);
        
        infile.getline(tmp, MAX_TEXT);
        ekstra_seng_pris = atoi(tmp);
        
        infile.getline(tmp, MAX_TEXT);
        antall_fasciliteter = atoi(tmp);
        
        
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

