/*
 * FitZone Gym Management System
 * LLT-1 Project: Application Development Using Design Concepts
 * Language: C++ (Interactive CLI)
 */

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

// ─────────────────────────────────────────────────────────────
//  Utilities
// ─────────────────────────────────────────────────────────────
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\n  Press Enter to continue...";
    cin.get();
}

void printLine(char ch = '-', int n = 60) {
    cout << "  " << string(n, ch) << "\n";
}

void printHeader(const string& title) {
    clearScreen();
    printLine('=');
    cout << "   FITZONE GYM MANAGEMENT SYSTEM\n";
    printLine('=');
    cout << "   >> " << title << "\n";
    printLine();
}

int getIntInput(const string& prompt, int lo, int hi) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= lo && val <= hi) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Invalid. Enter a number between " << lo << " and " << hi << ".\n";
    }
}

float getFloatInput(const string& prompt) {
    float val;
    while (true) {
        cout << prompt;
        if (cin >> val && val > 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  [!] Enter a valid positive number.\n";
    }
}

string getStringInput(const string& prompt) {
    string val;
    cout << prompt;
    getline(cin, val);
    return val;
}

class Person {
private:
    string name;
    int    age;
    string contact;

public:
    Person(string n, int a, string c) : name(n), age(a), contact(c) {}

    string getName()    const { return name; }
    int    getAge()     const { return age; }
    string getContact() const { return contact; }
    void   setContact(const string& c) { contact = c; }

    virtual void displayInfo() const = 0;   // Pure virtual (Abstraction)
    virtual ~Person() {}
};

class GymPlan {
private:
    string planName;
    int    durationMonths;
    float  price;
    string features;

public:
    GymPlan(string pn, int d, float p, string f)
        : planName(pn), durationMonths(d), price(p), features(f) {}

    string getPlanName()  const { return planName; }
    int    getDuration()  const { return durationMonths; }
    float  getPrice()     const { return price; }
    string getFeatures()  const { return features; }

    void display(int idx) const {
        cout << "  [" << idx << "] "
             << left << setw(12) << planName
             << setw(14) << to_string(durationMonths) + " month(s)"
             << "Rs." << setw(8) << fixed << setprecision(0) << price
             << features << "\n";
    }
};

// ─────────────────────────────────────────────────────────────
//  Member  (Inherits Person)
// ─────────────────────────────────────────────────────────────
class Member : public Person {
private:
    string   memberId;
    GymPlan* plan;
    bool     active;
    static int counter;

public:
    Member(string n, int a, string c, GymPlan* p)
        : Person(n, a, c), plan(p), active(true) {
        memberId = "MEM" + to_string(counter++);
    }

    string   getMemberId() const { return memberId; }
    GymPlan* getPlan()     const { return plan; }
    bool     isActive()    const { return active; }

    void setPlan(GymPlan* p) { plan = p; }
    void deactivate()         { active = false; }
    void reactivate()         { active = true;  }

    // Polymorphism: overrides Person::displayInfo()
    void displayInfo() const override {
        cout << "  " << left
             << setw(10) << memberId
             << setw(18) << getName()
             << setw(5)  << getAge()
             << setw(14) << getContact()
             << setw(12) << plan->getPlanName()
             << (active ? "Active" : "Inactive") << "\n";
    }
};
int Member::counter = 1001;

// ─────────────────────────────────────────────────────────────
//  Trainer  (Inherits Person)
// ─────────────────────────────────────────────────────────────
class Trainer : public Person {
private:
    string          trainerId;
    string          specialization;
    float           salary;
    vector<Member*> assigned;
    static int      counter;

public:
    Trainer(string n, int a, string c, string spec, float sal)
        : Person(n, a, c), specialization(spec), salary(sal) {
        trainerId = "TRN" + to_string(counter++);
    }

    string getTrainerId()     const { return trainerId; }
    string getSpecialization()const { return specialization; }
    float  getSalary()        const { return salary; }
    int    getAssignedCount() const { return assigned.size(); }

    void assignMember(Member* m) { assigned.push_back(m); }

    void listAssigned() const {
        if (assigned.empty()) { cout << "  No members assigned.\n"; return; }
        for (auto* m : assigned)
            cout << "    - " << m->getMemberId() << "  " << m->getName() << "\n";
    }

    // Polymorphism: overrides Person::displayInfo()
    void displayInfo() const override {
        cout << "  " << left
             << setw(10) << trainerId
             << setw(18) << getName()
             << setw(5)  << getAge()
             << setw(14) << getContact()
             << setw(22) << specialization
             << "Rs." << fixed << setprecision(0) << salary
             << "  [" << assigned.size() << " members]\n";
    }
};
int Trainer::counter = 501;

// ─────────────────────────────────────────────────────────────
//  GymManagementSystem  (Central Controller)
// ─────────────────────────────────────────────────────────────
class GymManagementSystem {
private:
    string           gymName;
    vector<GymPlan*> plans;
    vector<Member*>  members;
    vector<Trainer*> trainers;

    GymPlan* findPlan(const string& name) {
        for (auto* p : plans)
            if (p->getPlanName() == name) return p;
        return nullptr;
    }
    Member* findMember(const string& id) {
        for (auto* m : members)
            if (m->getMemberId() == id) return m;
        return nullptr;
    }
    Trainer* findTrainer(const string& id) {
        for (auto* t : trainers)
            if (t->getTrainerId() == id) return t;
        return nullptr;
    }

    // ─── Plan submenu ─────────────────────────────────────────
    void menuPlans() {
        while (true) {
            printHeader("Plan Management");
            cout << "  [1] Add Plan\n";
            cout << "  [2] View All Plans\n";
            cout << "  [0] Back to Main Menu\n";
            printLine();
            int ch = getIntInput("  Choice: ", 0, 2);

            if (ch == 0) break;

            else if (ch == 1) {
                printHeader("Add Gym Plan");
                string name = getStringInput("  Plan Name          : ");
                if (findPlan(name)) {
                    cout << "  [!] Plan '" << name << "' already exists.\n";
                    pauseScreen(); continue;
                }
                int   dur   = getIntInput  ("  Duration (months)  : ", 1, 24);
                float price = getFloatInput("  Price (Rs.)        : ");
                string feat = getStringInput("  Features           : ");
                plans.push_back(new GymPlan(name, dur, price, feat));
                cout << "\n  [+] Plan '" << name << "' added!\n";
                pauseScreen();
            }
            else if (ch == 2) {
                printHeader("All Gym Plans");
                if (plans.empty()) { cout << "  No plans available.\n"; pauseScreen(); continue; }
                cout << "  " << left << setw(5) << "#"
                     << setw(12) << "Plan" << setw(14) << "Duration"
                     << setw(12) << "Price" << "Features\n";
                printLine();
                for (int i = 0; i < (int)plans.size(); i++)
                    plans[i]->display(i + 1);
                printLine();
                pauseScreen();
            }
        }
    }

    // ─── Member submenu ───────────────────────────────────────
    void menuMembers() {
        while (true) {
            printHeader("Member Management");
            cout << "  [1] Register New Member\n";
            cout << "  [2] View All Members\n";
            cout << "  [3] Search Member by ID\n";
            cout << "  [4] Upgrade Member Plan\n";
            cout << "  [5] Deactivate / Reactivate Member\n";
            cout << "  [0] Back to Main Menu\n";
            printLine();
            int ch = getIntInput("  Choice: ", 0, 5);

            if (ch == 0) break;

            else if (ch == 1) {
                printHeader("Register New Member");
                if (plans.empty()) {
                    cout << "  [!] No plans available. Add a plan first.\n";
                    pauseScreen(); continue;
                }
                string name = getStringInput("  Full Name           : ");
                int    age  = getIntInput   ("  Age                 : ", 10, 100);
                string cont = getStringInput("  Contact No.         : ");
                cout << "\n  Available Plans:\n";
                for (int i = 0; i < (int)plans.size(); i++) plans[i]->display(i + 1);
                int idx = getIntInput("  Select Plan #       : ", 1, plans.size()) - 1;
                Member* m = new Member(name, age, cont, plans[idx]);
                members.push_back(m);
                cout << "\n  [+] Member registered! ID: " << m->getMemberId() << "\n";
                pauseScreen();
            }
            else if (ch == 2) {
                printHeader("All Members");
                if (members.empty()) { cout << "  No members found.\n"; pauseScreen(); continue; }
                cout << "  " << left << setw(10) << "ID" << setw(18) << "Name"
                     << setw(5) << "Age" << setw(14) << "Contact"
                     << setw(12) << "Plan" << "Status\n";
                printLine();
                for (auto* m : members) m->displayInfo();
                printLine();
                pauseScreen();
            }
            else if (ch == 3) {
                printHeader("Search Member");
                string id = getStringInput("  Enter Member ID: ");
                Member* m = findMember(id);
                if (!m) { cout << "  [!] Member not found.\n"; }
                else {
                    cout << "\n  " << left << setw(10) << "ID" << setw(18) << "Name"
                         << setw(5) << "Age" << setw(14) << "Contact"
                         << setw(12) << "Plan" << "Status\n";
                    printLine();
                    m->displayInfo();
                    printLine();
                }
                pauseScreen();
            }
            else if (ch == 4) {
                printHeader("Upgrade Member Plan");
                if (members.empty() || plans.empty()) {
                    cout << "  [!] No members or plans available.\n";
                    pauseScreen(); continue;
                }
                string id = getStringInput("  Enter Member ID: ");
                Member* m = findMember(id);
                if (!m) { cout << "  [!] Member not found.\n"; pauseScreen(); continue; }
                cout << "  Current Plan : " << m->getPlan()->getPlanName() << "\n\n";
                cout << "  Available Plans:\n";
                for (int i = 0; i < (int)plans.size(); i++) plans[i]->display(i + 1);
                int idx = getIntInput("  Select New Plan #: ", 1, plans.size()) - 1;
                m->setPlan(plans[idx]);
                cout << "\n  [+] Plan upgraded to '" << plans[idx]->getPlanName()
                     << "' for " << m->getName() << ".\n";
                pauseScreen();
            }
            else if (ch == 5) {
                printHeader("Toggle Member Status");
                string id = getStringInput("  Enter Member ID: ");
                Member* m = findMember(id);
                if (!m) { cout << "  [!] Member not found.\n"; pauseScreen(); continue; }
                if (m->isActive()) {
                    m->deactivate();
                    cout << "  [-] " << m->getName() << " has been deactivated.\n";
                } else {
                    m->reactivate();
                    cout << "  [+] " << m->getName() << " has been reactivated.\n";
                }
                pauseScreen();
            }
        }
    }

    // ─── Trainer submenu ──────────────────────────────────────
    void menuTrainers() {
        while (true) {
            printHeader("Trainer Management");
            cout << "  [1] Add Trainer\n";
            cout << "  [2] View All Trainers\n";
            cout << "  [3] Assign Member to Trainer\n";
            cout << "  [4] View Trainer's Members\n";
            cout << "  [0] Back to Main Menu\n";
            printLine();
            int ch = getIntInput("  Choice: ", 0, 4);

            if (ch == 0) break;

            else if (ch == 1) {
                printHeader("Add Trainer");
                string name = getStringInput("  Full Name          : ");
                int    age  = getIntInput   ("  Age                : ", 18, 70);
                string cont = getStringInput("  Contact No.        : ");
                string spec = getStringInput("  Specialization     : ");
                float  sal  = getFloatInput ("  Salary (Rs.)       : ");
                Trainer* t = new Trainer(name, age, cont, spec, sal);
                trainers.push_back(t);
                cout << "\n  [+] Trainer added! ID: " << t->getTrainerId() << "\n";
                pauseScreen();
            }
            else if (ch == 2) {
                printHeader("All Trainers");
                if (trainers.empty()) { cout << "  No trainers found.\n"; pauseScreen(); continue; }
                cout << "  " << left << setw(10) << "ID" << setw(18) << "Name"
                     << setw(5) << "Age" << setw(14) << "Contact"
                     << setw(22) << "Specialization" << "Salary\n";
                printLine();
                for (auto* t : trainers) t->displayInfo();
                printLine();
                pauseScreen();
            }
            else if (ch == 3) {
                printHeader("Assign Member to Trainer");
                if (trainers.empty() || members.empty()) {
                    cout << "  [!] Need at least one trainer and one member.\n";
                    pauseScreen(); continue;
                }
                string tid = getStringInput("  Enter Trainer ID : ");
                Trainer* t = findTrainer(tid);
                if (!t) { cout << "  [!] Trainer not found.\n"; pauseScreen(); continue; }
                string mid = getStringInput("  Enter Member ID  : ");
                Member* m = findMember(mid);
                if (!m) { cout << "  [!] Member not found.\n"; pauseScreen(); continue; }
                t->assignMember(m);
                cout << "\n  [+] " << m->getName() << " assigned to " << t->getName() << ".\n";
                pauseScreen();
            }
            else if (ch == 4) {
                printHeader("Trainer's Assigned Members");
                string tid = getStringInput("  Enter Trainer ID: ");
                Trainer* t = findTrainer(tid);
                if (!t) { cout << "  [!] Trainer not found.\n"; }
                else {
                    cout << "\n  Trainer : " << t->getName()
                         << "  (" << t->getSpecialization() << ")\n";
                    printLine();
                    t->listAssigned();
                    printLine();
                }
                pauseScreen();
            }
        }
    }

    // ─── Summary ──────────────────────────────────────────────
    void showSummary() {
        printHeader("System Summary");
        int active = 0;
        for (auto* m : members) if (m->isActive()) active++;
        printLine('=');
        cout << "  Gym Name        : " << gymName << "\n";
        printLine();
        cout << "  Total Plans     : " << plans.size() << "\n";
        cout << "  Total Members   : " << members.size()
             << "  (Active: " << active
             << "  Inactive: " << members.size() - active << ")\n";
        cout << "  Total Trainers  : " << trainers.size() << "\n";
        printLine('=');
        pauseScreen();
    }

public:
    GymManagementSystem(string n) : gymName(n) {}

    void run() {
        while (true) {
            printHeader("Main Menu");
            cout << "  [1] Plan Management\n";
            cout << "  [2] Member Management\n";
            cout << "  [3] Trainer Management\n";
            cout << "  [4] System Summary\n";
            cout << "  [0] Exit\n";
            printLine();
            int ch = getIntInput("  Choice: ", 0, 4);

            if      (ch == 0) { cout << "\n  Goodbye! Thank you for using FitZone.\n\n"; break; }
            else if (ch == 1) menuPlans();
            else if (ch == 2) menuMembers();
            else if (ch == 3) menuTrainers();
            else if (ch == 4) showSummary();
        }
    }

    ~GymManagementSystem() {
        for (auto* p : plans)    delete p;
        for (auto* m : members)  delete m;
        for (auto* t : trainers) delete t;
    }
};

