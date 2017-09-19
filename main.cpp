#include <sstream>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <Packman.h>

sf::RenderWindow *window;

int main() {
    std::vector<Packman *> packmans;
    sf::Clock fpsClock;
    int frames = 0;

    window = new sf::RenderWindow(sf::VideoMode(1600, 600), "Packmans!");
    window->clear(sf::Color::Black);

    while (window->isOpen()) {
        int fps = (int) (frames / fpsClock.getElapsedTime().asSeconds());

        sf::Event e{};
        window->setTitle("Packmans! ~ [" + std::to_string(fps) + "FPS] [" + std::to_string(packmans.size()) + "]");

        while (window->pollEvent(e)) {

            if (e.type == sf::Event::Closed) {
                window->close();
            }


            if (e.type == sf::Event::MouseButtonPressed) {
                packmans.push_back(new Packman(
                        sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y)));
            }
        }


        window->clear();


        for (auto packman:packmans) {
            packman->draw(*window);
        }

        window->display();
        frames++;
    }

    return 0;
}

