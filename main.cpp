	//  PROSEDYREDEKLARASJON:
char les_kommando();
void skriv_meny();
void reserver_rom();
void avbestill_rom();
void innsjekking();
void utsjekking();
void registrer_regning();
void endre_ankomst();
void endre_avreisedato();
void bytt_rom();
void oversikt_over_hotell();
void beskrivelse_av_suiter();
void alle_reservasjoner_person();
void rom_ledig();
void vis_reservasjoner_for_rom();
void vis_alle_data_for_rom();
void vis_alle_ledige_rom_i_kategori();
void skriv_til_fil();
void bytt_hotell();
void les_fra_fil();
void avslutt();

int main( void ) {
	char kommando;	//Må endres til å ta tre tegn.
	
	skriv_meny();                        //  Skriver brukermeny.
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
		 case 'E 1' : endre_ankomst();
		break;
		 case 'E 2' : endre_avreisedato;
		break;
		 case 'E 3' : bytt_rom();
		break;
		 case 'O 1' : oversikt_over_hotell();
		break;
		 case 'O 2' : beskrivelse_av_suiter();
		break;
		 case 'O 3' : vis_reservasjoner_for_rom();
		break;	
		 case 'O 4' : rom_ledig();
		break;
		 case 'O 5' : vis_reservasjoner_for_rom();
		break;
		 case 'O 6' : vis_alle_data_for_rom();
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

void skriv_meny()  {
  cout << "\n\nF›lgende kommandoer er lovlig:";
  cout << "\n\tB -	 Bestill/reserver/book et rom";
  cout << "\n\tA -	 Avbestill et rom";
  cout << "\n\tI -	 Innsjekking paa(ankomst til) hotellet;
  cout << "\n\tU -	 Utsjekking(avreise) fra hotellet";
  cout << "\n\tR -	 Registrer/legg inn en regning paa et rom";
  cout << "\n\tE 1 - Endre ankomst -og/eller avreisedato f>r innsjekking paa hotellet";
  cout << "\n\tE 2 - Beskrivelse av alle hotellers suiter";
  cout << "\n\tE 3 - Bytte til et annet (ledig) rom enn det tildelte";
  cout << "\n\tO 1 - hoveddatene om ett hotell";
  cout << "\n\tO 2 - beskrivelse av alle hotellets suiter";
  cout << "\n\tO 3 - alle reservasjoner som står i en persons navn;
  cout << "\n\tO 4 - naar et rom er ledig";
  cout << "\n\tO 5 - alle reservasjoner for/paa et rom";
  cout << "\n\tO 6 - alle data for ett roms nåv>erende beboer, inkludert dens regninger";
  cout << "\n\tO 7 - alle ledeige rom i en kategori";
  cout << "\n\tT -   skriv alt om hotellet til fil";
  cout << "\n\tH -   Bytte over til et annet hotell";
}