#include <iostream>
#include <cstdio>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <conio.h>
#include <stdio.h>

#define s6 "\t\t\t\t\t\t"
#define s5 "\t\t\t\t\t"
#define s4 "\t\t\t\t"
#define s3 "\t\t\t"
#define s2 "\t\t"
#define s1 "\t"
#define sp2 "  "
#define nl endl
#define cyp "Choose your option : "
using namespace std;
void recover(char* , char*);
float getSal(string );
int hashed(char , char, int);
class Player
{
	public :
	string name, ssn, amt, age,  badc, tt, vb, bb, stime, etime, mins;
	Player(){
		badc="200",tt="150",vb="100",bb="400",stime="-",etime="-",mins="0";
	}
	void deletecourt();
	void searchcourt();
	void modcourt();
	void dispcourt();
	void addUser();
	void modUser();
};

void addUser()
{
	Player e;
	cout<<s4<<"Enter the ID : ";
	cin>>e.ssn;
	e.ssn.resize(8);
	cout<<s4<<"Enter the Name : ";
	cin>>e.name;
	e.name.resize(8);
	cout<<s4<<"Enter the Age : ";
	cin>>e.age;
	e.age.resize(8);
	cout<<s4<<"Enter the Security Money : ";
	cin>>e.amt;
	e.amt.resize(8);
	
	fstream file1,file2,file3;
	file1.open("plyr.txt",ios::binary|ios::app);
	file2.open("court.txt",ios::binary|ios::app);
	file3.open("securityamnt.txt",ios::binary|ios::app);
	if(!file1||!file2){
		cout<<s4<<"Error Occured!"<<nl;
		return;
	}
	e.badc=e.badc+"/200-0",e.tt=e.tt+"/150-0",e.vb=e.vb+"/100-0",e.bb=e.bb+"/400-0";
	e.badc.resize(10),e.tt.resize(10),e.vb.resize(10),e.bb.resize(10),e.stime.resize(10),e.etime.resize(10),e.mins.resize(5);
	file1<<s4<<"|"<<e.ssn<<"|"<<e.name<<"|"<<e.age<<"|"<<e.amt<<"|"<<nl;
	file2<<e.ssn<<"|"<<e.name<<"|"<<e.badc<<"|"<<e.tt<<"|"<<e.vb<<"|"<<e.bb<<"|"<<e.amt<<"|"<<e.stime<<"|"<<e.etime<<"|"<<e.mins<<"|"<<nl;
	file3<<e.ssn<<"|"<<e.amt<<"|"<<nl;
	file1.close();
	file2.close();
	file3.close();
	int index = hashed(e.ssn[0],e.ssn[1],1);

	cout<<s4<<"User added successfully!"<<nl<<nl<<nl;
}
int hashed(char ch1, char ch2, int n)
{
	fstream file1;
	cout<<s4;
	for(int i=0;i<50;i++){
		cout<<".";
	}
	if(n==1)
	cout<<"Storing data at hash index "<<(ch1 + ch2)%100;
	else
		cout<<"Retrieving data from hash index "<<(ch1 + ch2)%100;
	
	for(int i=0;i<50;i++){
		cout<<".";
	}
	cout<<endl;
	return (ch1+ch2)%100;
}
void modUser()
{
	char ch;
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("plyr.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Player ID to modify : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=5;
	while(file1){
		file1.seekg(index, ios::beg);
		getline(file1,str,'|');
		
		if(str==id){
			found=1;
			break;
	    }
		else{
			index+=51;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		start:
		int ch,beg,end;
		string newstr,str;
		cout<<s4<<"1. EDIT AGE"<<nl;
		cout<<s4<<"2. EDIT SECURITY AMOUNT"<<nl;
		
		cout<<s4<<cyp;
		cin>>ch;
		cout<<nl;
		if(ch==1 || ch==2 ){
			cout<<s4<<"Enter the new value : ";
			cin>>newstr;
		}
		else
			goto start;
		newstr.resize(8);
	
		file1.open("plyr.txt",ios::binary|ios::in);
		file2.open("tplyr.txt",ios::binary|ios::app);

		while(count--){
		getline(file1,str);
		file2<<str<<endl;
	    }
	    if(ch==1)
	    beg=3,end=2;
		else if(ch==2)
		beg=4,end=1;
		else if(ch==3)
		beg=5,end=0;
	    for(int i=0;i<beg;i++){
	    	getline(file1,str,'|');
	    	file2<<str<<"|";
	    }

	    file2<<newstr<<"|";
	    getline(file1,str,'|');
	    for(int i=0;i<end;i++){
	    	getline(file1,str,'|');
	    	file2<<str<<"|";
	    }

	    while(file1){
	    	getline(file1,str);
	    	file2<<str;
	    	if(file1)
	    	file2<<endl;
	    }
	    file1.close();
	    file2.close();
	    cout<<s4<<"Player has been updated!"<<nl<<nl;
	    char fn1[]="plyr.txt",fn2[]="tplyr.txt";
	   	recover(fn1,fn2);
		   
		
	}
	else
		cout<<s4<<"Player not found!"<<nl<<nl;

}
void recover(char *fn1,char *fn2)
{
	remove(fn1);
	rename(fn2,fn1);
}

void displayUsers()
{
	string str;
	fstream file;
	file.open("plyr.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	cout<<nl<<s4<<"Player ID"<<s2<<"Name"<<s2<<"Age"<<s2<<"Security Amount"<<nl<<nl;
	while(file){
		getline(file,str,'|');
		cout<<str<<s1;
	}
	file.close();
	int t=110;
	cout<<nl<<s3;
	while(t--)
		cout<<"-";
	cout<<nl<<nl;
	file.close();
}

void modcourt()
{
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("court.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Player ID : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file1){
		file1.seekg(index, ios::beg);
		getline(file1,str,'|');
		if(str==id){
			found=1;
			break;
		}
		else{
			index+=100;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		start:
		string stime,etime;
		int ch,com=7,beg,end,nol,ex=0,lea,tot,mins=0,court,nod;
		float amt,per;
		cout<<s4<<"1. BADMINTON COURT"<<nl;
		cout<<s4<<"2. TABLE TENNIS"<<nl;
		cout<<s4<<"3. VOLLEY BALL"<<nl;
		cout<<s4<<"4. BASKET BALL"<<nl<<nl;
		cout<<s4<<cyp;
		cin>>ch;
		if(ch==0 || ch>4)
			goto start;
		cout<<nl;
		if(ch==1){ beg=0,end=3,tot=200,per=0.025; }
		else if(ch==2){ beg=1,end=2,tot=150,per=0.025;}
		else if(ch==3){ beg=2,end=1,tot=100,per=0.025;}
		else if(ch==4){ beg=3,end=0,tot=400,per=0.025;}
		file1.open("court.txt",ios::binary|ios::in);
		file2.open("tplyr1.txt",ios::binary|ios::app);
		while(count--){
			getline(file1,str);
			file2<<str<<endl;
		}
		for(int i=0;i<2;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		for(int i=0;i<beg;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		cout<<s4<<"Enter the duration in minutes : ";
		cin>>nol;
		while(nol>tot){
			cout<<s4<<"Cannot play more than "<<tot<<" minutes"<<nl;
			cout<<s4<<"Enter the duration in minutes : ";
			cin>>nol;
		}
		getline(file1,str,'|');
		stringstream buf1(str);
		buf1>>lea;
		court=lea;
		if(lea-nol<0)
		mins=abs(lea-nol);
		lea=lea-nol;
		if(mins!=0)
		lea=0;
		fstream buf2;
		buf2.open("mod.txt",ios::binary|ios::out);
		buf2<<lea<<"/"<<tot<<"-"<<mins;
		buf2.close();
		buf2.open("mod.txt",ios::binary|ios::in);
		getline(buf2,str);
		buf2.close();
		remove("mod.txt");
		str.resize(10);
		file2<<str<<"|";
		for(int i=0;i<end;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		getline(file1,str,'|');
		amt=getSal(id);

		if(court-nol<0)
		amt-=(float)amt*per*abs(court-nol);
		
		ostringstream buf4;
		buf4<<amt;
		str=buf4.str();
		str.resize(8);
		file2<<str<<"|";

		cout<<s4<<"Enter the Starting Time(hh:mm) : ";
		cin>>stime;
		cout<<s4<<"Enter the End Time(hh/mm) : ";
		cin>>etime;
		stime.resize(10);
		etime.resize(10);
		file2<<stime<<"|";
		file2<<etime<<"|";
		for(int i=0;i<3;i++)
		getline(file1,str,'|');

		stringstream buf5(str);
		buf5>>nod;
		nod=nod+nol;

		ostringstream buf6;
		buf6<<nod;
		str=buf6.str();
		str.resize(5);
		file2<<str<<"|";

		while(file1){
			getline(file1,str);
			file2<<str;
			if(file1)
			file2<<endl;
		}
		file1.close();
		file2.close();
		char fn1[]="court.txt",fn2[]="tplyr1.txt";
		recover(fn1,fn2);
		cout<<s4<<"Court updated!"<<nl<<nl;
	}
	else
		cout<<s4<<"User not found!"<<nl<<nl;
}	

void dispcourt()
{
	string str;
	fstream file;
	file.open("court.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	cout<<nl<<"EId\t"<<"Name\t"<<"BadCourt(200)\t"<<"TTennis(150)\t"<<"VBall(100)\t"<<"BBall(400)\t"<<"SAmt\t"<<"STime"<<sp2<<sp2<<"ETime"<<sp2<<sp2<<"Duration(mins)"<<nl<<nl;
	while(file){
		getline(file,str,'|');
		cout<<str<<"\t";
	}
	cout<<nl<<nl;
	cout<<"Note : This table shows remaining courts."<<nl<<sp2<<"BadCourt: BADMINTON COURT"<<nl<<sp2<<"TTennis: TABLE TENNIS COURT"<<nl<<sp2<<"VBall : VOLLEY BALL COURT"<<nl<<sp2<<"BBall : BASKET BALL COURT"<<nl<<sp2<<"SAmt : SECURITY AMOUNT"<<nl<<sp2<<"STime : START TIME"<<nl<<sp2<<"ETime : END TIME"<<nl<<sp2<<"Number after '-' sign indicates extra duration."<<nl<<nl;
	file.close();
}

void deletecourt()
{
	string id,str;
	int found=0,count=0;
	fstream file1,file2;
	file1.open("court.txt",ios::binary|ios::in);
	cout<<s4<<"Enter the Player ID to delete : ";
	cin>>id;
	id.resize(8);
	if(!file1){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file1){
		file1.seekg(index,ios::beg);
		getline(file1,str,'|');
		if(str==id){
			found=1;
			break;
		}
		else{
			index+=100;
			str.clear();
			count++;
		}
	}
	file1.close();
	if(found==1)
	{
		file1.open("court.txt",ios::binary|ios::in);
		file2.open("tplyr1.txt",ios::binary|ios::app);
		while(count--){
			getline(file1,str);
			file2<<str<<endl;
		}
		for(int i=0;i<2;i++){
			getline(file1,str,'|');
			file2<<str<<"|";
		}
		str="200/200-0";str.resize(10);
		file2<<str<<"|";
		str="150/150-0";str.resize(10);
		file2<<str<<"|";
		str="100/100-0";str.resize(10);
		file2<<str<<"|";
		str="400/400-0";str.resize(10);
		file2<<str<<"|";
		float sal=getSal(id);
		ostringstream buf;
		buf<<sal;
		str=buf.str();
		str.resize(8);
		file2<<str<<"|";
		str="-";str.resize(10);
		file2<<str<<"|"<<str<<"|";
		str="0";str.resize(5);
		file2<<str<<"|";
		for(int i=0;i<8;i++)
			getline(file1,str,'|');
		while(file1){
			getline(file1,str);
			file2<<str;
			if(file1)
			file2<<endl;
		}
		file1.close();
		file2.close();
		char fn1[]="court.txt",fn2[]="tplyr1.txt";
		recover(fn1,fn2);
	}
	else
		cout<<s4<<"User not found!"<<nl;
}

float getSal(string id)
{
	fstream file;
	float sal;
	string str;
	file.open("securityamnt.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return 0;
	}
	int index=0;
	while(file){
		file.seekg(index,ios::beg);
		getline(file,str,'|');
		str.resize(8);
		if(str==id){
			break;
		}
		else{
			index+=19;
			str.clear();
		}
	}
	str.clear();
	getline(file,str,'|');
	stringstream buf(str);
	buf>>sal;
	file.close();
	return sal;
}
void searchcourt()
{
	string id,str;
	cout<<s4<<"Enter the Player ID : ";
	cin>>id;
	id.resize(8);
	fstream file;
	file.open("court.txt",ios::binary|ios::in);
	if(!file){
		cout<<s4<<"Error Occured"<<nl;
		return;
	}
	int index=0;
	while(file){
		file.seekg(index,ios::beg);
		getline(file,str,'|');
		str.resize(8);
		if(str==id){
			break;
		}
		else{
			index+=100;
			str.clear();
		}
	}
	int hash = hashed(id[0], id[1], 0);
	cout<<nl<<"Player ID\t"<<"Name\t\t"<<"Badminton(200)\t\t"<<"TableTennis(150)\t\t"<<"VolleyBall(100)\t\t"<<"BasketBall(400)\t\t"<<"Security Amount\t\t"<<"Start Time"<<sp2<<sp2<<"End Time"<<sp2<<sp2<<"Duration"<<nl<<nl;
	cout<<str<<"\t";
	for(int i=0;i<9;i++){
		getline(file,str,'|');
		cout<<str<<"\t";
	}
	file.close();
	cout<<nl<<nl;
}
int main()
{
	while(true){
	start:
	int ch;
	cout<<s3<<"----- S P O R T S  C O U R T   C O N N E C T   M A N A G E M E N T  S Y S T E M -----"<<nl<<nl;
	cout<<s6<<"--- M A I N  M E N U ---"<<nl<<nl;
	cout<<s4<<"1. SELECT COURT"<<nl;
	cout<<s4<<"2. RESET ALL"<<nl;
	cout<<s4<<"3. SEARCH COURT"<<nl;
	cout<<s4<<"4. MODIFY COURT"<<nl;
	cout<<s4<<"5. DISPLAY ALL INFO"<<nl;
	cout<<s4<<"6. USER MANAGEMENT"<<nl;
	cout<<s4<<"7. EXIT"<<nl;
	cout<<nl<<s4<<cyp;
	cin>>ch;
	cout<<nl;
	switch(ch)
	{
		case 1:
			modcourt();
			break;
		case 2:
			deletecourt();
			break;
		case 3:
			searchcourt();
			break;
		case 4:
			modcourt();
			break;
		case 5:
		 	dispcourt();
		 	break;
		case 6:
			int ch1;
			cout<<s4<<"1. ADD USER"<<nl<<s4<<"2. MODIFY USER"<<nl;
			cout<<s4<<"3. DISPLAY ALL USERS INFORMATION"<<nl;
			cout<<nl<<s4<<cyp;
			cin>>ch1;
			cout<<nl;
			if(ch1==1)
			addUser();
			else if(ch1==2)
			modUser();
			else if(ch1==3)
			displayUsers();
			break;

		case 7:
			exit(0);

		default : goto start;
	 }
	}
	return 0;
}