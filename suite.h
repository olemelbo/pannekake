#if !defined(__SUTIE_H)
#define __SUTIE_H

#include "coen.h"
#include "rom.h"

class Suite: public Rom {
private:
	int antall_senger;
	int antall_kvadratmeter;
	char* beskrivelse;

public:
	Suite();
	Suite(int romnr);
	~Suite();
};

#endif