//Lukasz Ciesielski, 198014, EiT
//Gra Black Box

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace this_thread;
using namespace chrono;


struct Game
{
    int posX;
    int posY;
    bool gameStarted;
    int boardSize;
    int atomsN;
    int oCounter;
    int laserCounter;
    int points;
    char atomsTab[12][12];
    int guessTab[12][12];
};

void menu(Game& game, Game pastStates[6], int& state);
void logo();
void drawing(Game& game);
void chooseLevel(Game& game, Game pastStates[6], int& state);
void control(Game& game, Game pastStates[6], int& state);
void atomsGeneration(Game& game);
void reflectionsGeneration(Game& game);
void showAtoms(Game& game);
void laser(Game& game);
void endLevel(Game& game);
void resetValues(Game& game, Game pastStates[6], int& state);
void savePastStates(Game& game, Game pastStates[6]);


int main()
{
    Game game;
    Game pastStates[6];
    int state = 0;

    menu(game, pastStates, state);
    system("cls");
    while (true)
    {
        drawing(game);
        control(game, pastStates, state);
        system("cls");
    }

}

void menu(Game& game, Game pastStates[6], int& state)
{
    char keyboard;

    logo();

    cout << "1. NOWA GRA" << endl;

    if (game.gameStarted == true)
    {
        cout << "2. KONTYNUUJ" << endl;
        cout << "3. ZAKONCZ" << endl;
    }
    else
    {
        cout << "2. ZAKONCZ" << endl;
    }

    cin >> keyboard;
    switch (keyboard)
    {
    case '1':
    {
        game.posX = 1;
        game.posY = 1;
        game.gameStarted = true;
        system("cls");
        logo();
        chooseLevel(game, pastStates, state);
    }
    break;

    case '2':
    {

        if (game.gameStarted == 1)
        {
            return;
        }
        else
        {
            exit(NULL);
        }
    }
    break;

    default:
        system("cls");
        menu(game, pastStates, state);

    }

}

void chooseLevel(Game& game, Game pastStates[6], int &state)
{
    char keyboard;
    cout << "1. POZIOM LATWY: 5x5, 3 atomy" << endl;
    cout << "2. POZIOM SREDNI: 8x8, 5 atomow" << endl;
    cout << "3. POZIOM TRUDNY: 10x10, 8 atomow" << endl;
    cin >> keyboard;
    switch (keyboard)
    {
    case '1':
    {
        game.boardSize = 5;
        game.atomsN = 3;
        resetValues(game, pastStates, state);
        atomsGeneration(game);
        reflectionsGeneration(game);
        for (int i = 0; i < 6; i++)
        {
            pastStates[i] = game;
        }
    }
    break;

    case '2':
    {
        game.boardSize = 8;
        game.atomsN = 5;
        resetValues(game, pastStates, state);
        atomsGeneration(game);
        reflectionsGeneration(game);
        for (int i = 0; i < 6; i++)
        {
            pastStates[i] = game;
        }
    }
    break;

    case '3':
    {
        game.boardSize = 10;
        game.atomsN = 8;
        resetValues(game, pastStates, state);
        atomsGeneration(game);
        reflectionsGeneration(game);
        for (int i = 0; i < 6; i++)
        {
            pastStates[i] = game;
        }
    }
    break;

    default:
        system("cls");
        logo();
        chooseLevel(game, pastStates, state);
    }
}

void logo()
{
    cout << endl;
    cout << "______ _            _     ______" << endl;
    cout << "| ___ \\ |          | |    | ___ \\ " << endl;
    cout << "| |_/ / | __ _  ___| | __ | |_/ / _____  __" << endl;
    cout << "| ___ \\ |/ _` |/ __| |/ / | ___ \\/ _ \\ \\/ /" << endl;
    cout << "| |_/ / | (_| | (__|   <  | |_/ / (_) >  <" << endl;
    cout << "\\____/|_|\\__,_|\\___|_|\\_\\ \\____/ \\___/_/\\_\\ " << endl;
    cout << "    Autor: Lukasz Ciesielski, s198014" << endl << endl;

}

