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
/**
 *	Leser inn char
 *  @return char
 */
char les_kommando() {
    return read_char("Tast inn kommando");
}

/**
 *	Skriver ut hovedmenyen for programmet.
 */
void skriv_meny()  {
	cout << "\n\nF>lgende kommandoer er lovlig:";
	cout << "\n\tB - Bestill/reserver/book et rom";
	cout << "\n\tA - Avbestill et rom";
	cout << "\n\tI - Innsjekking paa(ankomst til) hotellet";
	cout << "\n\tU - Utsjekking(avreise) fra hotellet";
	cout << "\n\tR - Registrer/legg inn en regning paa et rom";
	cout << "\n\tZ - Endre ankomst -og/eller avreisedato f>r innsjekking paa hotellet";
	cout << "\n\tX - Endre avreisedato n>r noen allerede bor(er innsjekket) paa hotellet";
	cout << "\n\tC - Bytte til et annet (ledig) rom enn det tildelte";
	cout << "\n\tS - Hoveddatene om ett hotell";
	cout << "\n\tD - Beskrivelse av alle hotellets suiter";
	cout << "\n\tF - Alle reservasjoner som staar i en persons navn";
	cout << "\n\tG - Naar et rom er ledig";
	cout << "\n\tJ - Alle reservasjoner for/paa et rom";
	cout << "\n\tK - Alle data for ett roms n>v>erende beboer, inkludert dens regninger";
	cout << "\n\tL - Alle ledeige rom i en kategori";
	cout << "\n\tT - Skriv alt om hotellet til fil";
	cout << "\n\tH - Bytte over til et annet hotell";
}
/**
 *	Funksjon som reserverer/booker et rom.
 */
void reserver_rom() {
	Reservasjon *temp;

	string romtype_tmp;
	// Sp>r etter romtype
	romtype_tmp = getln("Hvilken romtype >nsker du? [Singel/Dobbel/Suite]");
    
    int romtype = 0;
	if(romtype_tmp.compare("Singel") == 0)
        romtype = SINGEL;	// Setter romtype til singel
    if(romtype_tmp.compare("Dobbel") == 0)
        romtype = DOBBEL;	// Setter romtype til dobbel
    if(romtype_tmp.compare("Suite") == 0)
        romtype = SUITE;	// Setter romtype til suite

	int ankomstdato = 0;
	int avreisedato = 0;
	int teller = 0;

	// Leser inn ankomstdato og avreisedato.
	do {
		if(teller > 0)
			cout << "Avreisedato m> v>ere st>rre enn ankomstdato" << endl;
		ankomstdato = read_int("Skriv inn annkomstdato[AAAAMMDD]");
		avreisedato = read_int("Skriv inn avreisedato[AAAAMMDD]");
		teller++;
	// Looper til det blir skrevet inn en gyldig ankomstdato.
	} while(!gyldig_ankomst(ankomstdato, avreisedato, dagens_dato));

	bool frokost = false;
	// Leser inn om beboeren >sker frokost eller ikke.
	char onskerfrokost = read_char(">nsker du frokost? [y/n]");
	if(onskerfrokost == 'Y'){
		frokost = true;
	}

	bool ekstraseng = false;
	// Sjekker om romtype er dobbeltrom.
	if(romtype == DOBBEL){
		char onskerekstraseng = read_char("Er det behov for en ekstra seng? [y/n]");
		if(onskerekstraseng == 'Y'){
			ekstraseng = true;
		}
	}

    // Prøver å hente ledig rom i angitt kategori
	Rom* r = hotellet->get_ledig_rom(romtype, ankomstdato, avreisedato);
    
    // Avslutter med melding hvis det
    // ikke finnes ledige rom i kategorien.
    if(!r) {
        cout << "Det finnes ingen ledige rom i denne kategorien\n";
        return;
    }
    
	// Oppretter array med beboere.
    string beboere[MAX_ARRAY];
	int counter = 0;
	string input;
	// Skriver inn navnet på antall beboere.
	do {
		input = getln("Skriv inn navnet p> beboer", counter + 1);
		// Teller opp hvis brukeren ikke har trykket på enter
		if(!did_the_user_press_enter(input)) {
			beboere[counter] = input;
			counter++;
		}
	// Looper til brukeren har trykket på enter og antall bebebore er over 1.
	} while(ingen_beboere(input, counter));


    // Oppretter reservasjon
	temp = new Reservasjon(ankomstdato, avreisedato, romtype, frokost, ekstraseng, counter, beboere);
    
    // Legger reservasjonen til i rommet.
    r->get_reservasjoner()->add(temp);

	cout << "Reservasjonen ble velykket opprettet!" << endl;
	temp->display(r);	// Displayer rom.
}

