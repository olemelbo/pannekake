#if !defined(__REGNING_H)
#define __REGNING_H 
#include "listtool.h"
class Regning : public Num_element {
	private:
		float totalsum;
	public:
    Regning();
    Regning(int total, char* nvn);
    ~Regning();
};

#endif
