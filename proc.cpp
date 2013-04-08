#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include "proc.h"
#include "coen.h"
#include "hotell.h"
#include "reservasjon.h"
#include "utils.h"

using namespace std;

// Extern 
extern Hotell* hotellet;

//  PROSEDYREDEKLARASJON:
char les_kommando() {
	char cmd;
    cout << endl << "Tast inn kommando: ";
    cin >> cmd; cin.ignore(0);
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
	char buffer[80];

	Reservasjon *temp;

	char* romtype;
	cout << "Hvilken romtype ønsker du? [Singel/Dobbel/Suite] ";
	cin >> buffer;
	romtype = new char[strlen(buffer)+1];
	strcpy(romtype, buffer);

	int annkomstdato;
	cout << "Skriv inn annkomstdato[ååååmmdd]: ";
	cin >> annkomstdato;//Sjekk >= dagens dato
	cin.ignore();

	int avreisedato;
	cout << "Skriv inn avreisedato[ååååmmdd]: ";
	cin >> avreisedato;//Større enn annkomstdato
	cin.ignore();

	bool frokost = false;
	char onskerfrokost;
	cout << "Ønsker du frokost? [y/n] ";
	cin >> onskerfrokost;
	if(onskerfrokost == 'y'){
		frokost == true;
	}
	
	bool ekstraseng = false;
	char onskerekstraseng;
	if(romtype == "Dobbel"){
		cout << "Er det behov for en ekstra seng? [y/n] ";
		cin >> onskerekstraseng;
		if(onskerekstraseng == 'y'){
			ekstraseng == true;
		}
	}



	temp = new Reservasjon(romtype, annkomstdato, avreisedato, frokost, ekstraseng);

	if(romtype == "Singel"){
		hotellet->get_rom(SINGEL)->add(temp);
	}
	else if(romtype == "Dobbel"){
		hotellet->get_rom(DOBBEL)->add(temp);
	}
	else if(romtype == "Suite"){
		hotellet->get_rom(SUITE)->add(temp);
	}
	else;

}

void avbestill_rom() {
	char temp_navn[MAX_TEXT];
	char* navn;
	
	cout << "Skriv inn reservat>ens navn";
	cin >> temp_navn;
	navn = new char[strlen(temp_navn)+1];
	
	hotellet->avbestill_rom(navn);
	
}

void innsjekking() {
	cout << "Skriv inn reservat>ens navn";
	char temp_navn[MAX_TEXT];
	char* navn;
	cin >> temp_navn;
	navn = new char[strlen(temp_navn)+1];
	
}

void utsjekking() {

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

}

void beskrivelse_av_suiter() {

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
	char* fil;
    fil = new char[strlen(HOTELL_SKRIV_FIL)+1];
    strcpy(fil, HOTELL_SKRIV_FIL);
	ofstream utfil(fil);
	if (utfil.is_open()) 	// Åpner filen
		hotellet->skriv_til_fil(&utfil);
    
    utfil.close();
}

void bytt_hotell() {
    char* userinput = getln("Tast inn navnet på filen");
    ifstream infile(HOTELL_FIL);
    if(infile.is_open()) {
        while(!infile.eof()) {
            
            //Initierer variabler
            char linje[MAX_TEXT];
            char original[MAX_TEXT];
            
            //Henter hele linjen fra filen
            infile.getline(original, MAX_TEXT);
            
            //Kopierer linje inn i egen variabel
            //slik at strtok ikke erstatter originalen
            strcpy(linje, original);
            
            //Henter ut første ord fra linjen
            char* nextWord = strtok(linje, " ");
            
            //Oppretter ny char peker og kopierer
            //første ordet inn i denne (kortnavn).
            char* kortnavn = new char[strlen(nextWord) + 1];
            strcpy(kortnavn, nextWord);
            
            //Langnavn er lik original - kortnavn.
            char* langnavn = stripWord(kortnavn, original);
            
            //Hvis brukerinput og langnavn er like
            if(strcmp(userinput, langnavn) == 0) {
                char* fil = strcat(kortnavn, ".DTA");
                hotellet = new Hotell(fil);
                return;
            }
        }
        
        cout << "Hotellet du spesifiserte finnes ikke";
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
