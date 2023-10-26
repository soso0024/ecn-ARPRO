#include <iostream>
#include <ctime>

using namespace std;

bool isNumber(const string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

int main()
{
    srand(time(0));
    int random = rand() % 100 + 1;
    // cout << "randomNumber: " << random << "\n";
    cout << "userInput: ";

    while (1)
    {
        string userInput;
        cin >> userInput;

        if (isNumber(userInput))
        {
            int num = atoi(userInput.c_str());

            if (num > random)
            {
                cout << "smaller"
                     << "\n"
                     << "\n"
                     << "userInput: ";
            }

            if (num == random)
            {
                cout << "Correct!"
                     << "\n";
                break;
            }

            if (num < random)
            {
                cout << "bigger"
                     << "\n"
                     << "\n"
                     << "userInput: ";
            }
        }
        else
        {
            cout << "You should input the Number!"
                 << "\n"
                 << "\n"
                 << "userInput";
        }
    }
    return 0;
}