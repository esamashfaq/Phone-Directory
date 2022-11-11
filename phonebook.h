#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>
#include <stdio.h>

using namespace std;

namespace register1 {

	class phoneBook {
			char name[20],phno[11],email[30];
		public:
			void getdata();
			void showdata();
			char *getname() {
				return name;
			}
			char *getphno() {
				return phno;
			}
			char *getemail() {
				return email;
			}
			void update(char *nm,char *telno,char *mail) {
				strcpy(name,nm);
				strcpy(phno,telno);
				strcpy(email,mail);
			}
			void newrecord();
			void display();
			void display(char *nm);
			void searchpname();
			void updaterec();
			void deleterec();
			void showemergency();
	};

	void phoneBook :: getdata() {
		cout<<"\nEnter Name : ";
		cin>>name;
repeat:
		cout<<"Enter Phone No. : ";
		cin>>phno;            //CAN CREATE A FUNCTION THAT CHECKS WHETHER STRING IS DIGIT OR NOT

		for(int i=0; i<strlen(phno); i++) {
			try {
				if(phno[i]<48 || phno[i]>57||strlen(phno)!=10)
					throw phno[i];
			} catch(char a) {
				cout<<"Enter a valid number"<<endl;
				cout<<"Try again"<<endl;
				goto repeat;
			}
		}
		cout<<"Enter E-Mail: ";
		cin>>email;


	}

	void phoneBook :: showdata() {
		cout<<"\n";
		cout<<setw(20)<<name;
		cout<<setw(15)<<phno;
		cout<<setw(30)<<email;

	}

	void phoneBook :: newrecord() {
		int found=0;
		char rrep[11];
		char nmopi[20];
		char eml[30];

		getdata();
		strcpy(nmopi,name);
		strcpy(rrep,phno);
		strcpy(eml,email);
		fstream file;
		file.open("phone.txt", ios::in | ios::app | ios::binary );
		while(file.read((char *) this, sizeof(*this))) {
			if(strcmp(rrep,getphno())==0) {
				found=1;
				break;
			}
		}
		file.clear();
		file.close();
		if(found==1)
			cout<<"\n\n---Contact already exist---\n";

		else {
			file.open("phone.txt", ios::app | ios::binary );
			update(nmopi,rrep,eml);
			file.write((char *) this, sizeof(*this));
			cout<<"Record Added Succesfully!!\n";
			file.close();
		}


	}
	void phoneBook :: display() {
		//Display All Records
		fstream file;
		file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
		file.seekg(0,ios::beg);
		cout<<"\n\nRecords in Phone Book:\n";
		while(file) {
			file.read((char *) this, sizeof(*this));
			if(!file.eof())
				showdata();
		}
		file.clear();
		file.close();
	}

	void phoneBook :: display(char *nm) {             //function overloading
		//Search Tel. no. when person name is known.
		char c, telno[11];
		int cnt,found=0;

		fstream file;
		file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {

			if(strcmp(nm,getname())==0) {
				found=1;
				showdata();
			}
		}
		file.clear();
		if(found==0)
			cout<<"\n\n---Record Not found---\n";
		file.close();

	}

	void phoneBook :: searchpname() {
		//Search name on basis of tel. no
		char c,ch,nm[20],telno[11],ml[30];
		int cnt,found=0;
		cout<<"\n\nEnter Phone No. : ";
		cin>>telno;
		fstream file;
		file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {
			if(strcmp(telno,getphno())==0) {
				found=1;
				showdata();
			}
		}
		file.clear();
		if(found==0)
			cout<<"\n\n---Record Not found---\n";
		file.close();

	}


