#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <time.h>

using namespace std;

void originalArr(int field[]);
void showField(int field[]);
void showConclusion(int computerWins, int playerWins);
void makeUserMotion(int field[], bool isPlayerCrosses);
void makeComputerMotion(int field[], int move, bool isPlayerCrosses);
bool chooseMarker();
bool crossOrZero(int move);
void pause();
void printWinner(int field[]);
int checkWinner(int field[]);
bool isPositionFree(int field[], int pos);
void printButtons();
int gameCycle(int field[], bool isPlayerCrosses);
int makeAIDecision(int field[], bool isPlayerCrosses);
bool isField(int x);
int changePlayerScore(int result, bool isPlayerCrosses);
int changeComputerScore(int result, bool isPlayerCrosses);
int findComputerMarker(int field[], bool isPlayerCrosses);

int main()
{
    int field[9] = { 0 };
    int computerScore = 0;
    int playerScore = 0;
    bool isPlayerCrosses = false;
    int result = 0;

    for (int i = 0; i < 8; i++)
    {
        isPlayerCrosses = chooseMarker();
        result = gameCycle(field, isPlayerCrosses);
        playerScore += changePlayerScore(result, isPlayerCrosses);
        computerScore += changeComputerScore(result, isPlayerCrosses);
    }

    showConclusion(computerScore, playerScore);
    pause();
    return 0;
}

int changePlayerScore(int result, bool isPlayerCrosses)
{
    if ((result == -1 && isPlayerCrosses) or (result == 1 && !isPlayerCrosses))
        return 3;
    else if (!((result == -1 && !isPlayerCrosses) or (result == 1 && isPlayerCrosses)))
        return 1;
    else return 0;
}

int changeComputerScore(int result, bool isPlayerCrosses)
{
    if (!((result == -1 && isPlayerCrosses) or (result == 1 && !isPlayerCrosses)))
        return 3;
    else if (((result == -1 && !isPlayerCrosses) or (result == 1 && isPlayerCrosses)))
        return 1;
    else return 0;
}

int gameCycle(int field[], bool isPlayerCrosses)
{
    int move = 0;

    originalArr(field);
    if (!isPlayerCrosses) {
        makeComputerMotion(field, move, isPlayerCrosses);
        showField(field);
        move++;
    }
    while (move <= 9 and checkWinner(field) == 1)
    {
        showField(field);
        makeUserMotion(field, isPlayerCrosses);
        showField(field);
        move++;
        if (move == 9) break;
        makeComputerMotion(field, move, isPlayerCrosses);
        showField(field);
        move++;
    }
    printWinner(field);
    if (checkWinner(field) == -1)
        return 1;
    else if (checkWinner(field) == 0)
        return -1;
    else
        return 0;
}

int findComputerMarker(int field[], bool isPlayerCrosses)
{
    for (int i = 0; i < 9; i++)
    {
        if (field[i] == -1 and !isPlayerCrosses)
            return i;
        else if (field[i] == 0 and isPlayerCrosses)
                return i;
    }
    return -1;
}
int makeAIDecision(int field[], bool isPlayerCrosses)
{
    int potentialPosition = 0;

    if (field[4] == 5)
        return 4;
    
    potentialPosition = findComputerMarker(field, isPlayerCrosses) + 1;
    if (isField(potentialPosition) and isPositionFree(field, potentialPosition)) {
        return potentialPosition;
    }
    potentialPosition -= 2;
    if (isField(potentialPosition) and isPositionFree(field, potentialPosition)) {
        return potentialPosition;
    }
    potentialPosition -= 2;
    if (isField(potentialPosition) and isPositionFree(field, potentialPosition)) {
        return potentialPosition;
    }
    potentialPosition += 6;
    if (isField(potentialPosition) and isPositionFree(field, potentialPosition)) {
        return potentialPosition;
    }

    return -1;
}

