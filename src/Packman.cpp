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
    radius = strength * 1.1f;

    if (clock.getElapsedTime().asMilliseconds() >= animationResolution) {
        clock.restart();
        currentFrame = (currentFrame == (frameCount - 1)) ? 0 : currentFrame + 1;
    }

    sprite.setTextureRect(frames[currentFrame]);
    sprite.setScale(radius / 44, radius / 44);
    sprite.setPosition(position);
    sprite.setRotation(angle);
    sprite.setColor(color);
    window.draw(sprite);

    strengthText.setFont(font);
    strengthText.setPosition(position);
    strengthText.setString(std::to_string(strength));
    strengthText.setOrigin(sf::Vector2f(5, radius + 20));
    window.draw(strengthText);


    sf::VertexArray quad;
    quad.setPrimitiveType(sf::LineStrip);
    quad.resize(5);

//    quad[0].position = sf::Vector2f(position.x - radius, position.y - radius);
//    quad[1].position = sf::Vector2f(position.x + radius, position.y - radius);
//    quad[2].position = sf::Vector2f(position.x + radius, position.y + radius);
//    quad[3].position = sf::Vector2f(position.x - radius, position.y + radius);
//    quad[4].position = sf::Vector2f(position.x - radius, position.y - radius);
//
//    window.draw(quad);
}

void Packman::updateLogic() {
    if (prey) {
        angle = angleToPrey();

        if (distanceToPrey(prey) <= radius + prey->radius) {
            //catched
            speed = speed + 3;
            strength += 1;

            pWar::remove(prey);

            if (pWar::packmans.size() == 1) {
                speed = 0;
            }
        }
    } else {
        detectPrey();
    }

    float frameDistance = speed * frameTime.restart().asSeconds();
    auto rad = angle * M_PI / 180.f;

    position.x = position.x + (float) std::cos(rad) * frameDistance;
    position.y = position.y + (float) std::sin(rad) * frameDistance;

    visionRadius = visionRadius + radius;

    correctWindowBoundaries();
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

Packman::Packman(sf::Vector2f position, int strength) {

    sprite.setTexture(pWar::packmanTexture);

    setPosition(position);
    setStrength(strength);

    sprite.setOrigin(radius, radius);

    for (int i = 0; i < frameCount; ++i) {
        sf::IntRect rect(i * 85, 0, 85, 85);
        frames.push_back(rect);
    }

    sprite.setTextureRect(frames[0]);

    angle = pWar::rnd(0, 359);
    state = States::Living;

    strengthText.setFillColor(sf::Color::White);
    strengthText.setCharacterSize(16);
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

int Packman::getSpeed() const {
    return speed;
}

void Packman::setSpeed(int speed) {
    Packman::speed = speed;
}

const sf::Color &Packman::getColor() const {
    return color;
}

void Packman::setColor(const sf::Color &color) {
    Packman::color = color;
}


