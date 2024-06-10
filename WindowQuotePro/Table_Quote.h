#pragma once
#include <list>

class Quote
{
	public:
		int id;
		char quote_name[100];
		char customer[100];
		char material[10];
		char size[10];
		float price;
};

void connect();

void insert(const char quote_name[100], const char customer[100], const char material[10], const char size[10], const float price);

std::list<Quote> select_all();

void disconnect();