/**
 *	Avbestiller reservasjon/booking
 *
 */
void avbestill_rom() {
	Rom* rommet;
	Reservasjon* reservasjon;
	char temp;
	bool finnes_reservatoren = false;
	
	// Skriver inn reservat>ens navn
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
					finnes_reservatoren = true;
					//Displayer reservasjonen
					reservasjon->display();
					// Brukeren maa svare ja eller nei om reservasjonen skal slettes.
					do {
						temp = read_char("Skal reservasjonen slettes?[Y/N]");
					} while(!temp == 'Y' && !temp == 'N');

					if(temp == 'Y') {
						cout << "Reservasjonen ble fjernet" << endl;
					} else {
						// Reservasjonen skal ikke fjernes. Legger den tilbake i listen.
						rommet->get_reservasjoner()->add(reservasjon);
						cout << "Reservasjonen ble ikke fjernet" << endl;
					} 
				}	// endif 
				// Legger reservasjonen tilbake i rommet
				rommet->get_reservasjoner()->add(reservasjon);
			} // end for
			// Legger rommet tilbake i listen over rom
			hotellet->get_rom(i)->add(rommet);
		}	// end for
	} // end for
	if(!finnes_reservatoren) {
		cout << "Personen du s>ker etter har ingen reservasjoner" << endl;
	}
}

/**
 *	Innsjekker beboeren paa rommet han/hun har reservert / booket.	
 */
void innsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	bool finnes_reservatoren = false;
	bool kan_sjekke_inn = false;
	// Henter navnet paa reservat>eren
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
					finnes_reservatoren = true;
					// Sjekker om ankomst dato er i dag.
					if(reservasjon->getAnkomstDato() == dagens_dato) {
						kan_sjekke_inn = true;
						cout << "Romnummer: " << rommet->getRomNummer() << endl;
							
							string beboere[MAX_ARRAY];
							string input;
							int teller = 0;
							cout << "Det er registert " << reservasjon->getAntallBeboere() << " beboere.\n"
								 << "For a legge inn flere, skriv inn navnet pa beboeren. For aa avslutte trykk p> enter" << endl;
							int antall = reservasjon->getAntallBeboere();
							do {
								antall += 1;
								input = getln("Skriv inn navnet p> beboer", antall);
								// Telelr bare opp hvis brukeren ikke har trykket paa enter.
								if(!did_the_user_press_enter(input)) {
									beboere[teller] = input;
									teller++;
								}
							// Looper til brukeren har trykket på enter.
							} while(!did_the_user_press_enter(input));
	
							
							// Setter beboere paa reservasjonen
							reservasjon->setBeboere(beboere, teller);
							// Displayer reservasjon
							reservasjon->display();
							// Setter status paa seng.
							if(reservasjon->get_status_seng() == 1)
								reservasjon->set_seng_status(2);
							reservasjon->set_innsjekk();		// Sjekker inn beboren paa rommet.
							// Legger reservasjon til 
							rommet->get_reservasjoner()->add(reservasjon);
			
					} else {
						rommet->get_reservasjoner()->add(reservasjon);
					} // End ankomst er storre enn dagens_dato
				} else {
					// Legger resvasjon tilbake i listen
					rommet->get_reservasjoner()->add(reservasjon);
				} // End is_name_in_array
			
			} // End for reservasjoner
			//Legger rommet tilbake i listen.
			hotellet->get_rom(i)->add(rommet);
		}	// end rom
	} // end rom kat
	if(!finnes_reservatoren) 
		cout << "Det finnes ingen personer som har reservert rom med det navnet." << endl;
	if(finnes_reservatoren && !kan_sjekke_inn) 
		cout << "Personen du s>kte etter har ingen reservasjoner paa dagens dato" << endl;
}

