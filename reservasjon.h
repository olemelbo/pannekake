#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

#include <fstream>
#include "listtool.h"
#include "coen.h"
#include <string>
#include "rom.h"
using namespace std;

/** Klassen Reservasjon inneholder informasjon om romtype, avreise- og ankomst-dato, 
 *  priser per d�gn, regniner, status for ekstra seng og frokost,
 *  antall beboere, navn p� beboere og status for innsjekking
 */
class Reservasjon : public Num_element {
	private:
		int romtype;		//romtype[singel, dobbel, suite]
		int avreise_dato;	//avreise-dato
		int antall_dogn;	//avreise-dato
		float pris[MAX_ARRAY];	//array med priser per d�gn for overnatting
		List* regninger;	//liste med regninger
		int status_seng;	//status for ekstra seng
		int status_frokost;	//status for frokost
		int antall_beboere;	//antall beboere
		string navn[MAX_ARRAY];	//array med navn p� beboere
		bool innsjekket;	//om reservasjonen er innsjekket
	public:
    Reservasjon();

    Reservasjon(int ankomst, int avreise, int romt, bool frokost, bool seng, int ant_beboere, string beboere[MAX_ARRAY]);
    
    Reservasjon(int ankomst, ifstream &file);

    ~Reservasjon();

	bool is_name_in_array(string name);
	int getAnkomstDato();
	int getAvreiseDato();
	void setAntallBeboere(int ant);
	void setBeboere(string beboere[MAX_ARRAY], int teller);
    void les_fra_fil();
    void skriv_til_fil(ostream* ut);
    void display();
	void display(Rom* rom);
	int getAntallBeboere();
	void display_faktura();
	void skriv_faktura_til_fil(string fil);
	void display_list(int count);
	void endre_ankomst(int ankomst);
	void endre_avreise(int avreise);
	void set_innsjekk();
	void set_utsjekk();
	bool er_innsjekket();
	void set_seng_status(int status);
	int get_status_seng();
	void ledig_i_tidsperiode(int avreise, int ankomst, int teller, int antall_reservasjoner);
};

#endif