#include <iostream>
#include <conio.h>

using namespace std;
bool gameOver;
int x, y, Fruit_x, Fruit_y;
int score = 0;
int nTail = 0;
int TailX[100], TailY[100];
const int width = 20;
const int height = 20;
enum E_move{STOP = 0, RIGHT, LEFT, UP, DOWN};
E_move dir;
void Setup(){
    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    Fruit_x = rand() % width;
    Fruit_y = rand() % height;

}

void Draw(){
    system("cls");
    for(int i = 0; i < width+1; i++)
        cout << "#";
    cout<<endl;
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            if (j == 0 || j == width-1)
                cout << "#";
            if (j == x && i == y)
                cout << "0";
            else if (j == Fruit_x && i == Fruit_y)
                cout << "@";
            else {
                bool tail = false;
                for (int k = 0; k < nTail; k++)
                    if (TailX[k] == j && TailY[k] == i) {
                        cout << "o";
                        tail = true;
                    }
                if (!tail)
                    cout << " ";
            }
        }
        cout<<endl;
    }
    for(int i = 0; i < width+1; i++)
        cout << "#";
    cout<<endl;
    cout << "Score: "<< score << endl;

}

void Input(){
    if (_kbhit()){
        switch (_getch())
        {
            case 'a':
                dir = LEFT;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 'x':
                gameOver = true;
        }
    }
}

void Logic(){
    int prevX = TailX[0];
    int prevY = TailY[0];
    TailX[0] = x;
    TailY[0] = y;
    int prev2X, prev2Y;
    for (int i = 1; i < nTail; i++){
        prev2X = TailX[i];
        TailX[i] = prevX;
        prevX = prev2X;
        prev2Y = TailY[i];
        TailY[i] = prevY;
        prevY = prev2Y;
    }
    switch (dir){
        case LEFT:
            x--;
            break;
        case DOWN:
            y++;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
    }
    if (x >= width - 1)
        x = 0;
    else if(x < 0)
        x = width - 2;

    if (y >= height)
        y = 0;
    else if(y < 0)
        y = height - 1;
    for (int i = 0; i < nTail; i++)
        if (TailX[i] == x && TailY[i] == y)
            gameOver = true;
    if (x == Fruit_x && y == Fruit_y){
        score += 10;
        Fruit_x = rand() % width;
        Fruit_y = rand() % height;
        nTail++;
    }
}
int main() {
    Setup();
    while (!gameOver){
        Draw();
        Input();
        Logic();
    }
    return 0;
}