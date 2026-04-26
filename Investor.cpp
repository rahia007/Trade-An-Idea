#include "Investor.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
using namespace std;

Investor::Investor() : User() {
    interestCount = 0;
    for (int i = 0; i < MAX_INTERESTS; i++) {
        myInterests[i] = nullptr;
    }
}

Investor::Investor(string uname, string pwd, string email) 
    : User(uname, pwd, email) {
    interestCount = 0;
    for (int i = 0; i < MAX_INTERESTS; i++) {
        myInterests[i] = nullptr;
    }
}

Investor::~Investor() {
    for (int i = 0; i < interestCount; i++) {
        if (myInterests[i] != nullptr) {
            delete myInterests[i];
        }
    }
}

void Investor::displayMenu() {
    int choice;
    do {
        cout << "\n========== INVESTOR MENU ==========" << endl;
        cout << "Welcome, " << username << "!" << endl;
        cout << "1. Browse All Ideas" << endl;
        cout << "2. Search/Filter Ideas" << endl;
        cout << "3. Show Interest in Idea" << endl;
        cout << "4. View My Interests" << endl;
        cout << "5. Display My Info" << endl;
        cout << "6. Logout" << endl;
        cout << "====================================" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        
        switch(choice) {
            case 1: {
                Idea* allIdeas[100];
                int ideaCount = 0;
                Idea::loadIdeasFromFile(allIdeas, ideaCount, 100);
                browseAllIdeas(allIdeas, ideaCount);
                for (int i = 0; i < ideaCount; i++) delete allIdeas[i];
                break;
            }
            case 2: {
                Idea* allIdeas[100];
                int ideaCount = 0;
                Idea::loadIdeasFromFile(allIdeas, ideaCount, 100);
                searchFilterIdeas(allIdeas, ideaCount);
                for (int i = 0; i < ideaCount; i++) delete allIdeas[i];
                break;
            }
            case 3: {
                Idea* allIdeas[100];
                int ideaCount = 0;
                Idea::loadIdeasFromFile(allIdeas, ideaCount, 100);
                showInterestInIdea(allIdeas, ideaCount);
                for (int i = 0; i < ideaCount; i++) delete allIdeas[i];
                break;
            }
            case 4:
                viewMyInterests();
                break;
            case 5:
                displayInfo();
                break;
            case 6:
                cout << "Logging out..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while(choice != 6);
}

void Investor::displayInfo() const {
    User::displayInfo();
    cout << "Role: Investor" << endl;
    cout << "Total Interests Shown: " << interestCount << endl;
}

void Investor::browseAllIdeas(Idea** allIdeas, int ideaCount) {
    if (ideaCount == 0) {
        cout << "\nNo ideas available yet!" << endl;
        return;
    }
    
    cout << "\n=== All Available Ideas ===" << endl;
    for (int i = 0; i < ideaCount; i++) {
        if (allIdeas[i]->getStatus() != "Withdrawn") {
            allIdeas[i]->displayInfo();
            cout << "------------------------" << endl;
        }
    }
}

void Investor::searchFilterIdeas(Idea** allIdeas, int ideaCount) {
    if (ideaCount == 0) {
        cout << "\nNo ideas available!" << endl;
        return;
    }
    
    int choice;
    cout << "\n=== Search/Filter Options ===" << endl;
    cout << "1. Search by Title" << endl;
    cout << "2. Filter by Category" << endl;
    cout << "3. Filter by Min Estimated Value" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    
    string keyword, category;
    double minValue;
    bool found = false;
    
    switch(choice) {
        case 1:
            cout << "Enter title keyword: ";
            getline(cin, keyword);
            cout << "\n=== Search Results ===" << endl;
            for (int i = 0; i < ideaCount; i++) {
                string title = allIdeas[i]->getTitle();
                for (int j = 0; j < title.length(); j++) title[j] = tolower(title[j]);
                string searchKeyword = keyword;
                for (int j = 0; j < searchKeyword.length(); j++) searchKeyword[j] = tolower(searchKeyword[j]);
                
                if (title.find(searchKeyword) != string::npos && allIdeas[i]->getStatus() != "Withdrawn") {
                    allIdeas[i]->displayInfo();
                    cout << "------------------------" << endl;
                    found = true;
                }
            }
            if (!found) cout << "No ideas found matching '" << keyword << "'" << endl;
            break;
            
        case 2:
            cout << "Enter category (Tech/Health/Education/Business/Other): ";
            getline(cin, category);
            cout << "\n=== Filter Results ===" << endl;
            for (int i = 0; i < ideaCount; i++) {
                if (allIdeas[i]->getCategory() == category && allIdeas[i]->getStatus() != "Withdrawn") {
                    allIdeas[i]->displayInfo();
                    cout << "------------------------" << endl;
                    found = true;
                }
            }
            if (!found) cout << "No ideas found in category '" << category << "'" << endl;
            break;
            
        case 3:
            cout << "Enter minimum estimated value ($): ";
            cin >> minValue;
            cout << "\n=== Filter Results ===" << endl;
            for (int i = 0; i < ideaCount; i++) {
                if (allIdeas[i]->getEstimatedValue() >= minValue && allIdeas[i]->getStatus() != "Withdrawn") {
                    allIdeas[i]->displayInfo();
                    cout << "------------------------" << endl;
                    found = true;
                }
            }
            if (!found) cout << "No ideas found with value >= $" << minValue << endl;
            break;
            
        default:
            cout << "Invalid choice!" << endl;
    }
}

void Investor::showInterestInIdea(Idea** allIdeas, int ideaCount) {
    if (ideaCount == 0) {
        cout << "\nNo ideas available!" << endl;
        return;
    }
    
    int ideaID;
    double offerAmount;
    string message;
    
    browseAllIdeas(allIdeas, ideaCount);
    
    cout << "\nEnter Idea ID to show interest: ";
    cin >> ideaID;
    cin.ignore();
    
    Idea* selectedIdea = nullptr;
    for (int i = 0; i < ideaCount; i++) {
        if (allIdeas[i]->getIdeaID() == ideaID && allIdeas[i]->getStatus() != "Withdrawn") {
            selectedIdea = allIdeas[i];
            break;
        }
    }
    
    if (!selectedIdea) {
        cout << "Invalid Idea ID or idea not available!" << endl;
        return;
    }
    
    cout << "Enter your offer amount ($): ";
    cin >> offerAmount;
    cin.ignore();
    cout << "Enter message to innovator: ";
    getline(cin, message);
    
    Interest* newInterest = new Interest(ideaID, username, offerAmount, message);
    if (interestCount < MAX_INTERESTS) {
        myInterests[interestCount++] = newInterest;
        newInterest->saveToFile();
        cout << "\nInterest shown successfully! The innovator will be notified." << endl;
    } else {
        cout << "Cannot show more interest! Maximum limit reached." << endl;
        delete newInterest;
    }
}

void Investor::viewMyInterests() {
    if (interestCount == 0) {
        cout << "\nYou haven't shown interest in any ideas yet!" << endl;
        return;
    }
    
    cout << "\n=== My Interests ===" << endl;
    for (int i = 0; i < interestCount; i++) {
        myInterests[i]->displayInfo();
        cout << "------------------------" << endl;
    }
}

void Investor::addInterest(Interest* interest) {
    if (interestCount < MAX_INTERESTS) {
        myInterests[interestCount++] = interest;
    }
}

Interest* Investor::getInterestAt(int index) {
    if (index >= 0 && index < interestCount) {
        return myInterests[index];
    }
    return nullptr;
}

int Investor::getInterestCount() const {
    return interestCount;
}

void Investor::saveInvestorsToFile(Investor** investors, int count) {
    ofstream file("investors.txt");
    if (!file.is_open()) {
        cout << "Error opening investors.txt for writing!" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << investors[i]->getUserID() << endl;
        file << investors[i]->getUsername() << endl;
        file << investors[i]->getPassword() << endl;
        file << investors[i]->getEmail() << endl;
    }
    file.close();
}

void Investor::loadInvestorsFromFile(Investor** investors, int& count, int maxCount) {
    ifstream file("investors.txt");
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
        
        investors[count] = new Investor(uname, pwd, email);
        count++;
        
        if (id > maxID) maxID = id;
    }
    User::setNextID(maxID + 1);
    file.close();
}
#include "Investor.h"
