# Idea Marketplace System

## Project Title
**Idea Marketplace System** - A console-based C++ OOP platform connecting innovators with investors.

## Project Description
The concept of Trade an Idea is an innovative digital platform designed to create a structured system for 
evaluating, exchanging, and developing ideas into real-world outcomes. It is designed to bridge the gap between individuals who have ideas and organizations that need innovation.  Initially, the platform focuses on user who registers, completes an evaluation process, and receives a unique system ID.  
The Idea Marketplace System is a comprehensive console application that serves as a virtual platform where **Innovators** can post their ideas and **Investors** can browse, search, and express interest in promising ideas. The system includes an automated evaluation system that scores ideas based on description length, estimated value, and category relevance, assigning user levels (Beginner, Intermediate, Expert) to innovators.

This project demonstrates key Object-Oriented Programming (OOP) concepts including:
- **Classes and Objects**
- **Encapsulation** (private members with getters/setters)
- **Inheritance** (Innovator and Investor inherit from User)
- **Polymorphism** (virtual functions and function overriding)
- **Abstraction** (abstract base class Evaluator with pure virtual function)
- **File Handling** (persistent storage using text files)
- **Dynamic Memory Management** (using new/delete with vectors)

## Group Members
|      Name      | Student ID |
|----------------|----------|
| Rahia Sarfraz  | 25K-0546 |
| Rumiasa Abassi | 25K-0585 |


## Use Cases

### 1. User Registration (Sign Up)
- **Actor:** New User
- **Description:** User creates a new account as either an Innovator or Investor
- **Precondition:** Username must be unique
- **Postcondition:** New user account is saved to users.txt

### 2. User Login
- **Actor:** Registered User
- **Description:** User logs into the system with username and password
- **Precondition:** User must have a valid registered account
- **Postcondition:** User is granted access to role-specific menu

### 3. Post New Idea (Innovator)
- **Actor:** Innovator
- **Description:** Innovator posts a new idea with title, description, category, and estimated value
- **Precondition:** Innovator must be logged in
- **Postcondition:** New idea is saved to ideas.txt with "Active" status

### 4. Browse and Filter Ideas (Investor)
- **Actor:** Investor
- **Description:** Investor browses all ideas or searches by title, category, or minimum value
- **Precondition:** Investor must be logged in
- **Postcondition:** Filtered list of matching ideas is displayed

### 5. Show Interest in Idea (Investor)
- **Actor:** Investor
- **Description:** Investor expresses interest in an idea by providing offer amount and message
- **Precondition:** Valid idea ID and investor must be logged in
- **Postcondition:** Interest record is saved to interests.txt

### 6. Evaluate Ideas (System + Innovator)
- **Actor:** System, Innovator
- **Description:** System automatically evaluates all ideas of an innovator based on rules (description length, value, category)
- **Precondition:** Innovator must have at least one posted idea
- **Postcondition:** Evaluation report with scores and user level is displayed

### 7. View Own Ideas (Innovator)
- **Actor:** Innovator
- **Description:** Innovator views all ideas they have posted
- **Precondition:** Innovator must be logged in
- **Postcondition:** List of all ideas with details is displayed

### 8. View Interests (Investor)
- **Actor:** Investor
- **Description:** Investor views all interests they have shown
- **Precondition:** Investor must be logged in
- **Postcondition:** List of all interests with status is displayed

## Project Structure
```
IdeaMarketplace/
├── User.h / User.cpp           # Abstract base class for all users
├── Innovator.h / Innovator.cpp # Innovator class (inherits User)
├── Investor.h / Investor.cpp   # Investor class (inherits User)
├── Idea.h / Idea.cpp           # Idea class for marketplace listings
├── Interest.h / Interest.cpp   # Interest class for investor offers
├── Evaluation.h / Evaluation.cpp # Evaluation system (abstraction)
├── main.cpp                    # Entry point and main menu
└── README.md                   # This file
```

## File Handling
The system creates and manages the following text files:
- **users.txt** - Stores user credentials and info (deprecated in favor of separate role files)
- **innovators.txt** - Stores innovator-specific user data
- **investors.txt** - Stores investor-specific user data
- **ideas.txt** - Stores all posted ideas
- **interests.txt** - Stores all investor interests

## Compilation Instructions

### Prerequisites
- C++ compiler with C++11 support or higher (g++, clang++, MSVC)
- Operating System: Windows/Linux/macOS

