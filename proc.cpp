#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include "proc.h"
#include "coen.h"
#include "hotell.h"

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

}

void avbestill_rom() {

}

void innsjekking() {

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
    fil = new char[strlen(HOTELL_FIL)+1];
    strcpy(fil, HOTELL_FIL);
	ofstream utfil(fil);
	hotellet->skriv_til_fil(&utfil);
}

void bytt_hotell() {

}

void les_fra_fil() {
    char* fil;
    fil = new char[strlen(HOTELL_FIL)+1];
    strcpy(fil, HOTELL_FIL);

    Hotell* h = new Hotell(fil);
    h->display();
    
}

void avslutt() {

}
