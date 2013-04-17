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
#include "pris.h"
#include "hotell.h"
#include "singel.h"
#include "dobbel.h"
#include "suite.h"

using namespace std;

extern Timer timer;
extern Hotell* hotellet;

Reservasjon::Reservasjon() {
    
}

Reservasjon::Reservasjon(int ankomst,
                         int avreise,
                         int romt,
                         bool frokost,
                         bool seng,
                         int ant_beboere,
                         string beboere[MAX_ARRAY]
                         ): Num_element(ankomst) {
	
	avreise_dato = avreise;
    
    romtype = romt;
    
    //Standard for oppretting av reservasjon
    innsjekket = false;
    
	antall_dogn = timer.forskjell_datoer(number, avreise_dato);
    
    Pris* prs = new Pris(number, avreise_dato);
    int dato = ankomst;
    for(int i = 0; i < antall_dogn; i++) {
        pris[i] = prs->hent_pris(romtype, dato);
        dato = timer.nestedato(dato);
    }
    
	if(seng == true){
		status_seng = 1;
	} else {
        status_seng = 0;
    }

	if(frokost == true){
		status_frokost = 1;
	}
	else status_frokost = 0;
	
	antall_beboere = ant_beboere;
    
    for(int i = 0; i < ant_beboere; i++) {
        navn[i] = beboere[i];
    }
}

Reservasjon::Reservasjon(int ankomst, ifstream &file): Num_element(ankomst) {
    avreise_dato = read_int(file);
    romtype = read_int(file);
    innsjekket = read_bool(file);
    antall_dogn = read_int(file);
    
    for(int i = 0; i < antall_dogn; i++) {
        pris[i] = read_float(file);
    }
    status_seng = read_int(file);
	status_frokost = read_int(file);
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

void Reservasjon::setBeboere(string beboere[MAX_ARRAY], int teller) {
	for(int i = 0; i < teller; i++) {
		navn[antall_beboere++] = beboere[i];
    }
}

int Reservasjon::getAvreiseDato() {
	return avreise_dato;
}

int Reservasjon::getAnkomstDato() {
	return number;
}

int Reservasjon::getAntallBeboere() {
	return antall_beboere;
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
		<< status_frokost << "\n"
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

void Reservasjon::display(Rom* rom) {
	if(rom) {
		if(romtype == SINGEL) {
			rom = (Singel*) rom;
			rom->display();
		}
		if(romtype == DOBBEL) {
			rom = (Dobbel*) rom;
			rom->display();
		}
		if(romtype == SUITE) {
			rom = (Suite*) rom;
			rom->display();
		}
		display();
	} else {
		display();
	}
}

void Reservasjon::display_faktura() 
{
	int pris_seng = 0;
	int pris_frokost = 0;
	Regning* regning;
	if(status_seng == true){
	cout << "Ekstra seng\n";
	pris_seng = hotellet->get_pris_seng();
	}
	else cout << "Uten ekstra seng\n";

	if(status_frokost == true){
		cout << "Med frokost\n";
		pris_frokost = hotellet->get_pris_frokost();
	}
	else cout << "Uten frokost\n";

	int total = 0;
	int overnatting = 0;

	for(int i = 0; i < antall_dogn; i++) {
        overnatting += pris[i];
    }

	float tot_regninger = 0;

	int antall_regninger = regninger->no_of_elements();

	for (int j = 1;  j <= antall_regninger;  j++)  { 
		regning = (Regning*) regninger->remove();
		tot_regninger += regning->hent_sum();
		regninger->add(regning);
	}

	total = overnatting + tot_regninger + pris_frokost + pris_seng;//LEgge på frokost, ekstra seng

	cout << "Pris for overnatting: " <<  overnatting << endl;
	cout << "Totalt: " << total;
}

void Reservasjon::skriv_faktura_til_fil(string fil){
	int pris_frokost = 0;
	int pris_seng = 0;
	int overnatting = 0;
	int pris = 100;
	overnatting += antall_dogn * pris;
	int total = 0;
	float tot_regninger = 0;
	for (int j = 1;  j <= regninger->no_of_elements();  j++)  { 
		Regning* regning = (Regning*) regninger->remove_no(j);
		tot_regninger += regning->hent_sum();
		regninger->add(regning);
	}
	if(status_frokost == true)
		pris_frokost = hotellet->get_pris_frokost();
	if(status_seng == true)
		pris_seng = hotellet->get_pris_seng();
	total = overnatting + tot_regninger + pris_frokost + pris_seng;
	
	ofstream utfil(fil);
	utfil.open( fil.c_str(), ios::out | ios::app );
	utfil << "--------------FAKTURA--------------\n"
			<< "Ankomst-dato: " << number << "\n"
			<< "Avreise-dato: " << avreise_dato << "\n"
			<< "Antall døgn: " << antall_dogn << "\n"
			<< "Antall beboere: " << antall_beboere << "\n"
			<< "Navn på beboere: \n";
	for(int i = 0; i < antall_beboere; i++) {
		utfil << navn[i] << "\n";
	}
	if(status_seng == true){
		utfil << "Med ekstra seng\n";
	}
	if(status_frokost == true){
		utfil << "Med frokost\n";
	}
	utfil << "Antall regninger: " << regninger->no_of_elements() << "\n"
			<< "Total sum på regninger: " << tot_regninger << "\n"
			<< "Total sum på overnatting: " << overnatting << "\n"
			<< "Total pris: " << total << "\n";
	
    utfil.close();
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
void Reservasjon::set_innsjekk(){
	innsjekket = true;
}

void Reservasjon::set_utsjekk(){
	innsjekket = false;
}
bool Reservasjon::er_innsjekket(){
	return innsjekket;
}

void Reservasjon::set_seng_status(int status){
	status_seng = status;
}

int Reservasjon::get_status_seng(){
	return status_seng;
}
