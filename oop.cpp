#include <iostream>
#include <string>

using namespace std;

static int memberCount = 0;

class Place {
protected:
    int subscription[4] = { 25, 65, 110, 220 };
    int month = 0;
    int paymentForMem = 0;
public:
    Place() {
    }

    virtual ~Place() {
    }

    void displayMembership() {
        cout << "Here is our monthly subscription:\n";
        cout << "1 month for 25$ jd\n";
        cout << "3 months for 65$ jd\n";
        cout << "6 months for 110$ jd\n";
        cout << "1 year for 220$ jd\n";
    }

    void setMonths(int m) {
        month = m;
    }

    virtual void calculatePayment() = 0; // Pure virtual method

    int getPaymentForMem() const {
        return paymentForMem;
    }

    int getMonth() const {
        return month;
    }
};

class Members : public Place {
    int maxMembers = 12;
    int* payment;
    string* names;
    int* passwords;
    int* durations;

public:
    Members() {
        payment = new int[maxMembers];
        names = new string[maxMembers];
        passwords = new int[maxMembers];
        durations = new int[maxMembers];
    }

    ~Members() {
        delete[] payment;
        delete[] names;
        delete[] passwords;
        delete[] durations;
    }

    bool isFull() const {
        return memberCount >= maxMembers;
    }

    void expandCapacity() {
        maxMembers *= 2;
        int* newPayment = new int[maxMembers];
        string* newNames = new string[maxMembers];
        int* newPasswords = new int[maxMembers];
        int* newDurations = new int[maxMembers];

        for (int i = 0; i < memberCount; ++i) {
            newPayment[i] = payment[i];
            newNames[i] = names[i];
            newPasswords[i] = passwords[i];
            newDurations[i] = durations[i];
        }

        delete[] payment;
        delete[] names;
        delete[] passwords;
        delete[] durations;

        payment = newPayment;
        names = newNames;
        passwords = newPasswords;
        durations = newDurations;

        cout << "Capacity expanded to " << maxMembers << " members.\n";
    }

    void addMember(const string& name, int pass, int duration, int paymentAmount) {
        if (isFull()) {
            cout << "Maximum number of members reached. Expanding capacity...\n";
            expandCapacity();
        }

        names[memberCount] = name;
        passwords[memberCount] = pass;
        durations[memberCount] = duration;
        payment[memberCount] = paymentAmount;
        memberCount++;
    }

    void displayMembers() const {
        for (int i = 0; i < memberCount; ++i) {
            cout << "Member " << names[i] << " has subscribed for " << durations[i]
                << " months with a total payment of " << payment[i] << " jd"
                << " and their password is " << passwords[i] << endl;
        }
    }

    void removeMember(const string& name) {
        for (int i = 0; i < memberCount; ++i) {
            if (names[i] == name) {
                for (int j = i; j < memberCount - 1; ++j) {
                    names[j] = names[j + 1];
                    passwords[j] = passwords[j + 1];
                    payment[j] = payment[j + 1];
                    durations[j] = durations[j + 1];
                }
                memberCount--;
                cout << "Member " << name << " removed successfully.\n";
                return;
            }
        }
        cout << "Member " << name << " not found.\n";
    }

    void calculatePayment() override {
        if (month == 1)
            paymentForMem = subscription[0];
        else if (month == 3)
            paymentForMem = subscription[1];
        else if (month == 6)
            paymentForMem = subscription[2];
        else if (month == 12)
            paymentForMem = subscription[3];
        else
            paymentForMem = month * 25;  // Default rate for custom months
    }
};

class Employee : public Members {
    int employeePass[3] = { 202311259, 202311834, 202310696 };
    string employeeName[3] = { "ghazi", "hussam", "naeem" };

public:
    bool validateEmployee(const string& name, const int pass) {
        for (int i = 0; i < 3; ++i) {
            if (employeeName[i] == name && employeePass[i] == pass) {
                return true;
            }
        }
        return false;
    }

    void accessEmployeeFunctions(int& choice) {
        cout << "\nEmployee Menu:\n";
        cout << "1. Display subscribers\n";
        cout << "2. Expand capacity\n";
        cout << "3. Remove subscribers\n";
        cout << "4. Logout\n";
        cin >> choice;
    }
};

int main() {
    bool exit = false;
    Members* memberObj = new Members();
    Employee* employeeGym = new Employee();

    cout << "Welcome to our little gym";

    while (!exit) {
        cout << "\nMain Menu:\n";
        cout << "1. Display membership options\n";
        cout << "2. Add new member\n";
        cout << "3. Employee login\n";
        cout << "4. Exit\n";
        int choice;
        cin >> choice;
        system("CLS");

        switch (choice) {
        case 1:
            memberObj->displayMembership();
            break;
        case 2: {
            if (!memberObj->isFull()) {
                memberObj->displayMembership();
                int gymsubs;
                cout << "How many months do you want?\n";
                cin >> gymsubs;
                memberObj->setMonths(gymsubs);
                memberObj->calculatePayment();
                string name;
                int pass;
                cout << "Enter your name: ";
                cin >> name;
                cout << "Enter your password: ";
                cin >> pass;
                int payment = memberObj->getPaymentForMem();
                memberObj->addMember(name, pass, gymsubs, payment);
            }
            else {
                cout << "Maximum number of members reached. Expanding capacity...\n";
                memberObj->expandCapacity();
            }
            break;
        }
        case 3: {
            int choiceEm;
            string name;
            int pass;
            cout << "Enter employee name: ";
            cin >> name;
            cout << "Enter employee password: ";
            cin >> pass;

            if (employeeGym->validateEmployee(name, pass))
            {
                employeeGym->accessEmployeeFunctions(choiceEm);
                switch (choiceEm) {
                case 1:
                    memberObj->displayMembers();
                    break;
                case 2:
                    memberObj->expandCapacity();
                    break;
                case 3: {
                    string name;
                    cout << "Enter member name to remove: ";
                    cin >> name;
                    memberObj->removeMember(name);
                    break;
                }
                case 4:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
            }
            break;
        }
        case 4:
            exit = true;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }

    delete memberObj;
    delete employeeGym;

    return 0;
}
