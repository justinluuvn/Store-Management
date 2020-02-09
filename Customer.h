#include "Product.h"

class Customer: virtual public Basic_info, virtual public Firm_info {
	char address[ADDRLEN], purchase[PURLEN];
	char category[CATLEN];

public:
	//constructors
	Customer();
	Customer(char*, char*);

	//set values
	void update_purchase(Product, float);
	void update_info(char*, char*, char*);
	void more_purchase(char*);
	void set_addr(char*);
	void clear_purchase();

	//get values
	float get_total_purchase(Product*, short);
	char* print_basic_info();
	char* print_purchase();

	//search
	Customer* search_customer_id(char*, short);
	Customer* search_customer_name(char*, short);
};