/**
 * Sjekker ut en person av rommet han/hun har reservert.
 */
void utsjekking() {
	Rom* rommet;
	Reservasjon* reservasjon;
	bool er_rom = false;
	bool er_sjekket_inn = false;
	// Henter romnummeret.
	int rom_nummer = read_int("Skriv inn rommnummeret");
	// Sjekker om input er et gyldig romnummer
	if(rom_nummer == -1) {
		cout << "Du skrev ikke inn et gyldig romnummer" << endl;
		return;
	}
	
	
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
                rommet->get_reservasjoner()->add(reservasjon);
                
				if(rommet->getRomNummer() == rom_nummer) {
					er_rom = true;	// Det finnes et rom med romnummret.
					// Sjekker om reservat>ren er innsjekket.
					if(reservasjon->er_innsjekket()) {
						er_sjekket_inn = true;	
						if(reservasjon->getAvreiseDato() == dagens_dato) {
							//Skriver ut alle 
							reservasjon->display();
							reservasjon->display_faktura();

							reservasjon->set_seng_status(0);
							reservasjon->set_utsjekk();
							reservasjon->skriv_faktura_til_fil(hotellet->get_filnavn() + ".HST");
						
                            
						} else {
							cout << "Reservasjonen har ikke avreisedato i dag. Avreisedatoen er: " << reservasjon->getAvreiseDato() << endl;
							rommet->get_reservasjoner()->add(reservasjon);
						} // end avreisdato == dagens_dato
					} // end innsjekket	
				}
			} // end for reservasjoner
			hotellet->get_rom(i)->add(rommet);
		} // end for rom
	} // end for romtyper
	if(!er_rom) 
		cout << "Det finnes ingen rom p> hotellet med det romnummeret!" << endl;
	if(er_rom && !er_sjekket_inn) {
		cout << "Reservasjonen du s>kte etter er ikke innsjekket" << endl;
	}
}


void registrer_regning() {
	Rom* rommet;
	Reservasjon* reservasjon;
	Regning* regning;
	char *cstr;
	int rom_nummer = read_int("Skriv inn romnummeret");
	bool er_rom_nummer = false;
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori; j++)  { 
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);	
			if(rommet->getRomNummer() == rom_nummer) {
				er_rom_nummer = true;
				int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
				for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
					//Henter reservasjon ut fra rommet.
					reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
					if(reservasjon->er_innsjekket()) {
						reg_post.display();
						int menunr = read_int("Skriv inn nr fra menyelementet over. Dersom du >nsker aa skrive inn egen beskrivelse, skriv en bokstav\n");
							if(menunr == -1){
								// user didn't input a number
								string beskrivelse = getln("Skriv inn egen beskrivelse");
								cstr = new char[beskrivelse.length() + 1];
								strcpy(cstr, beskrivelse.c_str());
							
							} else{
								
								//Brukeren skrev inn et nr
								string post_beskrivelse = reg_post.get_post(menunr);
								cstr = new char[post_beskrivelse.length() + 1];
								strcpy(cstr, post_beskrivelse.c_str());
							} // end menur else

							float pris = read_float("Skriv inn regningens bel>p");

							regning = new Regning(cstr, pris);
							cout << "Regningen ble velykket lagt til" << endl;
							delete [] cstr;
						} else {
						cout << "Det er ingen som bor p> dette rommet for >yeblikket" << endl;
					} // end innsjekket else
					rommet->get_reservasjoner()->add(reservasjon);
				} // end for reservasjoner
				
			}	// end if romnummer
			hotellet->get_rom(i)->add(rommet);
		}	// end for rom
	} // end for rom i kategori
	if(!er_rom_nummer) {
		cout << "Det finnes ingen rom med det romnummeret. Pr>v igjen!" << endl;		
	}
}

