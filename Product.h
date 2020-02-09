#include "Basic_info.h"
#include "Firm_info.h"

class Product: virtual public Basic_info, virtual public Firm_info{
	float price, amount;
	char category[CATLEN];

public:
	//constructors
	Product();
	Product(float, float);

	//get values
	float get_price(char* name);
	float get_amount();
	void print_values(char*);
	void print_to_file(char*);

	//set values
	void update_amount(float);
	void set_price(float);
	void set_amount(float);
	void update_info(char*, char*, char*);

	//search
	Product* search_product(char*, short);
	Product* search_by_name(char*, short);
};