	void phoneBook :: updaterec() {
		//Update Telephone No.
		int k;
		fstream file;
		file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
		cout<<"Choose the operation you want to perform:\n";
		cout<<"1. to update name."<<endl;
		cout<<"2. to update phone number."<<endl;
		cout<<"3. to update email."<<endl;
		cin>>k;
		if(k==1) {
			char c,ch,nm[20],newnm[15],teleno[15],mail[30];
			int cnt=0,found=0;
			cout<<"\n\nEnter Name : ";
			cin>>nm;
			file.seekg(0,ios::beg);
			while(file.read((char *) this, sizeof(*this))) {
				cnt++;
				if(strcmp(nm,getname())==0) {
					found=1;
					break;
				}
			}
			file.clear();
			if(found==0)
				cout<<"\n\n---Record Not found---\n";
			else {
				strcpy(teleno,phno);
				strcpy(mail,email);
				int location = (cnt-1) * sizeof(*this);
				cin.get(ch);
				if(file.eof())
					file.clear();

				cout<<"Enter New Name: ";
				cin>>newnm;
				file.seekp(location);
				update(newnm,teleno,email);
				file.write((char *) this, sizeof(*this));
				file.flush();
			}
		}

		if(k==2) {
			char c,ch,nm[20],telno[15],newteleno[15],mail[30];
			int cnt=0,found=0;
			cout<<"\n\nEnter Phone number : ";
			cin>>telno;
			file.seekg(0,ios::beg);
			while(file.read((char *) this, sizeof(*this))) {
				cnt++;
				if(strcmp(telno,getphno())==0) {
					found=1;
					break;
				}
			}
			file.clear();
			if(found==0)
				cout<<"\n\n---Record Not found---\n";
			else {
				strcpy(nm,name);
				strcpy(mail,email);
				int location = (cnt-1) * sizeof(*this);
				cin.get(ch);
				if(file.eof())
					file.clear();

				cout<<"Enter New Phone number: ";
				cin>>newteleno;
				file.seekp(location);
				update(nm,newteleno,email);
				file.write((char *) this, sizeof(*this));
				file.flush();
			}
		}

		if(k==3) {
			char c,ch,nm[20],teleno[15],mail[30],newmail[30];
			int cnt=0,found=0;
			cout<<"\n\nEnter E-Mail : ";
			cin>>mail;
			file.seekg(0,ios::beg);
			while(file.read((char *) this, sizeof(*this))) {
				cnt++;
				if(strcmp(mail,getemail())==0) {
					found=1;
					break;
				}
			}
			file.clear();
			if(found==0)
				cout<<"\n\n---Record Not found---\n";
			else {
				strcpy(nm,name);
				strcpy(teleno,phno);
				int location = (cnt-1) * sizeof(*this);
				cin.get(ch);
				if(file.eof())
					file.clear();

				cout<<"Enter New E-Mail: ";
				cin>>newmail;
				file.seekp(location);
				update(nm,teleno,newmail);
				file.write((char *) this, sizeof(*this));
				file.flush();
			}
		}

		file.close();
	}



	void phoneBook :: deleterec() {
		char bb[20],teleno[11];
		cout<<"Enter the name of the record which is to be deleted: ";
		cin>>bb;
		fstream file;
		file.open("phone.txt",  ios::in | ios::binary );
		fstream fout;
		fout.open("tempfile.txt",ios::out | ios::binary);
		int i=0,j=0,found=0;
		file.read((char *) this, sizeof(*this));
		while(!file.eof()) {
			i++;
			if(strcmp(bb,getname())) {
				fout.write((char*)this,sizeof(*this));
				j++;
			}
//        found++
			file.read((char*)this,sizeof(*this));


		}
		fout.close();
		file.close();
		if(i-j<=1) {

			file.close();
			remove("phone.txt");
			rename("tempfile.txt","phone.txt");
			if(j<i)
				cout<<"Record successfully deleted!!"<<endl;


			if(j==i)
				cout<<"Record not found!!"<<endl;

		} else {
			cout<<"\n\nMore than one contact exist with same name.\n"<<endl;
			file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
			file.seekg(0,ios::beg);
			while(file.read((char *) this, sizeof(*this))) {
				if(strcmp(bb,getname())==0) {
					found=1;
					showdata();
					cout<<endl;
				}
			}
			file.clear();
			file.close();
			cout<<"\n\nPlease enter the contact number you want to delete :  "<<endl;
			cin>>teleno;
			//fstream file;
			file.open("phone.txt",  ios::in | ios::binary );
			//    fstream fout;
			fout.open("tempfileph.txt",ios::out | ios::binary);
			//  int i=0,j=0,found=0;
			file.read((char *) this, sizeof(*this));
			i=0;
			j=0;
			while(!file.eof()) {
				i++;
				if(strcmp(teleno,getphno())) {
					fout.write((char*)this,sizeof(*this));
					j++;
				}
				//        found++
				file.read((char*)this,sizeof(*this));
			}
			fout.close();
			file.close();
			remove("phone.txt");
			rename("tempfileph.txt","phone.txt");
			if(j<i)cout<<"\n\nRECORD DELETED\n\n"<<endl;
			else cout<<"Record NOT found!!"<<endl;
		}
	}
	void phoneBook :: showemergency() {
		cout<<"\n\nFOLLOWING ARE THE EMERGENCY NUMBERS:\n\n1. Police - 100\n2. Fire Brigade - 101\n3. Ambulance and Health Services - 102\n4. Women Helpline - 1091\n5. National Emergency Number - 112";
	}
}

