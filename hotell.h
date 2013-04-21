#if !defined(__HOTELL_H)
#define __HOTELL_H

#include "coen.h"
#include <fstream>
#include "listtool.h"
#include "singel.h"
#include "dobbel.h"
#include "suite.h"
#include <string>
using namespace std;
/**
 *	Hotell klassen inneholder navn, gateadresse, mailadresse,
 *	filnavn, telefon, fax, ekstra pris for seng, fasiliteter,
 *  liste med rom.
 *
 */																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																												
class Hotell {
private:
	string navn;					// Hotellnavnet
	string gateadresse;				// Gateadresse
    string postadresse;				// Postadresse
	string mailadresse;				// Mailadresse
	string filnavn;					// Kortnavnet til fila
	int telefon;					// Telefon
	int fax;						// Fax
	int frokost_pris;				// Frokostpris
	int ekstra_seng_pris;			// Pris for ekstra seng
	int antall_fasciliteter;		// Antll fasiliteter
	string fasciliteter[MAX_ARRAY];	// Fasilteter
	List* rom[ANTALL_ROMTYPER];		// Liste med rom.

public:
	Hotell();
	Hotell(string fil);
	~Hotell();
	void skriv_til_fil(ostream* ut);
	void display();
	List* get_rom(int romtype);
    Rom* get_spesifikk_rom(int romnr);
    Rom* get_ledig_rom(int romtype, int ankomst, int avreise);
	string get_filnavn();
	int get_pris_seng();
	int get_pris_frokost();
};

#endif