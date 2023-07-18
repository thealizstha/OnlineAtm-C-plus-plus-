#include<iostream>
#include<fstream>
using namespace std;
class user//User Details
	{
			long int accountno;
			char username[30];
			public:
			void getuser()
		{
			cout<<"Enter name of user:\t";
			gets(username);
			cout<<"Enter account number:\t";
			cin>>accountno;
		}
				void displayuser()
				{
					cout<<"\t\tUsername:\t"<<username<<endl;
					cout<<"\t\tAccount Number:\t"<<accountno<<endl;
			   	}
    };
		class account:public user
		{
		private:
		int pin;
		int userid;
		public:
		float money;
		void getaccount()
	    	{
			getuser();
			cout<<"Enter user id:\t";
			cin>>userid;
			cout<<"Enter pin:\t";
			cin>>pin;
			cout<<"Enter the amount to deposit"<<endl;
			cin>>money;
           }
        void updatecash(float m)
            {
	           money = money - m;
         	}
		void displayaccount()
		    {
			displayuser();
			cout<<"\t\tUser id:\t"<<userid<<endl;
			cout<<"\t\tAccount balance: "<<money<<endl<<endl;
			cout<<"____________________________________________________________"<<endl<<endl;
			}
			int getid()
			{
				return userid;
			}
			int getpin()
			{
				return pin;
			}
        };
		int checkdetails(int,int,account);
		void withdrawmoney(account,int);
		void checkbalance(account,int);
		void write(account);
		void update(account,int,float);
		int main()
		{ 
			account acc;
			float amount;
			int n,pin_no;
			int id;
			char k,z[3];
			cout<<"***************ATM***************"<<endl;
			cout<<"DO YOU WANT TO WRITE TO FILE(Y/N)"<<endl;
			cin>>k;
			gets(z);
			if(k=='y'||k=='Y')
		    {
		 	  write(acc);
			}
				system("cls");
				while(1)
			{
				system("cls");
				cout<<"\t\tLOGIN"<<endl;
				cout<<"USER ID:\t";
				cin>>id;
				cout<<"PIN:\t";
				cin>>pin_no;
				system("cls");
				int check= checkdetails(id,pin_no,acc);
				if(check==1)
			{
			break;
			}
			else
			{
		     	cout<<"!!!!!!!!!!! INVALID DETAILS !!!!!!!!!!!"<<endl;
			}
			    system("cls");
			
			}
			
			    
		     	while(1)
            {
            	cout<<"\t**************MENU**************"<<endl<<endl;
				cout<<"\t\t1. Withdraw cash"<<endl;
				cout<<"\t\t2. Check balance"<<endl;
				cout<<"\t\t3. Logout"<<endl;
				cin>>n;
				system("cls");
				if(n==1)
			{
			    withdrawmoney(acc,id);
			}
			else if(n==2)
			{
			    checkbalance(acc,id);
			}
			else if(n==3)
			{
					
			while(1)
			{
				cout<<"\t\tLOGIN"<<endl;
				cout<<"USER ID:\t";
				cin>>id;
				cout<<"PIN:\t";
				cin>>pin_no;
				int check= checkdetails(id,pin_no,acc);
				if(check==1)
			{
			break;
			}
			else
			{
				cout<<"\t!!!!!!!!!!! INVALID DETAILS !!!!!!!!!!!"<<endl;
				system("cls");
			}
			}
			}
			else
		    	cout<<"\t!!!!!!!!!!! INVALID CHOICE !!!!!!!!!!!"<<endl;
			}
			return 0;
		}
			void write(account acc)
			{
		    	int n;
		     	char x[2];
				ofstream outfile;
				outfile.open("ATM_data.dat",ios::binary/*|ios::app*/);
			while(1)
			{
				acc.getaccount();
				outfile.write(reinterpret_cast<char*>(&acc),sizeof(acc));
				cout<<"Enter 0 to end and 1 to continue:"<<endl;
				cin>>n;
				gets(x);
		    if(n==0)
			   {
				break;
			   }
		    }
				outfile.close();
            }
			void checkbalance(account acc,int id)
			{
			int returned_id;
					ifstream infile;
					infile.open("ATM_data.dat",ios::binary);
			while(!infile.eof())
			{
			if(infile.read(reinterpret_cast<char*>(&acc),sizeof(acc))>0)
		     	returned_id=acc.getid();
			if(id==returned_id)
			{
		       	acc.displayaccount();
			    break;
            }
            }
                infile.close();
            }
			void withdrawmoney(account acc,int id)
			{
			float m;
			int returned_id;
				ifstream infile;
				cout<<"ENTER THE AMOUNT TO WITHDRAW:\t"<<endl;
				cin>>m;
				
				infile.open("ATM_data.dat",ios::binary);
				//infile.clear();
				fstream temp;
				temp.open("temp.dat", ios::binary|ios::app);

			while(!infile.eof())
			{
			    if(infile.read(reinterpret_cast<char*>(&acc),sizeof(acc))>0)
			{
		      	returned_id=acc.getid();
		    	if(id==returned_id)
			{
			if(m<acc.money){
				acc.money = acc.money - m;
				cout<<"You took out Rs. "<<m<<endl;
				cout<<"Your balance after withdrawl is Rs.  "<<acc.money<<endl<<endl;
				cout<<"___________________________________________________________"<<endl<<endl;
			}
			else
			    cout<<"!!!!!!!!!! Insufficient Balance !!!!!!!!!!"<<endl<<endl;
			}
			    temp.write(reinterpret_cast<char*>(&acc), sizeof(acc));
			}
            }
				infile.close();
				temp.close();
				remove("ATM_data.dat");
				rename("temp.dat", "ATM_data.dat");
		    }
			int checkdetails(int id,int pin_no,account acc)
			{
			ifstream infile;
				int returned_id,returned_pin,c;
				infile.open("ATM_data.dat",ios::binary);
			while(!infile.eof())
			{
			if(infile.read(reinterpret_cast<char*>(&acc),sizeof(acc))>0)
				returned_id=acc.getid();
				returned_pin=acc.getpin();
			if(id==returned_id && pin_no==returned_pin)
			{
			   c=1;
			   break;
			}
			else
			   c=0;
			}
			    infile.close();
				return c;
        	}