class pvt {
		char name[20],phno[11],email[30];
	public:
		void getdata();
		void showdata();
		char *getname() {
			return name;
		}
		char *getphno() {
			return phno;
		}
		char *getemail() {
			return email;
		}
		void update(char *nm,char *telno,char *mail) {
			strcpy(name,nm);
			strcpy(phno,telno);
			strcpy(email,mail);
		}
		void newrecord();
		void display();
		void display(char *nm);
		void searchpname();
		void updaterec();
		void deleterec();
		void showemergency();
};

void pvt :: getdata() {
	cout<<"\nEnter Name : ";
	cin>>name;
repeat:
	cout<<"Enter Phone No. : ";
	cin>>phno;            //CAN CREATE A FUNCTION THAT CHECKS WHETHER STRING IS DIGIT OR NOT

	for(int i=0; i<strlen(phno); i++) {
		try {
			if(phno[i]<48 || phno[i]>57||strlen(phno)!=10)
				throw phno[i];
		} catch(char a) {
			cout<<"Enter a valid number"<<endl;
			cout<<"Try again"<<endl;
			goto repeat;
		}
	}
	cout<<"Enter E-Mail: ";
	cin>>email;


}

void pvt :: showdata() {
	cout<<"\n";
	cout<<setw(20)<<name;
	cout<<setw(15)<<phno;
	cout<<setw(30)<<email;

}

void pvt :: newrecord() {
	int found=0;
	char rrep[11];
	char nmopi[20];
	char eml[30];

	getdata();
	strcpy(nmopi,name);
	strcpy(rrep,phno);
	strcpy(eml,email);
	fstream file;
	file.open("phone.txt", ios::in | ios::app | ios::binary );
	while(file.read((char *) this, sizeof(*this))) {
		if(strcmp(rrep,getphno())==0) {
			found=1;
			break;
		}
	}
	file.clear();
	file.close();
	if(found==1)
		cout<<"\n\n---Contact already exist---\n";

	else {
		file.open("phone.txt", ios::app | ios::binary );
		update(nmopi,rrep,eml);
		file.write((char *) this, sizeof(*this));
		cout<<"Record Added Succesfully!!\n";
		file.close();
	}


}
void pvt :: display() {
	//Display All Records
	fstream file;
	file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
	file.seekg(0,ios::beg);
	cout<<"\n\nRecords in Phone Book:\n";
	while(file) {
		file.read((char *) this, sizeof(*this));
		if(!file.eof())
			showdata();
	}
	file.clear();
	file.close();
}

void pvt :: display(char *nm) {             //function overloading
	//Search Tel. no. when person name is known.
	char c, telno[11];
	int cnt,found=0;

	fstream file;
	file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
	file.seekg(0,ios::beg);
	while(file.read((char *) this, sizeof(*this))) {

		if(strcmp(nm,getname())==0) {
			found=1;
			showdata();
		}
	}
	file.clear();
	if(found==0)
		cout<<"\n\n---Record Not found---\n";
	file.close();

}

void pvt :: searchpname() {
	//Search name on basis of tel. no
	char c,ch,nm[20],telno[11],ml[30];
	int cnt,found=0;
	cout<<"\n\nEnter Phone No. : ";
	cin>>telno;
	fstream file;
	file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
	file.seekg(0,ios::beg);
	while(file.read((char *) this, sizeof(*this))) {
		if(strcmp(telno,getphno())==0) {
			found=1;
			showdata();
		}
	}
	file.clear();
	if(found==0)
		cout<<"\n\n---Record Not found---\n";
	file.close();

}


