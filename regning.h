#if !defined(__REGNING_H)
#define __REGNING_H 
#include "listtool.h"
#include <fstream>
using namespace std;

class Regning : public Num_element {

	private:
		float totalsum;
	public:
    Regning();
    Regning(int total, char* nvn);
    ~Regning();
	void skriv_til_fil(ostream* ut);
};

#endif
