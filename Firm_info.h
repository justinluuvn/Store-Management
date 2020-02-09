#include "Constants.h"

class Firm_info {
	static char shop_name[NLEN], shop_pnumber[PHLEN];
	char category[CATLEN];

public:
	//Constructors
	Firm_info();
	Firm_info(char*);
	Firm_info(char*, char*, char*);

	//get values
	static void get_shop_info(char*);
	char* get_category();

	//set values
	static void update_shop_info(char*, char*);
	void set_category(char*);
};