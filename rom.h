#if !defined(__ROM_H)
#define __ROM_H

#include "listtool.h"
#include <fstream>

using namespace std;
/**
 *	Rom klassen innholder romnummeret, sortert liste med reservasjoner, 
 *	antall senger, om frokst er inkludert eller ikke.
 */
class Rom: public Num_element {
protected:
	List* reservasjoner;	// Liste med reservasjoner
	int ant_senger;	// Antall senger
	bool frokost_inkludert;	// Om frokost er inkludert

public:
	Rom();
	Rom(int romnr);
    Rom(int romnr, ifstream &file);
	~Rom();
	void skriv_til_fil(ostream* ut);
    bool ledig(int ankomst, int avreise);
	bool ledig(int ankomst);
	void display();
    List* get_reservasjoner();
	int getRomNummer();
};

#endif