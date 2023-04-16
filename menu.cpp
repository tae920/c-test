#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "customer.hpp" 

using namespace std;
vector <Customer*> customerList;

vector<string> Ids;

string filePath;

string salesStaff[] = { "Brad", "Janet", "Dr Scott", "Rifraf", "Nell", "Eddie" };

#define dir "C:\\Users\\hyole\\Downloads\\Assign1FilesZip\\"


string FNAME1 = "NamesdataA1TxtTst.txt";
string FNAME2 = "NamesdataA1Txt.txt";
string FNAME3 = "NamesdataA2Txt.txt";
string FNAME4 = "NamesdataA1TxtBadData.txt";
string FNAME5 = "NamesdataA1TxtDupid.txt";
string FNAME6 = "NamesdataA1TxtFraud.txt";


void doFilenames()
{
	FNAME1 = string(dir) + FNAME1;
	FNAME2 = string(dir) + FNAME2;
	FNAME3 = string(dir) + FNAME3;
	FNAME4 = string(dir) + FNAME4;
	FNAME5 = string(dir) + FNAME5;
	FNAME6 = string(dir) + FNAME6;

}

void tellFileName() {
	cout << "File: " << filePath << endl;
	cout << "Count of records: " << customerList.size() << endl;
}



Customer* parseLine(string str)
{
	vector<string> data;
	string newChar = "";
	Customer* retv = nullptr;

	for (int i = 0; i < (int)str.size(); i++)
	{

		char c = str[i];
		if (c != ',')
		{
			newChar = newChar + c;
		}
		else
		{
			data.push_back(newChar);
			newChar = "";
		}
	}


	retv = new Customer(stoi(data[0]), data[1], data[2], data[3], data[4], data[5], stof(data[6]), data[7], stof(data[8]));
	
	Ids.push_back(data[0]);


	return retv;
}

bool readFile() {
	ifstream myFile(filePath);

	if (!myFile.is_open())
	{
		cout << "It failed to open the file" << endl;
		return false;
	}

	string str;

	int i = 0;
	while (getline(myFile, str))
	{
		if (str[0] !=NULL)
		{
			Customer* customer = parseLine(str);
			customerList.push_back(customer);
		}
	}
	cout << "File "<< filePath<< " has been read successfully" << endl<<endl;
	return true;
}

void optionRead() {
	int selectedFile;
	customerList.clear();
	cout << "Option selected: r" << endl;
	cout << "Select file to process" << endl;
	cout << "1-" << FNAME1 << endl;
	cout << "2-" << FNAME2 << endl;
	cout << "3-" << FNAME3 << endl;
	cout << "4-" << FNAME4 << endl;
	cout << "5-" << FNAME5 << endl;
	cout << "6-" << FNAME6 << endl;
	cout << "Select file name: ";
	cin >> selectedFile;
	switch (selectedFile)
	{
	case 1:
		filePath = FNAME1;
		break;
	case 2:
		filePath = FNAME2;
		break;
	case 3:
		filePath = FNAME3;
		break;
	case 4:
		filePath = FNAME4;
		break;
	case 5:
		filePath = FNAME5;
		break;
	case 6:
		filePath = FNAME6;
		break;
	default:
		cout << "Not a Valid Choice. \n";
		cout << "Choose again.\n";
		cin >> selectedFile;
		break;
	}
	readFile();
}

void fileCheck() {
	double totalValue= 0;
	double totalCom = 0;
	for (Customer* customer : customerList) {
		totalValue = totalValue + customer->getPurchaseValue();
	}
	for (Customer* customer : customerList) {
		totalCom = totalCom + customer->getComValue();
	}
	cout << "Checking report" << endl;
	cout << "----------------" << endl;
	tellFileName();
	cout << "Total value: "<< totalValue<< endl;
	cout << "Total commisions: " << totalCom << endl;
}

void listShortForm() {
	cout << "Option selected: l"<< endl;
	for (int i = 0; i < customerList.size(); i++) {

		cout << "[" << i << "] = "; 
		customerList[i]->printDetail();
	}
}

void getFraudCustomer() {
	int countFraud=0;
	cout << "Option selected: f" << endl << endl;
	cout << "Fraud report" << endl;
	cout << "-------------" << endl;
	tellFileName();
	for (Customer* customer : customerList) {
		if (customer->checkFraud()) {
			countFraud = countFraud + 1;
		}
	}
	cout << "Total count of fraudulent transactions is: " << countFraud<<endl;
	}

vector<string> parseLineAudit(string pSalesNames)
{
	vector<string> pSalesNameList;
	string newChar = "";

	for (int i = 0; i < (int)pSalesNames.size(); i++)
	{

		char c = pSalesNames[i];
		if (c != ':')
		{
			newChar = newChar + c;
		}
		else
		{
			pSalesNameList.push_back(newChar);
			newChar = "";
		}
	}
	if (newChar != "") { pSalesNameList.push_back(newChar); }



	return pSalesNameList;
}

