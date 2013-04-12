#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

#include <fstream>
#include "listtool.h"
#include "coen.h"
#include <string>
using namespace std;

class Reservasjon : public Num_element {
	private:
		string romtype;
		int avreise_dato;
		int antall_dogn;
		float pris[MAX_ARRAY];
		List* regninger;
		int status_seng;
		int status_frokost;
		int antall_beboere;
		string navn[MAX_ARRAY];
	public:
    Reservasjon();

    Reservasjon(int ankomst, int avreise, bool frokost, bool seng, int ant_beboere, string beboere[MAX_ARRAY]);
    
    Reservasjon(int ankomst, ifstream &file);
    ~Reservasjon();

	bool is_name_in_array(string name);

	int getAnkomstDato();
	int getAvreiseDato();
	void setAntallBeboere(int ant);
	void setBeboere(string beboere[MAX_ARRAY]);
    void les_fra_fil();
    void skriv_til_fil(ostream* ut);
    void display();
};

#endif