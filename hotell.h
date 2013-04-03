#if !defined(__HOTELL_H)
#define __HOTELL_H

#include "coen.h"
#include <fstream>
#include "listtool.h"
#include "singel.h"
#include "dobbel.h"
#include "suite.h"

class Hotell {
private:
	char* navn;
	char* gateadresse;
    char* postadresse;
	char* mailadresse;
	char* filnavn;
	int telefon;
	int fax;
	int frokost_pris;
	int ekstra_seng_pris;
	int antall_fasciliteter;
	char* fasciliteter[MAX_ARRAY];
	List* rom[ANTALL_ROMTYPER];

public:
	Hotell();
	Hotell(char* fil);
	~Hotell();
	void les_fra_fil();
	void skriv_til_fil();
	void display();
    void read_line(char* pointer, ifstream& infile);
};

#endif