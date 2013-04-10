#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

#include <fstream>
#include "listtool.h"
#include "coen.h"

using namespace std;

class Reservasjon : public Num_element {
	private:
		char* romtype;
		int avreise_dato;
		int ankomst_dato;
		int antall_dogn;
		float pris[MAX_ARRAY];
		List* regninger;
		int status_seng;
		int status_frokost;
		int antall_beboere;
		char* navn[MAX_ARRAY];
	public:
    Reservasjon();

    Reservasjon(int ankomst, int avreise, bool frokost, bool seng, int ant_beboere, char* beboere[MAX_ARRAY]);
    
    Reservasjon(int ankomst, ifstream &file);
    ~Reservasjon();

	bool is_name_in_array(char *name);

	int getAnkomstDato();
	int getAvreiseDato();
	void setAntallBeboere(int ant);
	void setBeboere(char* beboere[MAX_ARRAY]);
    void les_fra_fil();
    void skriv_til_fil(ostream* ut);
    void display();
};

#endif