#include "Firm_info.h"
#include <cstring>
#include <cstdio>

//Constructors
Firm_info::Firm_info()
{
	strcpy(this->category, "unknown");
}

Firm_info::Firm_info(char* cat)
{
	strcpy(this->category, cat);
}

Firm_info::Firm_info(char* name, char* pnum, char* cat)
{
	strcpy(this->shop_name, name);
	strcpy(this->shop_pnumber, pnum);
	strcpy(this->category, cat);
}

//get values
void Firm_info::get_shop_info(char* str)
{
	sprintf(str, "%s", shop_name);
	for (int i = strlen(shop_name); i < NLEN; i++)
		strcat(str, " ");
	char temp[PHLEN];
	sprintf(temp, "%s", shop_pnumber);
	strcat(str, temp);
}

char* Firm_info::get_category()
{
	return this->category;
}

//set values
void Firm_info::update_shop_info(char* name, char* pnum)
{
	strcpy(shop_name, name);
	strcpy(shop_pnumber, pnum);
}

void Firm_info::set_category(char* cat)
{
	strcpy(this->category, cat);
}