#ifndef INNOVATOR_H
#define INNOVATOR_H

#include "User.h"
#include "Idea.h"

// Maximum ideas an innovator can have (dynamic array size)
const int MAX_IDEAS = 50;

class Innovator : public User {
private:
    Idea* myIdeas[MAX_IDEAS];  // Dynamic array of pointers
    int ideaCount;
    
public:
    Innovator();
    Innovator(string uname, string pwd, string email);
    ~Innovator();
    
    // Override virtual functions (Polymorphism)
    void displayMenu() override;
    void displayInfo() const override;
    
    // Innovator specific methods
    void postIdea();
    void viewMyIdeas();
    void addIdea(Idea* idea);
    Idea* getIdeaAt(int index);
    int getIdeaCount() const;
    
    // Save/Load - MATCHING signatures
    static void saveInnovatorsToFile(Innovator** innovators, int count);
    static void loadInnovatorsFromFile(Innovator** innovators, int& count, int maxCount);
};

#endif
#ifndef INNOVATOR_H
#define INNOVATOR_H

class Innovator
{
	public:
	protected:
};

#endif
