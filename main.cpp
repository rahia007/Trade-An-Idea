#include <iostream>
#include <fstream>
#include <cstring>
#include "User.h"
#include "Innovator.h"
#include "Investor.h"
#include "Idea.h"
#include "Interest.h"
#include "Evaluation.h"

using namespace std;

// Constants for array sizes
const int MAX_INNOVATORS = 50;
const int MAX_INVESTORS = 50;

// Global arrays to store active users (using dynamic memory - NO VECTORS)
Innovator* innovators[MAX_INNOVATORS];
Investor* investors[MAX_INVESTORS];
int innovatorCount = 0;
int investorCount = 0;
User* currentUser = nullptr;

// Function prototypes
void loadAllData();
void saveAllData();
void clearAllData();
void signUp();
void login();
void displayMainMenu();
bool usernameExists(const string& username);

int main() {
    cout << "========================================" << endl;
    cout << "   WELCOME TO IDEA MARKETPLACE SYSTEM   " << endl;
    cout << "========================================" << endl;
    
    // Initialize arrays to nullptr
    for (int i = 0; i < MAX_INNOVATORS; i++) innovators[i] = nullptr;
    for (int i = 0; i < MAX_INVESTORS; i++) investors[i] = nullptr;
    
    loadAllData();
    
    int choice;
    do {
        displayMainMenu();
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                signUp();
                break;
            case 2:
                login();
                break;
            case 3:
                cout << "\nThank you for using Idea Marketplace System!" << endl;
                saveAllData();
                clearAllData();
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while(choice != 3);
    
    return 0;
}

void displayMainMenu() {
    cout << "\n========== MAIN MENU ==========" << endl;
    cout << "1. Sign Up" << endl;
    cout << "2. Login" << endl;
    cout << "3. Exit" << endl;
    cout << "================================" << endl;
}

bool usernameExists(const string& username) {
    for (int i = 0; i < innovatorCount; i++) {
        if (innovators[i] != nullptr && innovators[i]->getUsername() == username) {
            return true;
        }
    }
    for (int i = 0; i < investorCount; i++) {
        if (investors[i] != nullptr && investors[i]->getUsername() == username) {
            return true;
        }
    }
    return false;
}

void signUp() {
    string username, password, email;
    int userType;
    
    cout << "\n--- Sign Up ---" << endl;
    cout << "Username: ";
    getline(cin, username);
    
    if (usernameExists(username)) {
        cout << "Username already exists!" << endl;
        return;
    }
    
    cout << "Password: ";
    getline(cin, password);
    cout << "Email: ";
    getline(cin, email);
    cout << "User Type (1: Innovator, 2: Investor): ";
    cin >> userType;
    cin.ignore();
    
    if (userType == 1) {
        if (innovatorCount < MAX_INNOVATORS) {
            innovators[innovatorCount] = new Innovator(username, password, email);
            innovatorCount++;
            cout << "\nInnovator account created successfully!" << endl;
        } else {
            cout << "Maximum innovator limit reached!" << endl;
        }
    } else if (userType == 2) {
        if (investorCount < MAX_INVESTORS) {
            investors[investorCount] = new Investor(username, password, email);
            investorCount++;
            cout << "\nInvestor account created successfully!" << endl;
        } else {
            cout << "Maximum investor limit reached!" << endl;
        }
    } else {
        cout << "Invalid user type!" << endl;
    }
}

void login() {
    string username, password;
    
    cout << "\n--- Login ---" << endl;
    cout << "Username: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);
    
    for (int i = 0; i < innovatorCount; i++) {
        if (innovators[i] != nullptr && 
            innovators[i]->getUsername() == username && 
            innovators[i]->getPassword() == password) {
            currentUser = innovators[i];
            cout << "\nLogin successful! Welcome " << username << "!" << endl;
            currentUser->displayMenu();
            currentUser = nullptr;
            return;
        }
    }
    
    for (int i = 0; i < investorCount; i++) {
        if (investors[i] != nullptr && 
            investors[i]->getUsername() == username && 
            investors[i]->getPassword() == password) {
            currentUser = investors[i];
            cout << "\nLogin successful! Welcome " << username << "!" << endl;
            currentUser->displayMenu();
            currentUser = nullptr;
            return;
        }
    }
    
    cout << "Invalid username or password!" << endl;
}

void loadAllData() {
    int tempMaxInnovators = MAX_INNOVATORS;  // Create a non-const copy
    int tempMaxInvestors = MAX_INVESTORS;    // Create a non-const copy
    
    Innovator::loadInnovatorsFromFile(innovators, innovatorCount, tempMaxInnovators);
    Investor::loadInvestorsFromFile(investors, investorCount, tempMaxInvestors);
    
    Idea* allIdeas[100];
    int ideaCount = 0;
    Idea::loadIdeasFromFile(allIdeas, ideaCount, 100);
    
    for (int i = 0; i < ideaCount; i++) {
        string poster = allIdeas[i]->getPostedBy();
        for (int j = 0; j < innovatorCount; j++) {
            if (innovators[j] != nullptr && innovators[j]->getUsername() == poster) {
                innovators[j]->addIdea(allIdeas[i]);
                break;
            }
        }
    }
    
    Interest* allInterests[100];
    int interestCount = 0;
    Interest::loadInterestsFromFile(allInterests, interestCount, 100);
    
    for (int i = 0; i < interestCount; i++) {
        string investorName = allInterests[i]->getInvestorName();
        for (int j = 0; j < investorCount; j++) {
            if (investors[j] != nullptr && investors[j]->getUsername() == investorName) {
                investors[j]->addInterest(allInterests[i]);
                break;
            }
        }
    }
    
    cout << "Data loaded successfully!" << endl;
    cout << "Innovators: " << innovatorCount << ", Investors: " << investorCount << endl;
}

void saveAllData() {
    Innovator::saveInnovatorsToFile(innovators, innovatorCount);
    Investor::saveInvestorsToFile(investors, investorCount);
    
    Idea* allIdeas[500];
    int ideaCount = 0;
    for (int i = 0; i < innovatorCount; i++) {
        for (int j = 0; j < innovators[i]->getIdeaCount(); j++) {
            allIdeas[ideaCount++] = innovators[i]->getIdeaAt(j);
        }
    }
    Idea::saveAllIdeasToFile(allIdeas, ideaCount);
    
    Interest* allInterests[500];
    int interestCount = 0;
    for (int i = 0; i < investorCount; i++) {
        for (int j = 0; j < investors[i]->getInterestCount(); j++) {
            allInterests[interestCount++] = investors[i]->getInterestAt(j);
        }
    }
    Interest::saveAllInterestsToFile(allInterests, interestCount);
    
    cout << "All data saved successfully!" << endl;
}

void clearAllData() {
    for (int i = 0; i < innovatorCount; i++) {
        if (innovators[i] != nullptr) {
            delete innovators[i];
            innovators[i] = nullptr;
        }
    }
    
    for (int i = 0; i < investorCount; i++) {
        if (investors[i] != nullptr) {
            delete investors[i];
            investors[i] = nullptr;
        }
    }
    
    innovatorCount = 0;
    investorCount = 0;
    
    cout << "Memory cleaned up successfully!" << endl;
}
