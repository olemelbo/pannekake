#if !defined(__REG_POST_H)
#define __REG_POST_H 

class Reg_post {
	private:
		int antall_brukt_reg_post;
		char mest_vanlige_poster[];
	public:
		Reg_post() {}
		Reg_post(int total, char* nvn) {}
		~Reg_post();
};

#endif