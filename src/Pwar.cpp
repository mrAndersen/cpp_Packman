#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <list>
#include <random>
#include "Packman.h"

namespace pWar {
    sf::RenderWindow *window;

    int screenWidth = 1600;
    int screenHeight = 600;

    sf::Font openSans;
    std::list<Packman *> packmans;

    int rnd(int min, int max) {
        static bool first = true;

        if (first) {
            srand(time(NULL)); //seeding for the first time only!
            first = false;
        }
        return min + rand() % (max - min);
    }

    void remove(Packman *item) {
        //delete all prey targets if has one
        for (auto packman:packmans) {
            if (packman->getPrey() == item) {
                packman->setPrey(nullptr);
            }
        }

        auto it = packmans.begin();
        while (it != packmans.end()) {
            if (*it == item) {
                it = packmans.erase(it);
                delete item;
            } else {
                ++it;
            }
        }
    }
}