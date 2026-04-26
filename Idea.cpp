#include "Idea.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int Idea::nextID = 2000;

Idea::Idea() {
    ideaID = nextID++;
    title = "";
    description = "";
    category = "";
    estimatedValue = 0;
    postedBy = "";
    status = "Active";
}

Idea::Idea(string tit, string desc, string cat, double value, string poster) {
    ideaID = nextID++;
    title = tit;
    description = desc;
    category = cat;
    estimatedValue = value;
    postedBy = poster;
    status = "Active";
}

Idea::~Idea() {}

int Idea::getIdeaID() const { return ideaID; }
string Idea::getTitle() const { return title; }
string Idea::getDescription() const { return description; }
string Idea::getCategory() const { return category; }
double Idea::getEstimatedValue() const { return estimatedValue; }
string Idea::getPostedBy() const { return postedBy; }
string Idea::getStatus() const { return status; }

void Idea::setStatus(string newStatus) {
    status = newStatus;
}

void Idea::displayInfo() const {
    cout << "Idea ID: " << ideaID << endl;
    cout << "Title: " << title << endl;
    cout << "Description: " << description << endl;
    cout << "Category: " << category << endl;
    cout << "Estimated Value: $" << estimatedValue << endl;
    cout << "Posted by: " << postedBy << endl;
    cout << "Status: " << status << endl;
}

void Idea::saveToFile() const {
    ofstream file("ideas.txt", ios::app);
    if (file.is_open()) {
        file << ideaID << endl;
        file << title << endl;
        file << description << endl;
        file << category << endl;
        file << estimatedValue << endl;
        file << postedBy << endl;
        file << status << endl;
        file.close();
    }
}

void Idea::loadIdeasFromFile(Idea** ideas, int& count, int maxCount) {
    ifstream file("ideas.txt");
    if (!file.is_open()) {
        return;
    }
    
    int id, maxID = 2000;
    string title, desc, category, postedBy, status;
    double value;
    
    while (file >> id && count < maxCount) {
        file.ignore();
        getline(file, title);
        getline(file, desc);
        getline(file, category);
        file >> value;
        file.ignore();
        getline(file, postedBy);
        getline(file, status);
        
        Idea* idea = new Idea();
        idea->ideaID = id;
        idea->title = title;
        idea->description = desc;
        idea->category = category;
        idea->estimatedValue = value;
        idea->postedBy = postedBy;
        idea->status = status;
        ideas[count++] = idea;
        
        if (id > maxID) maxID = id;
    }
    Idea::nextID = maxID + 1;
    file.close();
}

void Idea::saveAllIdeasToFile(Idea** ideas, int count) {
    ofstream file("ideas.txt");
    if (!file.is_open()) {
        cout << "Error opening ideas.txt for writing!" << endl;
        return;
    }
    
    for (int i = 0; i < count; i++) {
        file << ideas[i]->ideaID << endl;
        file << ideas[i]->title << endl;
        file << ideas[i]->description << endl;
        file << ideas[i]->category << endl;
        file << ideas[i]->estimatedValue << endl;
        file << ideas[i]->postedBy << endl;
        file << ideas[i]->status << endl;
    }
    file.close();
}

int Idea::getNextID() { return nextID; }
void Idea::setNextID(int id) { nextID = id; }
#include "Idea.h"
