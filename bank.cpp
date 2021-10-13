#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

class Account{
public:
	int accNo;
	string accName;
	char accType;
	int accMoney;
	string accPin;

	stack<pair<string,int>> accTransaction;
};

// *********************************************
// Password Masking
// *********************************************
string inpwd(){

	string pass = "";

	while(1){

		char inpkey;
		inpkey = getch();

		if(inpkey == 13){
			return pass;
		}

		else if(inpkey == 8 && pass.size() == 0){
			continue;
		}

		else if(inpkey == 8 && pass.size() != 0){
			cout<<"\b \b";
			pass.pop_back();
			continue;
		}

		pass.push_back(inpkey);
		cout<<"*";

	}
}

/******************************
Generating Account No
*****************************/
__int64 unqno() {
    static auto rng = std::default_random_engine{ std::random_device{}() };
    constexpr auto digits = 10;
    static auto dist = std::uniform_int_distribution<__int64>{ 
        static_cast<__int64>(pow(10, digits)), 
        static_cast<__int64>(pow(10, digits+1) - 1) };
    return dist(rng);
}

void create_account(vector<Account> &AccountList){

	cout<<"--------------------------------------------"<<endl;
	cout<<"\n Enter name of Customer :";
	string name;
	getline(cin >> ws,name);

	string p1,p2;

	while(1){

		cout<<"\nEnter the 4 digit pin : ";
		p1 = inpwd();

		cout<<endl;
		cout<<"\nConfirm the 4 digit pin again : ";
		p2 = inpwd();

		cout<<endl;
		if(p1 != p2){
			cout<<"Pin do not match, enter again"<<endl;
		}

		else
			break;
	}

	int no = unqno();

	char type;
	cout<<"\n Enter the type of account (S - Saving / C - Current) : ";
	cin >> type;

	int amt;

	while(1){
		cout<<"\n Enter the initial deposit amount (>=500 for Saving / >= 1000 for Current) : ";
		cin >> amt;

		if(type == 'S' && amt <500){
			cout<<"Saving account needs to start with atleast Rs.500"<<endl;
			continue;
		}

		else if(type == 'C' && amt<1000){
			cout<<"Current account needs to start with atleast Rs.1000"<<endl;
			continue;
		}

		else break;
	}

	cout<<"*******************************************"<<endl;
	cout<<"\n Your account number is : "<<no<<endl;
	cout<<"\n Welcome to XYZ Bank"<<endl;
	cout<<"*******************************************"<<endl;

	Account tempAcc;
	tempAcc.accNo = no;
	tempAcc.accName = name;
	tempAcc.accType = type;
	tempAcc.accMoney = amt;
	tempAcc.accPin = p1;

	AccountList.push_back(tempAcc);

}


// ****************************
// Displaying AccountList
// ****************************
void display_account(vector<Account> &AccountList){

	cout<<endl;

	cout<<"Enter name of the Customer : ";
	string tempName;
	getline(cin >> ws,tempName);

	bool key = false;

	for(unsigned int i=0; i<AccountList.size(); i++){

		Account curr = AccountList[i];

		if(curr.accName == tempName){
			key = true;

			cout<<"********************************************"<<endl;
			cout<<"Name of Customer : "<<curr.accName<<endl;
			cout<<"Account number : "<<curr.accNo<<endl;
			cout<<"Account type : ";
			if(curr.accType == 'S')
				cout<<"Saving"<<endl;
			else
				cout<<"Current"<<endl;

			cout<<"Amount : "<<curr.accMoney<<endl;
			cout<<"*********************************************"<<endl;
		}
	}

	if(!key)
		cout<<"*********NO ACCOUNT FOUND*********"<<endl;
}



