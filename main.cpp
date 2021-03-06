#include <iostream>
#include "coen.h"
#include "proc.h"
#include "hotell.h"
#include "reg_post.h"
#include "timer.h"

using namespace std;

//	Globale variable
Hotell* hotellet;	// Et hotell
Reg_post reg_post;	// Et reg_post objekt
Timer timer;		// Et timer objekt
int dagens_dato = timer.hent_dato();	// Dagensdato

int main( void ) {
    bytt_hotell();
	skriv_meny();
	
	char kommando = les_kommando();	

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
		 case 'Z' : endre_ankomst_avreisedato();
		break;
		 case 'X' : endre_avreisedato();
		break;
		 case 'C' : bytt_rom();
		break;
		 case 'S' : oversikt_over_hotell();
		break;
		 case 'D' : beskrivelse_av_suiter();
		break;
		 case 'F' : vis_alle_reservasjoner_for_person();
		break;	
		 case 'G' : rom_ledig();
		break;
		 case 'J' : vis_reservasjoner_for_rom();
		break;
		 case 'K' : vis_navarende_beboer();
		break;
		 case 'L' : vis_alle_ledige_rom_i_kategori();
		break;
		 case 'T' : skriv_til_fil();
		break;
		 case 'H' :
                    skriv_til_fil();
                    bytt_hotell();
					skriv_meny();
		break;	
    	 default:   skriv_meny();  
        break;
     }

     kommando = les_kommando();        //  F�r inn brukers �nske.
   }
	return 0;
}