bool isField(int x)
{
    if (x > 8 or x < 0)
        return false;
    return true;
}

bool isPositionFree(int field[], int pos) 
{
    if (field[pos - 1] != -1 and field[pos - 1] != 0)
        return true;
    return false;
}

int getFreePositions(int field[]) 
{
    return 0;
}

void printWinner(int field[]) 
{
    if (checkWinner(field) == -1)
        cout << "Crosses Win!!!" << endl;
    else if (checkWinner(field) == 0)
        cout << "Zeros Win!!!" << endl;
    else
        cout << "Draw!!!" << endl;
}

int checkWinner(int field[])
{
    if ((field[4] == field[1] and field[4] == field[7]) or
        (field[4] == field[3] and field[4] == field[5]) or
        (field[0] == field[4] and field[4] == field[8]) or
        (field[4] == field[6] and field[4] == field[2]))
        return field[4];

    if ((field[0] == field[1] and field[1] == field[2]) or
        (field[0] == field[3] and field[3] == field[6]))
        return field[0];

    if ((field[8] == field[5] and field[5] == field[2]) or
        (field[8] == field[7] and field[7] == field[6]))
        return field[8];

    return 1;
}

void pause()
{
    cout << endl << "To continue press any button....";
    rewind(stdin);
    getchar();
}

bool crossOrZero(int move) 
{
    if (move % 2 == 0)
        return false;
    else
        return true;
}

bool chooseMarker()
{
    int choice = 0;

    cout << "What do you want to play with?" << endl;
    cout << "1) Crosses" << endl;
    cout << "2) Zeros" << endl;
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1)
        return true;
    return false;
}

void showConclusion(int computerWins, int playerWins)
{
    system("cls");
    cout << "Result of the fight" << endl;
    cout << "Player : AI" << endl;
    cout << "     " << playerWins << " : " << computerWins;
}

void makeUserMotion(int field[], bool isPlayerCrosses) 
{
    int cell = 0;

    do
    {
        cout << endl << "*******Your move*******" << endl;
        cout << "Select an empty cell: ";
        cin >> cell;
    } while (!isPositionFree(field, cell));

    if (isPlayerCrosses)
        field[cell - 1] = -1;
    else
        field[cell - 1] = 0;
}

void makeComputerMotion(int field[], int move, bool isPlayerCrosses)
{
    int computerChoice = 0;

    srand(time(NULL));

    if (move == 0) {
        computerChoice = rand() % 9 + 0;
        if (isPlayerCrosses)
            field[computerChoice] = 0;
        else
            field[computerChoice] = -1;
    }
    else {

        computerChoice = makeAIDecision(field, isPlayerCrosses);
        if (computerChoice != -1 and isPositionFree(field, computerChoice + 1)) {
            if (isPlayerCrosses)
                field[computerChoice] = 0;
            else
                field[computerChoice] = -1;
        }
        else {
            do
            {
                computerChoice = rand() % 9 + 0;
            } while (!isPositionFree(field, computerChoice + 1));

            if (isPlayerCrosses)
                field[computerChoice] = 0;
            else
                field[computerChoice] = -1;
        }
    }
}

void showField(int field[]) 
{
    system("cls");
    printButtons();

    cout << "-------------" << endl;
    for (int i = 1; i < 10; i+=3)
    {
        cout << "|";
        for (int j = 0; j < 3; j++)
        {
            
            if (field[i - 1 + j] == -1) {
                cout << " X |";
            }
            else if (field[i - 1 + j] == 0) {
                cout << " 0 |";
            }
            else cout << "   |";
        }
        cout << endl <<"-------------" << endl;
    }
}

void originalArr(int field[])
{
    for (int i = 0; i < 10; i++)
        field[i] = i + 1;
}

void printButtons() {
    for (int i = 1; i <= 9; i++)
    {
        cout << "  " << i << " ";
        if (i % 3 == 0) {
            cout << endl << endl;
        }
    }
}