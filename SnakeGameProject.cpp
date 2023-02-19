#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <fstream>

using namespace std;

struct tailPosition //for pointers
{
       int x;
       int y;
       struct tailPosition *next;
       struct tailPosition *prev;
};

class snake //organizing variables and functions by class named "snake"
{
public:
       int wallsX, wallsY; //s stands for "start"
       int walleX, walleY; //e stands for "end"

       int boardWidth; 
       int boardHeight;


       int score;

       int foodx, foody;

       HANDLE console_handle;
       COORD cur_cord;

       tailPosition *start, *current, *newtail;
       snake();

       void menu();
       void help();
       void draw();
       void drawWall();
       void drawfood(int x);
       void insert(int x, int y);
       void move();
       bool collision();
       void gameOver();
       void resetGame();
       void startGame();
       // void loop(snake & ob);
};

int d = 4; //global variable for direction more of which in insert function

snake::snake() //setting NULL values, setting coordinates for food and wall
{
       score = 0;

       start = NULL;
       current = NULL;
       newtail = NULL;
       console_handle = GetStdHandle(STD_OUTPUT_HANDLE);

       foodx = 12;
       foody = 14;

       wallsX = 2;
       wallsY = 3;
       walleX = 70;
       walleY = 20;

       boardWidth = walleX - wallsX - 1;
       boardHeight = walleY - wallsY - 1;

}

// void snake::resetGame()
// {
//        // Reset all game variables to their initial state
       
//        score = 0;
//        start = NULL;
//        current = NULL;
//        newtail = NULL;
//        foodx = 12;
//        foody = 14;
// }

void snake::resetGame()
{
    // Reset the score
    score = 0;

    // Remove all tail positions
    while (start != NULL) {
        current = start;
        start = start->next;
        delete current;
    }

    // Reset the tail pointers
    start = NULL;
    current = NULL;
    newtail = NULL;

    // Reset the direction
    d = 4;

    // Reset the food position
    foodx = 12;
    foody = 14;

    // Reset the board dimensions
    wallsX = 2;
    wallsY = 3;
    walleX = 70;
    walleY = 20;

    boardWidth = walleX - wallsX - 1;
    boardHeight = walleY - wallsY - 1;
}


void snake::draw()
{
       cur_cord.X = 30;
       cur_cord.Y = 1;

       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "SCORE : " << score;

       tailPosition *tmp, *last;
       tmp = start;
       last = current;

       //snake moving forward
       while (tmp != NULL)  
       {
              cur_cord.X = tmp->x;
              cur_cord.Y = tmp->y;
              SetConsoleCursorPosition(console_handle, cur_cord);

              // cout << (char)206;
              // cout << (char)177;
              cout << '@';
              tmp = tmp->next;
       }

       //adding backspace as the snake moves forward
       cur_cord.X = last->x;
       cur_cord.Y = last->y;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << ' ';

       //for food
       cur_cord.X = foodx;
       cur_cord.Y = foody;
       SetConsoleCursorPosition(console_handle, cur_cord);
}

void snake::drawWall() 
{
    cur_cord.X = wallsX;
    cur_cord.Y = wallsY;

    SetConsoleCursorPosition(console_handle, cur_cord);
    for (int i = 0; i <= walleX - wallsX; i++) 
    {
        cout << "*";
    }

    for (int i = 1; i < walleY - wallsY; i++) 
    {
        cur_cord.X = wallsX;
        cur_cord.Y = wallsY + i;
        SetConsoleCursorPosition(console_handle, cur_cord);
        cout << "*";
        cur_cord.X = walleX;
        SetConsoleCursorPosition(console_handle, cur_cord);
        cout << "*";
    }

    cur_cord.X = wallsX;
    cur_cord.Y = walleY;

    SetConsoleCursorPosition(console_handle, cur_cord);
    for (int i = 0; i <= walleX - wallsX; i++) 
    {
        cout << "*";
    }
}

void snake::insert(int x, int y) //adding a new node for snake's body
{
       if (start == NULL)
       {
              newtail = new tailPosition;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = NULL;
              start = newtail;
              current = newtail;
       }
       else
       {
              newtail = new tailPosition;
              newtail->x = x;
              newtail->y = y;
              newtail->next = NULL;
              newtail->prev = current;
              current->next = newtail;
              current = newtail;
       }
}

void snake::drawfood(int x) //randomly generating food
{
       tailPosition *tmp;
       tmp = start;
       if (x == 1)
       {
              // Generate random coordinates for the food
              foodx = rand() % (boardWidth - 2) + wallsX + 1;
              foody = rand() % (boardHeight - 2) + wallsY + 1;

              // Check if the food coordinates overlap with the snake's body or the wall
              while (tmp != NULL)
              {
                     if (foodx == tmp->x && foody == tmp->y)
                     {
                            // Generate new coordinates if the food overlaps with the snake's body
                            drawfood(1);
                            return;
                     }
                     tmp = tmp->next;
              }

              if (foodx <= wallsX || foodx >= walleX || foody <= wallsY || foody >= walleY)
              {
                     // Generate new coordinates if the food is outside the wall
                     drawfood(1);
                     return;
              }
       }
}

void snake::move()
{
       tailPosition *tmp, *cur;

       tmp = current;

       while (tmp->prev != NULL)
       {
              tmp->x = tmp->prev->x;
              tmp->y = tmp->prev->y;
              tmp = tmp->prev;
       }

       if (d == 1)
              start->y--;

       if (d == 2)
              start->y++;

       if (d == 3)
              start->x--;

       if (d == 4)
              start->x++;
}

