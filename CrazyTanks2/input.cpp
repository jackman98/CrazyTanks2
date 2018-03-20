#include "input.h"
#include "bullet.h"

Input::Input()
{
}

void Input::process()
{
    auto myTank = m->tank;
    while (!m->stopGame) {
        //key processing
        if (_kbhit()) {
            switch (_getch()) {
            case 72:
                myTank->move(m->field, Direction::UP);
                break;
            case 80:
                myTank->move(m->field, Direction::DOWN);
                break;
            case 75:
                myTank->move(m->field, Direction::LEFT);
                break;
            case 77:
                myTank->move(m->field, Direction::RIGHT);
                break;
            case 32: {
                //create new bullet and add in myBullets pull
                Bullet *b = new Bullet (myTank->x, myTank->y, myTank->type, myTank->direction);
                m->myBullets.push_back(b);
                break;
            }
            }
        }
        this_thread::sleep_for(chrono::milliseconds(INPUT_TIME));
    }
}
