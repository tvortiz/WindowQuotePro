#include <iostream>
#include "Table_Quote.h"
#include "sqlite.h"
#include <list>

void connect()
{
	sqlite_open("local_database.sql");

	sqlite_run_query("CREATE TABLE Quotes (id INTEGER PRIMARY KEY AUTOINCREMENT, quote_name varchar(101), customer varchar(101), material varchar(10), size varchar(10), price float)");
}

void insert(const char quote_name[100], const char customer[100], const char material[10], const char size[10], const float price)
{
	char query[500];

	sprintf_s(query, "INSERT INTO Quotes (quote_name, customer, material, size, price) VALUES ('%s', '%s', '%s', '%s', %f)", quote_name, customer, material, size, price);

	sqlite_run_query(query);
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	std::list<Quote>* l = (std::list<Quote>*)NotUsed;
	
	Quote q;

	q.id = atoi(argv[0]);
	strcpy_s(q.quote_name, argv[1]);
	strcpy_s(q.customer, argv[2]);
	strcpy_s(q.material, argv[3]);
	strcpy_s(q.size, argv[4]);
	q.price = atof(argv[5]);

	l->push_back(q);

	return 0;
}

std::list<Quote> select_all()
{
	std::list<Quote> l;

	sqlite_run_select("select * FROM Quotes", callback, &l);

	return l;
}

void disconnect()
{
	sqlite_close();
}