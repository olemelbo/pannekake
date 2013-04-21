#if !defined(__REG_POST_H)
#define __REG_POST_H 

#include "coen.h"
#include <string>

using namespace std;
/**
 *	Reg_post klassen inneholder antall standard reg poster,
 *	og navnet p� disse.
 */
class Reg_post {
	private:
		int antall_standard_reg_poster;
		string mest_vanlige_poster[MAX_ARRAY];
	public:
		Reg_post();
		Reg_post( int antall, string vanlige_reg_poster[MAX_ARRAY] );
		~Reg_post();
		void display();
		string get_post(int tall);
};

#endif
