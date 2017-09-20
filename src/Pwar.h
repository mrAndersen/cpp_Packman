#ifndef PWAR_PWAR_H
#define PWAR_PWAR_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <list>

namespace pWar {
    extern sf::RenderWindow *window;

    extern int screenWidth;
    extern int screenHeight;

    extern sf::Font openSans;
    extern std::list<Packman *> packmans;

    int rnd(int min, int max);

    void remove(Packman *item);
}
#endif //PWAR_PWAR_H
