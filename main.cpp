#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Structures 
typedef struct users{
	string name;
	string mail;
	string password;
}user;

typedef struct Product {
    string name;
    double price;
    int quantity, p_id=1;
}pro;

string l_mail,l_name;
bool found = false,admin= false;  
int p_id=1;




	// Functions Declerations
inline void load(); //onload program
inline void head(); //header functions
inline void wel_menu(); //welcome menu 
inline void registered(); //register program
inline void login(); //login program
inline void product(); //product program
inline void dashboard(); //Admin Dashboard program
inline void list_user(); //list of users program
inline void Add_pro(); //Add products program
inline void list_pro(); //product program









int main() {

//	load(); // Loading Screen Function	

	wel_menu(); // welcome menu function
	if(found == true)
		product(); //user menu
	if(admin == true)
		dashboard();	//admindashboard

	return 0;
}



inline void product(){
	system("cls");
	head();

	ifstream file("products.txt");
    
	string storedname;
	int storeid,storedqty;
	double storedprice;
	 
    while (file>>storeid >> storedname >> storedprice >> storedqty) {	
    cout << "+------------------------------------+\n"
    	<< "|                                    |\n"
    	<< "|        " << storedname << "\n"		
    	<< "|                                    |\n"
    	<< "|    	 " << storedqty << "\n"
    	<< "|                                    |\n"
    	<< "|     	Rs." << storedprice << "\n"
    	<< "|                                    |\n"
    	<< "+------------------------------------+\n";  
	}
	file.close();
}



inline void list_pro(){
	system("cls");
	head();
	cout<<"\t\t\t\t\t\t\b\b\b\b......................\n\t\t\t\t\t       List Of All Products\n\t\t\t\t\t\t\b\b\b\b......................\n\n";		
	ifstream f("products.txt");
    string storedname;
	double storedprice;
	int storedqty,storedid;
    cout <<"\t\t\t-------------------------------------------------------------------------\n"
		<<"\t\t\t"<< setw(20) << left << "ID" 
        << setw(10) << right << "Name" 
        << setw(20) << right << "Price"
		<< setw(20) << right << "Qty" << endl
        <<"\t\t\t-------------------------------------------------------------------------\n";
         
    while (f >>storedid>> storedname >> storedprice >> storedqty) {
       cout <<"\t\t\t"<< setw(20) << left << storedid
            << setw(10) << right << storedname
            << setw(20) << right << storedprice 
			<< setw(20) << right << storedqty << endl;
    }
   	cout<<"\t\t\t-------------------------------------------------------------------------\n";
    f.close();	
	cout<<"\n\n\t\t Go back type \"back OR 1\" and go logout type \"logout OR 2\" : ";
	string op;
	cin>>op;
	if (op=="1"||op == "back"||op == "BACK"||op == "Back"){
		system("cls");
		head();
		dashboard();
	}
	else if (op=="2"||op == "logout"||op == "Logout"||op == "LOGOUT"){
		system("cls");
		head();
		wel_menu();
	}
	else{
		cout<<"\n\n\t\t\t\tdidn't find any option\n\n\n";
	   	Sleep(200);
		list_user();
	}

}



inline void Add_pro(){
	system("cls");
	head();
    pro p;
    	cout<<"\t\t\t\t\t\t\b\b\b\b......................\n\t\t\t\t\t       Add Product\n\t\t\t\t\t\t\b\b\b\b......................\n\n";		

    ifstream fi("products.txt");
    string storedname, storedmail, storedPassword;
	int storedid;
	
	while (fi >> storedid >>storedname >> storedmail >> storedPassword) {
    	p_id = storedid;
    } 
    
	p_id++;
    cout<<p_id;
    fi.close();
    
    cout << "\tEnter product name: ";
    cin.ignore();
    getline(cin, p.name);
    cout << "\tEnter product price: ";
    cin >> p.price;
    cout << "\tEnter product quantity: ";
    cin >> p.quantity;
    

    
    ofstream file("products.txt", ios::app);
    file << p_id<<"\t" << p.name << "\t" << p.price << "\t" << p.quantity << endl;
    file.close();
    cout<<"\n\n\t\t\t\tProduct Added Successfully\n";
    cout<<"\n\t\t If you want to add more products press 1 : ";
	string option;
	cin>>option;
	if(option=="1")
		Add_pro();
	system("cls");
		head();
 	cout<<"\t\t\t\t\t\t\b\b\b\b.....................................\n\t\t\t\t\t       Product Added Successfully\n\t\t\t\t\t\t\b\b\b\b.....................................\n\n";
	Sleep(300);
	system("cls");
	head();
	dashboard();
}



