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

    Reservasjon(int ankomst );
    
    Reservasjon(int ankomst, ifstream &file);
    ~Reservasjon();

    void les_fra_fil();
    void skriv_til_fil(ostream* ut);
    void display();
};

<<<<<<< HEAD
		void les_fra_fil();
		void skriv_til_fil();
		void display();
};

=======
>>>>>>> 5aa4343436c594663d2d2f199ab23c70f3496bf9
#endif