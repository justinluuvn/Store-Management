#include "Customer.h"
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

//constructors
Customer::Customer()
{
	strcpy(this->address, "unknown");
	strcpy(this->purchase, "");
}

Customer::Customer(char* address, char* purchase)
{
	strcpy(this->address, address);
	strcpy(this->purchase, purchase);
}

//set values
void Customer::update_purchase(Product product, float amount)
{
	char temp[NLEN + 18];
	sprintf(temp, "%-20s %-15.3f\n", product.name, amount);
	strcat(this->purchase, temp);
}

void Customer::update_info(char* name, char* id, char* category)
{
	strcpy(this->name, name);
	strcpy(this->id, id);
	strcpy(this->category, category);
}

void Customer::more_purchase(char* purchase)
{
	strcat(this->purchase, purchase);
}

void Customer::set_addr(char* addr)
{
	strcpy(this->address, addr);
}

void Customer::clear_purchase()
{
	strcpy(this->purchase,"");
}

//get values
float Customer::get_total_purchase(Product* product, short size)
{
	float sum = 0;
	short step = 1, i = 0, j = 0;
	char pname[NLEN], amount[15];

	for (i = 0; i < strlen(this->purchase); i++)
	{
		if (step == 0 && this->purchase[i] == '\n')
			step++;
		else if (step == 1)
		{
			pname[j] = this->purchase[i];
			j++;
			if (this->purchase[i + 1] == ' ' && this->purchase[i + 2] == ' ')
			{
				step++;
				pname[j] = '\0';
				j = 0;
			}
		}
		else if (step == 2 && this->purchase[i + 1] != ' ')
			step++;
		else if (step == 3)
		{
			amount[j] = this->purchase[i];
			j++;
			if ((this->purchase[i + 1] == ' ' && this->purchase[i + 2] == ' ') || this->purchase[i+1] == '\0')
			{
				step = 0;
				amount[j] = '\0';
				j = 0;
				cout.width(NLEN);
				cout << std::left << pname;
				Product* temp = product->search_by_name(pname, size);
				cout.width(15);
				cout << std::left << temp->get_price(pname);
				cout.width(15);
				cout << std::left << amount;
				float cost = atof(amount) * temp->get_price(pname);
				sum += cost;
				cout.width(20);
				cout << std::left << cost << endl;
				temp->update_amount(atof(amount));
			}
		}
	}

	return sum;
}

char* Customer::print_basic_info()
{
	char* temp = new char[110];
	sprintf(temp, "Name: %-20s\nID: %-5s\nCategory: %-15s\nAddress: %-32s", this->name, this->id, this->category, this->address);
	return temp;
}

char* Customer::print_purchase()
{
	return this->purchase;
}

//search
Customer* Customer::search_customer_id(char* id, short size)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp((this + i)->id, id))
			return (this + i);
	}
	return NULL;
}

Customer* Customer::search_customer_name(char* name, short size)
{
	for (int i = 0; i < size; i++)
	{
		if (!strcmp((this + i)->name, name))
			return (this + i);
	}
	return NULL;
}