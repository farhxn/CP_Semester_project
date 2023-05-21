#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>


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
    int quantity;
}pro;

int p_id=1,u_id=1,l_id = 0,l_total=0,pushid = 0;
string l_mail,l_name;
bool found = false,admin = false; 




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
inline void l_tot(); //total bill program
inline void checkout();//checkout
void deleteRecord(int);//order complete






int main() {


	load(); // Loading Screen Function	

	wel_menu(); // welcome menu function

	if(found == true)
		product(); //user menu
	if(admin == true)
		dashboard();	//admindashboard
	return 0;
}

inline void checkout(){
    system("cls");
    head();
    
	cout<<"\t\t\t\t\t\t\b\b\b\b...........................\n\t\t\t\t\t       Checkout       \t\t\tYour Total Bill is Rs. "<<l_total<<"\n\t\t\t\t\t\t\b\b\b\b...........................\n\n";
    
	
	ifstream check("order.txt");

    cout << "\t\t+-------------------------------------------------------------------------------+\n"<< "\t\t|    Product ID    |\t  Name\t   |  Quantity   |\tPrice\t|  Total Price\t|\n"<< "\t\t+-------------------------------------------------------------------------------+\n";

    int checkid, checkqty,checkprice,check_p_id;
    string checkname;
    while (check >> checkid >> checkname >> checkprice >> checkqty>>check_p_id) {
       if(l_id == checkid){
	    cout << "\t\t| " << setw(9) << check_p_id << setw(9)<<" | ";
        cout  <<setw(9) << checkname << setw(8)<< " | ";
        cout  << setw(8) << checkqty << setw(3)<< "\t |";
		cout << setw(5) <<"Rs. "<< checkprice << setw(5)<< "\t| ";
		cout << setw(5) <<"Rs. "<< checkprice*checkqty << setw(5)<< "\t| \n";
		}
    }
    cout << "\t\t+-------------------------------------------------------------------------------+\n";	     
	check.close();
	
	ifstream filling("push.txt");
	int pushid,counter =0,count,price;
	string name;
	
	while (filling >> pushid >> name >> count>>price) {
	if(l_id == count)
		counter ++;
	}  
	filling.close();
	
	if(counter >= 5){
    double discount = l_total - (l_total * 0.30);
		cout<<"\t\t\t\t\t\t\b\b\b\b...........................\n\t\t\t\t\t       After 30% Discount\n\t\t\t\t\t\tYour Total Bill is Rs. "<<discount<<"\n\t\t\t\t\t\t\b\b\b\b...........................\n\n";
	}
	else{
			cout<<"\t\t\t\t\t\t\b\b\b\b...........................\n\t\t\t\t\t       Your Total Bill is Rs. "<<l_total<<"\t\t\t\t\t\t\n\t\t\t\t\t\t\b\b\b\b...........................\n\n";
	}
	
	string out;
	cout<<"\n\n\t\tEnter any key to proceed to checkout : ";
	cin.ignore();
	getline(cin,out);
	deleteRecord(l_id);
	system("cls");
	head();
	cout<<"\t\t\t\t\t\t\b\b\b\b...........................\n\t\t\t\t\t     Your Order is Placed \n\t\t\t\t\t\tThank You for shopping Here       \t\t\t\n\t\t\t\t\t\t\b\b\b\b...........................\n\n";
	Sleep(2000);
	main();
}


void deleteRecord(int idToDelete) {
    ifstream inputFile("order.txt");
    ofstream outputFile("temp.txt", ios::app);
    ofstream outputFile1("push.txt", ios::app);

    int u_id;
    string p_name;
    int price, qty, p_id;

    while (inputFile >> u_id >> p_name >> price >> qty >> p_id) {
        if (u_id != idToDelete) {
            outputFile << u_id << "\t" << p_name << "\t" << price << "\t" << qty << "\t" << p_id << endl;
        }
        else{
        	ifstream fill("push.txt");
        	int orderid=0;
        		while (fill >> orderid) {
				pushid = orderid;
			}  
			fill.close();
			pushid++;
        	outputFile1 << pushid << "\t" << l_name << "\t" << l_id << "\t" << l_total << endl;
        	outputFile1.close();
		}
    }

    inputFile.close();
    outputFile.close();

    if (remove("order.txt") != 0) {
        perror("Error deleting the file.");
        return;
    }

    if (rename("temp.txt", "order.txt") != 0) {
        perror("Error renaming the file.");
        return;
    }
}




inline void l_tot(){
	ifstream total("order.txt");
	int o_id,o_price,o_qty,o_p_id;
	string o_p_name;
	l_total = 0;
	while(total>>o_id>>o_p_name>>o_price>>o_qty>>o_p_id){
		if(l_id == o_id){
			l_total += (o_price*o_qty);
		}
	}
	total.close();
}




