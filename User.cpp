#include "User.h"
#include <iostream>
using namespace std;

int User::nextID = 1000;

User::User() {
    username = "";
    password = "";
    email = "";
    userID = nextID++;
}

User::User(string uname, string pwd, string em) {
    username = uname;
    password = pwd;
    email = em;
    userID = nextID++;
}

User::~User() {
    // Virtual destructor
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

string User::getEmail() const {
    return email;
}

int User::getUserID() const {
    return userID;
}

void User::setUsername(string uname) {
    username = uname;
}

void User::setPassword(string pwd) {
    password = pwd;
}

void User::setEmail(string email) {
    this->email = email;
}

void User::displayInfo() const {
    cout << "User ID: " << userID << endl;
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
}

int User::getNextID() {
    return nextID;
}

void User::setNextID(int id) {
    nextID = id;
}
#include "User.h"
