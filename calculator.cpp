#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <sstream>
#include <conio.h>

using namespace std;

#define DEFDIR "C:\\Users\\hyole\\Downloads\\MandatoryTests\\"

map<string, string>memories;
vector<char>txtContents;
string dir = DEFDIR;
string filename;
string fullFileName;

bool fileExists(const string& fname)
{
	FILE* file;
	if (0 == fopen_s(&file, fname.c_str(), "r"))
	{
		fclose(file);
		return true;
	}
	else
	{
		return false;
	}
}

bool getFileName()
{
	cout << "enter filename:";
	cin >> filename;
	cout << endl;
	fullFileName = dir + filename;
	cout << "Full FileName is:'" << fullFileName << "'" << endl;
	if (fileExists(fullFileName))
		return true;
	cout << "** ERROR ** File '" << fullFileName << "'Does not exist";
	return false;
}

void do_S()
{
	cout << "enter directory:";
	cin >> dir;
	cout << endl;
	cout << "\nCurrent Directory :" << dir << endl;
}
void do_R()
{
	cout << "\nCurrent Directory :" << dir << endl;
	if (!getFileName()) return;
}

bool readFile() {
	ifstream myFile(fullFileName);

	string str;
	txtContents.push_back(' ');
	int i = 0;
	while (getline(myFile, str))
	{
		if (str[0] != NULL)
		{
			for (int i = 0; i < (int)str.size(); i++)
			{

				char c = str[i];
				if (c == '\t' || c == '\n' || c == '\r' || c == ' ')continue;
				txtContents.push_back(c);

			}
		}
	}
	return true;
}

double calculate(double total, string newNum, char sign)
{
	switch (sign)
	{
	case '+':
		total += stod(newNum);
		break;
	case '-':
		total -= stod(newNum);
		break;
	case '*':
		total *= stod(newNum);
		break;
	case '/':
		if (newNum == "0")
		{
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << "error" << "|" << endl;
			cout << "+----------+" << endl;
			return 0;
		}
		total /= stod(newNum);
		break;
	case ' ':
		if (newNum == "")
		{
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << "no input" << "|" << endl;
			cout << "+----------+" << endl;
			return 0;
		}
		total = stod(newNum);
		break;
	case '=':
		break;
	}
	cout << "+----------+" << endl;
	cout << "|" << setw(10) << total << "|" << endl;
	cout << "+----------+" << endl;
	return total;
}
void keyStrokeCalculator()
{
	cout << fixed;
	cout.precision(2);
	cout << "+----------+" << endl;
	cout << "|          |" << endl;
	cout << "+----------+" << endl;
	char userInput = ' ';
	string newNum, temp;
	char sign = ' ', signTemp = ' ';
	double total = 0;
	int countDot = 0;
	string memName;
	int countR = 0;
	while (userInput != ';')
	{
		userInput = _getch();
		if (userInput == '\t' || userInput == '\n' || userInput == '\r' || userInput == ' ')continue;
		else if (isdigit(userInput) || userInput == '.')
		{
			if (userInput == '.')countDot++;
			newNum += userInput;
			if (countDot > 1) {
				cout << "You typed two dots in the number" << endl;
				cout << "Type the number again" << endl;
				newNum = "";
				countDot = 0;
			}
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == 'm') {
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			char memNum = _getch();
			memName = userInput + memNum;
			memories[memName] = newNum;
			cout << memNum << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			memName = "";
		}
		else if (userInput == 'r') {
			if (countR < 1) {
				sign = ' ';
				signTemp = ' ';
			}
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			char callMem = _getch();
			memName = 'm' + callMem;
			newNum = memories[memName];
			cout << callMem << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			memName = "";
			countR++;
		}
		else if (userInput == 's') {
			cout << userInput << endl << endl;
			double changeWord = stod(newNum);
			changeWord = sqrt(changeWord);
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << changeWord << "|" << endl;
			cout << "+----------+" << endl;
			newNum = to_string(changeWord);

		}
		else if (userInput == '!') {
			if (newNum[0] == '-') {
				newNum.erase(0, 1);
			}
			else if (isdigit(newNum[0])) {
				newNum.insert(0, "-");
			}
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << stod(newNum) << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == 'c')
		{
			total = 0;
			sign = ' ';
			signTemp = ' ';
			newNum = "";
			memories.clear();
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << " " << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == 'k')
		{
			signTemp = ',';
			newNum = "";
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << " " << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == '+' || userInput == '-' || userInput == '*' || userInput == '/' || userInput == '=')
		{
			countDot = 0;
			temp = newNum;
			signTemp = userInput;
			cout << userInput << endl << endl;
			total = calculate(total, newNum, sign);
			newNum = "";
		}
		sign = signTemp;
	}

}

