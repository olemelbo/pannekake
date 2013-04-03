//
//  reservasjon.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//


#include <fstream>
#include "reservasjon.h"
#include "listtool.h"
#include "utils.h"

using namespace std;

Reservasjon::Reservasjon() {
    
}

Reservasjon::Reservasjon(int ankomst): Num_element(ankomst) {
    
}

Reservasjon::Reservasjon(int ankomst, ifstream &file): Num_element(ankomst) {
    avreise_dato = read_int(file);
    antall_dogn = read_int(file);
    for(int i = 0; i < antall_dogn; i++) {
        pris[i] = read_int(file);
    }
    status_seng = read_int(file);
    antall_beboere = read_int(file);
    for(int i = 0; i < antall_beboere; i++) {
        navn[i] = read_text(file);
    }
}

Reservasjon::~Reservasjon() {
    
}

void Reservasjon::les_fra_fil() {
    
}

void Reservasjon::skriv_til_fil() {
    
}

void Reservasjon::display() {
    
}