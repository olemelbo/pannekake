//
//  reservasjon.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
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

Reservasjon::Reservasjon() {                                                  //| 
    //Konstruktør som ikke brukes
}

//Konstruktør med parametere som oppretter en reservasjon
Reservasjon::Reservasjon(int ankomst,	//ankomstdato
                         int avreise,	//avreisedato
                         int romt,		//romtype
                         bool frokost,	//ønsker frokost
                         bool seng,		//ønsker ekstra seng
                         int ant_beboere,	//antall beboere på rommet
                         string beboere[MAX_ARRAY]	//array med navn på beboere
                         ): Num_element(ankomst) {  //sortert på ankomstdato
	
	avreise_dato = avreise;
    
    romtype = romt;
    
    innsjekket = false;	//Standard for oppretting av reservasjon
    
										//Regner ut antall døgn
	antall_dogn = timer.forskjell_datoer(number, avreise_dato);
    
    Pris* prs = new Pris(number, avreise_dato);	//lager et nytt pris-objekt
    int dato = ankomst;

    for(int i = 0; i < antall_dogn; i++) {  //Looper igjennom alle døgnene
        pris[i] = prs->hent_pris(romtype, dato); //Henter ut prisen på gitt dato
        dato = timer.nestedato(dato);	//Henter ut neste dato
    }
    
	if(seng == true){  //Dersom reservatør ønsker ekstra seng
		status_seng = 1;	//settes status_seng til 1
	} else {
        status_seng = 0;	//ellers settes den til 0
    }

	if(frokost == true){  //Dersom reservatør ønsker forkost
		status_frokost = 1;	//status_frokost settes til 1
	}
	else status_frokost = 0; //ellers settes den til 0
	
	antall_beboere = ant_beboere;
    
    for(int i = 0; i < ant_beboere; i++) {
        navn[i] = beboere[i]; //Legger inn navnene på beboerene i beboere-arrayen
    }
}

/** Konstruktør som henter informasjon om reservasjon fra fil
 *	@param int ankomst	ankomst-dato
 *	@param ifstream &file 
 */
Reservasjon::Reservasjon(int ankomst, ifstream &file): Num_element(ankomst) {
    avreise_dato = read_int(file);	//avreisedato
    romtype = read_int(file);		//romtype
    innsjekket = read_bool(file);	//om reservasjonen er innsjekket
    antall_dogn = read_int(file);	//antall døgn reservert
    
    for(int i = 0; i < antall_dogn; i++) {//looper gjennom antall døgn
        pris[i] = read_float(file);		//lagrer prisen per døgn i arrayen pris
    }
    status_seng = read_int(file);	//leser inn status på ekstra seng
	status_frokost = read_int(file);	//leser inn status på frokost
    antall_beboere = read_int(file);	//leser inn antall beboere
    for(int i = 0; i < antall_beboere; i++) { //lagrer navnet på beboerene i arrayen navn
        navn[i] = read_text(file);
    }
    
    regninger = new List(FIFO);		//Lager en ny liste i reservasjonen for regninger
    int antall_regninger = read_int(file);	//antall regninger
    for(int i = 0; i < antall_regninger; i++) {  //looper gjennom alle regningene
        string beskrivelse = read_text(file);	//regning beskrivelse
		char* c = convert_string_to_char(beskrivelse);	//konverterer stringen til en char-peker
        Regning* r = new Regning(c, file);	//oppretter et nytt regning-objekt
        regninger->add(r);	//Legger regningen inn i lista over regninger
    }
}

//Destruktor for reservasjon
Reservasjon::~Reservasjon() {
    delete regninger;
}
/** Metode for å sette antall beboere på reservasjonen
 *	@param int ant	antall beboere
 */
void Reservasjon::setAntallBeboere(int ant) {
	antall_beboere = ant;
}

/** Metode som lagrer navnene på beboerne
 *	@param array string beboere		navnet på beboerne
 *	@param int teller	antall beboere
 */
