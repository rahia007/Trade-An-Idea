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
    
//    loadAllData(); //returns a string describing WHAT error occurred
      try {
        loadAllData();
    }
    catch (const exception& e) {
        cout << "Error loading data: " << e.what() << endl;
        cout << "Starting with empty database..." << endl;
    }
    
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


/*
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <limits>
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

// Custom exception classes
class FileOperationException : public exception {
private:
    string message;
public:
    FileOperationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class MemoryAllocationException : public exception {
private:
    string message;
public:
    MemoryAllocationException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class UserNotFoundException : public exception {
private:
    string message;
public:
    UserNotFoundException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidInputException : public exception {
private:
    string message;
public:
    InvalidInputException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class ArrayFullException : public exception {
private:
    string message;
public:
    ArrayFullException(const string& msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

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
int getValidatedIntInput(int min, int max, const string& prompt);
double getValidatedDoubleInput(double min, double max, const string& prompt);
string getValidatedStringInput(const string& prompt, bool allowEmpty = false);

int main() {
    try {
        cout << "========================================" << endl;
        cout << "   WELCOME TO IDEA MARKETPLACE SYSTEM   " << endl;
        cout << "========================================" << endl;
        
        // Initialize arrays to nullptr with exception handling
        try {
            for (int i = 0; i < MAX_INNOVATORS; i++) innovators[i] = nullptr;
            for (int i = 0; i < MAX_INVESTORS; i++) investors[i] = nullptr;
        } catch (const bad_alloc& e) {
            throw MemoryAllocationException("Failed to initialize memory arrays: " + string(e.what()));
        }
        
        // Load data with exception handling
        try {
            loadAllData();
        } catch (const FileOperationException& e) {
            cerr << "Warning: Could not load previous data. Starting with empty database." << endl;
            cerr << "Reason: " << e.what() << endl;
            // Continue execution with empty database
        }
        
        int choice;
        do {
            try {
                displayMainMenu();
                choice = getValidatedIntInput(1, 3, "Enter choice: ");
                
                switch(choice) {
                    case 1:
                        signUp();
                        break;
                    case 2:
                        login();
                        break;
                    case 3:
                        cout << "\nThank you for using Idea Marketplace System!" << endl;
                        try {
                            saveAllData();
                        } catch (const FileOperationException& e) {
                            cerr << "Error saving data: " << e.what() << endl;
                            cout << "Do you want to exit anyway? (y/n): ";
                            char response;
                            cin >> response;
                            if (response != 'y' && response != 'Y') {
                                choice = 0; // Don't exit
                                continue;
                            }
                        }
                        clearAllData();
                        break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                }
            } catch (const InvalidInputException& e) {
                cerr << "Input Error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Press Enter to continue..." << endl;
                cin.get();
            } catch (const exception& e) {
                cerr << "Unexpected error: " << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Press Enter to continue..." << endl;
                cin.get();
            }
        } while(choice != 3);
        
    } catch (const MemoryAllocationException& e) {
        cerr << "Fatal Error: " << e.what() << endl;
        cerr << "System cannot start. Exiting..." << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "Fatal Error: " << e.what() << endl;
        cerr << "System encountered a fatal error. Exiting..." << endl;
        return 1;
    }
    
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
    if (username.empty()) {
        throw InvalidInputException("Username cannot be empty");
    }
    
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

// Input validation functions
int getValidatedIntInput(int min, int max, const string& prompt) {
    int value;
    cout << prompt;
    
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException("Invalid integer input. Please enter a number.");
    }
    
    cin.ignore();
    
    if (value < min || value > max) {
        throw InvalidInputException("Input out of range. Expected between " + 
                                    to_string(min) + " and " + to_string(max));
    }
    
    return value;
}

double getValidatedDoubleInput(double min, double max, const string& prompt) {
    double value;
    cout << prompt;
    
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw InvalidInputException("Invalid numeric input. Please enter a valid number.");
    }
    
    cin.ignore();
    
    if (value < min || value > max) {
        throw InvalidInputException("Input out of range. Expected between " + 
                                    to_string(min) + " and " + to_string(max));
    }
    
    return value;
}

string getValidatedStringInput(const string& prompt, bool allowEmpty) {
    string value;
    cout << prompt;
    getline(cin, value);
    
    if (!allowEmpty && value.empty()) {
        throw InvalidInputException("Input cannot be empty. Please enter a valid value.");
    }
    
    return value;
}

void signUp() {
    try {
        string username, password, email;
        int userType;
        
        cout << "\n--- Sign Up ---" << endl;
        username = getValidatedStringInput("Username: ", false);
        
        if (usernameExists(username)) {
            throw UserNotFoundException("Username already exists! Please choose a different username.");
        }
        
        password = getValidatedStringInput("Password: ", false);
        
        if (password.length() < 4) {
            throw InvalidInputException("Password must be at least 4 characters long.");
        }
        
        email = getValidatedStringInput("Email: ", false);
        
        // Basic email validation
        if (email.find('@') == string::npos || email.find('.') == string::npos) {
            throw InvalidInputException("Invalid email format. Email should contain '@' and '.'");
        }
        
        userType = getValidatedIntInput(1, 2, "User Type (1: Innovator, 2: Investor): ");
        
        if (userType == 1) {
            if (innovatorCount >= MAX_INNOVATORS) {
                throw ArrayFullException("Maximum innovator limit (" + to_string(MAX_INNOVATORS) + ") reached!");
            }
            
            innovators[innovatorCount] = new Innovator(username, password, email);
            if (innovators[innovatorCount] == nullptr) {
                throw MemoryAllocationException("Failed to allocate memory for new Innovator");
            }
            innovatorCount++;
            cout << "\nInnovator account created successfully!" << endl;
            
        } else if (userType == 2) {
            if (investorCount >= MAX_INVESTORS) {
                throw ArrayFullException("Maximum investor limit (" + to_string(MAX_INVESTORS) + ") reached!");
            }
            
            investors[investorCount] = new Investor(username, password, email);
            if (investors[investorCount] == nullptr) {
                throw MemoryAllocationException("Failed to allocate memory for new Investor");
            }
            investorCount++;
            cout << "\nInvestor account created successfully!" << endl;
        }
        
    } catch (const UserNotFoundException& e) {
        cerr << "Sign Up Error: " << e.what() << endl;
    } catch (const InvalidInputException& e) {
        cerr << "Input Error: " << e.what() << endl;
    } catch (const ArrayFullException& e) {
        cerr << "System Limit Error: " << e.what() << endl;
    } catch (const MemoryAllocationException& e) {
        cerr << "Memory Error: " << e.what() << endl;
        throw; // Re-throw critical error
    }
}

void login() {
    try {
        string username, password;
        
        cout << "\n--- Login ---" << endl;
        username = getValidatedStringInput("Username: ", false);
        password = getValidatedStringInput("Password: ", false);
        
        bool found = false;
        
        // Check innovators
        for (int i = 0; i < innovatorCount; i++) {
            if (innovators[i] != nullptr && 
                innovators[i]->getUsername() == username && 
                innovators[i]->getPassword() == password) {
                currentUser = innovators[i];
                cout << "\nLogin successful! Welcome " << username << "!" << endl;
                currentUser->displayMenu();
                currentUser = nullptr;
                found = true;
                return;
            }
        }
        
        // Check investors
        for (int i = 0; i < investorCount; i++) {
            if (investors[i] != nullptr && 
                investors[i]->getUsername() == username && 
                investors[i]->getPassword() == password) {
                currentUser = investors[i];
                cout << "\nLogin successful! Welcome " << username << "!" << endl;
                currentUser->displayMenu();
                currentUser = nullptr;
                found = true;
                return;
            }
        }
        
        if (!found) {
            throw UserNotFoundException("Invalid username or password!");
        }
        
    } catch (const UserNotFoundException& e) {
        cerr << "Login Error: " << e.what() << endl;
        cout << "Please check your credentials and try again." << endl;
    } catch (const InvalidInputException& e) {
        cerr << "Input Error: " << e.what() << endl;
    }
}

void loadAllData() {
    try {
        int tempMaxInnovators = MAX_INNOVATORS;
        int tempMaxInvestors = MAX_INVESTORS;
        
        // Load users with exception handling
        try {
            Innovator::loadInnovatorsFromFile(innovators, innovatorCount, tempMaxInnovators);
            Investor::loadInvestorsFromFile(investors, investorCount, tempMaxInvestors);
        } catch (const ifstream::failure& e) {
            throw FileOperationException("Failed to read user data file: " + string(e.what()));
        }
        
        // Load ideas
        Idea* allIdeas[100];
        int ideaCount = 0;
        
        try {
            Idea::loadIdeasFromFile(allIdeas, ideaCount, 100);
        } catch (const ifstream::failure& e) {
            throw FileOperationException("Failed to read ideas data file: " + string(e.what()));
        }
        
        // Associate ideas with innovators
        for (int i = 0; i < ideaCount; i++) {
            if (allIdeas[i] == nullptr) {
                throw MemoryAllocationException("Null idea pointer encountered during loading");
            }
            
            string poster = allIdeas[i]->getPostedBy();
            bool found = false;
            
            for (int j = 0; j < innovatorCount; j++) {
                if (innovators[j] != nullptr && innovators[j]->getUsername() == poster) {
                    innovators[j]->addIdea(allIdeas[i]);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                // Innovator not found - delete orphaned idea
                delete allIdeas[i];
                allIdeas[i] = nullptr;
            }
        }
        
        // Load interests
        Interest* allInterests[100];
        int interestCount = 0;
        
        try {
            Interest::loadInterestsFromFile(allInterests, interestCount, 100);
        } catch (const ifstream::failure& e) {
            throw FileOperationException("Failed to read interests data file: " + string(e.what()));
        }
        
        // Associate interests with investors
        for (int i = 0; i < interestCount; i++) {
            if (allInterests[i] == nullptr) {
                throw MemoryAllocationException("Null interest pointer encountered during loading");
            }
            
            string investorName = allInterests[i]->getInvestorName();
            bool found = false;
            
            for (int j = 0; j < investorCount; j++) {
                if (investors[j] != nullptr && investors[j]->getUsername() == investorName) {
                    investors[j]->addInterest(allInterests[i]);
                    found = true;
                    break;
                }
            }
            
            if (!found) {
                // Investor not found - delete orphaned interest
                delete allInterests[i];
                allInterests[i] = nullptr;
            }
        }
        
        cout << "Data loaded successfully!" << endl;
        cout << "Innovators: " << innovatorCount << ", Investors: " << investorCount << endl;
        
    } catch (const FileOperationException& e) {
        cerr << "Data Loading Warning: " << e.what() << endl;
        throw; // Re-throw to let main handle it
    } catch (const MemoryAllocationException& e) {
        cerr << "Memory Error during loading: " << e.what() << endl;
        throw;
    }
}

void saveAllData() {
    try {
        // Save users
        try {
            Innovator::saveInnovatorsToFile(innovators, innovatorCount);
            Investor::saveInvestorsToFile(investors, investorCount);
        } catch (const ofstream::failure& e) {
            throw FileOperationException("Failed to save user data: " + string(e.what()));
        }
        
        // Collect all ideas
        Idea* allIdeas[500];
        int ideaCount = 0;
        
        for (int i = 0; i < innovatorCount; i++) {
            if (innovators[i] != nullptr) {
                for (int j = 0; j < innovators[i]->getIdeaCount(); j++) {
                    if (ideaCount >= 500) {
                        throw ArrayFullException("Too many ideas to save (max 500)");
                    }
                    Idea* idea = innovators[i]->getIdeaAt(j);
                    if (idea != nullptr) {
                        allIdeas[ideaCount++] = idea;
                    }
                }
            }
        }
        
        // Save ideas
        try {
            Idea::saveAllIdeasToFile(allIdeas, ideaCount);
        } catch (const ofstream::failure& e) {
            throw FileOperationException("Failed to save ideas data: " + string(e.what()));
        }
        
        // Collect all interests
        Interest* allInterests[500];
        int interestCount = 0;
        
        for (int i = 0; i < investorCount; i++) {
            if (investors[i] != nullptr) {
                for (int j = 0; j < investors[i]->getInterestCount(); j++) {
                    if (interestCount >= 500) {
                        throw ArrayFullException("Too many interests to save (max 500)");
                    }
                    Interest* interest = investors[i]->getInterestAt(j);
                    if (interest != nullptr) {
                        allInterests[interestCount++] = interest;
                    }
                }
            }
        }
        
        // Save interests
        try {
            Interest::saveAllInterestsToFile(allInterests, interestCount);
        } catch (const ofstream::failure& e) {
            throw FileOperationException("Failed to save interests data: " + string(e.what()));
        }
        
        cout << "All data saved successfully!" << endl;
        
    } catch (const FileOperationException& e) {
        cerr << "Save Error: " << e.what() << endl;
        throw;
    } catch (const ArrayFullException& e) {
        cerr << "Save Error: " << e.what() << endl;
        throw FileOperationException("Cannot save: " + string(e.what()));
    }
}

void clearAllData() {
    try {
        // Delete innovators
        for (int i = 0; i < innovatorCount; i++) {
            if (innovators[i] != nullptr) {
                delete innovators[i];
                innovators[i] = nullptr;
            }
        }
        
        // Delete investors
        for (int i = 0; i < investorCount; i++) {
            if (investors[i] != nullptr) {
                delete investors[i];
                investors[i] = nullptr;
            }
        }
        
        innovatorCount = 0;
        investorCount = 0;
        
        cout << "Memory cleaned up successfully!" << endl;
        
    } catch (const exception& e) {
        cerr << "Error during cleanup: " << e.what() << endl;
        // Don't throw - cleanup errors shouldn't crash the program
    }
}*/


