bool compareSalesman(string person) {
	int count = 0;
	for (int i = 0; i < 7; i++) {
		if (salesStaff[i] == person) {
			count = count + 1;
		}
	}
	if (count < 1) {
		return true;
	}
	return false;
}

bool duplicatedSalesman(string name, vector<string> pSalesNameList) {
	if (count(pSalesNameList.begin(), pSalesNameList.end(), name) > 1) {
		return true;
	}
	return false;
}

void findAudit() {
	int totalAudit = 0;
	cout << "Option selected: a" << endl;
	for (Customer* customer : customerList) {
		vector<string> pSalesNameList=parseLineAudit(customer->getPreSalesman());
		for (string salesName : pSalesNameList) {
			if (compareSalesman(salesName) || duplicatedSalesman(salesName, pSalesNameList)){
				totalAudit++;
				cout << "Account detail: ";
				customer->printDetail();
				cout << "Details: " << customer->getPreSalesman() << endl << endl;
				break;
			}
		}
	}
	cout << "Total count of bad data found: " << totalAudit << endl << endl;
}

void findDuplicatedId() {
	vector<int> idList;
	vector<int> sameIdList;
	cout << "Duplicate report" << endl;
	cout << "---------------"<<endl;
	tellFileName();
	for (Customer* customer : customerList) {
		idList.push_back(customer->getId());
	}

	for (int id : idList) {
		if (count(idList.begin(), idList.end(), id) > 1) {
			if (find(sameIdList.begin(), sameIdList.end(), id) ==sameIdList.end()) {
				sameIdList.push_back(id);
			}
		}
	}
	int countDupId = 0;
	for (int sameId : sameIdList) {
		vector<Customer*> answerCustomer;
		for (Customer* customer : customerList) {
			if (sameId == customer->getId()) {
				answerCustomer.push_back(customer);
			}
		}
		countDupId = countDupId + 1;
		cout << "Duplicate Account Found: Account number is: " << sameId<<endl;
		int countDetail = 0;
		for (Customer* answer : answerCustomer) {
			countDetail = countDetail + 1;
			cout << "Details "<<countDetail<<":"<<" ";
			answer->printDetail();
		}
		cout << endl;
	}
	cout<< "Total count of duplicate ID's found: " << countDupId<<endl<<endl;
}

void sortCustomer() {
	vector<int> idList;
	for (Customer* customer : customerList) {
		idList.push_back(customer->getId());
	}
	int comparisons = 0;
	int swaps = 0;
	for (int i = 0; i < idList.size(); i++)
	{
		int low = i;
		for (int k = i + 1; k < idList.size(); k++)
		{
			comparisons++;
			if (idList[k] < idList[low])
			{
				low = k;
			}
		}
		if (i != low)
		{
			swaps++;
			int temp = idList[i];
			idList[i] = idList[low];
			idList[low] = temp;
		}
	}
	vector<Customer*> sortedCustomer;
	for (int id : idList) {
		for (Customer* customer : customerList) {
			if (id == customer->getId()) {
				sortedCustomer.push_back(customer);
			}
		}
	}
	customerList = sortedCustomer;
	cout << "Option selected: s" << endl << endl;
	cout << "------sorting starting------" << endl;
	cout << "Number of comparisons: " << comparisons << endl;
	cout << "Number of swaps      : " << swaps << endl;
	cout << "-------sorting ending-------" << endl;
	cout << "Sort Testing" << endl;
	cout << "Sort Testing First[0]   ";
	sortedCustomer[0]->printDetail();
	cout << "Sort Testing Last       ";
	sortedCustomer.back()->printDetail();
	cout << "Sort Testing 9th[9]     ";
	sortedCustomer[9]->printDetail();
	if (sortedCustomer.size() > 499) {
		cout << "Sort Testing 499th[499] ";
		sortedCustomer[499]->printDetail();
	}
	cout << endl << endl;
}

void showMenu()
{
	char choice;
	bool menuOn = true;
	while (menuOn != false) {
		cout << "Assign1 2022 Menu" << endl;
		cout << "-------------------" << endl;
		cout << "E(xit)       - Exit" << endl;
		cout << "R(ead)       - Read File" << endl;
		cout << "C(heck)      - Check File details" << endl;
		cout << "L(ist)       - List in short form for checking" << endl;
		cout << "F(raud)      - Search for sales fraud" << endl;
		cout << "A(udit)      - Audit for rubish entries in previous sales people" << endl;
		cout << "D(uplicates) - Find and list duplicate id numbers" << endl;
		cout << "S(ort)       - Sort on account number" << endl;
		cout << "Select option: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 'e':
			cout << "End of Program."<<endl;
			menuOn = false;
			break;
		case 'r':
			optionRead();
			break;
		case 'c':
			fileCheck();
			break;
		case 'l':
			listShortForm();
			break;
		case'f':
			getFraudCustomer();
			break;
		case 'a':
			findAudit();
			break;
		case 'd':
			findDuplicatedId();
			break;
		case 's':
			sortCustomer();
			break;
		default:
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			break;
		}

	}

}

int main() {
	doFilenames();
	showMenu();
	return 0;
}