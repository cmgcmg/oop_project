#pragma once

#include "CategoryList.h"
#include "ItemList.h"

class Manager
{
private:
	CategoryList		*cList;
	ItemList			*iList;
	ofstream			fout;
	vector<ItemNode*>	vItem;

public:
	Manager();
	~Manager();

	void run(const char* fileName);

	bool LOAD();
	bool ADD(char* arg);
	bool MODIFY(char* arg);
	bool SELL(char* arg);
	bool DELETE(char* arg);
	bool SEARCH(char* arg);
	bool PRINT(char* arg);
	bool MANAGE(char* arg);
	bool SALES(char* arg);
	bool SAVE();
};