void endre_ankomst_avreisedato() {
	Rom* rommet;
	Reservasjon* reservasjon;
	bool er_innsjekket = false;
	int teller = 0;
	string reservator = getln("Skriv inn navnet p> reservat>ren");

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
					teller++;

					er_innsjekket = true;

					reservasjon->display_list(teller);
					char svar = read_char(">nsker du aa endre denne reservasjonen? [Y/N]");
					if(svar == 'Y'){
						string ankomst = getln("Skriv inn den nye ankomstdatoen [AAAAMMDD]");
						string avreise = getln("Skriv inn den nye avreisedatoen [AAAAMMDD]");

						if(ankomst.empty() && !avreise.empty()){
							//Ankomst er tom men ikke avreise
							int avreise_dato = atoi(avreise.c_str());
							if(rommet->ledig(reservasjon->getAnkomstDato(), avreise_dato)) {
								reservasjon->endre_avreise(avreise_dato);
								cout << "Avreisedatoen ble endret til: " << avreise_dato << endl;
							} else {
								cout << "Kan ikke bytte avreisedato til " << avreise_dato << ", rommet er ikke ledig den dagen" << endl;
							}
							
						}
						else if(avreise.empty() && !ankomst.empty()){
							//Avreise er tom men ikke ankomst
							int ankomst_dato = atoi(ankomst.c_str());
							if(rommet->ledig(ankomst_dato, reservasjon->getAvreiseDato())) {
								reservasjon->endre_ankomst(ankomst_dato);
								cout << "Ankomstdatoen ble endret til: " << ankomst_dato << endl;
							} else {
								cout << "Kan ikke bytte ankomstdato til " << ankomst_dato << ", rommet er ikke ledig den dagen" << endl;
							}
						} 
						else if(avreise.empty() && ankomst.empty()){
							//Begge er tomme
							//Gjør ingenting
							cout << "Du kan kun endre ankomstdato og/eller avreisedato her. Du har ikke valgt aa endre noe" << endl;
						}
						else{
							//Begge er utfylt
							int avreise_dato = atoi(avreise.c_str());
							int ankomst_dato = atoi(ankomst.c_str());
							
							if(rommet->ledig(avreise_dato, ankomst_dato)) {
								reservasjon->endre_ankomst(ankomst_dato);
								reservasjon->endre_avreise(avreise_dato);
								cout << "Ankomstdatoen ble endret til: " << ankomst_dato << endl;
								cout << "Avreisedatoen ble endret til: " << avreise_dato << endl;
							} else {
								cout << "Kan ikke bytte ankostdato og avreisedato, rommet er ikke ledig i den perioden" << endl;
							}
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
	if(!er_innsjekket) {
		cout << "Personen du s>kte etter har ingen reservasjoner (som ikke er innsjekket)" << endl;
		return;
	}
}

void endre_avreisedato() {
	Rom* rommet;
	Reservasjon* reservasjon;
	int counter = 0;

	string reservator = getln("Skriv inn navnet paa reservat>ren");

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
					char svar = read_char(">nsker du aa endre denne reservasjonen? [Y/N]");
					if(svar == 'Y'){
						string avreise = getln("Skriv inn den nye avreisedatoen [AAAAMMDD]");

						if(avreise.empty()){
							//Avreise er tom
							//Gjør ingenting
							cout << "Du kan kun endre avreisedato her. Du har valgt aa ikke endre den" << endl;
						}
						else{
							//Avreise er utfylt
							int avreise_dato = atoi(avreise.c_str());
					
							if(rommet->ledig(reservasjon->getAnkomstDato(), avreise_dato)) {
								reservasjon->endre_avreise(avreise_dato);
								cout << "Avreisedatoen ble endret til: " << avreise_dato << endl;
							} else {
								cout << "Kan ikke bytte avreisedato til " << avreise_dato << ", rommet er ikke ledig den dagen" << endl;
							}
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
		cout << "Personen du s>kte etter har ingen reservasjoner (som er insjekket)" << endl;
		return;
	}
}

void bytt_rom() {
	Rom* rommet;
	Rom* rom;
	Reservasjon* reservasjon;
	bool finnes_reservasjon;
	bool finnes_romnummer;
	int rom_nummer = 0;
	
	rom_nummer = read_int("Skriv inn romnummeret");
	
	if(rom_nummer == -1) {
		cout << "Du skrev ikke inn et tall!" << endl;
		return;
	}

	bool byttet = false;

	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			hotellet->get_rom(i)->add(rommet);
			//Henter ut alle reservasjoner innen for et bestemt rom.
			if(rommet->getRomNummer() == rom_nummer) {
				finnes_romnummer = true;
					for (int k = 1;  k <= rommet->get_reservasjoner()->no_of_elements();  k++)  {  
						//Henter reservasjon ut fra rommet.
						reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
						//Sjekker om navnet er i reservasjonen
					
						finnes_reservasjon = true;
						// Pr>er aa bytte rom
						for (int l = 1;  l <= antall_rom_i_kategori;  l++)  { 
							if(l != j) { 
								rom = (Rom*) hotellet->get_rom(i)->remove_no(l);
								if(rom->ledig(dagens_dato)) {
									byttet = true;
									char input;
									do {
										reservasjon->display();
										input = read_char(">nsker du aa endre denne reservasjonen? [Y/n]");
									} while (input != 'Y' && input != 'N');
									if(input == 'Y') {
										rom->get_reservasjoner()->add(reservasjon);
										cout << "Rommet ble byttet til romnummer: " << rom->getRomNummer() << endl;
										hotellet->get_rom(i)->add(rom);
										break;
									} else {
										rommet->get_reservasjoner()->add(reservasjon);
										hotellet->get_rom(i)->add(rom);
										cout << "Romnummeret ble ikke byttet " << endl;
									}
								} else {
									hotellet->get_rom(i)->add(rom);
								}
							}
						
						}
					if(!byttet) {
						rommet->get_reservasjoner()->add(reservasjon);
					}
						
				} // end antall reservasjoner
				
			} // end if
			//Legger rommet tilbake i listen.
			
		} // end rom i kat
	} // end rom typer
	if(!finnes_romnummer) 
		cout << "Det finnes ingen rom paa dette hotellet med det romnummeret" << endl;
	if(finnes_romnummer && !finnes_reservasjon)
		cout << "Det finnes ingen reservasjoner paa dette rommet" << endl;
	if(finnes_romnummer && finnes_reservasjon && !byttet) 
		cout << "Det finnes ingen ledige rom aa bytte til " << endl;
}

void oversikt_over_hotell() {
	hotellet->display();
}

void beskrivelse_av_suiter() {
	Suite* suite;
	int antll_suiter = hotellet->get_rom(SUITE)->no_of_elements();
	for (int j = 1;  j <= antll_suiter; j++)  {
		suite = (Suite*) hotellet->get_rom(SUITE)->remove_no(j);
		suite->display();
		hotellet->get_rom(SUITE)->add(suite);
	} 
}

void vis_alle_reservasjoner_for_person() {
	Rom* rommet;
	Reservasjon* reservasjon;
	bool finnes_navn= false;

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
					finnes_navn = true;
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
	if(!finnes_navn) 
		cout << "Personen du s>kte etter har ingen reservasjoner." << endl;
}

void rom_ledig() {
	Rom* rommet;
	int rom_nummer = read_int("Skriv inn rommnummeret");
    
    rommet = (Rom*) hotellet->get_spesifikk_rom(rom_nummer);
    
    if(!rommet) {
        cout << "\nRom " << rom_nummer << " finnes ikke i dette hotellet";
        return;
    }
    
    List* reservasjoner = rommet->get_reservasjoner();
    int antall_reservasjoner = reservasjoner->no_of_elements();
    
    for(int i = 1; i <= antall_reservasjoner; i++) {
        
        Reservasjon* res1 = (Reservasjon*) reservasjoner->remove_no(i);
        reservasjoner->add(res1);
        
        //Hvis siste, så vises rommet som ledig fra og med avreisedato
        if(i == antall_reservasjoner) {
            cout << "Rommet er ledig fra og med: " << res1->getAvreiseDato() << endl;
            break;
        }
        
        Reservasjon* res2 = (Reservasjon*) reservasjoner->remove_no(i+1);
        reservasjoner->add(res2);
        
        cout << "Rommet er ledig fra" << res1->getAvreiseDato() << " til " << res2->getAnkomstDato() << endl;    
    }
}

void vis_reservasjoner_for_rom() {
	Rom* rommet;
	Reservasjon* reservasjon;
	bool finnes_rom = false;
	bool finnes_res = false;
	int rom_nummer = read_int("Skriv inn rommnummeret");
	if(rom_nummer == -1) {
		cout << "Du skrev ikke inn et gyldig romnummer" << endl;
		return;
	}
	
	//Looper igjennom romtyper
	for(int i = 0; i < ANTALL_ROMTYPER; i++) { 
		//Finner hotellets rom
		int antall_rom_i_kategori = hotellet->get_rom(i)->no_of_elements();
		for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
			//Trekker ut et rom av lista.
			rommet = (Rom*) hotellet->get_rom(i)->remove_no(j);
			if(rommet->getRomNummer() == rom_nummer) {
				finnes_rom = true;
				//Henter ut alle reservasjoner innen for et bestemt rom.
				int antall_reservasjoner = rommet->get_reservasjoner()->no_of_elements();
				for (int k = 1;  k <= antall_reservasjoner;  k++)  {  
					//Henter reservasjon ut fra rommet.
					finnes_res = true;
					reservasjon = (Reservasjon*) rommet->get_reservasjoner()->remove_no(k); 
					reservasjon->display();
					rommet->get_reservasjoner()->add(reservasjon);
				}
			} // end for reservasjoner
			hotellet->get_rom(i)->add(rommet);
		} // end for rom
	} // end for romtyper
	if(!finnes_rom)
		cout << "Det finnes ingen rom p> hotellet med det romnummeret!" << endl;
	if(finnes_rom && !finnes_res) 
		cout << "Det finnes ingen reserveringer paa dette rommet!" << endl;
}

