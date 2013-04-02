#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

#include "listtool.h"
#include "coen.h"

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
    ~Reservasjon();

    void les_fra_fil();
    void skriv_til_fil();
    void display();
};

#endif