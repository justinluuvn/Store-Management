//#include "stdafx.h"
#include "Customer.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//function prototypes
//for Product
Product* add_product(Product*, short*);
Product* remove_product(Product*, Product*, short*);
Product init_product(Product*, short);
void capitalize(char*);
void file_string(char*, fstream&);
//for Customer
Customer* add_Customer(Customer*, short*);
Customer* remove_customer(Customer*, Customer*, short*);
Customer init_customer(Customer*, short, Product*, short);

//declare static variables for the Firm_info class
char Firm_info::shop_name[NLEN], Firm_info::shop_pnumber[PHLEN];

int main()
{
	//general variables
	short npro, ncus = 0;
	Product* products;
	Customer* customers;

	//name of the product file
	char filename1[] = "products.txt";
	char filename2[] = "shop.txt";

	//processing data within the file
	char pname[NLEN], pid[IDLEN], pcat[CATLEN];
	float pprice, pamount;

	//variable for making choices
	short choice;

	//variable checking if needed to save
	short save = 0;

	fstream file, file1;

	file1.open(filename2, ios::in);
	if (!file1)
	{
		char name[NLEN], pnum[PHLEN];
		cout << "Please enter information for the shop.\nName: ";
		cin.getline(name, NLEN);
		cout << "Phone Number: ";
		cin.getline(pnum, PHLEN);
		Firm_info::update_shop_info(name, pnum);
		file1.close();
		file1.open(filename2, ios::out);
		file1 << name << "    " << pnum << "\0";
	}
	else
	{
		char name[NLEN], pnum[PHLEN];
		file_string(name, file1); 
		while (file1.peek() == ' ')
			file1.get();
		file1.get(pnum,PHLEN);
		Firm_info::update_shop_info(name, pnum);
	}

	file.open(filename1, ios::in | ios::out);

	cout << "Choose from the following choices: " << endl;
	cout << "  1. Load the list of products from file." << endl;
	cout << "  2. (Re)initialize the list of products." << endl;
	cout << "Please make your choice: ";
	cin >> choice;

	if ((choice == 1 && !file) || choice == 2)
	{
		cout << "Enter the number of products: ";
		cin >> npro;
		while (npro <= 0)
		{
			cout << "The number of products must be greater than zero: ";
			cin >> npro;
		}

		products = new Product[npro];

		for (int i = 0; i < npro; i++)
			products[i] = init_product(products, npro);

		save = 1;
	}
	else 
	{
		file >> npro;
		products = new Product[npro];

		for (int i = 0; i < npro; i++)
		{
			while (file.peek() == ' ')
				file.get(); 
			file.ignore();
			file_string(pname, file);
			while (file.peek() == ' ')
				file.get();
			file.get(pid, IDLEN, ' ');
			while (file.peek() == ' ')
				file.get();
			file_string(pcat, file);
			while (file.peek() == ' ')
				file.get();
			file >> pprice >> pamount;
			products[i].set_amount(pamount);
			products[i].set_price(pprice);
			products[i].update_info(pname, pid, pcat);
			products[i].set_category(pcat);
		}
	}
	

	while (true)
	{
		cout << "Choose from the following choices:" << endl;
		cout << "   1. Update info for the shop." << endl;
		cout << "   2. Update list of products." << endl;
		cout << "   3. Update list of customers." << endl;
		cout << "   4. Display info for the shop." << endl;
		cout << "   5. Display info for products." << endl;
		cout << "   6. Display info for customers" << endl;
		cout << "   7. Check out." << endl;
		cout << "   8. Quit." << endl;
		cout << "Please make your choice: ";
		cin >> choice;
		if (choice == 1)
		{
			char name[NLEN], pnum[PHLEN];
			cout << "Please enter information for the shop.\nName: ";
			cin.ignore();
			cin.getline(name, NLEN);
			cout << "Phone Number: ";
			cin.getline(pnum, PHLEN);
			Firm_info::update_shop_info(name, pnum);
			file1.close();
			file1.open(filename2, ios::out);
			file1 << name << "    " << pnum << "\0";
		}
		if (choice == 2)
		{
			cout << "Choose from the following choices:" << endl;
			cout << "  1. Add new product." << endl;
			cout << "  2. Update info for existing product." << endl;
			cout << "  3. Remove an existing product." << endl;
			cout << "  4. Back to main menu." << endl;
			cout << "Please make your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				products = add_product(products, &npro);
				products[npro - 1] = init_product(products, npro);
				save = 1;
			}
			else if (choice == 2)
			{
				cout << "Enter the ID of the product: ";
				char id[IDLEN];
				cin >> id;
				capitalize(id);
				Product* temp = products->search_product(id, npro);
				if (temp == NULL)
					cout << "No product with such ID." << endl;
				else
				{
					cout << "Product name: " << temp->get_name() << endl;
					float price, amount;
					cout << "Enter the new price for the product: ";
					cin >> price;
					temp->set_price(price);
					cout << "Enter the new amount for the product: ";
					cin >> amount;
					temp->set_amount(amount);
				}
				save = 1;
			}
			else if (choice == 3)
			{
				cout << "Enter the ID of the product: ";
				char id[IDLEN];
				cin >> id;
				capitalize(id);
				Product* temp = products->search_product(id, npro);
				if (temp == NULL)
					cout << "No product with such ID." << endl;
				else
				{
					products = remove_product(products, temp, &npro);
				}
				save = 1;
			}
			else if (choice == 4)
				continue;
		}
		else if (choice == 3)
		{
			cout << "Choose from the following choices:" << endl;
			cout << "  1. Add new customer." << endl;
			cout << "  2. Update info for existing customer." << endl;
			cout << "  3. Remove an existing customer." << endl;
			cout << "  4. Back to main menu." << endl;
			cout << "Please make your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				if (ncus == 0)
				{
					ncus++;
					customers = new Customer;
					customers[0] = init_customer(customers, ncus, products, npro);
				}
				else
				{
					customers = add_Customer(customers, &ncus);
					customers[ncus - 1] = init_customer(customers, ncus, products, npro);
				}
			}
			else if (choice == 2)
			{
				cout << "Enter the name of the customer: ";
				char name[NLEN];
				cin.ignore();
				cin.getline(name, NLEN);
				Customer* temp = customers->search_customer_name(name, ncus);
				if (temp == NULL)
					cout << "No customer with such name." << endl;
				else
				{
					cout << "Customer name: " << temp->get_name() << endl;
					char addr[ADDRLEN], single[40];
					cout << "Enter the new address for the customer ";
					cin.getline(addr, ADDRLEN);
					temp->set_addr(addr);
					while (true)
					{
						cout << "Enter the name of product to purchase: ";
						cin.getline(pname, NLEN);
						cout << "Enter the amount to purchase: ";
						cin >> pamount;
						sprintf(single, "%20s%15.3f", pname, pamount);
						temp->more_purchase(single);
						cout << "Do you want to continue purchasing?\n  1. Yes\n  2. No\nPlease make your choice: ";
						cin >> choice;
						if (choice == 2)
							break;
					}
				}
			}
			else if (choice == 3)
			{
				cout << "Enter the name of the customer: ";
				char name[NLEN];
				cin.ignore();
				cin.getline(name, NLEN);
				Customer* temp = customers->search_customer_name(name, ncus);
				if (temp == NULL)
					cout << "No customer with such name." << endl;
				else
					customers = remove_customer(customers, temp, &ncus);
			}
		}
		else if (choice == 4)
		{
			cout.width(NLEN);
			cout << std::left << "Shop Name";
			cout.width(PHLEN);
			cout << std::left << "Phone Number";
			cout << endl;
			for (int i = 0; i < NLEN + PHLEN; i++)
				cout << "-";
			char temp[NLEN + PHLEN + 5];
			Firm_info::get_shop_info(temp);
			cout << endl << temp << endl;
		}
		else if (choice == 5)
		{
			cout << "Choose from the following choices:" << endl;
			cout << "  1. Search for one product." << endl;
			cout << "  2. Display all products." << endl;
			cout << "  3. Back to main menu." << endl;
			cout << "Please make your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				cout << "Enter the ID of the product: ";
				char id[IDLEN];
				cin >> id;
				capitalize(id);
				char temp[INFOLEN];
				for (int i = 0; i < npro; i++)
				{
					if (products[i].get_all_info(id, temp))
					{
						cout << temp << endl;
						char temp[PROLEN];
						products[i].print_values(temp);
						cout << temp << endl;
						break;
					}
					else if (i == npro - 1)
						cout << "No product with such ID" << endl;
				}
			}
			else if (choice == 2)
			{
				cout.width(NLEN + 1);
				cout << std::left << "Product Name";
				cout.width(IDLEN + 1);
				cout << std::left << "ID";
				cout.width(CATLEN + 1);
				cout << std::left << "Category";
				cout.width(11);
				cout << std::left << "Price";
				cout.width(11);
				cout << std::left << "Amount" <<endl;
				for (int i = 0; i < 70; i++)
					cout << "-";
				cout << endl;
				for (int i = 0; i < npro; i++)
				{
					char temp[70];
					products[i].print_to_file(temp);
					cout << temp << endl;
				}
				for (int i = 0; i < 70; i++)
					cout << "-";	
				cout << endl;
			}
			else if (choice == 3)
				continue;
		}
		else if (choice == 6)
		{
			cout << "Choose from the following choices:" << endl;
			cout << "  1. Search for one customer." << endl;
			cout << "  2. Display all customers." << endl;
			cout << "  3. Back to main menu." << endl;
			cout << "Please make your choice: ";
			cin >> choice;
			if (choice == 1)
			{
				cout << "Enter the name of the customer: ";
				char name[NLEN];
				cin.ignore();
				cin.getline(name, NLEN);
				Customer* temp = customers->search_customer_name(name, ncus);
				if (temp == NULL)
					cout << "No customer with such name." << endl;
				else
				{
					cout << temp->print_basic_info() << endl << endl;
					cout << "List of Purchase: \n" << temp->print_purchase();
				}
			}
			else if (choice == 2)
			{
				for (int i = 0; i < ncus; i++)
				{
					cout << customers[i].print_basic_info() << endl;
					cout << "List of Purchase: \n" << customers[i].print_purchase();
				}
			}
			else if (choice == 3)
				continue;
		}
		else if (choice == 7)
		{
			char cname[NLEN];
			cout << "Enter the name of the customer: ";
			cin.ignore();
			cin.getline(cname, NLEN);
			Customer* temp = customers->search_customer_name(cname, ncus);
			if (temp == NULL)
				cout << "No customer with such name." << endl;
			else
			{
				cout << temp->print_basic_info() << endl;
				cout.width(NLEN);
				cout << std::left << "Product Name";
				cout.width(15);
				cout << std::left << "Price";
				cout.width(15);
				cout << std::left << "Amount";
				cout.width(20);
				cout << std::left << "Individual Cost" << endl;
				for (int i = 0; i < 70; i++)
					cout << '-';
				cout << endl;
				float payment = temp->get_total_purchase(products, npro);
				for (int i = 0; i < 70; i++)
					cout << '-';
				cout << endl;
				cout.width(50);
				cout << std::left << "Total Payment";
				cout << payment << endl;
				temp->clear_purchase();  //after checkout, list of purchase gets erased
				save = 1;
			}
		}
		else if (choice == 8)
			break;
	}

	if (save)
	{
		char temp[DATALEN];
		file.close();
		file.open(filename1, ios::out);
		file << npro << endl;
		products[0].print_to_file(temp);
		file << temp;
		for (int i = 1; i < npro; i++)
		{
			products[i].print_to_file(temp);
			file << endl << temp;
		}
	}

	delete[] products;
	file.close();
	file1.close();

	return 0;
}

