#include <iostream>
#include <cmath>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3


string to_string(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(x<(GRIDSIZE-1))
        {
            x++;
        }
    }

    void moveLeft()
    {
        if(x>0)
        {
            x--;
        }
    }

    void moveUp()
    {
        if(y<(GRIDSIZE-1))
        {
            y++;
        }
    }

    void moveDown()
    {
        if(y>0)
        {
            y--;
        }
    }

    bool isAdjacent(Position p)
    {
        if(x == p.x)
        {
            if((y+1) == p.y || (y-1) == p.y )
            {
                return true;
            }
        }
        else if(y == p.y)
        {
            if((x+1) == p.x || (x-1) == p.x)
            {
                return true;
            }
        }
        return false;
    }

    bool isSamePoint(Position p)
    {
        if(x == p.x && y == p.y)
        {
            return true;
        }
        return false;
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class Wumpus
{

    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        srand(time(NULL));
        int x=rand()%4;
        int y=rand()%4;
        p=Position(x,y);
        killed=false;
    }

    void kill()
    {
        killed = true;
    }

    Position getPosition()
    {
        return p;
    }

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
        direction=UP;
        total_shots=MAX_SHOTS;
        killed=false;
        p=Position(0,0);
    }

    void turnLeft()
    {
        switch(direction)
        {
        case UP:
            direction=LEFT;
            break;
        case LEFT:
            direction=DOWN;
            break;
        case DOWN:
            direction=RIGHT;
            break;
        default:
            direction=UP;
            break;
        }
    }

    void turnRight()
    {
        switch(direction)
        {
        case UP:
            direction=RIGHT;
            break;
        case LEFT:
            direction=UP;
            break;
        case DOWN:
            direction=LEFT;
            break;
        default:
            direction=DOWN;
            break;
        }
    }

    void moveForward()
    {
        switch(direction)
        {
        case UP:
            p.moveUp();
            break;
        case DOWN:
            p.moveDown();
            break;
        case LEFT:
            p.moveLeft();
            break;
        default:
            p.moveRight();
            break;
        }
    }

    bool isAdjacent(Position pos)
    {
        return p.isAdjacent(pos);
    }

    bool isSamePoint(Position pos)
    {
        return p.isSamePoint(pos);
    }

    void kill()
    {
        killed = true;
    }

   /* string getPositionInfo()
    {
         return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }*/

    string getDirectionInfo()
    {
        string s;
        if (direction == UP) s = "up";
        if (direction == DOWN) s = "down";
        if (direction == LEFT) s = "left";
        if (direction == RIGHT) s = "right";
        return "Player is moving at direction: " + s;
    }

    Position getPosition()
    {
        return p;
    }

    int getDirection()
    {
        return direction;
    }

    int getTotalShots()
    {
        return total_shots;
    }

    void decreaseShots()
    {
        total_shots--;
    }
};

class Pit
{
    Position p;
public:
    Pit()
    {
        srand(time(NULL));
        int x=rand()%4;
        int y=rand()%4;
        p=Position(x,y);
    }
    Pit(int x, int y)
    {
        p=Position(x,y);
    }
    Position getPosition()
    {
        return p;
    }
};

class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Pit pit;
    Position gold_position;
    bool ended;

public:

    WumpusWorld()
    {
        player=Player();
        wumpus=Wumpus();
        pit=Pit();
        srand(time(NULL));
        int x=rand()%4;
        int y=rand()%4;
        gold_position=Position(x,y);
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        player=Player();
        wumpus=Wumpus(wumpus_x,wumpus_y);
        pit=Pit();
        srand(time(NULL));
        int x=rand()%4;
        int y=rand()%4;
        gold_position=Position(x,y);
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        player=Player();
        wumpus=Wumpus(wumpus_x, wumpus_y);
        pit=Pit();
        gold_position=Position(gold_x,gold_y);
        ended=false;
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        player=Player();
        wumpus=Wumpus(wumpus_x,wumpus_y);
        pit=Pit(pit_x,pit_y);
        gold_position=Position(gold_x,gold_y);
        ended=false;
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        if(player.getTotalShots())
        {
            player.decreaseShots();
            if (player.getDirection() == UP)
            {
                for (int i = player.getPosition().getY(); i < GRIDSIZE; i++)
                {
                    if (wumpus.getPosition().isSamePoint(Position(player.getPosition().getX(), i)))
                    {
                        cout << "You shot the Wumpus!" << endl;
                        wumpus.kill();
                        wumpus=Wumpus(4,4);
                        return showGameState();
                    }
                }
            }
            else if (player.getDirection() == DOWN)
            {
                for (int i = player.getPosition().getY(); i >= 0; i--)
                {
                    if (wumpus.getPosition().isSamePoint(Position(player.getPosition().getX(), i)))
                    {
                        cout << "You shot the Wumpus!" << endl;
                        wumpus.kill();
                        wumpus=Wumpus(4,4);
                        return showGameState();
                    }
                }
            }
            else if (player.getDirection() == LEFT)
            {
                for (int i = player.getPosition().getX(); i >= 0; i--)
                {
                    if (wumpus.getPosition().isSamePoint(Position(i, player.getPosition().getY())))
                    {
                        cout << "You shot the Wumpus!" << endl;
                        wumpus.kill();
                        wumpus=Wumpus(4,4);
                        return showGameState();
                    }
                }
            }
            else if (player.getDirection() == RIGHT)
            {
                for (int i = player.getPosition().getX(); i < GRIDSIZE; i++)
                {
                    if (wumpus.getPosition().isSamePoint(Position(i, player.getPosition().getY())))
                    {
                        cout << "You shot the Wumpus!" << endl;
                        wumpus.kill();
                        wumpus=Wumpus(4,4);
                        return showGameState();
                    }
                }
            }

            cout << "You missed the shot!" << endl;

            if (player.getTotalShots() == 0)
            {
                cout << "You are out of arrows!" << endl;
            }
        }
    else
    {
        cout << "You are out of arrows!" << endl;
    }

    return showGameState();
}



void showGameState()
{
    cout << "Player is now at:"<<player.getPosition().getX()<<","<<player.getPosition().getY()<< endl;
    cout << player.getDirectionInfo() << endl;

    if (player.isAdjacent(wumpus.getPosition()))
    {
        cout << "stench!" << endl;
    }
    if (player.isAdjacent(pit.getPosition()))
    {
        cout << "breeze!" << endl;
    }
    if (player.isSamePoint(wumpus.getPosition()))
    {
        cout << "Player is killed!" << endl;
        player.kill();
        cout << "Game over!" << endl;
        ended = true;
    }
    if (player.isSamePoint(pit.getPosition()))
    {
        cout << "Player is killed!" << endl;
        player.kill();
        cout << "Game over!" << endl;
        ended = true;
    }
    if (player.isSamePoint(gold_position))
    {
        cout << "Got the gold!" << endl;
        cout << "Game ended, you won!" << endl;
        ended = true;
    }
}

bool isOver()
{
    return ended;
}

};

int main()
{
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
    ifstream fin("in.txt");
    if(!fin)
    {
        cout<<"Failed to open the file."<<endl;
        return -1;
    }
    fin>>wumpus_x>>wumpus_y>>gold_x>>gold_y>>pit_x>>pit_y;
    fin.close();
    /*cin>>wumpus_x>>wumpus_y>>gold_x>>gold_y>>pit_x>>pit_y;*/
    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    return 0;
}
