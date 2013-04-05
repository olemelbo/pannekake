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
#include "regning.h"

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
    
    regninger = new List(FIFO);
    int antall_regninger = read_int(file);
    for(int i = 0; i < antall_regninger; i++) {
        char* beskrivelse = read_text(file);
        Regning* r = new Regning(beskrivelse, file);
        regninger->add(r);
    }
}

Reservasjon::~Reservasjon() {
    
}

void Reservasjon::les_fra_fil() {
   
}

void Reservasjon::skriv_til_fil(ostream* ut) {
	*ut << number << "\n"
        << avreise_dato << "\n"
		<< antall_dogn << "\n";
    
    for(int i = 0; i < antall_dogn; i++) {
        *ut << pris[i] << "\n";
    }
    
    *ut << status_seng << "\n"
        << antall_beboere << "\n";
    
    for(int i = 0; i < antall_beboere; i++) {
        *ut << navn[i] << "\n";
    }
    
    *ut << regninger->no_of_elements() << "\n";
    
	Regning* temp;
	for (int j = 1;  j <= regninger->no_of_elements();  j++)  {
		temp = (Regning*) regninger->remove();
		temp->skriv_til_fil(ut);
		regninger->add(temp); 
	}
}

void Reservasjon::display() {
    
}