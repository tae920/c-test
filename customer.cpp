#include <iostream>
#include <string>
#include "customer.hpp" 

using namespace std;

Customer::Customer(int customerId, string honoric, string fName, string lName,
    string cName, string cSalesman, float purchaseValue, string preSalesman, float comValue)
{
    this->customerId = customerId;
    this->honoric = honoric;
    this->fName = fName;
    this->lName = lName;
    this->cName = cName;
    this->cSalesman = cSalesman;
    this->purchaseValue = purchaseValue;
    this->preSalesman = preSalesman;
    this->comValue = comValue;
}

Customer::~Customer() {} 

float Customer::getPurchaseValue() {
    return purchaseValue;
}
float Customer::getComValue() {
    return comValue;
}
bool Customer::checkFraud() {
    float reasonValue = purchaseValue * 0.11f;
    if (reasonValue < comValue) {
        cout << "Fraudulent Account : " << customerId << " " << honoric << " " << fName << " " << lName << " " << cName << endl;
        cout << "Acount Value is    : " << purchaseValue << endl;
        cout << "Comission Value is : " << comValue << endl;
        cout << "Reasonable Value is: " << reasonValue << endl << endl;
        return true;
    }
    return false;
}

string Customer::getPreSalesman() {
    return preSalesman;
}

void Customer::printDetail() {
    cout << customerId << " " << honoric << " " << fName << " " << lName << " " << cName << endl;
}

int Customer::getId() {
    return customerId;
}