bool snake::collision()
{
       tailPosition *tmp;
       tmp = start->next;

       while (tmp->next != NULL)
       {
              if (start->x == tmp->x && start->y == tmp->y)
                     return true;

              tmp = tmp->next;
       }

       if (start->x == foodx && start->y == foody)
       {
              insert(foodx, foody);
              drawfood(1);
              score++;
       }


       for (int x = wallsX; x <= walleX; x++)
       {
              if (start->x == x && start->y == wallsY)
              {
                     return true;
              }
       }

       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == wallsX && start->y == y)
              {
                     return true;
              }
       }

       for (int y = wallsY; y <= walleY; y++)
       {
              if (start->x == walleX && start->y == y)
              {
                     return true;
              }
       }

       for (int x = wallsX; x <= walleX; x++)
       {
              if (start->x == x && start->y == walleY)
              {
                     return true;
              }
       }

       return false;
}

void snake::gameOver()
{
       system("cls"); // Clear the console screen

       cur_cord.X = (walleX / 4);
       cur_cord.Y = (walleY / 4);
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "YOU ARE DEAD\n";

       cur_cord.Y = (walleY / 4) + 1;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "YOUR HIGH SCORE IS " << score <<endl;

       cur_cord.Y = (walleY / 4) + 2;
       SetConsoleCursorPosition(console_handle, cur_cord);
       cout << "Thank you for enjoying the game created by GP 1." <<endl;

       // Ask the user if they want to play again
       char response;
       do {
              cur_cord.Y = (walleY / 4) + 3;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cout << "Do you want to play again? (y/n)" << endl;
              
              cur_cord.Y = (walleY / 4) + 4;
              SetConsoleCursorPosition(console_handle, cur_cord);
              cin >> response;
              
       } while (response != 'y' && response != 'n');

       if (response == 'y') {
              // Reset the game state and start a new game
              system("CLR");
              resetGame();
              startGame();
       } else {
              // Exit the game
              exit(0);
       }
} 

void snake::menu() //reading text file for menu
{
       ifstream iFile("menu.txt", ios::binary);
       while (iFile)
       {
              cout << (char)iFile.get();
       }
       iFile.close();
}

void snake::help() //reading text file for help
{
       ifstream iFile("help.txt");
       while (iFile)
       {
              cout << (char)iFile.get();
       }
       iFile.close();
       getch();
}

void loop(snake & ob) {
       int difLvl;

       do {
              COORD cur_cord;
              cur_cord.X = (70 / 3);
              cur_cord.Y = (20 / 3);

              HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
              SetConsoleCursorPosition(console_handle, cur_cord);

              cout << "Choose the difficulty level: 1 for easy, 2 for medium, 3 for difficult" << endl;
              cur_cord.Y = (20 / 3) + 1;
              SetConsoleCursorPosition(console_handle, cur_cord);

              cin >> difLvl;
              switch (difLvl) {
              case 1: {
              system("CLS");
              ob.insert(10, 6);
              ob.insert(10, 7);
              ob.insert(10, 8);
              ob.insert(10, 9);

              ob.drawWall();
              int dir = 1;
              while (1) {
                     ob.draw();
                     Sleep(275);

                     if (ob.collision()) {
                     ob.gameOver();
                     break;
                     }

                     if (kbhit()) {
                     switch (getch()) {
                     case 'w':
                     d = 1;
                     break;
                     case 's':
                     d = 2;
                     break;
                     case 'a':
                     d = 3;
                     break;
                     case 'd':
                     d = 4;
                     break;
                     default:
                     break;

                     }

                     }

                     ob.move();
              }
              break;
              }

              case 2: {
              system("CLS");
              ob.insert(10, 6);
              ob.insert(10, 7);
              ob.insert(10, 8);
              ob.insert(10, 9);

              ob.drawWall();
              int dir = 1;
              while (1) {
                     ob.draw();
                     Sleep(200);

                     if (ob.collision()) {
                     ob.gameOver();
                     break;
                     }

                     if (kbhit()) {
                     switch (getch()) {
                     case 'w':
                     d = 1;
                     break;
                     case 's':
                     d = 2;
                     break;
                     case 'a':
                     d = 3;
                     break;
                     case 'd':
                     d = 4;
                     break;
                     default:
                     break;

                     }

                     }

                     ob.move();
              }
              break;
              }

              case 3: {
              system("CLS");
              ob.insert(10, 6);
              ob.insert(10, 7);
              ob.insert(10, 8);
              ob.insert(10, 9);

              ob.drawWall();
              int dir = 1;
              while (1) {
                     ob.draw();
                     Sleep(100);

                     if (ob.collision()) {
                     ob.gameOver();
                     break;
                     }

                     if (kbhit()) {
                     switch (getch()) {
                     case 'w':
                     d = 1;
                     break;
                     case 's':
                     d = 2;
                     break;
                     case 'a':
                     d = 3;
                     break;
                     case 'd':
                     d = 4;
                     break;
                     default:
                     break;

                     }

                     }

                     ob.move();
              }
              break;
              }

              }
       }
       while (difLvl != 1 && difLvl != 2 && difLvl != 3);
}


void snake::startGame()
{
       system("CLS");

       snake start;
       start.menu();
       
       switch (getch())
       {
       case 's':
              system("CLS");
              loop(start);
              break;
       case 'h':
              system("CLS");
              start.help();
              system("CLS");
              startGame();
              break;
       case 'q':
              break;
       default:
              system("CLS");
              startGame();
       }
       
}

// void snake::startGame()
// {
//     resetGame();
//     loop(*this);
// }


int main()
{
       snake gp1;
       gp1.menu();
       
       switch (getch())
       {
       case 's':
              system("CLS");
              loop(gp1);
              break;
       case 'h':
              system("CLS");
              gp1.help();
              system("CLS");
              main();
              break;
       case 'q':
              break;
       default:
              system("CLS");
              main();
       }
       return 0;
}
