#ifndef INVESTOR_H
#define INVESTOR_H

#include "User.h"
#include "Idea.h"
#include "Interest.h"

const int MAX_INTERESTS = 50;

class Investor : public User {
private:
    Interest* myInterests[MAX_INTERESTS];
    int interestCount;
    
public:
    Investor();
    Investor(string uname, string pwd, string email);
    ~Investor();
    
    void displayMenu() override;
    void displayInfo() const override;
    
    // Investor specific methods
    void browseAllIdeas(Idea** allIdeas, int ideaCount);
    void searchFilterIdeas(Idea** allIdeas, int ideaCount);
    void showInterestInIdea(Idea** allIdeas, int ideaCount);
    void viewMyInterests();
    void addInterest(Interest* interest);
    Interest* getInterestAt(int index);
    int getInterestCount() const;
    
    // Save/Load - MATCHING signatures
    static void saveInvestorsToFile(Investor** investors, int count);
    static void loadInvestorsFromFile(Investor** investors, int& count, int maxCount);
};

#endif
#ifndef INVESTOR_H
#define INVESTOR_H

class Investor
{
	public:
	protected:
};

#endif
