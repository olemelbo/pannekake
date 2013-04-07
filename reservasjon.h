#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

#include <fstream>
#include "listtool.h"
#include "coen.h"

using namespace std;

class Reservasjon : public Num_element {
	private:
		int avreise_dato;
		int antall_dogn;
		float pris[MAX_ARRAY];
		List* regninger;
		int status_seng;
		int antall_beboere;
		char* navn[MAX_ARRAY];
	public:
    Reservasjon();

    Reservasjon(char* romtype, int ankomst, int avreise, bool frokost, bool seng );
    
    Reservasjon(int ankomst, ifstream &file);
    ~Reservasjon();

	bool is_name_in_array(char *name);

    void les_fra_fil();
    void skriv_til_fil(ostream* ut);
    void display();
};

#endif