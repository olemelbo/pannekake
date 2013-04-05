#if !defined(__DOBBEL_H)
#define __DOBBEL_H

#include "rom.h"
#include <fstream>

using namespace std;

class Dobbel: public Rom {
private:
	bool ekstra_seng;

public:
	Dobbel();
	Dobbel(int romnr);
    Dobbel(int romnr, ifstream &file);
	~Dobbel();
	void skriv_til_fil(ostream *ut);
};

#endif