// ***************************************
// Deposit Money
// ***************************************
void deposit(vector<Account> &AccountList){

	cout<<"-----------------------------------"<<endl;
	cout<<"Enter name of the Customer : ";
	string tempName;
	getline(cin >> ws,tempName);

	bool key = false;

	for(unsigned int i=0; i<AccountList.size(); i++){

		Account& curr = AccountList[i];

		if(curr.accName == tempName){
			key = true;

			cout<<"Enter the money to be deposited : ";
			int x;
			cin >> x;

			curr.accMoney = curr.accMoney + x;

			cout<<"Updated money in account = "<<curr.accMoney<<endl;

			cout<<"--------------------------------------"<<endl;

			curr.accTransaction.push({"Deposit",x});
		}
	}

	if(!key)
		cout<<"*********NO ACCOUNT FOUND*********"<<endl;

}


// ****************************************
// Withdraw
// ****************************************
void withdraw(vector<Account>& AccountList){

	cout<<"-----------------------------------"<<endl;
	cout<<"Enter name of the Customer : ";
	string tempName;
	getline(cin >> ws,tempName);

	bool key = false;

	for(unsigned int i=0; i<AccountList.size(); i++){

		Account& curr = AccountList[i];

		if(curr.accName == tempName){
			key = true;

			cout<<"Enter the money to be withdrawn : ";
			int x;
			cin >> x;

			cout<<"Please enter your 4 digit Pin : ";
			string pin = inpwd();

			cout<<endl;

			if(pin == curr.accPin){

				if(x > curr.accMoney){
					cout<<"Account Balance is less than the money to be Withdrawn"<<endl;
					cout<<"-------------------------------------------"<<endl;
				}

				else{
					curr.accMoney -= x;

					cout<<"Updated Balance is : "<<curr.accMoney<<endl;

					curr.accTransaction.push({"Withdraw",x});

					cout<<"-------------------------------------------"<<endl;
				}
			}

			else{
				cout<<"Wrong Pin Entered";
				cout<<"-------------------------------------------"<<endl;
			}
		}
	}

	if(!key)
		cout<<"*********NO ACCOUNT FOUND*********"<<endl;
}





// *****************************************
// Last 5 transaction 
// *****************************************
void last_transaction(vector<Account> &AccountList){

	cout<<"-----------------------------------"<<endl;
	cout<<"Enter name of the Customer : ";
	string tempName;
	getline(cin >> ws,tempName);

	bool key = false;

	for(unsigned int i=0; i<AccountList.size(); i++){

		Account& curr = AccountList[i];

		if(curr.accName == tempName){
			key = true;

			cout<<"---------------------------------------------------------"<<endl;
			cout<<"Transaction Type (Withdraw/Deposit)                Amount"<<endl;
			cout<<"---------------------------------------------------------"<<endl;

			int transacCount =0;

			while(!curr.accTransaction.empty()){

				pair<string,int> temp = curr.accTransaction.top();

				cout<<temp.first<<"                                             "<<temp.second<<endl;

				transacCount++;
				if(transacCount==5)
					break;

				curr.accTransaction.pop();

			}
		}
	}

	if(!key)
		cout<<"*********NO ACCOUNT FOUND*********"<<endl;

}




int main(){

	vector<Account> AccountList;

	cout<<"\n\n\t Welcome to XYZ Bank Management System"<<endl;

	while(1){
		
		cout<<"\n 1 - Create New Account"<<endl;
		cout<<"\n 2 - Deposit Amount"<<endl;
		cout<<"\n 3 - Withdraw Amount"<<endl;
		cout<<"\n 4 - View Account Details / Balance Enquiry"<<endl;
		cout<<"\n 5 - View Last 5 Transactions"<<endl;
		cout<<"\n 6 - EXIT";

		int menuInp;
		cout<<"\n";
		cin >> menuInp;

		if(menuInp == 1){
			create_account(AccountList);
		}

		else if(menuInp == 2){
			deposit(AccountList);
		}

		else if(menuInp == 3){
			withdraw(AccountList);
		}

		else if(menuInp == 4){
			display_account(AccountList);
		}

		else if(menuInp == 5){
			last_transaction(AccountList);
		}

		else
			break;

	}



}