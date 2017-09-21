#include <sstream>
#include <SFML/Graphics/CircleShape.hpp>
#include <Packman.h>
#include <Pwar.h>
#include <random>

int main() {
    pWar::openSans.loadFromFile("resources/open-sans.ttf");
    const_cast<sf::Texture &>(pWar::openSans.getTexture(16)).setSmooth(true);


    sf::Clock fpsClock;
    sf::Clock generatorClock;
    sf::Clock sortClock;
    int frames = 0;

    pWar::window = new sf::RenderWindow(sf::VideoMode(pWar::screenWidth, pWar::screenHeight), "PWar!",
                                        sf::Style::Close);
    pWar::window->setFramerateLimit(500);

    bool startedSession = false;

    std::map<std::string, sf::Text> dString;

    Packman *strongest = nullptr;
    Packman *fastest = nullptr;

    pWar::packmanTexture.loadFromFile("resources/packman.png");
    pWar::packmanTexture.setSmooth(true);

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

                for (int i = 0; i < 1; ++i) {
                    auto *pack = new Packman(
                            sf::Vector2f(pWar::rnd(0, pWar::screenWidth), pWar::rnd(0, pWar::screenHeight)),
                            pWar::rnd(5, 10));
                    pWar::packmans.push_back(pack);
                }
            }
        }

        if(sortClock.getElapsedTime().asMilliseconds() >= 1000){
            pWar::packmans.sort([&](Packman *a, Packman *b) -> bool {
                return a->getStrength() > b->getStrength();
            });

            strongest = pWar::packmans.front();

            pWar::packmans.sort([&](Packman *a, Packman *b) -> bool {
                return a->getSpeed() > b->getSpeed();
            });

            fastest = pWar::packmans.front();
        }



        dString["d_fps"] = sf::Text("fps:" + std::to_string(fps), pWar::openSans, 14);
        dString["d_count"] = sf::Text("count:" + std::to_string(pWar::packmans.size()), pWar::openSans, 14);

        if (strongest && fastest) {
            dString["d_strongest"] = sf::Text("strongest:" + std::to_string(strongest->getStrength()), pWar::openSans, 14);
            dString["d_fastest"] = sf::Text("fastest:" + std::to_string(fastest->getSpeed()), pWar::openSans, 14);
        }

        if (strongest && strongest->getStrength() >= 150) {
            startedSession = false;
            strongest->setColor(sf::Color::Blue);
        }

        pWar::window->clear(sf::Color::Black);

        for (auto p:pWar::packmans) {
            p->update(*pWar::window, pWar::openSans);
        }

        int i = 0;
        for (auto s:dString) {
            s.second.setPosition(15, i * 15);
            s.second.setOrigin(0, 0);
            s.second.setFillColor(sf::Color::White);

            pWar::window->draw(s.second);
            i++;
        }

        pWar::window->display();
        frames++;
    }

    return 0;
}




