#include <iostream>
#include "proc.h"

using namespace std;

//  PROSEDYREDEKLARASJON:
char les_kommando() {
	char cmd;
    cout << endl << "Tast inn kommando: ";
    cin >> cmd; cin.ignore(0);
    return toupper(cmd);
}

void skriv_meny()  {
	cout << "\n\nF›lgende kommandoer er lovlig:";
	cout << "\n\tB -	 Bestill/reserver/book et rom";
	cout << "\n\tA -	 Avbestill et rom";
	cout << "\n\tI -	 Innsjekking paa(ankomst til) hotellet";
	cout << "\n\tU -	 Utsjekking(avreise) fra hotellet";
	cout << "\n\tR -	 Registrer/legg inn en regning paa et rom";
	cout << "\n\tE 1 - Endre ankomst -og/eller avreisedato f>r innsjekking paa hotellet";
	cout << "\n\tE 2 - Beskrivelse av alle hotellers suiter";
	cout << "\n\tE 3 - Bytte til et annet (ledig) rom enn det tildelte";
	cout << "\n\tO 1 - hoveddatene om ett hotell";
	cout << "\n\tO 2 - beskrivelse av alle hotellets suiter";
	cout << "\n\tO 3 - alle reservasjoner som står i en persons navn";
	cout << "\n\tO 4 - naar et rom er ledig";
	cout << "\n\tO 5 - alle reservasjoner for/paa et rom";
	cout << "\n\tO 6 - alle data for ett roms nåv>erende beboer, inkludert dens regninger";
	cout << "\n\tO 7 - alle ledeige rom i en kategori";
	cout << "\n\tT -   skriv alt om hotellet til fil";
	cout << "\n\tH -   Bytte over til et annet hotell";
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

}

void bytt_hotell() {

}

void les_fra_fil() {

}

void avslutt() {

}
