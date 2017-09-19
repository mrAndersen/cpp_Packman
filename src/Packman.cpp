#include <cmath>
#include "Packman.h"

const sf::Vector2f &Packman::getPosition() const {
    return position;
}

void Packman::setPosition(const sf::Vector2f &position) {
    Packman::position = position;
}

void Packman::draw(sf::RenderWindow &window) {
//    sf::Transform transform;
//
//    transform.rotate(90);

    window.draw(verticies);
}

Packman::Packman(sf::Vector2f position) {
    setPosition(position);

    int detalization = 20;
    int radius = 15;
    float degreeStep = 360 / detalization;

    verticies.append(sf::Vertex(position, sf::Color::Yellow));
    verticies.setPrimitiveType(sf::TriangleFan);

    for (int i = 0; i < detalization; ++i) {
        auto rad = degreeStep * i * M_PI / 180.f;

        if (degreeStep * i > 22.5 && degreeStep * i < 337.5) {
            verticies.append(sf::Vertex(
                    sf::Vector2f(position.x + (float) std::cos(rad) * radius,
                                 position.y + (float) std::sin(rad) * radius),
                    sf::Color::Yellow));
        }
    }

    state = States::Living;
}
