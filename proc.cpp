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

	char* romtype_tmp;
	cout << "Hvilken romtype >nsker du? [Singel/Dobbel/Suite] " << endl;
	cin >> buffer;
	romtype_tmp = new char[strlen(buffer)+1];
	strcpy(romtype_tmp, buffer);
    
    int romtype;
    if(strcmp(romtype_tmp, "Singel") == 0)
        romtype = SINGEL;
    if(strcmp(romtype_tmp, "Dobbel") == 0)
        romtype = DOBBEL;
    if(strcmp(romtype_tmp, "Suite") == 0)
        romtype = SUITE;

	int annkomstdato;
	cout << "Skriv inn annkomstdato[AAAAMMDD]: ";
	cin >> annkomstdato;//Sjekk >= dagens dato
	cin.ignore();

	int avreisedato;
	cout << "Skriv inn avreisedato[AAAAMMDD]: ";
	cin >> avreisedato;//Større enn annkomstdato
	cin.ignore();

	bool frokost = false;
	char onskerfrokost;
	cout << "Ønsker du frokost? [y/n] ";
	cin >> onskerfrokost;
	if(onskerfrokost == 'y'){
		frokost = true;
	}
	
	bool ekstraseng = false;
	char onskerekstraseng;
	if(romtype == DOBBEL){
		cout << "Er det behov for en ekstra seng? [y/n] ";
		cin >> onskerekstraseng;
		if(onskerekstraseng == 'y'){
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
    
    
    // Denne skal loope til vi har en reservatør
    char tmp[MAX_TEXT];
    int ant;

    /** // Kan ikke allokere array størrelse dynamisk ved runtime.
    cout << "Hvor mange beboere skal reserveres? ";
    cin >> tmp;
    ant = atoi(tmp);
    
    char* beboere[ant];
    for(int i = 0; i < ant; i++) {
        cout << "Skriv inn navnet på beboer " << i+1 << ": ";
        
        cin >> tmp;
        beboere[i] = new char[strlen(tmp)+1];
        strcpy(beboere[i], tmp);
    }

	*/

	cout << "Hvor mange beboere skal reserveres? ";
    cin >> tmp;
    ant = atoi(tmp);

	char* beboere[MAX_ARRAY];
	
	for(int i = 0; i < ant; i++) {
        cout << "Skriv inn navnet på beboer " << i+1 << ": ";
        
        cin >> tmp;
        beboere[i] = new char[strlen(tmp)+1];
        strcpy(beboere[i], tmp);
    }

    // Oppretter reservasjon
	temp = new Reservasjon(annkomstdato, avreisedato, frokost, ekstraseng, ant, beboere);
    
    // Legger reservasjonen til i rommet.
    r->get_reservasjoner()->add(temp);

    hotellet->les_fra_fil();
}

void avbestill_rom() {
	char temp_navn[MAX_TEXT];
	char* navn;
	
	cout << "Skriv inn reservat>ens navn: " << endl;
	cin >> temp_navn;
	navn = new char[strlen(temp_navn)+1];
	strcpy(navn, temp_navn);
	hotellet->avbestill_rom(navn);
}

void innsjekking() {
	cout << "Skriv inn reservat>ens navn" << endl;
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
	char* userinput;
	char* fil;
	do {
		ifstream infile(HOTELL_FIL);
		userinput = getln("Tast inn navnet p> filen");
		fil = does_hotell_exist_in_file(infile, userinput);
	} while(!fil);
	
	cout << userinput << " er lastet inn" << endl;
	hotellet = new Hotell(fil);
}

char* does_hotell_exist_in_file(ifstream& infile, char* userinput )
{
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
                return fil;
			} 
        }
		return false;
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