void drawing(Game& game)
{
    cout << "LICZBA ATOMOW: " << game.atomsN << endl << endl;
    for (int i = 0; i < game.boardSize + 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < game.boardSize + 2; k++)
            {
                if (j == 0 && game.posX == k && game.posY == i)
                {
                    cout << "+    ";
                }
                else if (j == 1 && game.guessTab[i][k] == 1)
                {
                    cout << "    o";
                }
                else if (j == 1 && game.guessTab[i][k] == 100)
                {
                    cout << "    H";
                }
                else if (j == 1 && game.guessTab[i][k] == 101)
                {
                    cout << "    R";
                }
                else if (j == 1 && (i == 0 || i == game.boardSize + 1 || k == 0 || k == game.boardSize + 1) && game.guessTab[i][k] > 1)
                {
                    cout << setw(5) << game.guessTab[i][k] - 1;
                }
                else
                {
                    cout << "     ";
                }

                if (k != game.boardSize + 1)
                {
                    cout << "บ";
                }
            }
            cout << endl;
        }
        if (i != game.boardSize + 1)
        {
            for (int l = 0; l < game.boardSize + 1; l++)
            {
                cout << "อออออฮ";
            }
            cout << "อออออ" << endl;
        }
    }
}

void control(Game& game, Game pastStates[6], int& state)
{
    char keyboard;
    cin.get(keyboard);
    switch (keyboard)
    {
    case 'w':
    case 'W':
    {
        state = 0;

        if (!(game.posY == 0 || (game.posY == 1 && (game.posX == 0 || game.posX == game.boardSize + 1))))
            game.posY -= 1;

        savePastStates(game, pastStates);
    }
    break;

    case 's':
    case 'S':
    {
        state = 0;

        if (!(game.posY == game.boardSize + 1 || (game.posY == game.boardSize && (game.posX == 0 || game.posX == game.boardSize + 1))))
            game.posY += 1;

        savePastStates(game, pastStates);
    }
    break;

    case 'd':
    case 'D':
    {
        state = 0;

        if (!(game.posX == game.boardSize + 1 || (game.posX == game.boardSize && (game.posY == 0 || game.posY == game.boardSize + 1))))
            game.posX += 1;

        savePastStates(game, pastStates);
    }
    break;

    case 'a':
    case 'A':
    {
        state = 0;

        if (!(game.posX == 0 || (game.posX == 1 && (game.posY == 0 || game.posY == game.boardSize + 1))))
            game.posX -= 1;

        savePastStates(game, pastStates);
    }
    break;

    case 'q':
    case 'Q':
    {
        system("cls");
        menu(game, pastStates, state);
    }
    break;

    case 'p':
    case 'P':
    {
        system("cls");
        showAtoms(game);
        system("pause");
        game.gameStarted = false;
        system("cls");
        menu(game, pastStates, state);
    }
    break;

    case 'h':
    case 'H':
    {
        system("cls");
        showAtoms(game);
        sleep_for(milliseconds(500));
        system("cls");
    }
    break;

    case 'o':
    case 'O':
    {
        state = 0;

        if (game.posX != 0 && game.posX != game.boardSize + 1 && game.posY != 0 && game.posY != game.boardSize + 1)
        {
            if (game.guessTab[game.posY][game.posX] == 0)
            {
                game.guessTab[game.posY][game.posX] = 1;
                game.oCounter++;
            }
            else if (game.guessTab[game.posY][game.posX] == 1)
            {
                game.guessTab[game.posY][game.posX] = 0;
                game.oCounter--;
            }
        }

        savePastStates(game, pastStates);
    }
    break;

    case ' ':
    {
        state = 0;

        if ((game.posX == 0 || game.posX == game.boardSize + 1 || game.posY == 0 || game.posY == game.boardSize + 1) && game.guessTab[game.posY][game.posX] == 0)
        {
            game.guessTab[game.posY][game.posX] = game.laserCounter;
            laser(game);
        }

        savePastStates(game, pastStates);
    }
    break;

    case 'k':
    case 'K':
    {
        if (game.atomsN == game.oCounter)
        {
            system("cls");
            endLevel(game);
            system("pause");
            game.gameStarted = false;
            system("cls");
            menu(game, pastStates, state);

        }
        else
        {
            cout << "Liczba zaznaczonych pozycji musi wynosic dokladnie " << game.atomsN << "!" << endl;
            system("pause");
        }
    }
    break;

    case 'u':
    case 'U':
    {

        if (state < 5)
        {
            state++;
            game = pastStates[state];
        }
    }
    break;

    case 'r':
    case 'R':
    {
        if (state > 0)
        {
            state--;
            game = pastStates[state];
            
        }
    }
    break;
    }

}

