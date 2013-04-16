#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "proc.h"
#include <algorithm>
#include "coen.h"
#include "hotell.h"
#include "regning.h"
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
    return read_char("Tast inn kommando");
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
    
    int romtype = 0;
	if(romtype_tmp.compare("Singel") == 0)
        romtype = SINGEL;
    if(romtype_tmp.compare("Dobbel") == 0)
        romtype = DOBBEL;
    if(romtype_tmp.compare("Suite") == 0)
        romtype = SUITE;

	int ankomstdato;
	int avreisedato;
	int teller = 0;
	do {
		if(teller > 0)
			cout << "Avreisedato m> v>ere større enn avreisedato" << endl;
		ankomstdato = read_int("Skriv inn annkomstdato[AAAAMMDD]");
		avreisedato = read_int("Skriv inn avreisedato[AAAAMMDD]");
		teller++;
	} while(ankomstdato > avreisedato);

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
     
    string beboere[MAX_ARRAY];
	int counter = 0;
	string input;
	do {
		input = getln("Skriv inn navnet p> beboer", counter + 1);
		if(!did_the_user_press_enter(input)) {
			beboere[counter] = input;
			counter++;
		}
	} while(!did_the_user_press_enter(input));


    // Oppretter reservasjon
	temp = new Reservasjon(ankomstdato, avreisedato, frokost, ekstraseng, counter, beboere);
    
    // Legger reservasjonen til i rommet.
    r->get_reservasjoner()->add(temp);
}

bool did_the_user_press_enter(string temp) {
	if(temp.empty())
		return true;
	return false;
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
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  j <= antall_reservasjoner; j++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if(reservasjon->is_name_in_array(navn)) { 
					counter++;
					//Displayer reservasjonen
					reservasjon->display();
					do {
						temp = read_char("Skal reservasjonen slettes?[Y/N]");
					} while(!temp == 'Y' && !temp == 'N');

					if(temp == 'Y') {
						cout << "Reservasjonen ble fjernet" << endl;
					} else {
						rommet->get_reservasjoner()->add(reservasjon);
						cout << "Reservasjonen ble ikke fjernet" << endl;
					} 
				}	// endif 
				rommet->get_reservasjoner()->add(reservasjon);
			} // end for
			hotellet->get_rom(i)->add(rommet);
		}	// end for
	} // end for
	if(counter == 0) {
		cout << "Personen du s>ker etter har ingen reservasjoner" << endl;
	}
}

void innsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;


	string navn = getln("Skriv inn reservat>ens navn");
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if(reservasjon->is_name_in_array(navn)) {
				//Teller opp telleren
				counter++;
					// Sjekker om ankomst dato er i dag.
					if(reservasjon->getAnkomstDato() == dagens_dato) {
					
						cout << "Romnummer: " << rommet->getRomNummer() << endl;
							
							string beboere[MAX_ARRAY];
							string input;
							int teller = 0;
							cout << "Det er registert " << reservasjon->getAntallBeboere() << " beboere.\n"
								 << "For a legge inn flere, skriv inn navnet pa beboeren. For aa avslutte trykk p> enter" << endl;
							do {
								input = getln("Skriv inn navnet p> beboer", reservasjon->getAntallBeboere() + 1);
								if(!did_the_user_press_enter(input)) {
									beboere[teller] = input;
									teller++;
								}
							} while(!did_the_user_press_enter(input));
	
							
							// Setter beboere paa reservasjonen
							reservasjon->setBeboere(beboere, teller);
							// Displayer reservasjon
							reservasjon->display();
							
							reservasjon->set_innsjekk();
							rommet->get_reservasjoner()->add(reservasjon);
			
					} else {
						rommet->get_reservasjoner()->add(reservasjon);
					}
				} else {
					// Legger resvasjon tilbake i listen
					rommet->get_reservasjoner()->add(reservasjon);
				}
			}
			//Legger rommet tilbake i listen.
			hotellet->get_rom(i)->add(rommet);
		}
	}
	if(counter == 0) 
		cout << "Personen du s>kte etter har ingen reservasjoner paa dagens dato" << endl;
}


void utsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter_rom = 0;
	int counter_res = 0;
	int rom_nummer = read_int("Skriv inn rommnummeret");
	
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				if(rommet->getRomNummer() == rom_nummer) {
					counter_rom++;
					if(reservasjon->getAvreiseDato() == dagens_dato) {
						counter_res++;
						//Skriver ut alle 
						reservasjon->display();
						reservasjon->display_faktura();
						reservasjon->set_utsjekk();
						string filnavn = hotellet->get_filnavn();
						reservasjon->skriv_faktura_til_fil(filnavn);
					} else {
						rommet->get_reservasjoner()->add(reservasjon);
					}
				} else {
					rommet->get_reservasjoner()->add(reservasjon);
				}
			} // end for reservasjoner
			hotellet->get_rom(i)->add(rommet);
		} // end for rom
	} // end for romtyper
	if(counter_rom == 0) 
		cout << "Det finnes ingen rom p> hotellet med det romnummeret!" << endl;
	if(counter_res == 0 && counter_rom != 0) 
		cout << "Personen du s>kte etter har ingen reservasjoner paa dagens dato" << endl;
}


void registrer_regning() {
	Rom* rommet;
	Reservasjon* reservasjon;
	Regning* regning;
	Reg_post regpost;
	char *cstr;
	int rom_nummer = read_int("Skriv inn romnummeret");
	int counter = 0;
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		for (int j = 1;  j <= hotellet->get_rom(i)->no_of_elements();  j++)  { 
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);	
			if(rommet->getRomNummer() == rom_nummer) {
				counter++;
				int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
				for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
					//Henter reservasjon ut fra rommet.
					reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
					if(reservasjon->er_innsjekket()){
						regpost.display();
						int menunr = read_int("Skriv inn nr fra menyelementet over. Dersom du ønsker å skrive inn egen beskrivelse, skriv en bokstav\n");
						if(menunr == -1){
							// user didn't input a number
							string beskrivelse = getln("Skriv inn egen beskrivelse");
							cstr = new char[beskrivelse.length() + 1];
							strcpy(cstr, beskrivelse.c_str());
						}
						else{
							//Brukeren skrev inn et nr
							string post_beskrivelse = regpost.get_post(menunr);
							cstr = new char[post_beskrivelse.length() + 1];
							strcpy(cstr, post_beskrivelse.c_str());
						}
						float pris = read_float("Skriv inn regningens beløp");

						regning = new Regning(cstr, pris);
						delete [] cstr;
					} 
					else {
						cout << "Det er ingen som bor p> dette rommet for >yeblikket" << endl;
					}
					rommet->get_reservasjoner()->add(reservasjon);
				}
				hotellet->get_rom(i)->add(rommet);
			}
		}
	}
	if(counter == 0) {
		cout << "Det finnes ingen rom med det romnummeret. Pr>v igjen!" << endl;		
	}
}