void fileReadCalculator()
{
	cout << fixed;
	cout.precision(2);
	cout << "+----------+" << endl;
	cout << "|          |" << endl;
	cout << "+----------+" << endl;
	char userInput = ' ';
	string newNum, temp;
	int  i = 1;
	char sign = ' ', signTemp = ' ';
	double total = 0;
	int countDot = 0;
	string memName;
	int countR = 0;
	while (i < txtContents.size())
	{
		userInput = txtContents[i];
		if (userInput == 'm' || txtContents[i - 1] == 'm') {
			cout << userInput << endl << endl;
			memName += userInput;
			memories[memName] = newNum;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			memName = "";
		}
		else if (userInput == 'r' || txtContents[i - 1] == 'r') {
			if (countR < 1) {
				sign = ' ';
				signTemp = ' ';
			}
			cout << userInput << endl << endl;
			if (userInput == 'r')userInput == 'm';
			memName += userInput;
			newNum = memories[memName];
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
			memName = "";
			countR++;
		}
		else if (isdigit(userInput) || userInput == '.')
		{
			if (userInput == '.')countDot++;
			newNum += userInput;
			if (countDot > 1) {
				cout << "You typed two dots in the number" << endl;
				cout << "Type the number again" << endl;
				newNum = "";
				countDot = 0;
			}
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << newNum << "|" << endl;
			cout << "+----------+" << endl;
		}

		else if (userInput == 's') {
			cout << userInput << endl << endl;
			double changeWord = stod(newNum);
			changeWord = sqrt(changeWord);
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << changeWord << "|" << endl;
			cout << "+----------+" << endl;
			newNum = to_string(changeWord);

		}
		else if (userInput == '!') {
			if (newNum[0] == '-') {
				newNum.erase(0, 1);
			}
			else if (isdigit(newNum[0])) {
				newNum.insert(0, "-");
			}
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << stod(newNum) << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == 'c')
		{
			total = 0;
			sign = ' ';
			signTemp = ' ';
			newNum = "";
			memories.clear();
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << " " << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == 'k')
		{
			signTemp = ',';
			newNum = "";
			cout << userInput << endl << endl;
			cout << "+----------+" << endl;
			cout << "|" << setw(10) << " " << "|" << endl;
			cout << "+----------+" << endl;
		}
		else if (userInput == '+' || userInput == '-' || userInput == '*' || userInput == '/' || userInput == '=')
		{
			countDot = 0;
			temp = newNum;
			signTemp = userInput;
			cout << userInput << endl << endl;
			total = calculate(total, newNum, sign);
			newNum = "";
		}
		sign = signTemp;
		i++;
	}
}

void showMenu()
{

	char choice;
	bool menuOn = true;
	while (menuOn != false) {
		txtContents.clear();
		memories.clear();
		cout << "Assign2 2022 Menu" << endl;
		cout << "-------------------" << endl;
		cout << "e  - Exit" << endl;
		cout << "s  - Set Directory" << endl;
		cout << "4  - Run 4 function calculator from keyboard input" << endl;
		cout << "r  - Read single test file and run" << endl;
		cout << "d  - Distinction/HD level Read a test file and run test" << endl;
		cout << "Select option: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 'e':
			cout << "End of Program." << endl;
			menuOn = false;
			break;
		case 's':
			do_S();
			break;
		case '4':
			keyStrokeCalculator();
			break;
		case 'r':
			do_R();
			readFile();
			fileReadCalculator();
			break;
		case 'd':
			do_R();
			readFile();
			fileReadCalculator();
			break;
		default:
			cout << "Not a Valid Choice. \n";
			cout << "Choose again.\n";
			break;
		}

	}

}

int main() {
	showMenu();
	return 0;
}