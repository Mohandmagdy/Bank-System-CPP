#ifndef BankAccount_H

using namespace std;

class BankAccount{
double balance;
public:
    string accountID="User";
    string Account_Type;
    BankAccount();
    BankAccount(double o);
    void set_balance(double t);
    double get_balance();
    virtual int withdraw(double r);
    virtual int deposit(double t);
};

class SavingsBank : public BankAccount{
public:
    static double minimum_balance;
    SavingsBank();
    SavingsBank(double t);
    int withdraw(double t);
    int deposit(double o);
};

class Client{
string name;
string address;
string phone_number;
public:
    static int cnt;
	Client(){};
    map <string,string>sub;
    BankAccount *user_balance;
    Client(string n, string a, string p);
    void set_bal(double y);
    double get_bal();
    void new_user();
    string get_name();
    string get_address();
    string get_phone();
    string print();
};


class BankApplication {
int choice;
static string file_content;
public:
    static Client *client_info;
    static BankAccount *user_balance_acc;
    static map<string,Client>data;
    static void write();
    static void read();
    BankApplication();
    void list_data();
    bool search_(string g , int choice);
    int select_choice();
    bool add_client(string name,string address , string phone);
};


#endif // BankAccount_H