void endre_ankomst_avreisedato() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;
	int ant;

	string reservator = getln("Skriv inn navnet på reservatøren");

	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if((reservasjon->is_name_in_array(reservator)) && (reservasjon->er_innsjekket() == false)) {
					//Teller opp telleren
					counter++;

					reservasjon->display_list(counter);
					char svar = read_char("Ønsker du å endre denne reservasjonen? [Y/N]");
					if(svar == 'Y'){
						string ankomst = getln("Skriv inn den nye ankomstdatoen [AAAAMMDD]");
						string avreise = getln("Skriv inn den nye avreisedatoen [AAAAMMDD]");

						if(ankomst.empty() && !avreise.empty()){
							//Ankomst er tom men ikke avreise
							int avreise_dato = atoi(avreise.c_str());
							reservasjon->endre_avreise(avreise_dato);
						}
						else if(avreise.empty() && !ankomst.empty()){
							//Avreise er tom men ikke ankomst
							int ankomst_dato = atoi(ankomst.c_str());
							reservasjon->endre_ankomst(ankomst_dato);
						} 
						else if(avreise.empty() && ankomst.empty()){
							//Begge er tomme
							//Gjør ingenting
							cout << "Du kan kun endre ankomstdato og/eller avreisedato her. Du har ikke valgt å endre noe" << endl;
						}
						else{
							//Begge er utfylt
							int avreise_dato = atoi(avreise.c_str());
							int ankomst_dato = atoi(ankomst.c_str());
							reservasjon->endre_ankomst(ankomst_dato);
							reservasjon->endre_avreise(avreise_dato);
						}
					}
					rommet->get_reservasjoner()->add(reservasjon);
				} else {
					// Legger resvasjon tilbake i listen
					rommet->get_reservasjoner()->add(reservasjon);
				}
			}
			//Legger rommet tilbake i listen.
			hotellet->get_rom(i)->add(rommet);
		}
	}
	if(counter == 0) {
		cout << "Personen du søkte etter har ingen reservasjoner (som ikke er innsjekket)" << endl;
		return;
	}
}

void endre_avreisedato() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;
	int ant;

	string reservator = getln("Skriv inn navnet på reservatøren");

	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if((reservasjon->is_name_in_array(reservator)) && (reservasjon->er_innsjekket() == true)) {
					//Teller opp telleren
					counter++;

					reservasjon->display_list(counter);
					char svar = read_char("Ønsker du å endre denne reservasjonen? [Y/N]");
					if(svar == 'Y'){
						string avreise = getln("Skriv inn den nye avreisedatoen [AAAAMMDD]");

						if(avreise.empty()){
							//Avreise er tom
							//Gjør ingenting
							cout << "Du kan kun endre avreisedato her. Du har valgt å ikke endre den" << endl;
						}
						else{
							//Avreise er utfylt
							int avreise_dato = atoi(avreise.c_str());
							reservasjon->endre_avreise(avreise_dato);
						}
					}
					rommet->get_reservasjoner()->add(reservasjon);
				} else {
					// Legger resvasjon tilbake i listen
					rommet->get_reservasjoner()->add(reservasjon);
				}
			}
			//Legger rommet tilbake i listen.
			hotellet->get_rom(i)->add(rommet);
		}
	}
	if(counter == 0) {
		cout << "Personen du søkte etter har ingen reservasjoner (som er insjekket)" << endl;
		return;
	}
}

void bytt_rom() {

}

void oversikt_over_hotell() {
	hotellet->display();
}

void beskrivelse_av_suiter() {
	Suite* suite;
	Rom* rommet;
	int antll_suiter = hotellet->get_rom(2)->no_of_elements();
	for (int j = 1;  j <= antll_suiter; j++)  {
		suite = (Suite*) hotellet->get_rom(2)->remove_no(j);
		suite->display();
		hotellet->get_rom(2)->add(suite);
	} 
}

void vis_alle_reservasjoner_for_person() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;
	int ant;

	string navn = getln("Skriv inn reservat>ens navn");
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
			for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
				//Henter reservasjon ut fra rommet.
				reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
				//Sjekker om navnet er i reservasjonen
				if(reservasjon->is_name_in_array(navn)) {
					//Teller opp telleren
					counter++;
					reservasjon->display();
					rommet->get_reservasjoner()->add(reservasjon);
				} else {
					// Legger resvasjon tilbake i listen
					rommet->get_reservasjoner()->add(reservasjon);
				}
			}
			//Legger rommet tilbake i listen.
			hotellet->get_rom(i)->add(rommet);
		}
	}
	if(counter == 0) 
		cout << "Personen du s>kte etter har ingen reservasjoner." << endl;
}

void rom_ledig() {

}

