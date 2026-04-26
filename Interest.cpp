#include "Interest.h"
#include <iostream>
#include <fstream>
using namespace std;

int Interest::nextID = 3000;

Interest::Interest() {
    interestID = nextID++;
    ideaID = 0;
    investorName = "";
    offerAmount = 0;
    message = "";
    status = "Pending";
}

Interest::Interest(int ideaID, string investor, double amount, string msg) {
    interestID = nextID++;
    this->ideaID = ideaID;
    investorName = investor;
    offerAmount = amount;
    message = msg;
    status = "Pending";
}

Interest::~Interest() {}

int Interest::getInterestID() const { return interestID; }
int Interest::getIdeaID() const { return ideaID; }
string Interest::getInvestorName() const { return investorName; }
double Interest::getOfferAmount() const { return offerAmount; }
string Interest::getMessage() const { return message; }
string Interest::getStatus() const { return status; }

void Interest::setStatus(string newStatus) {
    status = newStatus;
}

void Interest::displayInfo() const {
    cout << "Interest ID: " << interestID << endl;
    cout << "Idea ID: " << ideaID << endl;
    cout << "Investor: " << investorName << endl;
    cout << "Offer Amount: $" << offerAmount << endl;
    cout << "Message: " << message << endl;
    cout << "Status: " << status << endl;
}

void Interest::saveToFile() const {
    ofstream file("interests.txt", ios::app);
    if (file.is_open()) {
        file << interestID << endl;
        file << ideaID << endl;
        file << investorName << endl;
        file << offerAmount << endl;
        file << message << endl;
        file << status << endl;
        file.close();
    }
}

void Interest::loadInterestsFromFile(Interest** interests, int& count, int maxCount) {
    ifstream file("interests.txt");
    if (!file.is_open()) {
        return;
    }
    
    int id, ideaID, maxID = 3000;
    string investor, message, status;
    double amount;
    
    while (file >> id && count < maxCount) {
        file >> ideaID;
        file.ignore();
        getline(file, investor);
        file >> amount;
        file.ignore();
        getline(file, message);
        getline(file, status);
        
        Interest* interest = new Interest();
        interest->interestID = id;
        interest->ideaID = ideaID;
        interest->investorName = investor;
        interest->offerAmount = amount;
        interest->message = message;
        interest->status = status;
        interests[count++] = interest;
        
        if (id > maxID) maxID = id;
    }
    Interest::nextID = maxID + 1;
    file.close();
}

void Interest::saveAllInterestsToFile(Interest** interests, int count) {
    ofstream file("interests.txt");
    if (!file.is_open()) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << interests[i]->interestID << endl;
        file << interests[i]->ideaID << endl;
        file << interests[i]->investorName << endl;
        file << interests[i]->offerAmount << endl;
        file << interests[i]->message << endl;
        file << interests[i]->status << endl;
    }
    file.close();
}
#include "Interest.h"
