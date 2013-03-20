#if !defined(__ROM_H)
#define __ROM_H

#include "listtool.h"

class Rom: public Num_element {
protected:
	List* reservasjoner;
	int ant_senger;
	bool frokost_inkludert;

public:
	Rom();
	Rom(int romnr);
	~Rom();
};

#endif