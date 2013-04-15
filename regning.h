#if !defined(__REGNING_H)
#define __REGNING_H 
#include "listtool.h"
#include <fstream>
#include <string>
using namespace std;

class Regning : public Text_element {

	private:
		float totalsum;
	public:
    Regning();
    Regning(char* nvn, int total);
    Regning(char* nvn, ifstream &file);
    ~Regning();
    void display();
    int sum();
	void skriv_til_fil(ostream* ut);
};

#endif