### Compilation using g++ (Linux/macOS)
```bash
# Navigate to project directory
cd IdeaMarketplace

# Compile all source files
g++ -std=c++11 -o idea_marketplace main.cpp User.cpp Innovator.cpp Investor.cpp Idea.cpp Interest.cpp Evaluation.cpp

# Alternative: Compile with warnings enabled
g++ -std=c++11 -Wall -Wextra -o idea_marketplace *.cpp
```

### Compilation using g++ (Windows with MinGW)
```bash
g++ -std=c++11 -o idea_marketplace.exe main.cpp User.cpp Innovator.cpp Investor.cpp Idea.cpp Interest.cpp Evaluation.cpp
```

### Compilation using Visual Studio (Windows)
```bash
cl /EHsc /std:c++11 main.cpp User.cpp Innovator.cpp Investor.cpp Idea.cpp Interest.cpp Evaluation.cpp
```

## Running the Project

### Execute the compiled program
```bash
# Linux/macOS
./idea_marketplace

# Windows
idea_marketplace.exe
```

### First-time Run
- The program will automatically create necessary data files if they don't exist
- No existing users - you need to sign up first

## Instructions to Use the System

### Main Menu Options
1. **Sign Up** - Create a new account
2. **Login** - Access existing account
3. **Exit** - Save data and exit system

### Sign Up Process
1. Enter desired username (must be unique)
2. Enter password
3. Enter email address
4. Select user type:
   - **1** for Innovator (can post ideas)
   - **2** for Investor (can browse and invest)

### Innovator Menu (After Login)
1. **Post New Idea** - Create and submit a new idea
   - Enter title, description, category, estimated value
   - System assigns unique Idea ID automatically
2. **View My Ideas** - See all ideas you've posted
3. **View Idea Evaluation** - Get AI-like evaluation of your ideas
   - Score (1-10) based on description length, value, category
   - User level: Beginner, Intermediate, or Expert
4. **Display My Info** - View account details
5. **Logout** - Return to main menu

### Investor Menu (After Login)
1. **Browse All Ideas** - View all active ideas in the marketplace
2. **Search/Filter Ideas** - Find specific ideas by:
   - Title keyword
   - Category (Tech, Health, Education, Business, Other)
   - Minimum estimated value
3. **Show Interest in Idea** - Make an offer on an idea
   - Enter Idea ID from browsing results
   - Provide offer amount and message
4. **View My Interests** - See all interests you've submitted
5. **Display My Info** - View account details
6. **Logout** - Return to main menu

### Evaluation Rules (NO AI - Rule-based)
The evaluation system scores ideas using these rules:
- **Description Length** (1-5 points)
  - 200+ characters: 5 points
  - 100-199 characters: 4 points
  - 50-99 characters: 3 points
  - 20-49 characters: 2 points
  - 1-19 characters: 1 point
- **Estimated Value** (1-3 points)
  - $100,000+: 3 points
  - $50,000-$99,999: 2 points
  - $10,000-$49,999: 1 point
- **Category Relevance** (1-2 points)
  - Tech or Health: 2 points
  - Education or Business: 1 point
  - Other: 0 points

**User Levels:**
- **Expert:** Average score 8-10
- **Intermediate:** Average score 5-7
- **Beginner:** Average score 1-4

## Assumptions

1. **Unique Usernames** - The system assumes all usernames are unique across both Innovators and Investors
2. **Case Sensitivity** - Usernames and passwords are case-sensitive
3. **Data Persistence** - All data is saved automatically after each operation
4. **Console Environment** - The system is designed for console/terminal use only
5. **Single Session** - Only one user can be logged in at a time (no concurrent sessions)
6. **Idea Status** - New ideas start with "Active" status
7. **Interest Status** - New interests start with "Pending" status
8. **No Real-time Updates** - Investors must refresh (browse again) to see new ideas

## Limitations

1. **No GUI** - The system uses console-based text interface only
2. **No Networking** - Cannot be accessed remotely; single machine only
3. **No Password Encryption** - Passwords are stored in plain text
4. **Limited Error Recovery** - No automatic data backup or recovery
5. **Simple Evaluation** - Evaluation is rule-based, not using actual AI/ML
6. **No Email Notifications** - No actual communication between users
7. **No Image/File Attachments** - Ideas are text-only
8. **No Rating System** - No peer review or rating of ideas
9. **No Funding Implementation** - No actual money transfer or contract system
10. **No Idea Updates** - Ideas cannot be edited after posting (only status change)
11. **Single Category** - Each idea belongs to exactly one category
12. **No Pagination** - Large lists may cause terminal scrolling

