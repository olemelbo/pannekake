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
 *	Hotell klassen
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
	int ekstra_seng_pris;
	int antall_fasciliteter;
	string fasciliteter[MAX_ARRAY];
	List* rom[ANTALL_ROMTYPER];

public:
	Hotell();
	Hotell(string fil);
	~Hotell();
	void les_fra_fil();
	void skriv_til_fil(ostream* ut);
	void display();
	List* get_rom(int romtype);
    Rom* get_spesifikk_rom(int romnr);
    Rom* get_ledig_rom(int romtype);
	string get_filnavn();
};

#endif