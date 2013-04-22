#if !defined(__REGNING_H)
#define __REGNING_H 
#include "listtool.h"
#include <fstream>
#include <string>
using namespace std;
/**
 *	Regning inneholder totalsum og sender teksten for hva regningen gjelder til Text_element
 */
class Regning : public Text_element {

	private:
		float totalsum; // Totalsum for regning.
		

public:
    Regning();
    Regning(char* nvn, float total);
    Regning(char* nvn, ifstream &file);
    ~Regning();
    void display();
    int sum();
	void skriv_til_fil(ostream* ut);
	float hent_sum();
};

#endif
