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
	char kommando;	//Må endres til å ta tre tegn.
	
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
		 case Valg:E1 : endre_ankomst();
		break;
		 case Valg:E2 : endre_avreisedato();
		break;
		 case Valg:E3 : bytt_rom();
		break;
		 case Valg:O1 : oversikt_over_hotell();
		break;
		 case Valg:O2 : beskrivelse_av_suiter();
		break;
		 case Valg:O3 : vis_reservasjoner_for_rom();
		break;	
		 case Valg:O4 : rom_ledig();
		break;
		 case Valg:O5 : vis_reservasjoner_for_rom();
		break;
		 case Valg:O6 : vis_alle_data_for_rom();
		break;
		 case 'T' : skriv_til_fil();
		break;
		 case 'H' : bytt_hotell();
		break;	
       default:   skriv_meny();  break;
     }
     kommando = les_kommando();        //  F†r inn brukers ›nske.
   }
	avslutt();
	return 0;
}