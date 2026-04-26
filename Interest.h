#ifndef INTEREST_H
#define INTEREST_H

#include <string>
using namespace std;

class Interest {
private:
    int interestID;
    int ideaID;
    string investorName;
    double offerAmount;
    string message;
    string status;  // Pending, Accepted, Rejected
    static int nextID;
    
public:
    Interest();
    Interest(int ideaID, string investor, double amount, string msg);
    ~Interest();
    
    int getInterestID() const;
    int getIdeaID() const;
    string getInvestorName() const;
    double getOfferAmount() const;
    string getMessage() const;
    string getStatus() const;
    
    void setStatus(string newStatus);
    
    void displayInfo() const;
    void saveToFile() const;
    static void loadInterestsFromFile(Interest** interests, int& count, int maxCount);
    static void saveAllInterestsToFile(Interest** interests, int count);
};

#endif
#ifndef INTEREST_H
#define INTEREST_H

class Interest
{
	public:
	protected:
};

#endif
