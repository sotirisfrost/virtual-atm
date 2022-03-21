#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstring>
#include "ACCOUNT.h"
using namespace std;
int main(){
	ACCOUNT client;
	bool checkFile=client.is_file_exist("ACCT.dat");
	if(checkFile==false){
		ofstream outCreditSystem("ACCT.dat", ios::binary);
		ACCOUNT blankClient;
		for(int i=0;i<200;i++)
			outCreditSystem.write(reinterpret_cast<const char*>(&blankClient),sizeof(ACCOUNT));
	}
	ifstream inCreditSystem("ACCT.dat", ios::in | ios::out | ios::binary);
	if(!inCreditSystem){
		cerr<<"File could not be opened!"<<endl;
		exit(1);
	}
	cout<<"----------------"<<endl;
	cout<<"On-line Shopping"<<endl;
	cout<<"----------------\n"<<endl;
	cout <<"----------------"<<endl;
	cout<<"Existing Records"<<endl;
	cout <<"----------------\n"<<endl;
	client.printRecords("ACCT.dat");
	//Starting the process
	client.enterClient();
return 0;
}
