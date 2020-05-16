#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

using namespace std;

const int Height=20;  //for height of play area
const int Width=20;   // for width of play area

enum DIRECTION{ STOP=0,LEFT,RIGHT,UP,DOWN};  //for direction of movement of snake

class Snake
{
    private:
        int headX;        //coordinate of head
        int headY;
        int tailX[100];   //coordinate of tails
        int tailY[100];
        int tailLength;   //length of snake
        int preyX;        // coordinate of prey
        int preyY;
        DIRECTION dir;    //direction of movement of snake
    public:
        bool Gameover;    //to check whether game is over or not
        int Score;        //to count the score
        void Setup();     //to initialize the game screen
        void paint();     //to paint play area
        void Move();      //to move accordance with user input
        void Play();      //main movement and interaction here
};
void Snake::Setup()
{
    Score=0;           //initially score is 0
    dir=STOP;          //so that snake doesn't move right from starting
    Gameover = false;  //initially game is not over
    tailLength=0;      //no tail at start
    headX = Width/2;   //stating coordinates of head
    headY = Height/2;
    preyX = rand() % Width;  //starting coordinates of prey
    preyY = rand() % Height;
}

void Snake::paint()
{
    int i;
    HANDLE hStdout;    // to overwrite on previous screen
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    //position cursor at start of window
    destCoord.X = 0;
    destCoord.Y = 0;
    SetConsoleCursorPosition(hStdout, destCoord);

    for(i=0;i<Width+2;i++)  // printing the boundaries,snake and prey
    cout<<"X";
    cout<<endl;

    for(i=0;i<Height;i++){
        for(int j=0;j<Width;j++){
            if(j==0)
                cout<<"X";
            if(i==headY && j==headX){
                cout<<"O";
            }
            else if(i==preyY && j==preyX){
                cout<<"*";
            }
            else{
                bool print= false;
                for(int k=0;k<tailLength;k++){
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                    cout<<" ";
            }
            if(j==Width-1)
                cout<<"X";
        }
        cout<<endl;
    }

    for(i=0;i<Width+2;i++)
        cout<<"X";
    cout<<endl;
    cout<<"Score: "<<Score<<endl;
}

void Snake::Move()
{
    if(_kbhit())  //check if key is pressed on keyboard or not
    {
        switch(_getch())  //which value is inserted through keyboard
        {
        case 'a':   // if pressed 'a' move left
            dir=LEFT;
            break;
        case 'w':
            dir=UP; // if pressed 'w' move up
            break;
        case 's':
            dir=DOWN; // if pressed 's' move down
            break;
        case 'd':    // if pressed 'd' move right
            dir=RIGHT;
            break;
        case 'x':    // exit if pressed 'x'
            Gameover=true;
            break;
        }
    }
}

void Snake::Play()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
    int prev2X,prev2Y;
    tailX[0]=headX;     // initial position of head assigned to tail array
    tailY[0]=headY;
    for(int i=1;i<tailLength;i++)  //updating values of each tail
    {
        prev2X=tailX[i];
        prev2Y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2Y;
    }
    switch(dir)   //where to move
    {
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    case STOP:
        break;
    }
    if(headX>Width || headX<0 || headY>Height || headY<0)   //game over if head touches wall
        Gameover=true;
    for(int j=0;j<tailLength;j++)       // game over if head touches body
    {
        if(headX==tailX[j] && headY==tailY[j]){
            Gameover=true;
        }
    }
    if(headX==preyX && headY==preyY)  // if snake eat prey
    {
        Score+=10;    // inc score
        preyX = rand() % Width;  //new coordinated of prey
        preyY = rand() % Height;
        tailLength++;  // tail increases
    }
}

int main()
{
    Snake game;
    char ch;
    do{
        system("cls");
        game.Setup();           //initial setting up of game
        while(!game.Gameover){  //repaint until game is not over
            game.paint();       //paint new position
            game.Move();        //movement of snake
            game.Play();        //check everything related
            Sleep(10);          //so that game is not too fast
        }
        cout<<"Play again(y/n): "<<endl;
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    return 0;
}
