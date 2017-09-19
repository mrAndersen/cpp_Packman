#include <cmath>
#include "Packman.h"

const sf::Vector2f &Packman::getPosition() const {
    return position;
}

void Packman::setPosition(const sf::Vector2f &position) {
    Packman::position = position;
}

void Packman::draw(sf::RenderWindow &window) {
    sf::Transform transform;

    if (clock.getElapsedTime().asMilliseconds() == animationResolution) {
        clock.restart();
        currentFrame = (currentFrame == 2) ? 0 : currentFrame + 1;
    }

    window.draw(vertexFrames[currentFrame], transform);
}

Packman::Packman(sf::Vector2f position) {
    setPosition(position);

    int detalization = 180;
    int radius = 15;
    float degreeStep = 360 / detalization;

    for (int k = 0; k < 3; ++k) {
        vertexFrames[k].append(sf::Vertex(position, sf::Color::Yellow));
        vertexFrames[k].setPrimitiveType(sf::TriangleFan);

        for (int i = 0; i < detalization; ++i) {
            auto rad = degreeStep * i * M_PI / 180.f;
            bool mouthCondition = false;

            switch (k) {
                case 0:
                    mouthCondition = degreeStep * i >= 22.5 && degreeStep * i <= 337.5;
                    break;
                case 1:
                    mouthCondition = degreeStep * i >= 11.25 && degreeStep * i <= 348.75;
                    break;
                case 2:
                    mouthCondition = degreeStep * i >= 0 && degreeStep * i <= 360;
                    break;
                default:
                    break;
            }

            if (mouthCondition) {
                vertexFrames[k].append(sf::Vertex(
                        sf::Vector2f(position.x + (float) std::cos(rad) * radius,
                                     position.y + (float) std::sin(rad) * radius),
                        sf::Color::Yellow));
            }
        }
    }

    state = States::Living;
}
