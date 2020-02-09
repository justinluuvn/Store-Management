#include "Constants.h"

class Basic_info {
	char name[NLEN], id[IDLEN], category[CATLEN];

public:
	//constructors
	Basic_info();
	Basic_info(char*, char*, char*);

	//get values
	short get_all_info(char*, char*);
	char* get_name();

	//list of friend classes
	friend class Product;
	friend class Customer;
};