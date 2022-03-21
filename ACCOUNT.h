#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <cstring>
using namespace std;
class ACCOUNT{
	public:
		//default ClientData constructor
		ACCOUNT(int=0,string="",double=0.00,double=0.00);
		//accessor functions for accountNumber
		void setAccountNumber(int);
		int getAccountNumber() const;
		//accessor functions for Name
		void setName(string);
		string getName() const;
		//accessor functions for balance
		void setBalance(double);
		double getBalance() const;
		//accessor functions for limit
		void setLimit(double);
		double getLimit() const;
		//function to check if the file exists
		bool is_file_exist(const char *);
		//Functions
		void enterClient();
		void check(int);
		void moneyTransfer(int, double, double);
		void newClient(int, double);
		void outputLine(ostream&, const ACCOUNT &);
		void printRecords(const char *);
	private:
		int accountNumber;
		char name[25];
		double balance;
		double limit;
};
#endif
