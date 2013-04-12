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

class Hotell {
private:
	string navn;
	string gateadresse;
    string postadresse;
	string mailadresse;
	string filnavn;
	int telefon;
	int fax;
	int frokost_pris;
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
    Rom* get_ledig_rom(int romtype);
};

#endif