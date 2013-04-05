#if !defined(__REGNING_H)
#define __REGNING_H 

class Regning {
	private:
		float totalsum;
		char* navn;
	public:
		Regning() {}
		Regning(int total, char* nvn) {}
		~Regning() {
			delete navn;
		}
};

#endif