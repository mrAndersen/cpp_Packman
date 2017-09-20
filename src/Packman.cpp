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
    radius = strength * 1.2f;

    sf::Transform transform;
    transform.rotate(angle, position);


    if (clock.getElapsedTime().asMilliseconds() >= animationResolution) {
        clock.restart();
        currentFrame = (currentFrame == (frameCount - 1)) ? 0 : currentFrame + 1;
    }

    strengthText.setFont(font);
    strengthText.setPosition(position);
    strengthText.setString(std::to_string(strength));
    strengthText.setPosition(position);
    strengthText.setOrigin(sf::Vector2f(3, radius + 20));

    window.draw(strengthText);
    window.draw(vertexFrames[currentFrame], transform);
}

void Packman::updateLogic() {
    if (prey) {
        angle = angleToPrey();

        if (distanceToPrey(prey) <= radius + prey->radius) {
            //catched
            speed = speed - 1;

            if (speed <= 0) {
                speed = 0;
            }

            strength += 1;

            pWar::remove(prey);
        }
    } else {
        detectPrey();
    }

    float frameDistance = speed * frameTime.restart().asSeconds();
    auto rad = angle * M_PI / 180.f;

    position.x = position.x + (float) std::cos(rad) * frameDistance;
    position.y = position.y + (float) std::sin(rad) * frameDistance;


    correctWindowBoundaries();
    updateVertexCoordinates();
}

void Packman::correctWindowBoundaries() {
    if (position.x >= pWar::screenWidth) {
        position.x = 0;
    }

    if (position.y >= pWar::screenHeight) {
        position.y = 0;
    }

    if (position.x < 0) {
        position.x = pWar::screenWidth;
    }

    if (position.y < 0) {
        position.y = pWar::screenHeight;
    }
}

void Packman::updateVertexCoordinates() {
    float degreeStep = 360 / detalization;

    for (int k = 0; k < frameCount; ++k) {
        vertexFrames[k].setPrimitiveType(sf::TriangleFan);
        vertexFrames[k].resize(1);

        vertexFrames[k][0].position = position;
        vertexFrames[k][0].color = sf::Color::White;

        for (int i = 1; i < detalization; ++i) {
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
                vertexFrames[k].resize(i + 1);
                vertexFrames[k][i].position = sf::Vector2f(position.x + (float) std::cos(rad) * radius,
                                                           position.y + (float) std::sin(rad) * radius);
                vertexFrames[k][i].color = sf::Color::Yellow;
            }
        }

        //Shitty hack
        for (int j = 0; j < vertexFrames[k].getVertexCount(); ++j) {
            if (vertexFrames[k][j].position.x == 0 || vertexFrames[k][j].position.y == 0) {
                vertexFrames[k][j].position = position;
                vertexFrames[k][j].color = sf::Color::White;
            }
        }
    }
}

Packman::Packman(sf::Vector2f position, int strength) {
    setPosition(position);
    setStrength(strength);

    state = States::Living;

    strengthText.setFillColor(sf::Color::White);
    strengthText.setCharacterSize(16);

    updateVertexCoordinates();
}

void Packman::update(sf::RenderWindow &window, sf::Font &font) {
    updateLogic();
    draw(window, font);
}

float Packman::angleToPrey() {
    float angleToPrey = 0;

    if (prey) {
        angleToPrey = static_cast<float>(std::atan2(prey->position.y - position.y, prey->position.x - position.x) *
                                         180.f / M_PI);
    }

    return angleToPrey;
}

void Packman::detectPrey() {
    if (!prey) {
        std::vector<Packman *> targets;

        for (auto potentialPrey:pWar::packmans) {
            if (distanceToPrey(potentialPrey) <= visionRadius) {

                //sees the prey
                if (strength > potentialPrey->strength) {
                    targets.push_back(potentialPrey);
                }
            }
        }

        //selecting closes prey
        if (!targets.empty()) {
            std::sort(targets.begin(), targets.end(), [&](Packman *a, Packman *b) -> bool {
                return distanceToPrey(a) < distanceToPrey(b);
            });

            prey = targets[0];
            targets[0]->hunter = this;
        }
    }
}

int Packman::getStrength() const {
    return strength;
}

void Packman::setStrength(int strength) {
    Packman::strength = strength;
}

float Packman::distanceToPrey(Packman *packman) {
    if (packman) {
        return static_cast<float>(std::sqrt(std::pow(packman->position.x - position.x, 2) +
                                            std::pow(packman->position.y - position.y, 2)));
    }

    return 0;
}

Packman *Packman::getPrey() const {
    return prey;
}

void Packman::setPrey(Packman *prey) {
    Packman::prey = prey;
}