void vis_navarende_beboer() {
    int romnr = read_int("Angi romnummer");
	if(romnr == -1) {
		cout << "Du skrev ikke inn et gyldig romnummer" << endl;
		return;
	}
    
    Rom* rom = (Rom*) hotellet->get_spesifikk_rom(romnr);
    
    if(!rom) {
        cout << "Rommet finnes ikke. Vennligst pr>v igjen.\n";
        return;
    }
    
    bool har_vist_reservasjon = false;
    List* reservasjoner = rom->get_reservasjoner();
    for(int i = 1; i <= reservasjoner->no_of_elements(); i++) {
        Reservasjon* res = (Reservasjon*) reservasjoner->remove_no(i);
        if(res->er_innsjekket()) {
            res->display();
            har_vist_reservasjon = true;
        } 
        reservasjoner->add(res);
    }
    
    if(!har_vist_reservasjon) {
        cout << "\n Personen er ikke innsjekket enda.";
    }
}

void vis_alle_ledige_rom_i_kategori() {
	Rom* rommet;
	string rom_kategori;
	int rom_kat;
	bool finnes_rom = false;
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
	bool er_rom_ledig = false;

	do {
		if(teller > 0) 
			cout << "Ankomstdato m> v>re st>rre enn avreise dato" << endl;
		ankomst_dato = read_int("Skriv inn ankomst dato(AAAAMMDD)");
		avreise_dato = read_int("Skriv inn avreise dato(AAAAMMDD)");
		teller++;
	} while(ankomst_dato > avreise_dato);

	int antall_rom_i_kategori = hotellet->get_rom(rom_kat)->no_of_elements();
	for (int j = 1;  j <= antall_rom_i_kategori;  j++)  { 
		finnes_rom = true;
		
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

		if(rommet->ledig(ankomst_dato, avreise_dato)) {
			rommet->display();
			//Legger rommet tilbake i listen.
			hotellet->get_rom(rom_kat)->add(rommet);

		} else {
			//Legger rommet tilbake i listen.
			er_rom_ledig = true;
			hotellet->get_rom(rom_kat)->add(rommet);
		}
		
	}
	
	if(!finnes_rom) 
		cout << "Det finnes ingen rom i denne kategorien." << endl;
	
	if(finnes_rom && !er_rom_ledig) 
		cout << "Det finnes ingen ledige rom i denne kategorien" << endl;
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
	ofstream utfil(hotellet->get_filnavn() + ".DTA");
	if (utfil.is_open()) 	// Åpner filen
		hotellet->skriv_til_fil(&utfil);
    utfil.close();
	cout << "Hotellet ble skrevet til fil";
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
     
			unsigned pos = (int) orginal.find(" ");

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
	return false;
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