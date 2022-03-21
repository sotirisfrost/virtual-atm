#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "ACCOUNT.h"
using namespace std;
//default ClientData constructor
ACCOUNT::ACCOUNT(int accountNumberValue,string nameValue,double balanceValue,double limitValue){
	setAccountNumber(accountNumberValue);
	setName(nameValue);
	setBalance(balanceValue);
	setLimit(limitValue);
}
//get account-number value
int ACCOUNT::getAccountNumber() const{
	return accountNumber;
}
//set account-number value
void ACCOUNT::setAccountNumber(int accountNumberValue){
	accountNumber=accountNumberValue;
}
//get Name value
string ACCOUNT::getName() const{
	return name;
}
//set Name value
void ACCOUNT::setName(string nameString){
	//copy at most 50 characters from string to firstName
	const char *nameValue=nameString.data();
	int length=nameString.size();
	length=(length<25 ? length:24);
	strncpy(name,nameValue,length);
	name[length]='\0';
}
//get balance value
double ACCOUNT::getBalance() const{
	return balance;
}
//set balance value
void ACCOUNT::setBalance(double balanceValue){
	balance=balanceValue;
}
//get limit value
double ACCOUNT::getLimit() const{
	return limit;
}
//set limit value
void ACCOUNT::setLimit(double limitValue){
	limit=limitValue;
}
//enterClient enters a new client
void ACCOUNT::enterClient(){
	int account;
	double amount;
	cout<<"\n\nPlease enter an Account Number (-1 to End): ";
	cin>>account;
	//Ending the program with a negative number
	//If the number is negative the program stops and it prints every registered with function textFile
	if(account<0){
		printRecords("ACCT.dat");
		exit(1);
	}
	else
		check(account);
}

void ACCOUNT::printRecords(const char *fileName){
	ifstream inCreditSystem("ACCT.dat",ios::in);
	ACCOUNT client;
	if(!inCreditSystem){
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
	cout<<left<<setw(25)<<"NAME"<<setw(20)<<"ACCOUNT NUMBER"<<setw(13)<<
	"BALANCE"<<setw(16)<<"CREDIT LIMIT"<<endl;
	cout<<"----------------------------------------------------------------------"<<endl;
	inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
	while(inCreditSystem && !inCreditSystem.eof()){
		if(client.getAccountNumber()!=0)
			outputLine(cout,client);
			inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
	}
}

void ACCOUNT::outputLine(ostream &output,const ACCOUNT &record){
	output<<left<<setw(25)<<record.getName()
	<<setw(17)<<record.getAccountNumber()
	<<setw(10)<<setprecision(2)<<right<<fixed
	<<showpoint<<record.getBalance()
	<<setw(18)<<setprecision(2)<<right<<fixed
	<<showpoint<<record.getLimit()<<endl;
}

bool ACCOUNT::is_file_exist(const char *fileName){
	std::ifstream infile(fileName);
	return infile.good();
}

void ACCOUNT::check(int account){
	bool error=false;
	double amount;
	char fullName[30];
	fstream inCreditSystem("ACCT.dat", ios::in | ios::out | ios::binary);
	ACCOUNT client;
	if(!inCreditSystem){
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
	inCreditSystem.seekp(((account/50)-1)*sizeof(ACCOUNT));
	inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
	cout<<"Enter Amount of Purchase(<=0): ";
	cin>>amount;
	while(amount<0){
		cout<<"Please enter a valid amount of purchase. You can't use a negative number."<<endl;
		cout<<"Enter Amount of Purchase: ";
		cin>>amount;
	}
	if(account==client.getAccountNumber()){
	cout<<"Please Enter client's Name: ";
	cin.ignore();
	cin.getline(fullName,25);
	string nameCheck(fullName);
		if (client.getName().compare(nameCheck)) error=true;
			if(error){
				cout<<"ACCOUNT NUMBER AND CUSTOMER NAME DO NOT MATCH - RE-ENTER DATA\n\n";
				client.enterClient();
			}
			else{
				client.moneyTransfer(account,amount,client.getLimit());
				client.enterClient();
			}
	}
	else{
		client.newClient(account,amount);
		client.enterClient();
	}
}

void ACCOUNT::newClient(int account,double amount){
	char answer;
	char nameArray[25];
	double limit;
	fstream inCreditSystem("ACCT.dat", ios::in | ios::out | ios::binary);
	ACCOUNT client;
	if(!inCreditSystem){
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
	cout<<"Is this a new Account Number? (Y/N): ";
	cin>>answer;
	//Checking that the answer is only Y or N
	while((answer!='Y')&&(answer!='N')){
		cout<<"Please enter a valid answer (Y/N): ";
		cin>>answer;
	}
	if(answer=='N'){
		//If the answer is N then you enter another client
		cout<<endl<<"INVALID ACCOUNT NUMBER - RE-ENTER DATA"<<endl;
		client.enterClient();
	}
	else{
		client.setAccountNumber(account);
		//Enter client's name
		cout<<"Please Enter client's Name: ";
		cin.ignore();
		cin.getline(nameArray, 25);
		string name(nameArray);
		client.setName(name);
		//Enter client's credit limit
		cout<<"Please Enter client's Credit Limit: ";
		cin>>limit;
		while(limit<=0){
			cout<<"Please enter a valid Credit Limit. You can't use a negative number."<<endl;
			cout<<"Please Enter client's Credit Limit: ";
			cin>>limit;
		}
		client.setLimit(limit);
		inCreditSystem.seekp(((account/50)-1)* sizeof(ACCOUNT));
		inCreditSystem.write(reinterpret_cast<const char*>(&client),sizeof(ACCOUNT));
		inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
		client.moneyTransfer(account,amount,limit);
	}
}

void ACCOUNT::moneyTransfer(int account, double amount, double limit){
	double over,purchase;
	fstream inCreditSystem("ACCT.dat", ios::in | ios::out | ios::binary);
	ACCOUNT client, blankClient;
	if(!inCreditSystem){
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
	inCreditSystem.seekp(((account/50)-1)*sizeof(ACCOUNT));
	inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
	purchase=(client.getBalance()+amount);
	if(purchase<=client.getLimit()){
		client.setBalance(client.getBalance()+amount);
		inCreditSystem.seekp(((account/50)-1)*sizeof(ACCOUNT));
		inCreditSystem.write(reinterpret_cast<const char*>(&client),sizeof(ACCOUNT));
		cout<<"\nDear "<<client.getName()<<","<<endl;
		cout<<"Thank you for your bussiness!\n"<<endl;
	}
	else{
		over=(client.getBalance()+amount)-client.getLimit();
		cout<<"\nDear "<<client.getName()<<","<<endl;
		cout<<"We CANNOT authorise this purchase at this time as it would put you $";
		cout<<over<<"\nover your credit limit\n"<<endl;
		inCreditSystem.read(reinterpret_cast<char*>(&client),sizeof(ACCOUNT));
	}
}
