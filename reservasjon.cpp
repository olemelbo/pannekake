//
//  reservasjon.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//


#include <fstream>
#include <string>
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
                         string beboere[MAX_ARRAY]
                         ): Num_element(ankomst) {
	
	avreise_dato = avreise;
	antall_dogn = timer.forskjell_datoer(number, avreise_dato);
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
        navn[i] = beboere[i];
    }
}

Reservasjon::Reservasjon(int ankomst, ifstream &file): Num_element(ankomst) {
    avreise_dato = read_int(file);
    antall_dogn = read_int(file);
    for(int i = 0; i < antall_dogn; i++) {
        pris[i] = read_float(file);
    }
    status_seng = read_int(file);
    antall_beboere = read_int(file);
    for(int i = 0; i < antall_beboere; i++) {
        navn[i] = read_text(file);
    }
    
    regninger = new List(FIFO);
    int antall_regninger = read_int(file);
    for(int i = 0; i < antall_regninger; i++) {
        string beskrivelse = read_text(file);
		char* c = convert_string_to_char(beskrivelse);
        Regning* r = new Regning(c, file);
        regninger->add(r);
    }
}

Reservasjon::~Reservasjon() {
    
}

void Reservasjon::setAntallBeboere(int ant) {
	antall_beboere = ant;
}

void Reservasjon::setBeboere(string beboere[MAX_ARRAY]) {
	for(int i = 0; i < antall_beboere; i++) {
         navn[i] = beboere[i];
    }
}

int Reservasjon::getAvreiseDato() {
	return avreise_dato;
}

int Reservasjon::getAnkomstDato() {
	return number;
}

bool Reservasjon::is_name_in_array(string name) {
    if(navn[0].compare(name) == 0)
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
	cout << "Ankomst: " << number << "\n"
		 << "Avreise: " << avreise_dato << "\n"
		 << "Antall d>gn: " << antall_dogn << "\n"
		 << "Antall beboere: " << antall_beboere << "\n";
	for(int i = 0; i < antall_beboere; i++) {
        cout << "Navn paa beboere: " << navn[i] << "\n";
    }
}

void Reservasjon::display_faktura() 
{
	cout << "/////////////////// FAKTURA //////////////////////" << endl; 
	cout << "Ankomst: " << number << "\n"
		 << "Avreise: " << avreise_dato << "\n"
		 << "Antall d>gn: " << antall_dogn << "\n"
		 << "Antall beboere: " << antall_beboere << "\n";
	for(int i = 0; i < antall_beboere; i++) {
        cout << "Navn paa beboere: " << navn[i] << "\n";
    }
	int total = 0;
	int antall_dogn = timer.forskjell_datoer(number, avreise_dato);
	int pris = 100;
	total += antall_dogn * pris;
	cout << "Pris for overnatting: " <<  total << endl;
	cout << "Totalt: " << total;
}

void Reservasjon::skriv_faktura_til_fil(string fil)
{

}

void Reservasjon::display_list(int count){
	cout << "- Reservasjon "<<count<<": Fra "<<number<<" til "<<avreise_dato<<endl;
}

void Reservasjon::endre_ankomst(int ankomst){
	number = ankomst;
}

void Reservasjon::endre_avreise(int avreise){
	avreise_dato = avreise;
}
void Reservasjon::set_innsjekk(bool svar){
	innsjekket = svar;
}
bool Reservasjon::er_innsjekket(){
	return innsjekket;
}
