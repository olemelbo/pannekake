#if !defined(__ROM_H)
#define __ROM_H

#include "listtool.h"
#include <fstream>

using namespace std;

class Rom: public Num_element {
protected:
	List* reservasjoner;
	int ant_senger;
	bool frokost_inkludert;

public:
	Rom();
	Rom(int romnr);
    Rom(int romnr, ifstream &file);
	~Rom();
	void skriv_til_fil(ostream* ut);
    bool ledig();
    List* get_reservasjoner();
};

#endif