#ifndef EVALUATION_H
#define EVALUATION_H

#include "Innovator.h"
#include "Idea.h"
#include <string>
using namespace std;

// Forward declaration
class Innovator;

// Abstract base class for Evaluation System (Abstraction)
class Evaluator {
public:
    virtual int evaluateIdea(Idea* idea) = 0;  // Pure virtual function
    virtual string getUserLevel(int score) = 0;
    virtual ~Evaluator() {}
};

// Concrete implementation of Evaluator
class IdeaEvaluator : public Evaluator {
public:
    int evaluateIdea(Idea* idea) override;
    string getUserLevel(int score) override;
    
    // Static helper methods
    static void evaluateMyIdeas(Innovator* innovator);
    static string getLevelFromScore(int score);  // Made static
};

#endif
#ifndef EVALUATION_H
#define EVALUATION_H

class Evaluation
{
	public:
	protected:
};

#endif
