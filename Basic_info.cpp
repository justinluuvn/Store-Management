#include "Basic_info.h"
#include <cstring>
#include <cstdio>
using namespace std;

Basic_info::Basic_info()
{
	strcpy(this->name, "unknown");
	strcpy(this->id, "unkonwn");
	strcpy(this->category, "unkonwn");
}

Basic_info::Basic_info(char* name, char* id, char* cat)
{
	strcpy(this->name, name);
	strcpy(this->id, id); 
	strcpy(this->category, cat);
}

short Basic_info::get_all_info(char* id, char* str)
{
	if (strcmp(this->id, id) == 0)
	{
		sprintf(str, "Name: %s\nID: %s\nCategory: %s", this->name, this->id, this->category);
		return 1;
	}
	else
		return 0;
}

char* Basic_info::get_name()
{
	return this->name;
}