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

using namespace std;

Hotell::Hotell() {
    
}

Hotell::Hotell(char* fil) {
    
    ifstream infile(fil);
    if(infile.is_open()) {
        
        char tmp[MAX_TEXT];
        
        
        read_line(navn, infile);
        
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


void Hotell::read_line(char* pointer, ifstream& file) {
    
    char tmp[MAX_TEXT];
    char* p;
    //Henter antallet leger og konverterer
    file.getline(tmp, MAX_TEXT);
    p = new char[strlen(tmp)+1];
    strcpy(p, tmp);
    pointer = p;
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

