#include <cmath>
#include "Packman.h"
#include "Pwar.h"

const sf::Vector2f &Packman::getPosition() const {
    return position;
}

void Packman::setPosition(const sf::Vector2f &position) {
    Packman::position = position;
}

void Packman::draw(sf::RenderWindow &window, sf::Font &font) {
    sf::Transform transform;

//    transform.scale(-1.f, 1.f, position.x, position.y);

    if (clock.getElapsedTime().asMilliseconds() >= animationResolution) {
        clock.restart();
        currentFrame = (currentFrame == (frameCount - 1)) ? 0 : currentFrame + 1;
    }

    window.draw(vertexFrames[currentFrame], transform);

    strengthText.setFont(font);
    strengthText.setPosition(position);
    strengthText.setString(std::to_string(strength));
    strengthText.setPosition(position);

    window.draw(strengthText);
}

void Packman::updateLogic() {
    float frameDistance = speed * frameTime.restart().asSeconds();

    if (state == States::Living) {
        position.x += frameDistance;
    }

    if (position.x >= pWar::screenWidth) {
        position.x = 0;
    }

    if (position.y >= pWar::screenHeight) {
        position.y = 0;
    }

    updateVertexCoordinates();
}

void Packman::updateVertexCoordinates() {
    float degreeStep = 360 / detalization;

    for (int k = 0; k < frameCount; ++k) {

        vertexFrames[k][0].position = position;

        for (int i = 1; i < vertexFrames[k].getVertexCount(); ++i) {
            auto rad = degreeStep * i * M_PI / 180.f;

            vertexFrames[k][i].position = sf::Vector2f(position.x + (float) std::cos(rad) * radius,
                                                       position.y + (float) std::sin(rad) * radius);
        }
    }
}

Packman::Packman(sf::Vector2f position) {
    setPosition(position);
    state = States::Living;

    strengthText.setFillColor(sf::Color::White);
    strengthText.setCharacterSize(10);

    strengthText.setOrigin(sf::Vector2f(0, radius + 14));

    for (int k = 0; k < frameCount; ++k) {
        vertexFrames[k].setPrimitiveType(sf::TriangleFan);
        vertexFrames[k].append(sf::Vertex(position, sf::Color::Yellow));

        float degreeStep = 360 / detalization;

        for (int i = 0; i < detalization; ++i) {
            auto rad = degreeStep * i * M_PI / 180.f;
            bool mouthCondition = false;

            switch (k) {
                case 0:
                    mouthCondition = degreeStep * i >= 45 && degreeStep * i <= 315;
                    break;
                case 1:
                    mouthCondition = degreeStep * i >= 22.5 && degreeStep * i <= 337.5;
                    break;
                case 2:
                    mouthCondition = degreeStep * i >= 11.25 && degreeStep * i <= 348.75;
                    break;
                case 3:
                    mouthCondition = true;
                    break;
                default:
                    break;
            }

            if (mouthCondition) {
                vertexFrames[k].append(sf::Vertex(sf::Vector2f(position.x + (float) std::cos(rad) * radius,
                                                               position.y + (float) std::sin(rad) * radius),
                                                  sf::Color::Yellow));
            }
        }
    }
}

void Packman::update(sf::RenderWindow &window, sf::Font &font) {
    updateLogic();
    draw(window, font);
}