void Reservasjon::setBeboere(string beboere[MAX_ARRAY], int teller) {
	for(int i = 0; i < teller; i++) {  //looper gjennom antall beboere
		navn[antall_beboere++] = beboere[i];	//lagrer navnene i arrayen navn
    }
}

/** Metode for å hente avreise-dato
 *	@return int avreise_dato
 */
int Reservasjon::getAvreiseDato() {
	return avreise_dato;
}

/** Metode for å hente ankomst-dato
 *  @return itn number	ankomst-dato
 */
int Reservasjon::getAnkomstDato() {
	return number;
}

/** Metode for å hente ut antall beboere
 *  @return int antall_beboere
 */
int Reservasjon::getAntallBeboere() {
	return antall_beboere;
}

/** Metode for å sjekke om et navn er reservatør for reservasjonen
 *  @param string name	reservatørens navn
 *  @return bool
 */
bool Reservasjon::is_name_in_array(string name) {
    if(navn[0].compare(name) == 0)
        return true;
    else
        return false;
}

//Metode for å lese reservasjon fra fil
void Reservasjon::les_fra_fil() {
   //Brukes ikke, utføres i konstruktør
}

/** Metode for å skrive reservasjonen til fil
 *  @param ostream* ut
 */
void Reservasjon::skriv_til_fil(ostream* ut) {
	*ut << number << "\n"	//ankomst-dato
        << avreise_dato << "\n"	//avreise-dato
		<< antall_dogn << "\n";	//antall døgn
    
    for(int i = 0; i < antall_dogn; i++) {  //looper gjennom alle døgnene
        *ut << pris[i] << "\n";	//lagrer pris per døgn
    }
    
    *ut << status_seng << "\n"	//status for ekstra seng
		<< status_frokost << "\n"	//status for frokost
        << antall_beboere << "\n";	//antall beboere
    
    for(int i = 0; i < antall_beboere; i++) {  //looper gjennom antall beboere
        *ut << navn[i] << "\n";		//lager navnet på beboerne i arrayen navn
    }
    
    *ut << regninger->no_of_elements() << "\n";	//antall regninger
    
	Regning* temp;
										//looper gjennom alle regnignene
	for (int j = 1;  j <= regninger->no_of_elements();  j++)  {
		temp = (Regning*) regninger->remove();	//henter ut regningen
		temp->skriv_til_fil(ut);	//skriver den til fil
		regninger->add(temp);	//legger den tilbake i listen
	}
}

/** Metode for å vise informasjon om reservasjonen
 */
void Reservasjon::display() {
	cout << "Ankomst: " << number << "\n"
		 << "Avreise: " << avreise_dato << "\n"
		 << "Antall d>gn: " << antall_dogn << "\n"
		 << "Antall beboere: " << antall_beboere << "\n";
	for(int i = 0; i < antall_beboere; i++) {  //looper gjennom alle beboerne
        cout << "Navn paa beboere: " << navn[i] << "\n";
    }
}

/** Metode for å vise informasjon om reservasjonens romtype
 *  @param Rom* rom
 */
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

/** Metode for å vise reservasjonens faktura
 */
void Reservasjon::display_faktura() 
{
	int pris_seng = 0;
	int pris_frokost = 0;
	Regning* regning;
	if(status_seng == true){
	cout << "Ekstra seng\n";
	pris_seng = hotellet->get_pris_seng();	//henter ut prisen for ekstra seng
	}
	else cout << "Uten ekstra seng\n";

	if(status_frokost == true){
		cout << "Med frokost\n";
		pris_frokost = hotellet->get_pris_frokost();	//henter ut prisen for frokost
	}
	else cout << "Uten frokost\n";

	int total = 0;
	int overnatting = 0;

	for(int i = 0; i < antall_dogn; i++) {  //looper gjennom antall døgn
        overnatting += pris[i];	//regner ut prisen for hele overnattingen
    }

	float tot_regninger = 0;

	int antall_regninger = regninger->no_of_elements();	//antall regninger

	for (int j = 1;  j <= antall_regninger;  j++)  { //looper gjennom antall regninger
		regning = (Regning*) regninger->remove();	//henter ut regning
		tot_regninger += regning->hent_sum();	//henter summen på regningen
		regninger->add(regning);	//legger regningen tilbake i listen
	}

												//regner ut totalen
	total = overnatting + tot_regninger + pris_frokost + pris_seng;

	cout << "Pris for overnatting: " <<  overnatting << endl;
	cout << "Totalt: " << total;
}

