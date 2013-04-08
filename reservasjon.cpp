//
//  reservasjon.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//


#include <fstream>
#include <cstring>
#include "reservasjon.h"
#include "listtool.h"
#include "utils.h"
#include "regning.h"
#include "timer.h"

using namespace std;

extern Timer timer;

Reservasjon::Reservasjon() {
    
}

Reservasjon::Reservasjon(int ankomst,
                         int avreise,
                         bool frokost,
                         bool seng,
                         int ant_beboere,
                         char* beboere[MAX_ARRAY]
                         ): Num_element(ankomst) {
	
	ankomst_dato = ankomst;
	avreise_dato = avreise;
	antall_dogn = timer.forskjell_datoer(ankomst_dato, avreise_dato);
	if(seng == true){
		//status_seng = ;//???????
	} else {
        //status_seng = ;
    }

	if(frokost == true){
		status_frokost = 1;//???????
	}
	else status_frokost = 0;
	
	antall_beboere = ant_beboere;
    
    for(int i = 0; i < ant_beboere; i++) {
        navn[i] = new char[strlen(beboere[i])+1];
        strcpy(navn[i], beboere[i]);
    }
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

bool Reservasjon::is_name_in_array(char* name) {
    if(strcmp(navn[0], name) == 0)
        return true;
    else
        return false;
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