void pvt :: updaterec() {
	//Update Telephone No.
	int k;
	fstream file;
	file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
	cout<<"Choose the operation you want to perform:\n";
	cout<<"1. to update name."<<endl;
	cout<<"2. to update phone number."<<endl;
	cout<<"3. to update email."<<endl;
	cin>>k;
	if(k==1) {
		char c,ch,nm[20],newnm[15],teleno[15],mail[30];
		int cnt=0,found=0;
		cout<<"\n\nEnter Name : ";
		cin>>nm;
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {
			cnt++;
			if(strcmp(nm,getname())==0) {
				found=1;
				break;
			}
		}
		file.clear();
		if(found==0)
			cout<<"\n\n---Record Not found---\n";
		else {
			strcpy(teleno,phno);
			strcpy(mail,email);
			int location = (cnt-1) * sizeof(*this);
			cin.get(ch);
			if(file.eof())
				file.clear();

			cout<<"Enter New Name: ";
			cin>>newnm;
			file.seekp(location);
			update(newnm,teleno,email);
			file.write((char *) this, sizeof(*this));
			file.flush();
		}
	}

	if(k==2) {
		char c,ch,nm[20],telno[15],newteleno[15],mail[30];
		int cnt=0,found=0;
		cout<<"\n\nEnter Phone number : ";
		cin>>telno;
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {
			cnt++;
			if(strcmp(telno,getphno())==0) {
				found=1;
				break;
			}
		}
		file.clear();
		if(found==0)
			cout<<"\n\n---Record Not found---\n";
		else {
			strcpy(nm,name);
			strcpy(mail,email);
			int location = (cnt-1) * sizeof(*this);
			cin.get(ch);
			if(file.eof())
				file.clear();

			cout<<"Enter New Phone number: ";
			cin>>newteleno;
			file.seekp(location);
			update(nm,newteleno,email);
			file.write((char *) this, sizeof(*this));
			file.flush();
		}
	}

	if(k==3) {
		char c,ch,nm[20],teleno[15],mail[30],newmail[30];
		int cnt=0,found=0;
		cout<<"\n\nEnter E-Mail : ";
		cin>>mail;
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {
			cnt++;
			if(strcmp(mail,getemail())==0) {
				found=1;
				break;
			}
		}
		file.clear();
		if(found==0)
			cout<<"\n\n---Record Not found---\n";
		else {
			strcpy(nm,name);
			strcpy(teleno,phno);
			int location = (cnt-1) * sizeof(*this);
			cin.get(ch);
			if(file.eof())
				file.clear();

			cout<<"Enter New E-Mail: ";
			cin>>newmail;
			file.seekp(location);
			update(nm,teleno,newmail);
			file.write((char *) this, sizeof(*this));
			file.flush();
		}
	}

	file.close();
}



void pvt :: deleterec() {
	char bb[20],teleno[11];
	cout<<"Enter the name of the record which is to be deleted: ";
	cin>>bb;
	fstream file;
	file.open("phone.txt",  ios::in | ios::binary );
	fstream fout;
	fout.open("tempfile.txt",ios::out | ios::binary);
	int i=0,j=0,found=0;
	file.read((char *) this, sizeof(*this));
	while(!file.eof()) {
		i++;
		if(strcmp(bb,getname())) {
			fout.write((char*)this,sizeof(*this));
			j++;
		}
//        found++
		file.read((char*)this,sizeof(*this));


	}
	fout.close();
	file.close();
	if(i-j<=1) {

		file.close();
		remove("phone.txt");
		rename("tempfile.txt","phone.txt");
		if(j<i)
			cout<<"Record successfully deleted!!"<<endl;


		if(j==i)
			cout<<"Record not found!!"<<endl;

	} else {
		cout<<"\n\nMore than one contact exist with same name.\n"<<endl;
		file.open("phone.txt", ios::ate | ios::in | ios::out | ios::binary );
		file.seekg(0,ios::beg);
		while(file.read((char *) this, sizeof(*this))) {
			if(strcmp(bb,getname())==0) {
				found=1;
				showdata();
				cout<<endl;
			}
		}
		file.clear();
		file.close();
		cout<<"\n\nPlease enter the contact number you want to delete :  "<<endl;
		cin>>teleno;
		//fstream file;
		file.open("phone.txt",  ios::in | ios::binary );
		//    fstream fout;
		fout.open("tempfileph.txt",ios::out | ios::binary);
		//  int i=0,j=0,found=0;
		file.read((char *) this, sizeof(*this));
		i=0;
		j=0;
		while(!file.eof()) {
			i++;
			if(strcmp(teleno,getphno())) {
				fout.write((char*)this,sizeof(*this));
				j++;
			}
			//        found++
			file.read((char*)this,sizeof(*this));
		}
		fout.close();
		file.close();
		remove("phone.txt");
		rename("tempfileph.txt","phone.txt");
		if(j<i)cout<<"\n\nRECORD DELETED\n\n"<<endl;
		else cout<<"Record NOT found!!"<<endl;
	}
}