Product* add_product(Product* products, short* size)
{
	Product *temp;
	(*size)++;
	try {
		temp = new Product[*size];
	}
	catch (bad_alloc xa)
	{
		cout << "\nAllocation failure\n";
	}

	for (int j = 0; j < *size - 1; j++)
		temp[j] = products[j];
	return temp;
}

Product* remove_product(Product* products, Product* rm_product, short* size)
{
	Product *temp;
	(*size)--;
	try {
		temp = new Product[*size];
	}
	catch (bad_alloc xa)
	{
		cout << "\nAllocation failure\n";
	}

	int j;

	for (j = 0; &products[j] != rm_product; j++)
	{
		temp[j] = products[j];
	}

	for (j; j < *size; j++)
		temp[j] = products[j + 1];
	return temp;
}

Product init_product(Product* product, short size)
{
	//variables for products
	char name[NLEN], id[IDLEN], cat[CATLEN];
	float price, amount;

	//enter information for the new product
	cin.ignore();
	cout << "Enter the name for product: ";
	cin.getline(name, NLEN);

	while (true)
	{
		cout << "Enter the ID for product: ";
		cin >> id;
		capitalize(id);
		if (product->search_product(id, size) == NULL)
			break;
		else
			cout << "This ID has already been used, please enter a different one." << endl;
	}
		
	cout << "Enter the category for product: ";
	cin.ignore();
	cin.getline(cat, CATLEN);

	cout << "Enter the price for product: ";
	cin >> price;

	cout << "Enter the amount for product: ";
	cin >> amount;

	Product temp = Product(price, amount);
	temp.update_info(name, id, cat);
	temp.set_category(cat);

	return temp;
}

