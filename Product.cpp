#include "Product.h"
#include <cstring>
#include <cstdio>

//Constructors
Product::Product()
{
	this->price = 0;
	this->amount = 0;
}

Product::Product(float price, float amount) 
{
	this->price = price;
	this->amount = amount;
}

//get values
float Product::get_price(char* name)
{
	if (strcmp(this->name, name) == 0)
		return this->price;
}

float Product::get_amount()
{
	return this->amount;
}

void Product::print_values(char* str)
{
	sprintf(str, "Price: %.3f\nAmount: %.3f", this->price, this->amount);
}

void Product::print_to_file(char* str)
{
	sprintf(str, "%-20s %-5s %-15s %-10.3f %-10.3f", this->name, this->id, this->category, this->price, this->amount);
}

//set values
void Product::update_amount(float amount)
{
	this->amount -= amount;
}

void Product::set_price(float price)
{
	this->price = price;
}

void Product::set_amount(float amount)
{
	this->amount = amount;
}

void Product::update_info(char* name, char* id, char* category)
{
	strcpy(this->name, name);
	strcpy(this->id, id);
	strcpy(this->category, category);
}

//search
Product* Product::search_product(char* id, short size)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp((this + i)->id, id))
			return (this + i);
	}
	return NULL;
}


Product* Product::search_by_name(char* name, short size)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp((this + i)->name, name))
			return (this + i);
	}
	return NULL;
}