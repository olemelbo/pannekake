#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "proc.h"
#include <algorithm>
#include "coen.h"
#include "hotell.h"
#include "reservasjon.h"
#include "utils.h"
#include "reg_post.h"
#include <sstream>

using namespace std;

// Extern 
extern Hotell* hotellet;
extern int dagens_dato;
extern Reg_post reg_post;

char les_kommando() {
char cmd;
    cout << endl << "Tast inn kommando: ";
    cin >> cmd; cin.ignore();
    return toupper(cmd);
}

void skriv_meny()  {
	cout << "\n\nF>lgende kommandoer er lovlig:";
	cout << "\n\tB - Bestill/reserver/book et rom";
	cout << "\n\tA - Avbestill et rom";
	cout << "\n\tI - Innsjekking paa(ankomst til) hotellet";
	cout << "\n\tU - Utsjekking(avreise) fra hotellet";
	cout << "\n\tR - Registrer/legg inn en regning paa et rom";
	cout << "\n\tZ - Endre ankomst -og/eller avreisedato f>r innsjekking paa hotellet";
	cout << "\n\tX - Beskrivelse av alle hotellers suiter";
	cout << "\n\tC - Bytte til et annet (ledig) rom enn det tildelte";
	cout << "\n\tS - hoveddatene om ett hotell";
	cout << "\n\tD - beskrivelse av alle hotellets suiter";
	cout << "\n\tF - alle reservasjoner som står i en persons navn";
	cout << "\n\tG - naar et rom er ledig";
	cout << "\n\tJ - alle reservasjoner for/paa et rom";
	cout << "\n\tK - alle data for ett roms nåv>erende beboer, inkludert dens regninger";
	cout << "\n\tL - alle ledeige rom i en kategori";
	cout << "\n\tT - skriv alt om hotellet til fil";
	cout << "\n\tH - Bytte over til et annet hotell";
}

void reserver_rom() {
	Reservasjon *temp;

	string romtype_tmp;
	romtype_tmp = getln("Hvilken romtype >nsker du? [Singel/Dobbel/Suite]");
    
    int romtype;
	if(romtype_tmp.compare("Singel") == 0)
        romtype = SINGEL;
    if(romtype_tmp.compare("Dobbel") == 0)
        romtype = DOBBEL;
    if(romtype_tmp.compare("Suite") == 0)
        romtype = SUITE;

	int ankomstdato;
	ankomstdato = read_int("Skriv inn annkomstdato[AAAAMMDD]");

	int avreisedato;
	ankomstdato = read_int("Skriv inn avreisedato[AAAAMMDD]");

	bool frokost = false;
	char onskerfrokost = read_char(">nsker du frokost? [y/n]");
	if(onskerfrokost == 'Y'){
		frokost = true;
	}
	
	bool ekstraseng = false;
	if(romtype == DOBBEL){
		char onskerekstraseng = read_char("Er det behov for en ekstra seng? [y/n]");
		if(onskerekstraseng == 'Y'){
			ekstraseng = true;
		}
	}

    // Prøver å hente ledig rom i angitt kategori
    Rom* r = hotellet->get_ledig_rom(romtype);
    
    // Avslutter med melding hvis det
    // ikke finnes ledige rom i kategorien.
    if(!r) {
        cout << "Det finnes ingen ledige rom i denne kategorien\n";
        return;
    }
     

	int ant = read_int("Hvor mange beboere skal reserveres?");
   

	string beboere[MAX_ARRAY];
	
	for(int i = 0; i < ant; i++) {
         beboere[i] = getln("Skriv inn navnet p> beboer", i + 1);
    }

    // Oppretter reservasjon
	temp = new Reservasjon(ankomstdato, avreisedato, frokost, ekstraseng, ant, beboere);
    
    // Legger reservasjonen til i rommet.
    r->get_reservasjoner()->add(temp);

    hotellet->les_fra_fil();
}

void avbestill_rom() {
	Rom* rommet;
	Reservasjon* reservasjon;
	char temp;
	int counter = 0;
	string navn = getln("Skriv inn reservat>ens navn");
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		for (int j = 1;  j <= hotellet->get_rom(i)->no_of_elements();  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			for (int k = 1;  j <= rommet->get_reservasjoner()->no_of_elements();  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if(reservasjon->is_name_in_array(navn)) { 
					counter++;
					//Displayer reservasjonen
					reservasjon->display();
					do {
						temp = read_char("Skal reservasjonen slettes?[Y/n]");
					} while(!temp == 'Y' && !temp == 'N');

					if(temp == 'Y') {
						rommet->get_reservasjoner()->add(reservasjon);
					} else {
						cout << "Reservasjonen ble fjernet" << endl;
					}
				} else {
					cout << "Personen du s>ker etter har ikke reservert et rom" << endl;
					rommet->get_reservasjoner()->add(reservasjon);
				}
			}
			
		}
	}
	if(counter == 0) {
		cout << "Personen du s>ker etter har ingen reservasjoner" << endl;
	}
}

void innsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;
	int ant;

	string navn = getln("Skriv inn reservat>ens navn");
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		for (int j = 1;  j <= hotellet->get_rom(i)->no_of_elements();  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			for (int k = 1;  j <= rommet->get_reservasjoner()->no_of_elements();  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if(reservasjon->is_name_in_array(navn)) {
				//Teller opp telleren
				counter++;
					// Sjekker om ankomst dato er i dag.
					if(reservasjon->getAnkomstDato() == dagens_dato) {
					
						cout << "Romnummer: " << rommet->getRomNummer() << endl;
						ant = read_int("Hvor mange beboere skal reserveres? ");

						// Setter antall beboere
						reservasjon->setAntallBeboere(ant);
					
						string beboere[MAX_ARRAY];

						if(ant > 0) {
	
							for(int i = 0; i < ant; i++) 
								beboere[i] = getln("Skriv inn navnet på beboer", i + 1);
								
							// Setter beboere paa reservasjonen
							reservasjon->setBeboere(beboere);
							// Displayer reservasjon
							reservasjon->display();
							// Legger reservasjonen tilbake i listen
							rommet->get_reservasjoner()->add(reservasjon);
						} else {
							cout << "Antall beboere må være minst én" << endl;
							rommet->get_reservasjoner()->add(reservasjon);
						}
					}
				} else {
				// Legger resvasjon tilbake i listen
				rommet->get_reservasjoner()->add(reservasjon);
				}
			}
		}
	}
	if(counter == 0) 
		cout << "Personen du s>kte etter har ingen reservasjoner paa dagens dato" << endl;
}


void utsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;
	string temp_romnummer = getln("Skriv inn rommnummeret");
	int romnummber = convert_to_int(temp_romnummer);

	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		if(rommet->getRomNummer() == romnummber) {
			for (int j = 1;  j <= rommet->get_reservasjoner()->no_of_elements();  j++)  { 
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(i);
				if(reservasjon->getAvreiseDato() == dagens_dato) { 
				
				}
			}
		}
	}
}


void registrer_regning() {

}

void endre_ankomst() {

}

void endre_avreisedato() {

}

void bytt_rom() {

}

void oversikt_over_hotell() {
	hotellet->display();
}

void beskrivelse_av_suiter() {
	Suite* suite;
	Rom* rommet;
	for (int j = 1;  j <= hotellet->get_rom(2)->no_of_elements();  j++)  {
		suite = (Suite*) hotellet->get_rom(2)->remove_no(j);
		suite->display();
		hotellet->get_rom(2)->add(suite);
	} 
}

void alle_reservasjoner_person() {

}

void rom_ledig() {

}

void vis_reservasjoner_for_rom() {

}

void vis_alle_data_for_rom() {

}

void vis_alle_ledige_rom_i_kategori() {

}

void skriv_til_fil() {
	string fil = getln("Skriv inn navnet på filen");
	ofstream utfil(fil);
	if (utfil.is_open()) 	// Åpner filen
		hotellet->skriv_til_fil(&utfil);
   
    utfil.close();
}

void bytt_hotell() {
	string userinput;
	string fil;
	int counter = 0;
	do {
		if(counter > 0) 
			cout << "Hotellet du s>kte etter finnes ikke. Pr>v igjen!" << endl;
		ifstream infile(HOTELL_FIL);
		userinput = getln("Tast inn navnet p> hotellet");
		fil = does_hotell_exist_in_file(infile, userinput);
		counter++;
	} while(fil.empty());
	
	cout << userinput << " er lastet inn" << endl;
	hotellet = new Hotell(fil);
	opprett_reg_post();
}

string does_hotell_exist_in_file(ifstream& infile, string userinput )
{
	string fil;
	if(infile.is_open()) {
        while(!infile.eof()) {
            
            //Initierer variabler
            string linje;
            string orginal;
            
            //Henter hele linjen fra filen
            getline(infile, orginal);
     

			unsigned pos = orginal.find(" ");  

			string kortnavn = orginal.substr(0,pos); 

            string langnavn = orginal.substr(pos + 1);


            //Hvis brukerinput og langnavn er like
			if(userinput.compare(langnavn) == 0) {
                 fil = kortnavn + ".DTA";
                return fil;
			} 
        }
		return fil;
	}
}

void opprett_reg_post() {
	string vanlige_poster[MAX_ARRAY];
	int antall = 0;
	ifstream infile(REG_POST_FIL);
	if(infile.is_open()) {
		while(!infile.eof()) {
			string temp;
			//Henter hele linjen fra filen
			getline(infile, temp);
			vanlige_poster[antall++] = temp;
		}
		reg_post = Reg_post(antall, vanlige_poster);
	}
}

void les_fra_fil() {
    char* fil;
	fil = new char[strlen(HOTELL_FIL)+1];
	strcpy(fil, HOTELL_FIL);

    hotellet = new Hotell(fil);
    hotellet->display();
    
}

void avslutt() {

}
