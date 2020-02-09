# ------------------------------------------------C++ STORE MANAGEMENT PROJECT------------------------------------------------------------------ 

This project uses C++ language to create an application for managing a grocery store. The store has its name, phone number and product information 
stored in files after initialization. The program is able to deal with customer and product affair like adding new one or changing existing one,
updating the product stocking information according to receipt.

Table of content

1. Confiuration
2. Installation
2. Operation
3. Manifest
4. Copyright and License
5. Contact Information

1. Configuration
	This project requires G++ application in Linux Operating System in order to compile and run.  
2. Installation
	a) Please download the zip file from github.
	b) Unzip the newly downloaded file.	
	c) Open the terminal and navigate to the unzipped folder.
	d) Issue the command "g++ Store.cpp Basic_info.cpp Customer.cpp Firm_info.cpp Product.cpp -o store.exe" to compile the program.
	e) Use the command "./store.exe" to run the newly compiled program.
3. Operation
	a) If this is the first time the program is run, please initialize the name and phone number.
	b) Then, if there has been a file storing product information, it can be loaded into the program.
	c) Otherwise, initialization of these information is also required.
	d) There are separate options to due with customers, products and receipt.
4. Manifest (list of files and short description of their roles)
	a) Store.cpp
		The main file consists of code dealing with main options and functions.
	b) Basic_info.h
		Definition of Basic_info class along with its function prototypes.
	c) Basic_info.cpp
		Definition of function associated with Basic_info class.
	d) Customer.h
		Definition of Customer class along with its function prototypes.
	e) Customer.cpp
		Definition of function associated with Customer class.
	f) Firm_info.h
		Definition of Firm_info class along with its function prototypes.
	g) Firm_info.cpp
		Definition of function associated with Firm_info class.
	h) Product.h
		Definition of Product class along with its function prototypes.
	i) Product.cpp
		Definition of function associated with Product class.
5. Copyright and License
	G++(GNU) is distributed under GNU General Public License version 3.
	Linux is distributed under GNU General Public License version 2.0
	Other trademarks and trade names are those of their respective owners.
	The person mentioned in the contact information content has the copyright and license for the code.		
6. Contact Information
	Tin Luu,
	Department of Information Technology
	Vaasa University of Applied Sciences
	Wolffintie 30, Vaasa, Finland
	Home: http://www.cc.puv.fi/~e1700674
	Email: e1700674(at)edu.vamk.fi