#if !defined(__SINGEL_H)
#define __SINGEL_H

#include <fstream>
#include "rom.h"

using namespace std;

class Singel: public Rom {
private:

public:
	Singel();
	Singel(int romnr);
    Singel(int romnr, ifstream& infile);
	~Singel();
	void skriv_til_fil(ostream* ut);
};

#endif