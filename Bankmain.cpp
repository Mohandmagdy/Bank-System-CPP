#include <bits/stdc++.h>
#include "BankHeader.h"
#include<string>
#include<fstream>
#include <sstream>

int main() {
	int cont = 1;
	while (cont) {
		BankApplication p;
		p.read();
		int choice = p.select_choice();
		if (choice == 1) {
			cout << "Please enter your name : ";
			string name, address, phone;
			cin.ignore();

			getline(cin, name);
			cout << "Please enter your address : ";
			getline(cin, address);
			cout << "Please enter your phone : ";
			cin >> phone;

			p.add_client(name, address, phone);
		} else if (choice == 2) {
			p.list_data();
		} else if (choice == 3 || choice == 4) {
			string id;
			cout << "Please enter your account ID : ";
			cin >> id;
			cout << endl;
			if (!p.search_(id, choice))
				cout << "This ID doesn't exist\n";
		}
		p.write();
		if (choice != 1) {
			cout << "Do you want to use any more options yes(1) No(0)?!\n";
			int choose;
			cin >> choose;
			cont = choose;
		} else cont = 0;
	}
}
