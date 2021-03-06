#if !defined(__SUTIE_H)
#define __SUTIE_H

#include <fstream>
#include "coen.h"
#include "rom.h"
#include "utils.h"

using namespace std;

/** Klassen Suite inneholder antall senger, antall kvadratmeter og en beskrivelse
 */
class Suite: public Rom {
private:
	int antall_senger;
	int antall_kvadratmeter;
	string beskrivelse;

public:
	Suite();
	Suite(int romnr);
    Suite(int romnr, ifstream &file);
	~Suite();

	void display();
	void skriv_til_fil(ostream* ut);
};

#endif