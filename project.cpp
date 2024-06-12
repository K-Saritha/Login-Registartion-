#include<string>
#include<iostream>
#include<fstream>
#include<time.h>
#include<bits/stdc++.h>
using namespace std;
class User 
{
	private:
		string username;
		string password;
	public:
			User(string&name,string&pass)
			{
				username=name;
				password=pass;		
			}
    string& getUsername() 
	{
        return username;
    }

     string& getPassword() 
	{
        return password;
    }
};

class login_and_register
{
public:
    void run() 
	{
        int choice;
        while(true)
		{
            displayMenu();
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) 
			{
                case 1:
                    if(login())
                    break;
                    else
                    	return;
                case 2:
                    register_user();
                    break;
                case 3:
                    forgot();
                    break;
                
                case 4:
                    cout << "Thanks for using this program.\n\n";
                    return;
                default:
                    cout << "You've made a mistake. Try again.\n" << endl;
                    break;
            }
        }
      
    }

private:
    void displayMenu() 
	{
		
        cout << "              Welcome to login page        \n";
        cout << "1. LOGIN" << endl;
        cout << "2. REGISTER" << endl;
        cout << "3. FORGOT PASSWORD (or) USERNAME" << endl;
        cout << "4. Exit" << endl;
    }
    bool login() 
	{
        string user, pass;
        int tries =3;
        int success=0;
        while(tries && !success){
        cout << "Please enter Username: ";
        cin >> user;
        cout << "Please enter Password: ";
        cin >> pass;
        string captcha = generateCaptcha();
	    cout << "Captch:"<<captcha;
	    string usr_captcha;
	    cout << "\nEnter above CAPTCHA: ";
	    cin >> usr_captcha;
        

        if (is_username_and_password_valid(user, pass)) 
		{
			if(checkCaptcha(captcha, usr_captcha))
			{
               cout << "\nHello, " << user << "\n<LOGIN SUCCESSFUL>\nThanks for logging in..\n";
            }
            else 
			{
			   cout<<"Captcha Invalid  !!!"<<endl;
			}
            success=1;
            return true;
            
        }
		else 
		{
            cout << "\nLOGIN ERROR\nPlease check your username and password\n";
            tries=tries-1;
        }
        
    }
    if(tries<1)
    {
    	cout<<"Your three chance are over program is exited!!!";
    	return false;
	}
    }

    void register_user() 
	{
        string user, pass;
        cout << "Enter the username\n username must contain atleast 8 characters: ";
        cin >> user;
        cout << "Enter the password \n Paasword must contain atleast one lowercase,one uppercase,one digit,one special character: \n";
        cin >> pass;
        if(is_username_valid(user))
        {
        	if(is_password_valid(pass))
        	{
        		User newUser(user, pass);
		
		        ofstream file("database.txt", ios::app);
		        file << newUser.getUsername() << ' ' << newUser.getPassword() << endl;
		
		        cout << "\nRegistration Successful\n";
			}
			else
			{
				cout<<"Enter credentials correctly\n";
			}

		}
		else
		{
			cout<<"Enter credentials  correctly\n ";
		}
    }
    bool is_username_valid(string &user)
    {
    	return user.length()>=8;
	}
	bool is_password_valid(string&pass)
	{
		return pass.length()>=8 && has_uppercase(pass) && has_lowercase(pass) && has_digit(pass) && has_special_character(pass);
	}
	
	bool has_uppercase(const string& pass) {
    for (int i = 0; i < pass.length(); i++) {
        if (isupper(pass[i])) {
            return true;
        }
    }
    return false;
}

	
	bool has_lowercase(const string& pass) {
	    for (int i = 0; i < pass.length(); i++) {
	        if (islower(pass[i])) {
	            return true;
	        }
	    }
	    return false;
	}
	
	
	bool has_digit(const string& pass) {
	    for (int i = 0; i < pass.length(); i++) {
	        if (isdigit(pass[i])) {
	            return true;
	        }
	    }
	    return false;
	}
	
	
	bool has_special_character(const string& pass) {
	    string specialChars = "!@#$%^&*()-_+=<>?{}[]|:;'',.";
	    for (int i = 0; i < pass.length(); i++) {
	        if (specialChars.find(pass[i]) != string::npos) {
	            return true;
	        }
	    }
	    return false;
	}
	
    bool is_username_and_password_valid( string& username,  string& password)
	 {
        ifstream file("database.txt");
        string u, p;
        while (file >> u >> p) 
		{
            if (u == username && p == password)
			 {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }
    bool checkCaptcha(string& captcha, string& user_captcha)
	{
	    return captcha.compare(user_captcha) == 0;
	}
	
	string generateCaptcha()
	{
		int n=4;
	    time_t t;
	    srand((unsigned)time(&t));
	    char* chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	    string captcha = "";
	    while (n){
	        captcha.push_back(chrs[rand() % 62]);
	        n--;
	    }
	 
	    return captcha;
	}

    void forgot() 
	{
        int choice;
        cout << "1. Search your ID by username" << endl;
        cout << "2. Search your ID by password" << endl;
        cout << "3. Main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
		{
            case 1:
                search_by_username();
                break;
            case 2:
                search_by_password();
                break;
            case 3:
                break;
            default:
                cout << "Sorry, you entered a wrong choice.  Try again" << endl;
                break;
        }
    }

    void search_by_username() 
	{
        string username;
        cout << "Enter your username: ";
        cin >> username;

        ifstream file("database.txt");
        string u, p;
        while (file >> u >> p) 
		{
            if (u == username) 
			{
                cout << "\nHurray, account found\n";
                cout << "\nYour password is " << p << endl;
                file.close();
                return;
            }
        }
        file.close();
        cout << "\nSorry, your userID is not found in our database\n";
        
    }

    void search_by_password() 
	{
        string password;
        cout << "Enter the password: ";
        cin >> password;

        ifstream file("database.txt");
        string u, p;
        while (file >> u >> p) 
		{
            if (p == password) 
			{
                cout << "\nYour password is found in the database\n";
                cout << "Your ID is: " << u << endl;
                file.close();
                return;
            }
        }
        file.close();
        cout << "Sorry, we cannot find your password in our database\n";
        
    }
   
};
int main() 
{
    login_and_register obj;
    obj.run();
    return 0;
}

