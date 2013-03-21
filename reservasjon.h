#if !defined(__RESERVASJON_H)
#define __RESERVASJON_H

class Reservasjon : public Num_element {
	private:
		int avreise_dato;
		int antall_dogn;
		float pris[];
		List* regninger;
		int status_seng;
		int antall_beboere;
		char navn[char* navn];
	public:
		Reservasjon() {
	
		}

		Reservasjon(int ankomst ) : public Num_element(ankomst) {
	
		}

		~Reservasjon() {

		}

		void les_fra_fil();
		void skriv_til_fil();
		void display();
}
#endif