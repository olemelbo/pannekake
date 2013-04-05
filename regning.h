#if !defined(__REGNING_H)
#define __REGNING_H 
<<<<<<< HEAD

class Regning {
=======
#include "listtool.h"
#include <fstream>
using namespace std;

class Regning : public Num_element {
>>>>>>> 5aa4343436c594663d2d2f199ab23c70f3496bf9
	private:
		float totalsum;
	public:
    Regning();
    Regning(int total, char* nvn);
    ~Regning();
	void skriv_til_fil(ostream* ut);
};

#endif
