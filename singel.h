#if !defined(__SINGEL_H)
#define __SINGEL_H

#include "rom.h"

class Singel: public Rom {
private:

public:
	Singel();
	Singel(int romnr);
	~Singel();
};

#endif