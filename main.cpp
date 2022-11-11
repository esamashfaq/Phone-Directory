#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include "phonebook.h"

using namespace std;

using namespace register1;

int main() {
	phoneBook pub;
	pvt pt;
	int choice, pw;

	while(1) {
		cout<<"\n\n*****Digital Town Phone Directory *****\n\n";
		cout<<"Choose the operation you want to perform:\n";
		cout<<"1. Public File\n";
		cout<<"2. Private File\n";
		cout<<"3. Emergency Contact No\n";
		cout<<"Any other key to exit.\n";
		
		cout<<"\nEnter your choice: ";
		cin>>choice;
		
		switch(choice) {
			
			case 1 :
				while(1) {
					char nm[20];
					cout<<"\n\n\n*****Public Town Phone Directory *****\n\n";
					cout<<"Choose the operation you want to perform:\n";
					cout<<"1. Add New Record\n";
					cout<<"2. Display All Records\n";
					cout<<"3. Search Telephone No.\n";
					cout<<"4. Search Person by Name\n";
					cout<<"5. Update Details\n";
					cout<<"6. Delete a record \n";
					cout<<"7. Exit\n\n";
					cout<<"Enter your choice : ";
					cin>>choice;
					
					switch(choice) {
						case 1 :
							pub.newrecord();
							break;

						case 2 :
							pub.display();
							break;

						case 3 :
							pub.searchpname();
							break;

						case 4 :
							cout<<"\n\nEnter Name : ";
							cin>>nm;
							pub.display(nm);
							break;

						case 5 :
							pub.updaterec();
							break;

						case 6:
							pub.deleterec();
							break;

						case 7:
							exit(1);

						default:
							cout<<"Invalid Option!!"<<endl;

					}

				}


			case 2 :
				cout<<"Enter the password: ";
				cin>>pw;
				
				if (pw==1234) {
					while(1) {
						char nm[20];
						cout<<"\n\n\n*****Private Town Phone Directory *****\n";
						cout<<"Choose the operation you want to perform:\n";
						cout<<"1. Add New Record\n";
						cout<<"2. Display All Records\n";
						cout<<"3. Search Telephone No.\n";
						cout<<"4. Search Person by Name\n";
						cout<<"5. Update Details\n";
						cout<<"6. Delete a record \n";
						cout<<"7. Exit\n\n";
						cout<<"Enter your choice : ";
						cin>>choice;
						
						switch(choice) {
							case 1 :
								pt.newrecord();
								break;

							case 2 :
								pt.display();
								break;

							case 3 :
								pt.searchpname();
								break;

							case 4 :
								cout<<"\n\nEnter Name : ";
								cin>>nm;
								pt.display(nm);
								break;

							case 5 :
								pt.updaterec();
								break;

							case 6:
								pt.deleterec();
								break;

							case 7:
								exit(1);

							default:
								cout<<"Invalid Option!!"<<endl;

						}

					}
				}

				else {
					cout<<"\nWrong Password!!! Locking out...";
					exit(1);
				}


			case 3:	
				pub.showemergency();
				exit(1);

			default:
				cout<<"Invalid Option!!"<<endl;

		}

	}
}
