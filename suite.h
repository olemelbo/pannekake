#if !defined(__SUTIE_H)
#define __SUTIE_H

#include <fstream>
#include "coen.h"
#include "rom.h"
#include "utils.h"

using namespace std;

class Suite: public Rom {
private:
	int antall_senger;
	int antall_kvadratmeter;
	char* beskrivelse;

public:
	Suite();
	Suite(int romnr);
    Suite(int romnr, ifstream &file);
	~Suite();
};

#endif