/** Metode for å skrive fakturaen til fil
 *  @param string fil
 */
void Reservasjon::skriv_faktura_til_fil(string fil){
	int pris_frokost = 0;
	int pris_seng = 0;
	int overnatting = 0;
	int total = 0;
	float tot_regninger = 0;
	
	for(int i = 0; i < antall_dogn; i++) {  //looper gjennom antall døgn
        overnatting += pris[i];	//regner ut prisen for hele overnattingen
    }

									//looper gjennom antall regninger
	for (int j = 1;  j <= regninger->no_of_elements();  j++)  { 
									//henter ut regning
		Regning* regning = (Regning*) regninger->remove_no(j);
		tot_regninger += regning->hent_sum();	//henter summen på regningen
		regninger->add(regning);	//legger regningen tilbake i listen
	}

	if(status_frokost == true) //dersom reservatør ønsker frokost 
		pris_frokost = hotellet->get_pris_frokost();	//henter ut pris på frokost
	if(status_seng == true)	//derom reservatør ønsker ekstra seng
		pris_seng = hotellet->get_pris_seng();	//henter ut pris på ektra seng
									//regner ut totalen
	total = overnatting + tot_regninger + pris_frokost + pris_seng;
	
	ofstream utfil(fil);
	utfil.open( fil.c_str(), ios::out | ios::app );
												//skriver ut fakturaen
	utfil << "--------------FAKTURA--------------\n"
			<< "Ankomst-dato: " << number << "\n"	
			<< "Avreise-dato: " << avreise_dato << "\n"
			<< "Antall døgn: " << antall_dogn << "\n"
			<< "Antall beboere: " << antall_beboere << "\n"
			<< "Navn på beboere: \n";

	for(int i = 0; i < antall_beboere; i++) { //looper gjennom antall beboere
		utfil << navn[i] << "\n";	//skriver ut beboerene sitt navn
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

/** Metode for å skrive ut en liste med reservasjoner
 *  @param int count	nummer i listen
 */
void Reservasjon::display_list(int count){
	cout << "- Reservasjon "<<count<<": Fra "<<number<<" til "<<avreise_dato<<endl;
}

/** Metode for å endre ankomst-dato
 *  @param int ankomst
 */
void Reservasjon::endre_ankomst(int ankomst){
	number = ankomst;
}

/** Metode for å endre avreise-dato
 *  @param int avreise
 */
void Reservasjon::endre_avreise(int avreise){
	avreise_dato = avreise;
}

/** Metode som setter at reservasjonen er innsjekket
 */
void Reservasjon::set_innsjekk(){
	innsjekket = true;
}

/** Metode som setter at reservasjonen er utsjekket
 */
void Reservasjon::set_utsjekk(){
	innsjekket = false;
}

/** Metode som sjekker om reservasjonen er innsjekket
 *  @return bool innsjekket
 */
bool Reservasjon::er_innsjekket(){
	return innsjekket;
}

/** Metode som sjekker om reservasjonen er ledig i en gitt tidsperiode
 *  @param int avreise
 *  @param int ankomst
 *  @param int teller
 *  @param int antall_reservasjoner
 */
void Reservasjon::ledig_i_tidsperiode(int avreise, int ankomst, int teller, int antall_reservasjoner) {
	if(teller == antall_reservasjoner) 
		cout << "Rommet er ledig fra : " << avreise << " - " << endl;
	cout << "Rommer er ledig fra: " << avreise << " - " << ankomst << endl;
}

/** Metode som setter status for ekstra seng
 *  @param  int status
 */
void Reservasjon::set_seng_status(int status){
	status_seng = status;
}
/** Metode for å hente statusen for ekstra seng
 *  @return int status_seng
 */
int Reservasjon::get_status_seng(){
	return status_seng;
}
