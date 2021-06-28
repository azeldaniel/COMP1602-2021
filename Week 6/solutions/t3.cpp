#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Question 1
int getPosition(char c)
{

    // if lowercase char
    if (c >= 'a' && c <= 'z')
    {
        return c - 'a' + 1;
    }

    // if uppercase char
    if (c >= 'A' && c <= 'Z')
    {
        return c - 'A' + 1;
    }

    return 0;
}

// Question 2
void addRandomNumbers()
{
    int num1 = 1 + rand() % (10 - 1 + 1);
    int num2 = 1 + rand() % (10 - 1 + 1);
    int sum = num1 + num2;
    cout << num1 << "+" << num2 << "=" << sum << endl;
}

// Question 3
void guessingGame()
{
    int guess;
    int num = 1 + rand() % (100 - 1 + 1);
    int i = 0;

    while (guess != num && i < 10)
    {
        cout << "Enter your guess: ";
        cin >> guess;

        if (guess < num)
        {
            cout << "Too low! Try Again" << endl;
        }
        else if (guess > num)
        {
            cout << "Too high! Try Again" << endl;
        }
        i++;
    }

    if (guess == num)
    {
        cout << "You win!" << endl;
    }
    else
    {
        cout << "You lose!" << endl;
    }
}

// Question 4
int cheatersDie()
{
    int side = 1 + rand() % (7 - 1 + 1);
    if (side == 7)
        return 6;
    return side;
}

int main()
{
    // Question 1
    cout << "Position of A is " << getPosition('A') << endl;
    cout << "Position of c is " << getPosition('c') << endl;
    cout << "Position of y is " << getPosition('y') << endl;
    cout << "Position of Y is " << getPosition('Y') << endl;

    // Question 2
    srand((time(0)));
    addRandomNumbers();

    // Question 3
    guessingGame();

    // Question 4
    cout << "Simulating 12 rolls of the cheater's die" << endl;
    for (int i = 0; i < 12; i++)
    {
        cout << cheatersDie() << " ";
    }

    // Question 6 c
    int num1 = 100;
    ofstream fout;
    fout.open("data.dat", ios::out | ios::binary);
    if (!fout.is_open())
    {
        cout << "ERROR!!!";
        return -1;
    }
    fout << num1;
    fout.close();

    int num2;
    ifstream fin;
    fin.open("data.dat", ios::in | ios::binary);
    if (!fin.is_open())
    {
        cout << "ERROR!!!";
        return -1;
    }
    fin >> num2;
    fin.close();

    cout << "Num is " << num2;

    return 0;
}