void atomsGeneration(Game& game)
{
    int rand1, rand2;
    srand(time(NULL));
    for (int i = 0; i < game.atomsN; i++)
    {
        rand1 = rand() % game.boardSize + 1;
        rand2 = rand() % game.boardSize + 1;
        while (game.atomsTab[rand1][rand2] == 'O')
        {
            rand1 = rand() % game.boardSize + 1;
            rand2 = rand() % game.boardSize + 1;
        }
        game.atomsTab[rand1][rand2] = 'O';
    }
}

void reflectionsGeneration(Game& game)
{
    for (int i = 1; i <= game.boardSize; i++)
    {
        for (int j = 1; j <= game.boardSize; j++)
        {
            if (game.atomsTab[i][j] != 'O')
            {
                if (game.atomsTab[i + 1][j + 1] == 'O' || game.atomsTab[i - 1][j - 1] == 'O')
                {
                    game.atomsTab[i][j] = '/';
                }
                if (game.atomsTab[i + 1][j - 1] == 'O' || game.atomsTab[i - 1][j + 1] == 'O')
                {
                    if (game.atomsTab[i][j] == '/')
                    {
                        game.atomsTab[i][j] = 'X';
                    }
                    else
                    {
                        game.atomsTab[i][j] = '\\';
                    }
                }
                if (game.atomsTab[i + 1][j] == 'O' || game.atomsTab[i - 1][j] == 'O')
                {
                    game.atomsTab[i][j] = '-';
                }
                if (game.atomsTab[i][j + 1] == 'O' || game.atomsTab[i][j - 1] == 'O')
                {
                    game.atomsTab[i][j] = '|';
                }
            }
        }
    }
}

void showAtoms(Game& game)
{
    cout << "LICZBA ATOMOW: " << game.atomsN << endl << endl;
    for (int i = 0; i < game.boardSize + 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < game.boardSize + 2; k++)
            {
                if (j == 1 && game.atomsTab[i][k] == 'O')
                {
                    cout << "    O";
                }
                else
                {
                    cout << "     ";
                }
                if (k != game.boardSize + 1)
                {
                    cout << "บ";
                }
            }
            cout << endl;
        }
        if (i != game.boardSize + 1)
        {
            for (int l = 0; l < game.boardSize + 1; l++)
            {
                cout << "อออออฮ";
            }
            cout << "อออออ" << endl;
        }
    }
}

