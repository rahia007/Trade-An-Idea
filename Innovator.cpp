#include "Innovator.h"
#include "Evaluation.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
using namespace std;

Innovator::Innovator() : User() {
    ideaCount = 0;
    for (int i = 0; i < MAX_IDEAS; i++) {
        myIdeas[i] = nullptr;
    }
}

Innovator::Innovator(string uname, string pwd, string email) 
    : User(uname, pwd, email) {
    ideaCount = 0;
    for (int i = 0; i < MAX_IDEAS; i++) {
        myIdeas[i] = nullptr;
    }
}

Innovator::~Innovator() {
    for (int i = 0; i < ideaCount; i++) {
        if (myIdeas[i] != nullptr) {
            delete myIdeas[i];
        }
    }
}

void Innovator::displayMenu() {
    int choice;
    do {
        cout << "\n========== INNOVATOR MENU ==========" << endl;
        cout << "Welcome, " << username << "!" << endl;
        cout << "1. Post New Idea" << endl;
        cout << "2. View My Ideas" << endl;
        cout << "3. View Idea Evaluation" << endl;
        cout << "4. Display My Info" << endl;
        cout << "5. Logout" << endl;
        cout << "=====================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1:
                postIdea();
                break;
            case 2:
                viewMyIdeas();
                break;
            case 3:
                IdeaEvaluator::evaluateMyIdeas(this);
                break;
            case 4:
                displayInfo();
                break;
            case 5:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 5);
}

void Innovator::displayInfo() const {
    User::displayInfo();
    cout << "Role: Innovator" << endl;
    cout << "Total Ideas Posted: " << ideaCount << endl;
}

void Innovator::postIdea() {
    if (ideaCount >= MAX_IDEAS) {
        cout << "Cannot post more ideas! Maximum limit reached." << endl;
        return;
    }
    
    string title, description, category;
    double estimatedValue;
    
    cout << "\n--- Post New Idea ---" << endl;
    cout << "Title: ";
    getline(cin, title);
    cout << "Description: ";
    getline(cin, description);
    cout << "Category (Tech/Health/Education/Business/Other): ";
    getline(cin, category);
    cout << "Estimated Value ($): ";
    cin >> estimatedValue;
    cin.ignore();
    
    Idea* newIdea = new Idea(title, description, category, estimatedValue, username);
    myIdeas[ideaCount++] = newIdea;
    newIdea->saveToFile();
    
    cout << "\nIdea posted successfully! Idea ID: " << newIdea->getIdeaID() << endl;
}

void Innovator::viewMyIdeas() {
    if (ideaCount == 0) {
        cout << "\nYou haven't posted any ideas yet!" << endl;
        return;
    }
    
    cout << "\n=== My Ideas ===" << endl;
    for (int i = 0; i < ideaCount; i++) {
        myIdeas[i]->displayInfo();
        cout << "------------------------" << endl;
    }
}

void Innovator::addIdea(Idea* idea) {
    if (ideaCount < MAX_IDEAS) {
        myIdeas[ideaCount++] = idea;
    }
}

Idea* Innovator::getIdeaAt(int index) {
    if (index >= 0 && index < ideaCount) {
        return myIdeas[index];
    }
    return nullptr;
}

int Innovator::getIdeaCount() const {
    return ideaCount;
}

void Innovator::saveInnovatorsToFile(Innovator** innovators, int count) {
    ofstream file("innovators.txt");
    if (!file.is_open()) {
        cout << "Error opening innovators.txt for writing!" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << innovators[i]->getUserID() << endl;
        file << innovators[i]->getUsername() << endl;
        file << innovators[i]->getPassword() << endl;
        file << innovators[i]->getEmail() << endl;
    }
    file.close();
}

void Innovator::loadInnovatorsFromFile(Innovator** innovators, int& count, int maxCount) {
    ifstream file("innovators.txt");
    if (!file.is_open()) {
        return;
    }
    
    int id, maxID = 1000;
    string uname, pwd, email;
    
    while (file >> id && count < maxCount) {
        file.ignore();
        getline(file, uname);
        getline(file, pwd);
        getline(file, email);
        
        innovators[count] = new Innovator(uname, pwd, email);
        count++;
        
        if (id > maxID) maxID = id;
    }
    User::setNextID(maxID + 1);
    file.close();
}
#include "Innovator.h"
