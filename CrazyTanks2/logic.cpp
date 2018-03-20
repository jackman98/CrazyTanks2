#include "logic.h"

Logic::Logic()
{
}

void Logic::process()
{
    while (!m->stopGame) {
        //my bullet pull processing
        for(size_t i = 0; i < m->myBullets.size(); i++) {
            if (m->myBullets[i] != nullptr) {
                //if the shot was fired
                if (m->myBullets[i]->isShotMade) {
                    //continue to move the bullet
                    BulletAction ba;
                    ba.shot(*m->myBullets[i]);
                }
                else {
                    delete m->myBullets[i];
                    m->myBullets[i] = nullptr;
                    m->myBullets.erase(m->myBullets.begin() + i);
                    vector<Bullet *>(m->myBullets).swap(m->myBullets);
                }
            }
        }

        //enemy bullet pull processing
        for(size_t i = 0; i < m->enemyBullets.size(); i++) {
            if (m->enemyBullets[i] != nullptr) {
                //if the shot was fired
                if (m->enemyBullets[i]->isShotMade) {
                    //continue to move the bullet
                    BulletAction ba;
                    ba.shot(*m->enemyBullets[i]);
                }
                else {
                    delete m->enemyBullets[i];
                    m->enemyBullets[i] = nullptr;
                    m->enemyBullets.erase(m->enemyBullets.begin() + i);
                    vector<Bullet *>(m->enemyBullets).swap(m->enemyBullets);
                }
            }
        }

        for (size_t i = 0; i < m->enemyTanks.size(); ++i) {
            //if the tank zero health increases the score and remove the tank
            if (m->enemyTanks[i]->health == 0) {
                m->score++;
                delete m->enemyTanks[i];
                m->enemyTanks[i] = nullptr;
                m->enemyTanks.erase(m->enemyTanks.begin() + i);
                vector<Tank *>(m->enemyTanks).swap(m->enemyTanks);
            }
        }

        if (m->tank->health == 0) {
            m->loss = true;
            m->victory = false;
        }

        if (m->enemyTanks.empty()) {
            m->loss = false;
            m->victory = true;
        }

        if (m->loss || m->victory)
            m->stopGame = true;

        this_thread::sleep_for(chrono::milliseconds(BULLET_SPEED));
    }
}