inline void product() {
	l_tot();
	string order1;
	int order2,qty;
	bool ord = false;
    system("cls");
    head();
    
	cout<<"\t\t\t\t\t\t\b\b\b\b...........................\n\t\t\t\t\t       Welcome "<< l_name<<"\t\t\tYour Total Bill is Rs. "<<l_total<<"\n\t\t\t\t\t\t\b\b\b\b...........................\n\n";
    
	
	ifstream file("products.txt");

    cout << "\t\t+---------------------------------------------------------------+\n";
    cout << "\t\t|    Product ID    |\t  Name\t   |  Quantity   |\tPrice\t|\n";
    cout << "\t\t+---------------------------------------------------------------+\n";

    int storeid, storedqty;
    double storedprice;
    string storedname;
    
    while (file >> storeid >> storedname >> storedprice >> storedqty) {
        cout << "\t\t| " << setw(9) << storeid << setw(9)<<" | ";
        cout  <<setw(9) << storedname << setw(8)<< " | ";
        cout  << setw(8) << storedqty << setw(3)<< "\t |";
		cout << setw(5) <<"Rs. "<< storedprice << setw(5)<< "\t| \n";
    }
    
    cout << "\t\t+---------------------------------------------------------------+\n";
    
	file.close();     
    cout<<"\n\n\tEnter the product ID number to add to cart or press any number (Except Product ID) to go on checkout : ";
    cin>>order1;

    stringstream ss(order1);
    ss >> order2;

	ifstream fl("products.txt");
  
    while (fl >> storeid >> storedname >> storedprice >> storedqty) {
    	
    	if(order2 == storeid){
		
			quantity : 
				cout<<"\n\t\tEnter Quantity of the product : ";
    			cin>>qty;
    	if(qty<=storedqty){
    	
    		ofstream order("order.txt",ios::app);
			order<<l_id<<"\t"<<storedname<<"\t"<<storedprice<<"\t"<<qty<<"\t"<<storeid<<endl;
			order.close();
			
    		ord = true;
    		char cont;
    		cout<<"\t\t\t\tAdded Successfully\n\t\tDo you want to continue your shopping (Y) for yes (C) for Checkout and (L) for logout : ";
    		cin.ignore();
			cin>>cont;
    		
			if(cont =='Y' || cont == 'y')
    		product();
			else if(cont =='C' || cont == 'c'){
    		l_tot();
			checkout();    		
			}
			else
			main();
		}
		else 
		goto quantity;
	}
		
   }
    
	fl.close();	
	
	if(ord == false){
		checkout();
	}
}



/*
inline void product() {
    system("cls");
    head();

    ifstream file("products.txt");
    
    string storedname;
    int storeid, storedqty;
    double storedprice;
    
    while (file >> storeid >> storedname >> storedprice >> storedqty) {
        cout << "+------------------------------------+\n"
             << "|                                    |\n"
             << "|        " << storedname << "\n"
             << "|                                    |\n"
             << "|         " << storedqty << "\n"
             << "|                                    |\n"
             << "|       Rs." << storedprice << "\n"
             << "|                                    |\n"
             << "+------------------------------------+\n";
    }
    file.close();
}*/




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





inline void login() {
    string mail, password;

login:
    cout << "\tType \"back\" to go back\n\n\t\t\tEnter your details to login\n\n";
    cout << "\tEnter mail: ";
    cin >> mail;

    if (mail == "back" || mail == "BACK" || mail == "Back")
        wel_menu();

    cout << "\tEnter password: ";
    cin >> password;
    cin.ignore(); 

    if (password == "back" || password == "BACK" || password == "Back")
        wel_menu();

    ifstream login("user.txt");
    string storedname, storedmail, storedPassword;
    int loginid;
    
    while (login >>loginid >> storedname >> storedmail >> storedPassword) {
        if (storedmail == mail && storedPassword == password) {
            l_id = loginid;
			l_mail = mail;
            l_name = storedname;
            found = true;
            break;
        }
        else if (mail == "admin" && password == "admin") {
        	admin = true;
        	break;
		}
    }
    login.close();
    
    if (admin == false && found == false) {
        cout << "\n\n\t\t\t\tWrong Credentials\n";
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
		int storeid;
		
		while(check >>storeid>> u_name >> u_mail >> u_password){
			if(u_mail == use.mail){
				cout<<"\n\t\t\tEmail Already Exists. please try different\n";
				goto mail;
		}
	}
	cout<<"\tEnter Your password : ";
		cin.ignore();
		cin >>use.password;
		if(use.password == "back"||use.password == "BACK"||use.password == "Back"){
    		wel_menu();
		}
		
		    ifstream fi("user.txt");
   			 string storedname, storedmail, storedPassword;
			int storedid;
	
	while (fi >> storedid >>storedname >> storedmail >> storedPassword) {
    	u_id = storedid;
    } 
    ++u_id;
    fi.close();
		
	ofstream reg("user.txt",ios::app);
	reg<<u_id<<"\t"<<use.name<<"\t"<<use.mail<<"\t"<<use.password<<endl;
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