void vis_reservasjoner_for_rom() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter_rom = 0;
	int counter_res = 0;
	int rom_nummer = read_int("Skriv inn rommnummeret");
	
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			if(rommet->getRomNummer() == rom_nummer) {
				counter_rom++;
				//Henter ut alle reservasjoner innen for et bestemt rom.
				int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
				for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
					//Henter reservasjon ut fra rommet.
					counter_res++;
					reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
					reservasjon->display();
					rommet->get_reservasjoner()->add(reservasjon);
				}
			} // end for reservasjoner
			hotellet->get_rom(i)->add(rommet);
		} // end for rom
	} // end for romtyper
	if(counter_rom == 0)
		cout << "Det finnes ingen rom p> hotellet med det romnummeret!" << endl;
	if(counter_res == 0 && counter_rom != 0) 
		cout << "Det finnes ingen reserveringer paa dette rommet!" << endl;
}

void vis_navarende_beboer() {
    int romnr = read_int("Angi romnummer");
    
    Rom* rom = (Rom*) hotellet->get_spesifikk_rom(romnr);
    
    if(!rom) {
        cout << "Rommet finnes ikke. Vennligst prøv igjen.\n";
        return;
    }
    

	if(!rom->ledig(dagens_dato)) {
        List* reservasjoner = rom->get_reservasjoner();
        for(int i = 1; i <= reservasjoner->no_of_elements(); i++) {
            Reservasjon* res = (Reservasjon*) reservasjoner->remove_no(i);
            if(res->er_innsjekket()) {
                res->display();
            }
            reservasjoner->add(res);
        }
    }
}

void vis_alle_ledige_rom_i_kategori() {
	Rom* rommet;
	string rom_kategori;
	int rom_kat;
	int counter = 0;
	do {
		rom_kategori = getln("Skriv inn romkategori[Singel/Dobbel/Suite]");
		transform(rom_kategori.begin(), rom_kategori.end(),rom_kategori.begin(), ::toupper);
	} while(!is_rom_category(rom_kategori));

	if(rom_kategori.compare("SINGEL") == 0)  {
		rom_kat = SINGEL;
	}

	if(rom_kategori.compare("DOBBEL") == 0)  {
		rom_kat = DOBBEL;
	}

	if(rom_kategori.compare("SUITE") == 0)  {
		rom_kat = SUITE;
	}
	
	int ankomst_dato;
	int avreise_dato;
	int teller = 0;
	do {
		if(teller > 0) 
			cout << "Ankomstdato m> v>re st>rre enn avreise dato" << endl;
		ankomst_dato = read_int("Skriv inn ankomst dato(AAAAMMDD)");
		avreise_dato = read_int("Skriv inn avreise dato(AAAAMMDD)");
		teller++;
	} while(ankomst_dato > avreise_dato);

	int antall_rom_i_kategori = hotellet->get_rom(rom_kat)->no_of_elements();
	for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
		counter++;
		
		switch (rom_kat)  {
			 case SINGEL : rommet = (Singel*) hotellet->get_rom(rom_kat)->remove_no(j);
			break;
			 case DOBBEL : rommet = (Dobbel*) hotellet->get_rom(rom_kat)->remove_no(j);
			break;
			 case SUITE :  rommet = (Suite*) hotellet->get_rom(rom_kat)->remove_no(j);
			break;
			 default:  rommet = (Rom*) hotellet->get_rom(rom_kat)->remove_no(j);
			break;
		}

		//Henter ut alle reservasjoner innen for et bestemt rom.
		if(rommet->ledig(ankomst_dato, avreise_dato)) {
			rommet->display();
			//Legger rommet tilbake i listen.
			hotellet->get_rom(rom_kat)->add(rommet);

		} else {
			//Legger rommet tilbake i listen.
			hotellet->get_rom(rom_kat)->add(rommet);
		}
		
	}
	
	if(counter == 0) 
		cout << "Det finnes ingen rom i denne kategorien." << endl;
		
}

bool is_rom_category(string rom_kategori) {
	if(rom_kategori.compare("SINGEL")== 0) {
		return true;
	} else if(rom_kategori.compare("DOBBEL") == 0) {
		return true;
	} else if(rom_kategori.compare("SUITE") == 0) {
		return true;
	} else {
		return false;
	}
	return false;
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
