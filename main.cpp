#include <sstream>
#include <SFML/Graphics/CircleShape.hpp>
#include <Packman.h>
#include <Pwar.h>
#include <random>

int main() {
    pWar::openSans.loadFromFile("resources/open-sans.ttf");
    const_cast<sf::Texture &>(pWar::openSans.getTexture(10)).setSmooth(true);


    sf::Clock fpsClock;
    sf::Clock generatorClock;
    int frames = 0;

    pWar::window = new sf::RenderWindow(sf::VideoMode(pWar::screenWidth, pWar::screenHeight), "PWar!");
    pWar::window->clear(sf::Color::Black);

    bool startedSession = false;

    while (pWar::window->isOpen()) {
        int fps = (int) (frames / fpsClock.getElapsedTime().asSeconds());

        sf::Event e{};
        pWar::window->setTitle(
                "PWar ~ [" + std::to_string(fps) + "FPS] [" + std::to_string(pWar::packmans.size()) + "]");

        while (pWar::window->pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                pWar::window->close();
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                startedSession = true;
            }

            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Right) {
                startedSession = false;
            }
        }


        if (startedSession) {

            if (generatorClock.getElapsedTime().asMilliseconds() >= 50) {
                generatorClock.restart();

                auto *pack = new Packman(
                        sf::Vector2f(pWar::rnd(0, pWar::screenWidth), pWar::rnd(0, pWar::screenHeight)),
                        pWar::rnd(5, 10));
                pWar::packmans.push_back(pack);
            }
        }


        pWar::window->clear();

        for (auto p:pWar::packmans) {
            p->update(*pWar::window, pWar::openSans);
        }

        pWar::window->display();
        frames++;
    }

    return 0;
}