void capitalize(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if ('a' <= str[i] && str[i] <= 'z')
			str[i] += 'A' - 'a';
	}
}

void file_string(char* str, fstream& file)
{
	char temp[WLEN];
	file.get(str, WLEN, ' ');
	while (file.peek() != (int)'\n' && file.peek() != (int)'\0')
	{
		file.get();
		if (file.peek() == (int)' ')
			break;
		else
		{
			file.get(temp, WLEN, ' ');
			strcat(str, " ");
			strcat(str, temp);
		}
	}
}

Customer* add_Customer(Customer* customers, short* size)
{
	Customer *temp;
	(*size)++;
	try {
		temp = new Customer[*size];
	}
	catch (bad_alloc xa)
	{
		cout << "\nAllocation failure\n";
	}

	for (int j = 0; j < *size - 1; j++)
		temp[j] = customers[j];
	return temp;
}

Customer* remove_customer(Customer* customers, Customer* rm_customer, short* size)
{
	Customer *temp;
	(*size)--;
	try {
		temp = new Customer[*size];
	}
	catch (bad_alloc xa)
	{
		cout << "\nAllocation failure\n";
	}

	int j;

	for (j = 0; &customers[j] != rm_customer; j++)
	{
		temp[j] = customers[j];
	}

	for (j; j < *size; j++)
		temp[j] = customers[j + 1];
	return temp;
}