inline void list_user(){
	system("cls");
	head();
	cout<<"\t\t\t\t\t\t\b\b\b\b......................\n\t\t\t\t\t       List Of All Users\n\t\t\t\t\t\t\b\b\b\b......................\n\n";		
	ifstream file("user.txt");
    string storedname, storedmail, storedPassword;
    cout <<"\t\t\t------------------------------------------------------\n"
		<<"\t\t\t"<< setw(20) << left << "Name" 
        << setw(10) << right << "Mail" 
        << setw(20) << right << "Password" << endl
        <<"\t\t\t------------------------------------------------------\n";
         
    while (file >> storedname >> storedmail >> storedPassword) {
       cout <<"\t\t\t"<< setw(20) << left << storedname
            << setw(10) << right << storedmail
            << setw(15) << right << storedPassword << endl;
    }
   	cout<<"\t\t\t------------------------------------------------------\n";
    file.close();	
	cout<<"\n\n\t\t Go back type \"back OR 1\" and go logout type \"logout OR 2\" : ";
	string op;
	cin>>op;
	if (op=="1"||op == "back"||op == "BACK"||op == "Back"){
		system("cls");
		head();
		dashboard();
	}
	else if (op=="2"||op == "logout"||op == "Logout"||op == "LOGOUT"){
		system("cls");
		head();
		wel_menu();
	}
	else{
		cout<<"\n\n\t\t\t\tdidn't find any option\n\n\n";
	   	Sleep(200);
		list_user();
	}
}





inline void dashboard(){
	system("cls");
	head();
	cout<<"\t\t\t\t\t\t\b\b\b\b...................\n\t\t\t\t\t       Welcome Admin\n\t\t\t\t\t\t\b\b\b\b...................\n\n";
	string opt;
	cout<<"\t\t Select from given options you want to perform operation\n\n\t Press 1 for List of all users\n\t Press 2 for List of all products\n\t Press 3 for List of Product sales\n\t Press 4 to add product\n\t Press 5 for Exit and logout\n\t Select your option : ";
	cin>>opt;
	if (opt=="1"){
		list_user();			
	}
	else if (opt=="2")
	list_pro();
	else if (opt=="3"){
		system("cls");
		head();
		cout<<"All products sales";
	}
	else if (opt=="4")
	Add_pro();
	else{
		cout<<"\n\t\t\tThank you for choosing Phoenix Bazaar";
		Sleep(300);
		wel_menu();
	}	
}





inline void login(){
    string mail, password;
    login:
    cout<<"\tType \"back\" go to back\n\n\t\t\tEnter your details to login \n\n";
    cout << "\tEnter mail: ";
	cin.ignore();
	cin >> mail;

    if(mail == "back"||mail == "BACK"||mail == "Back")
        wel_menu();

    cout << "\tEnter password: ";
	cin.ignore();
	cin >> password;

    if(password == "back"||password == "BACK"||password == "Back")
        wel_menu();

    ifstream file("user.txt");
    string storedname, storedmail, storedPassword;

    while (file >> storedname >> storedmail >> storedPassword) {
        if (storedmail == mail && storedPassword == password) {
            l_mail = mail;
            l_name = storedname;
            product();
            found = true;
            break;
        }
    }
    file.close();
    if(mail == "admin" && password =="admin"){
  		admin = true;
	}
	if(admin != true || found != true) {
        cout<<"\n\n\t\t\t\tWrong Credentials\n";
        Sleep(800);
        system("cls");
        head();
        goto login;
    }
}




inline void registered(){
	user use;
	string line;
	
	cout<<"\tType \"back\" go to back\n\n\t\t\tEnter your details to Register \n\n";
	cout<<"\tEnter Your name : ";
	cin.ignore();
	cin>> use.name;
	
	if(use.name== "back"||use.name == "BACK"||use.name == "Back"){
    		wel_menu();
	}
	
	mail : 	cout<<"\tEnter Your Mail : ";
		cin.ignore();
		cin>> use.mail;
	
		if(use.mail == "back"||use.mail == "BACK"||use.mail == "Back"){
    		wel_menu();
		}
		ifstream check("user.txt");
		string u_name,u_password,u_mail;
		
		while(check >> u_name >> u_mail >> u_password){
			if(u_mail == use.mail){
				cout<<"Email Already Exists. please try different\n";
				goto mail;
		}
	}
	cout<<"\tEnter Your password : ";
		cin.ignore();
		cin >>use.password;
		if(use.password == "back"||use.password == "BACK"||use.password == "Back"){
    		wel_menu();
		}
	ofstream reg("user.txt",ios::app);
	reg<<use.name<<"\t"<<use.mail<<"\t"<<use.password<<endl;
	reg.close();
	cout<<"\n\t\t\t\tRegistered Successfully\n";
	cout<<"\n\t\t\t\tLogin To Continue\n";
	Sleep(500);
	system("cls");
	head();
	login();
}


//Welcome menu function
inline void wel_menu(){
	system("cls");
	head();
	string opt;
	cout<<"\t Welcome,\n\t\t To start shopping you have to login first\n\n\t Press 1 for Login\n\t Press 2 for Registration\n\t Press 3 for Exit\n\t Select your option : ";
	cin>>opt;
	if (opt=="1"){
		system("cls");
		head();
		login();			
	}
	else if (opt=="2"){
		system("cls");
		head();
		registered();
	}
	else{
		found = false;
		cout<<"\n\t\t\tThank you for choosing Phoenix Bazaar";
	}	
}

//Header of program
inline void head(){
	cout << "\n\n\t\t\t\t\t=========================\n\t\t\t\t\t||    Phoenix Bazaar    ||\n\t\t\t\t\t=========================\n\n\n"<< endl;
}

// Load Function After Execution Program first function Executes 
inline void load(){
	system("cls");
	cout << "\n\n\n\n\n\n\n\n\n\t\t\t\t\t=========================================\n\t\t\t\t\t||\tWelcome To Phoenix Bazaar\t||\n\t\t\t\t\t=========================================\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
    Sleep(1000);
	system("cls");	
}


