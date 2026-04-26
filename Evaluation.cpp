#include "Evaluation.h"
#include <iostream>
using namespace std;

int IdeaEvaluator::evaluateIdea(Idea* idea) {
    int score = 0;
    string desc = idea->getDescription();
    
    // Rule 1: Score based on description length (1-5 points)
    int descLength = desc.length();
    if (descLength >= 200) score += 5;
    else if (descLength >= 100) score += 4;
    else if (descLength >= 50) score += 3;
    else if (descLength >= 20) score += 2;
    else if (descLength > 0) score += 1;
    
    // Rule 2: Score based on estimated value (1-3 points)
    double value = idea->getEstimatedValue();
    if (value >= 100000) score += 3;
    else if (value >= 50000) score += 2;
    else if (value >= 10000) score += 1;
    
    // Rule 3: Score based on category relevance (1-2 points)
    string category = idea->getCategory();
    if (category == "Tech" || category == "Health") score += 2;
    else if (category == "Education" || category == "Business") score += 1;
    
    // Ensure score is between 1 and 10
    if (score < 1) score = 1;
    if (score > 10) score = 10;
    
    return score;
}

string IdeaEvaluator::getUserLevel(int score) {
    if (score >= 8) return "Expert";
    else if (score >= 5) return "Intermediate";
    else return "Beginner";
}

string IdeaEvaluator::getLevelFromScore(int score) {
    if (score >= 8) return "Expert";
    else if (score >= 5) return "Intermediate";
    else return "Beginner";
}

void IdeaEvaluator::evaluateMyIdeas(Innovator* innovator) {
    int ideaCount = innovator->getIdeaCount();
    
    if (ideaCount == 0) {
        cout << "\nYou have no ideas to evaluate!" << endl;
        return;
    }
    
    IdeaEvaluator evaluator;
    cout << "\n=== Idea Evaluation Report ===" << endl;
    cout << "Innovator: " << innovator->getUsername() << endl;
    cout << "=================================" << endl;
    
    int totalScore = 0;
    int bestScore = 0;
    string bestIdea = "";
    
    for (int i = 0; i < ideaCount; i++) {
        Idea* idea = innovator->getIdeaAt(i);
        int score = evaluator.evaluateIdea(idea);
        totalScore += score;
        
        cout << "\nIdea: " << idea->getTitle() << endl;
        cout << "  Score: " << score << "/10" << endl;
        cout << "  Level: " << evaluator.getUserLevel(score) << endl;  // FIXED: use object
        
        if (score > bestScore) {
            bestScore = score;
            bestIdea = idea->getTitle();
        }
    }
    
    double avgScore = (double)totalScore / ideaCount;
    cout << "\n=================================" << endl;
    cout << "Average Score: " << avgScore << "/10" << endl;
    cout << "Best Idea: " << bestIdea << " (" << bestScore << "/10)" << endl;
    cout << "Innovator Level: " << evaluator.getUserLevel((int)avgScore) << endl;  // FIXED: use object
    cout << "=================================" << endl;
}
#include "Evaluation.h"