Customer init_customer(Customer* customer, short size, Product* product, short psize)
{
	//variables for products
	char name[NLEN], id[IDLEN], cat[CATLEN], addr[ADDRLEN], purchase[PURLEN] = "", pname[NLEN], single[40];
	float amount;
	short choice;

	//enter information for the new customer
	cout << "Enter the customer name: ";
	cin.ignore();
	cin.getline(name, NLEN);

	while (true)
	{
		cout << "Enter the ID for customer: ";
		cin >> id;
		if (customer->search_customer_id(id, size) == NULL)
			break;
		else
			cout << "This ID has already been used, please enter a different one." << endl;
	}

	cin.ignore();

	cout << "Enter the category for customer: ";
	cin.getline(cat, CATLEN);

	cout << "Enter the customer's address: ";
	cin.getline(addr, ADDRLEN);
	Product* protemp;

	while (true)
	{
		while (true)
		{
			cout << "Enter the name of product to purchase: ";
			cin.getline(pname, NLEN);
			protemp = product->search_by_name(pname, psize);
			if (protemp == NULL)
				cout << "Wrong name, please enter again.\n";
			else
				break;
		}
		while (true)
		{
			cout << "Enter the amount to purchase: ";
			cin >> amount;
			if (protemp->get_amount() < amount)
				cout << "Insufficient supply, please reduce your demand.\n";
			else
				break;
		}
		sprintf(single, "%-20s%-15.3f\n", pname, amount);
		strcat(purchase, single);
		cout << "Do you want to continue purchasing?\n  1. Yes\n  2. No\nPlease make your choice: ";
		cin >> choice;
		cin.ignore();
		if (choice == 2)
		{
			strcat(purchase, "\0");
			break;
		}
	}

	Customer temp = Customer(addr, purchase);
	temp.update_info(name, id, cat);
	return temp;
}