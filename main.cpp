#include <sstream>
#include <SFML/Graphics/CircleShape.hpp>
#include <Packman.h>
#include <Pwar.h>

int main() {
    sf::Font openSans;

    openSans.loadFromFile("resources/open-sans.ttf");
    const_cast<sf::Texture &>(openSans.getTexture(10)).setSmooth(true);

    std::vector<Packman *> packmans;
    sf::Clock fpsClock;
    int frames = 0;

    pWar::window = new sf::RenderWindow(sf::VideoMode(pWar::screenWidth, pWar::screenHeight), "PWar!");
    pWar::window->clear(sf::Color::Black);

    while (pWar::window->isOpen()) {
        int fps = (int) (frames / fpsClock.getElapsedTime().asSeconds());

        sf::Event e{};
        pWar::window->setTitle("PWar ~ [" + std::to_string(fps) + "FPS] [" + std::to_string(packmans.size()) + "]");

        while (pWar::window->pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                pWar::window->close();
            }


            if (e.type == sf::Event::MouseButtonPressed) {
                packmans.push_back(new Packman(
                        sf::Vector2f(sf::Mouse::getPosition(*pWar::window).x,
                                     sf::Mouse::getPosition(*pWar::window).y)));
            }
        }

        pWar::window->clear();

        for (auto packman:packmans) {
            packman->update(*pWar::window, openSans);
        }

        pWar::window->display();
        frames++;
    }

    return 0;
}




