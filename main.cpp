#include <iostream>
#include "coen.h"
#include "proc.cpp"

using namespace std;

enum Valg {
	E1,
	E2,
	E3,
	O1,
	O2,
	O3,
	O4,
	O5,
	O6
};

int main( void ) {
	char kommando;	//M� endres til � ta tre tegn.
	
	//  Looper til 'q'/'Q' tastes:
	while (kommando != 'Q')  {
     switch (kommando)  {
		 case 'B' : reserver_rom();
		break;
		 case 'A' : avbestill_rom();
		break;
		 case 'I' : innsjekking();
		break;
		 case 'U' : utsjekking();
		break;
		 case 'R' : registrer_regning();
		break;
		 case 'Z' : endre_ankomst();
		break;
		 case 'X' : endre_avreisedato();
		break;
		 case 'C' : bytt_rom();
		break;
		 case 'S' : oversikt_over_hotell();
		break;
		 case 'D' : beskrivelse_av_suiter();
		break;
		 case 'F' : vis_reservasjoner_for_rom();
		break;	
		 case 'G' : rom_ledig();
		break;
		 case 'J' : vis_reservasjoner_for_rom();
		break;
		 case 'K' : vis_alle_data_for_rom();
		break;
		 case 'L' : ledige_rom_kategori();
		break;
		 case 'T' : skriv_til_fil();
		break;
		 case 'H' : bytt_hotell();
		break;	
    	 default:   skriv_meny();  
        break;
     }

     kommando = les_kommando();        //  F�r inn brukers �nske.
   }
	avslutt();
	return 0;
}