void laser(Game& game)
{   
    char direction = 0;
    int laserX = game.posX;
    int laserY = game.posY;

    if (laserX == 0)
    {
        direction = 'r';
        laserX++;
    }
    else if (laserX == game.boardSize + 1)
    {
        direction = 'l';
        laserX--;
    }
    else if (laserY == 0)
    {
        direction = 'd';
        laserY++;
    }
    else if (laserY == game.boardSize + 1)
    {
        direction = 'u';
        laserY--;
    }

    while (laserX != 0 && laserX != game.boardSize + 1 && laserY != 0 && laserY != game.boardSize + 1)
    {
        if (direction == 'r')
        {
            if (game.atomsTab[laserY][laserX] == '\\')
            {
                direction = 'd';
                laserY++;
            }
            else if (game.atomsTab[laserY][laserX] == '/')
            {
                direction = 'u';
                laserY--;
            }
            else if (laserX == 1 && game.atomsTab[laserY][laserX] == '-')
            {
                game.guessTab[game.posY][game.posX] = 101;
                return;
            }
            else
            {
                laserX++;
            }
        }
        else if (direction == 'l')
        {
            if (game.atomsTab[laserY][laserX] == '\\')
            {
                direction = 'u';
                laserY--;
            }
            else if (game.atomsTab[laserY][laserX] == '/')
            {
                direction = 'd';
                laserY++;
            }
            else if (laserX == game.boardSize && game.atomsTab[laserY][laserX] == '-')
            {
                game.guessTab[game.posY][game.posX] = 101;
                return;
            }
            else
            {
                laserX--;
            }
        }
        else if (direction == 'd')
        {
            if (game.atomsTab[laserY][laserX] == '\\')
            {
                direction = 'r';
                laserX++;
            }
            else if (game.atomsTab[laserY][laserX] == '/')
            {
                direction = 'l';
                laserX--;
            }
            else if (laserY == 1 && game.atomsTab[laserY][laserX] == '|')
            {
                game.guessTab[game.posY][game.posX] = 101;
                return;
            }
            else
            {
                laserY++;
            }
        }
        else if (direction == 'u')
        {
            if (game.atomsTab[laserY][laserX] == '\\')
            {
                direction = 'l';
                laserX--;
            }
            else if (game.atomsTab[laserY][laserX] == '/')
            {
                direction = 'r';
                laserX++;
            }
            else if (laserY == game.boardSize && game.atomsTab[laserY][laserX] == '|')
            {
                game.guessTab[game.posY][game.posX] = 101;
                return;
            }
            else
            {
                laserY--;
            }
        }

        if (game.atomsTab[laserY][laserX] == '|' || game.atomsTab[laserY][laserX] == '-')
        { 
            game.guessTab[game.posY][game.posX] = 100;
            return;
        }
        else if (game.atomsTab[laserY][laserX] == 'X')
        {
            game.guessTab[game.posY][game.posX] = 101;
            return;
        }
    }

    game.guessTab[laserY][laserX] = game.laserCounter;
    game.laserCounter++;
    return;
}

void endLevel(Game& game)
{
    for (int i = 0; i < game.boardSize + 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < game.boardSize + 2; k++)
            {
                if (j == 1 && game.atomsTab[i][k] == 'O' && game.guessTab[i][k] == 1)
                {
                    cout << "    O";
                    game.points++;
                }
                else if (j == 1 && game.atomsTab[i][k] != 'O' && game.guessTab[i][k] == 1)
                {
                    cout << "    X";
                }
                else if (j == 1 && game.atomsTab[i][k] == 'O' && game.guessTab[i][k] == 0)
                {
                    cout << "    o";
                }
                else
                {
                    cout << "     ";
                }

                if (k != game.boardSize + 1)
                {
                    cout << "บ";
                }
            }
            cout << endl;
        }
        if (i != game.boardSize + 1)
        {
            for (int l = 0; l < game.boardSize + 1; l++)
            {
                cout << "อออออฮ";
            }
            cout << "อออออ" << endl;
        }
    }
    cout << "Punkty zdobyte: " << game.points << "/" << game.atomsN << endl;
}

void resetValues(Game& game, Game pastStates[6], int& state)
{
    game.laserCounter = 2;
    game.oCounter = 0;
    game.points = 0;
    state = -0;
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            game.atomsTab[i][j] = 0;
        }
    }
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            game.guessTab[i][j] = 0;
        }
    }
}

void savePastStates(Game& game, Game pastStates[6])
{
    pastStates[5] = pastStates[4];
    pastStates[4] = pastStates[3];
    pastStates[3] = pastStates[2];
    pastStates[2] = pastStates[1];
    pastStates[1] = pastStates[0];
    pastStates[0] = game;
}
