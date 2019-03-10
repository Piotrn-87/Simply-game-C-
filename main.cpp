#include <iostream>
#include <windows.h> // system(), Beep(), sleep()
#include <conio.h> // getch()
#include <vector> // vector

// Stale typu int
int const MAP_X = 20;
int const MAP_Y = 30;

using namespace std;


struct Position2D     // Przechowuje pozycjê na plaszczyznie 2d
{
    int x, y;
};

class Game  // Glowna klasa gry
{
    Position2D player;
    vector<Position2D> monsters;    // vector typu Position2D
    int score;
    int monster_selected;
    bool not_failed;
public:
    Game (int score = 0, int monster_selected = 0, bool not_failed = true)
    //Game() : monster_selected(0), score(0), not_failed(true)
    {
        this -> score = score;
        this -> monster_selected = monster_selected;
        this -> not_failed = not_failed;

        player.x = 10;  // Pozycja gracza na start
        player.y = 15;

    }
    void fail()  // Przegrana
    {
        system("cls");
        cout << "GAME OVER!" << endl;
        cout << "Monsters: " << monster_selected << endl;
        cout << "Score: " << score * monster_selected  << endl;
        //Beep(500, 200);
        //Beep(500, 200);
        //Beep(500, 200);
        //system("pause");
        not_failed = false;
    }
    bool fail_check ()
    {
        return not_failed;
    }

    void start()    // Start gry
    {
        system("title game");
        int wybor;// = getch(); //char menu = 'f';

        cout << " Ile potworow " << endl;
        cout << " 1 2 3 4 " << endl;

           cin >> wybor;

            switch(wybor)
            {
            case 1:
                create_monsters(1);
                monster_selected = 1;
                break;
            case 2:
                create_monsters(2);
                monster_selected = 2;
                break;
            case 3:
                create_monsters(3);
                monster_selected = 3;
                break;
            case 4:
                create_monsters(4);
                monster_selected = 4;
                break;
            default:
                cout << " Bledny wybor !!! " << endl;
                exit(0);
            }
            //not_failed = true;

        system("cls");
    }

    // Stworzenie potworow
    void create_monsters(int number)
    {
        // Tworzy potwory
        Position2D monster1 = {19, 29};
        Position2D monster2 = {0, 0};
        Position2D monster3 = {0, 29};
        Position2D monster4 = {19, 0};
        Position2D monster5 = {1, 1};
        Position2D monster6 = {20, 20};

        // Wrzuca stworzone potwory do wektora
        // w zeleznosci od tego ile zostalo wybranych
        switch(number)
        {
        case 1:
            monsters.push_back(monster1);
            break;
        case 2:
            monsters.push_back(monster1);
            monsters.push_back(monster2);
            break;
        case 3:
            monsters.push_back(monster1);
            monsters.push_back(monster2);
            monsters.push_back(monster3);
            break;
        case 4:
            monsters.push_back(monster1);
            monsters.push_back(monster2);
            monsters.push_back(monster3);
            monsters.push_back(monster4);
            //monsters.push_back(monster6);
            break;
        }
    }

    // Podnosi wynik
    void score_up()
    {
        score++;
    }

    // Zwraca referencje do wektora Position2D
    // ktorzy przechowuje pozycje potworow
    vector<Position2D> &return_ref_to_monster()
    {
        return monsters;
    }

    // Przesuwa gracza
    void move_player()
    {
        // Pobiera klawisz do zmiennej move
        char move = getch();

        switch(move)
        {
        case 'w':
            if(player.x-1 == -1)
                break;
            else
                player.x-=2;
            break;
        case 's':
            if(player.x+1 == MAP_X)
                break;
            else
                player.x+=2;
            break;
        case 'a':
            if(player.y-1 == -1)
                break;
            else
                player.y--;
            break;
        case 'd':
            if(player.y+1 == MAP_Y)
                break;
            else
                player.y++;
            break;
        }
    }

    // "ai" potworow
    void monster_ai()
    {
        // Prosty algorytm goniacego
        for(int i = 0; i < monsters.size(); i++)
        {
            if(monsters[i].x < player.x)
                monsters[i].x++;
            if(monsters[i].x > player.x)
                monsters[i].x--;
            if(monsters[i].y < player.y)
                monsters[i].y++;
            if(monsters[i].y > player.y)
                monsters[i].y--;
            //if(monsters[i].x < player.x)
            //  monsters[i].x++;

            // Jezeli jakis potwor ma takie same pozycje jak gracz
            // To znaczy, ze go zlapal wiec koniec gry
            if(monsters[i].y == player.y && monsters[i].x == player.x)
            {
                cout << "Got you!" << endl;
                fail();//not_failed = true;
            }
        }
    }

    // Zwraca referencje do Position2D przechowujacego
    // pozycje gracza
    Position2D& return_ref_to_player()
    {
        return player;
    }
};

class Map
{
    // Mapa gry
    int map[MAP_X][MAP_Y];

public:
    // Zeruje mape
    Map()
    {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                map[i][j] = 0;
            }
        }
    }

    // Rysuje mape
    void draw()
    {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                // Zamienia liczy na
                // odpowiednie znaki graficzne
                switch(map[i][j])
                {
                case 0:
                    cout << "-";
                    break;
                case 1:
                    cout << "M";
                    break;
                case 2:
                    cout << "Y";
                    break;
                }
            }
            // Kolejny wiersz mapy
            cout << endl;
        }
    }

    // Resetuje mape
    void reset()
    {
        for(int i = 0; i < MAP_X; i++)
        {
            for(int j = 0; j < MAP_Y; j++)
            {
                map[i][j] = 0;
            }
        }
    }
    // Umieszcza gracza na mapie
    void put_player(Position2D& player)
    {
        map[player.x][player.y] = 2;
    }

    // Umieszcza potwory na mapie
    void put_monster(vector<Position2D>& monsters)
    {
        for(int i = 0; i < monsters.size(); i++)
        {
            map[monsters[i].x][monsters[i].y] = 1;
        }
    }
};


int main()
{
    Map m;
    Game g;

    g.start();

    while (g.fail_check())
    {
        m.reset();
        m.put_player(g.return_ref_to_player());
        m.put_monster(g.return_ref_to_monster());
        m.draw();
        g.monster_ai();
        g.move_player();
        g.score_up();
        system("cls");
    }

    return 0;
}
