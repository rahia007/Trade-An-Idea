#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

// Abstract base class demonstrating Abstraction
class User {
protected:
    string username;
    string password;
    string email;
    int userID;
    static int nextID;

public:
    User();
    User(string uname, string pwd, string email);
    virtual ~User();
    
    // Getters and Setters (Encapsulation)
    string getUsername() const;
    string getPassword() const;
    string getEmail() const;
    int getUserID() const;
    
    void setUsername(string uname);
    void setPassword(string pwd);
    void setEmail(string email);
    
    // Pure virtual function for Abstraction
    virtual void displayMenu() = 0;
    
    // Virtual function for Polymorphism
    virtual void displayInfo() const;
    
    // Static method to get next ID
    static int getNextID();
    static void setNextID(int id);
};

#endif
#ifndef USER_H
#define USER_H

class User
{
	public:
	protected:
};

#endif
