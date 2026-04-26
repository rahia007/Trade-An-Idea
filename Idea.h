#ifndef IDEA_H
#define IDEA_H

#include <string>
using namespace std;

class Idea {
private:
    int ideaID;
    string title;
    string description;
    string category;
    double estimatedValue;
    string postedBy;  // username of innovator
    string status;    // Active, Interested, Funded, Withdrawn
    static int nextID;
    
public:
    Idea();
    Idea(string title, string desc, string category, double value, string poster);
    ~Idea();
    
    // Getters
    int getIdeaID() const;
    string getTitle() const;
    string getDescription() const;
    string getCategory() const;
    double getEstimatedValue() const;
    string getPostedBy() const;
    string getStatus() const;
    
    // Setters
    void setStatus(string newStatus);
    
    void displayInfo() const;
    
    // File handling
    void saveToFile() const;
    static void loadIdeasFromFile(Idea** ideas, int& count, int maxCount);
    static void saveAllIdeasToFile(Idea** ideas, int count);
    static int getNextID();
    static void setNextID(int id);
};

#endif
#ifndef IDEA_H
#define IDEA_H

class Idea
{
	public:
	protected:
};

#endif
