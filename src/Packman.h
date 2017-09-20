#ifndef THE_CORP_GAME_PACKMAN_H
#define THE_CORP_GAME_PACKMAN_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include <States.h>
#include <SFML/Graphics/VertexArray.hpp>

class Packman {
protected:
    sf::Vector2f position;
    States state;

    int currentFrame = 0;
    static const int frameCount = 4;

    sf::VertexArray vertexFrames[frameCount];
    sf::Text strengthText;

    sf::Clock clock;
    sf::Clock frameTime;

    int detalization = 180;
    int animationResolution = 100;
    float angle = 60;


    float radius;
    int speed = 0;
    int strength = 5;
    float visionRadius = 350;

    Packman *prey = nullptr;

    void updateVertexCoordinates();

    void correctWindowBoundaries();

    float angleToPrey();

    float distanceToPrey(Packman *packman);

    void detectPrey();

public:
    const sf::Vector2f &getPosition() const;

    void setPosition(const sf::Vector2f &position);

    void draw(sf::RenderWindow &window, sf::Font &font);

    void update(sf::RenderWindow &window, sf::Font &font);

    void updateLogic();

    int getStrength() const;

    void setStrength(int strength);

    explicit Packman(sf::Vector2f position, int strength);

    Packman *getPrey() const;

    void setPrey(Packman *prey);
};


#endif //THE_CORP_GAME_PACKMAN_H
