#pragma once
using namespace std;

class Customer
{
public:
	int customerId;
	string honoric;
	string fName;
	string lName;
	string cName;
	string cSalesman;
	float purchaseValue;
	string preSalesman;
	float comValue;

	Customer(int customerId, string honoric, string fName, string lName,
		string cName, string cSalesman, float purchaseValue, string preSalesman, float comValue);
	~Customer();
	float getPurchaseValue();
	float getComValue();
	bool checkFraud();
	string getPreSalesman();
	void printDetail(); 
	int getId();



};
