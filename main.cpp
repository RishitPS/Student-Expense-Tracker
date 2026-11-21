
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;

struct Expense
{
    string category;
    double amount;
    string description;
};

class ExpenseTracker
{
private:
    vector<Expense> expenses;
    const string filename = "expenses.txt";

    void saveToFile()
    {
        ofstream file(filename);

        for (const auto &e : expenses)
        {
            file << e.category << "|"
                 << e.amount << "|"
                 << e.description << "\n";
        }

        file.close();
    }

    void loadFromFile()
    {
        ifstream file(filename);
        string line;

        while (getline(file, line))
        {
            stringstream ss(line);
            Expense e;
            string amount;

            getline(ss, e.category, '|');
            getline(ss, amount, '|');
            getline(ss, e.description);

            if (!e.category.empty() && !amount.empty())
            {
                e.amount = stod(amount);
                expenses.push_back(e);
            }
        }

        file.close();
    }

public:
    ExpenseTracker()
    {
        loadFromFile();
    }

    void addExpense()
    {
        Expense e;

        cout << "Enter category: ";
        getline(cin, e.category);

        cout << "Enter amount: ";
        if (!(cin >> e.amount) || e.amount <= 0)
        {
            cout << "Invalid amount!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter description: ";
        getline(cin, e.description);

        if (e.category.find('|') != string::npos ||
            e.description.find('|') != string::npos)
        {
            cout << "Please do not use | in your input.\n";
            return;
        }

        expenses.push_back(e);
        saveToFile();

        cout << "Expense added successfully!\n";
    }

    void viewExpenses()
    {
        if (expenses.empty())
        {
            cout << "No expenses recorded.\n";
            return;
        }

        cout << "\n--- Expense History ---\n";

        for (int i = 0; i < expenses.size(); i++)
        {
            cout << i + 1 << ". "
                 << expenses[i].category << " | Rs. "
                 << fixed << setprecision(2)
                 << expenses[i].amount << " | "
                 << expenses[i].description << "\n";
        }
    }

    void totalSpending()
    {
        double total = 0;

        for (const auto &e : expenses)
        {
            total += e.amount;
        }

        cout << "\nTotal Spending: Rs. "
             << fixed << setprecision(2)
             << total << "\n";
    }

    void categoryAnalysis()
    {
        map<string, double> totals;

        for (const auto &e : expenses)
        {
            totals[e.category] += e.amount;
        }

        cout << "\n--- Category Analysis ---\n";

        for (const auto &item : totals)
        {
            cout << item.first << ": Rs. "
                 << fixed << setprecision(2)
                 << item.second << "\n";
        }
    }
};

int main()
{
    ExpenseTracker tracker;
    int choice;

    do
    {
        cout << "\n===== STUDENT EXPENSE TRACKER =====\n";
        cout << "1. Add Expense\n";
        cout << "2. View Expenses\n";
        cout << "3. Total Spending\n";
        cout << "4. Category Analysis\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice)
        {
        case 1:
            tracker.addExpense();
            break;
        case 2:
            tracker.viewExpenses();
            break;
        case 3:
            tracker.totalSpending();
            break;
        case 4:
            tracker.categoryAnalysis();
            break;
        case 5:
            cout << "Exiting application...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
