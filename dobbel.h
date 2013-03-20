#if !defined(__DOBBEL_H)
#define __DOBBEL_H

#include "rom.h"

class Dobbel: public Rom {
private:
	int ekstra_seng;

public:
	Dobbel();
	Dobbel(int romnr);
	~Dobbel();
};

#endif