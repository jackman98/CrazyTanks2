#include "render.h"
#include <iomanip>
//#include <windows.h>

Render::Render()
{
}

void Render::draw()
{
    int position = (WIDTH / 2 + TITLE.size() / 2);

    system("cls");
    //    setcur(0,0);
    string str;

    cout << setw(position) << TITLE << endl;
    cout << "Score: " << m->score << " | Health: " << m->tank->health << " | Time : " << m->timeInGame << endl;

    //draw field
    for (size_t i = 0; i < m->field.size(); i++) {
        for (size_t j = 0; j < m->field.at(i).size(); j++) {
            str += m->field.at(i).at(j).getCode();
        }
        str += "\n";
    }
    cout << str;


    if (m->victory) {
        cout << "YOU WINNER!!!";
    }
    else if (m->loss) {
        cout << "GAME OVER!!!";
    }
}

//
//The use of this function instead of "system("cls");" gives a better and optimized rendering
//
//void setcur(int x, int y)
//{
//    COORD coord;
//    coord.X = x;
//    coord.Y = y;
//    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//}

void Render::process()
{
    while (!m->stopGame) {
        draw();
        this_thread::sleep_for(chrono::milliseconds(RENDER_TIME));
    }
}