## Future Enhancements 
• AI-Based Idea Evaluation: AI analyzes ideas for feasibility, innovation strength, improvement 
  suggestions, and predicts success probability. 
  
• Smart Matchmaking System: Automatically connects creators, developers, and investors based on 
  idea relevance and skill compatibility. 
  
• Analytics Dashboard: Provides real-time insights into trending ideas, user performance, and 
  investment activity. 
  
• Blockchain Protection: Secures idea ownership using timestamps and smart contracts to prevent 
  plagiarism and ensure transparency. 
  
• Global Expansion Layer: TAI evolves into a global innovation network where companies post real
  world problems, and users compete to solve them, turning innovation into a continuous global 
  marketplace.
  
• Security Enhancements: Implement password hashes instead of plain text to prevent password theft even if database is compromised. Send         verification link during signup to validate email addresses. Reduces fake accounts and enables password recovery features.

• Real Time Notification System: Instant notifications for interests received, responses to offers, and rating updates. Keeps users engaged      without constant checking.

• GUI: Implement an app or website 

• Database Backend: To properly manage and secure data


## Troubleshooting (In Case facing an error)

| Issue | Solution |
|-------|----------|
| Compilation errors | Ensure all .cpp files are included and C++11 or higher is used |
| "File not found" errors | Run program from the correct directory; files will be auto-created |
| Cannot login after registration | Check username/password case sensitivity |
| Ideas not saving | Check write permissions in program directory |
| Memory leaks | The program uses proper destructors; run Valgrind to verify |

## Academic Integrity
This project was developed for educational purposes to demonstrate Object-Oriented Programming concepts. 
## Contact
For questions or support regarding this project:
- Email: rahiasarfraz@gmail.com
- Course: Object-Oriented Programming (OOP)


## VISUAL DEMO (for future implementation)
<img width="942" height="414" alt="image" src="https://github.com/user-attachments/assets/4a6ca9f9-d51d-44d9-bf22-db7e8fd347ce" />

<img width="1018" height="448" alt="image" src="https://github.com/user-attachments/assets/34568402-2ba3-4874-bde3-ff439815bed1" />

<img width="1032" height="621" alt="image" src="https://github.com/user-attachments/assets/1b137441-9ce8-46da-ace4-7dfe693ff4c1" />

<img width="1214" height="581" alt="image" src="https://github.com/user-attachments/assets/d35859fd-796d-45ba-b33d-e6e9bc978dc5" />

---
**© 2024 - Idea Marketplace System - All Rights Reserved**
```


## Complete Project Summary

You now have all **13 files** needed for the complete Idea Marketplace System:
Role-based system (Innovator / Investor)
Idea posting and browsing
Search and filtering functionality
Interest submission system
Evaluation scoring system
File-based data persistence
Proper OOP implementation

| # | File Name | Purpose |
|---|-----------|---------|
| 1 | `User.h` | Abstract base class definition |
| 2 | `User.cpp` | User implementation |
| 3 | `Innovator.h` | Innovator class definition |
| 4 | `Innovator.cpp` | Innovator implementation |
| 5 | `Investor.h` | Investor class definition |
| 6 | `Investor.cpp` | Investor implementation |
| 7 | `Idea.h` | Idea class definition |
| 8 | `Idea.cpp` | Idea implementation |
| 9 | `Interest.h` | Interest class definition |
| 10 | `Interest.cpp` | Interest implementation |
| 11 | `Evaluation.h` | Evaluator abstract class |
| 12 | `Evaluation.cpp` | Rule-based evaluation system |
| 13 | `main.cpp` | Entry point with menus |
| 14 | `README.md` | Documentation |

## Key OOP Concepts Demonstrated

✅ **Encapsulation** - Private members with public getters/setters in all classes  
✅ **Inheritance** - `Innovator` and `Investor` inherit from `User`  
✅ **Polymorphism** - Virtual `displayMenu()` and `displayInfo()` functions overridden in derived classes  
✅ **Abstraction** - `Evaluator` abstract base class with pure virtual `evaluateIdea()` function  
✅ **Dynamic Memory** - Vectors storing pointers with proper `new`/`delete` usage  

## To Compile and Run

```bash
# Save all files in the same directory
g++ -std=c++11 -o marketplace main.cpp User.cpp Innovator.cpp Investor.cpp Idea.cpp Interest.cpp Evaluation.cpp

# Run
./marketplace
```

The system will automatically create data files (`innovators.txt`, `investors.txt`, `ideas.txt`, `interests.txt`) on first run. 
