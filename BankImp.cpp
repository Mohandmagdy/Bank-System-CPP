#include <bits/stdc++.h>
#include "BankHeader.h"
#include<string>
#include<fstream>
#include <sstream>
using namespace std;
BankAccount::BankAccount(){Account_Type="Basic";}
BankAccount::BankAccount(double o){
  balance = o;
  cout<<"Your Account has been created successfully\n";
  Account_Type="Basic";
}

void BankAccount::set_balance(double t){balance=t;}

double BankAccount::get_balance(){
    return balance;
}



int BankAccount::withdraw(double r){
    if(balance>=r){
        balance-=r;
        cout << " Current Balance = " << balance << endl;
    }
    else
        cout << " You don't have enough money!.\n";
};



int BankAccount::deposit(double t){
    balance+=t;
    cout << " Current Balance = " << balance << endl;
}


Client::Client(string nam, string adr, string phone):name(nam), address(adr), phone_number(phone){
    cnt++;
}


void Client::set_bal(double y){
    (*user_balance).set_balance(y);
}


double Client::get_bal(){
    return (*user_balance).get_balance();
}


void Client::new_user() {
	cout << "Please choose which account type you want ? Basic(1) saving(2) : ";
	int choice;
	cin >> choice;
	double y;
	if (choice == 1) {
		cout << "Please enter your starting balance: ";
		cin >> y;
		user_balance = new BankAccount(y);
	} else if (choice == 2) {
		double money;
		cout << "Please enter your starting balance with at least " << SavingsBank::minimum_balance;
		cin >> money;
		cout << endl;
		user_balance = new SavingsBank(money);
	}
}

string Client::get_name(){return name;}

string Client::get_address(){return address;}

string Client::get_phone(){return phone_number;}

string Client::print(){
    cout<<" Your name is : "<<name<<" & Address is : "<<address<<" & Phone Number is : "<<phone_number<<endl;
    cout << (*user_balance).get_balance()<<endl;
}

// overWriting File with new data of map filled with pointers to created Client Objects
void BankApplication::write() {
	ofstream myfile;
	myfile.open("C:/Users/mohan/CLionProjects/Accounts.txt", ios::trunc);
	for (auto obj : data) {
		user_balance_acc = obj.second.user_balance;
		myfile << "ID: " << obj.first << endl;
		myfile << "Account_Type: " << user_balance_acc->Account_Type << endl;
		myfile << "User_name: " << obj.second.get_name() << endl;
		myfile << "address: " << obj.second.get_address() << endl;
		myfile << "phone_no.: " << obj.second.get_phone() << endl;
		myfile << "Balance: " << user_balance_acc->get_balance() << endl;
	}
	myfile.close();
}

void BankApplication::read() {
	fstream myfile("C:/Users/mohan/CLionProjects/Accounts.txt");
	string s;
	vector<string> t;
	cout << endl;
	int cnt = 0;
	if (!myfile.eof()) {
		while (getline(myfile, s)) {
			cnt++;
			stringstream m1(s);
			string t1;
			while (m1 >> t1) {
				t.push_back(t1);
				file_content += (t1 + " ");
			}
			file_content += "\n";
			if (cnt % 6 == 0) {
				file_content += "--------------\n";
				client_info = new Client(t[5], t[7], t[9]);
				if (t[3] == "Special") {
					(*client_info).user_balance = new SavingsBank();
				} else {
					(*client_info).user_balance = new BankAccount();
				}

				user_balance_acc = (*client_info).user_balance;
				(*user_balance_acc).set_balance(stod(t[t.size() - 1]));
				(*user_balance_acc).accountID += to_string(cnt / 5);
				(*user_balance_acc).Account_Type = t[3];
				data.insert({user_balance_acc->accountID, (*client_info)});
				t.clear();
			}
		};
	}
	myfile.close();
}

BankApplication::BankApplication(){
    cout << "Please enter a choice\nCreate a new account(1)\nList clients and accounts(2)\nWithdraw money(3)\nDeposit money(4)\n";
}

void BankApplication::list_data(){
	cout << endl << file_content << endl;
}

bool BankApplication::search_(string g , int choice) {
	if (data.find(g) != data.end()) {
		double amount;
		if (choice == 3) {
			cout << "Enter Amount to withdraw : ";
			cin >> amount;
			(*user_balance_acc).withdraw(amount);
		} else if (choice == 4) {
			cout << "Enter Amount to deposit: ";
			cin >> amount;
			(*user_balance_acc).deposit(amount);
		}
		return true;
	}
	return false;
}

int BankApplication::select_choice(){
    cout << "Please enter your Choice : ";
    int cho;
    cin >> cho;
    return cho;
}

bool BankApplication::add_client(string name,string address , string phone) {
	client_info = new Client(name, address, phone);
	(*client_info).new_user();
	user_balance_acc = (*client_info).user_balance;
	(*user_balance_acc).accountID += to_string((*client_info).cnt);
	data[user_balance_acc->accountID] = *client_info;
	return true;
}

SavingsBank::SavingsBank(){Account_Type="Special";};
SavingsBank::SavingsBank(double t):BankAccount{t}{
   Account_Type="Special";
}

int SavingsBank::withdraw(double t){
    double u = get_balance();
   if(t <= u){
        double n = get_balance()-t;
            set_balance(n);
     }
   else
	   cout << "You don't have enough money!.\n";
}

int SavingsBank :: deposit(double o){
     if(o >= 100)
        set_balance(get_balance()+o);
     else
        cout << " You cannot deposit less than 100\n";
}



// static members initializations

int Client::cnt=0;

string BankApplication::file_content="";

map <string,Client> BankApplication::data;

Client* BankApplication::client_info=new Client();

double SavingsBank::minimum_balance=200;

BankAccount* BankApplication::user_balance_acc=new BankAccount();



