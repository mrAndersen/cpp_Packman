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

    sf::VertexArray vertexFrames [frameCount];
    sf::Text strengthText;

    sf::Clock clock;
    sf::Clock frameTime;

    int detalization = 50;
    int animationResolution = 100;


    int radius = 10;
    int speed = 100;
    int strength = 2;

    void updateVertexCoordinates();

public:
    const sf::Vector2f &getPosition() const;

    void setPosition(const sf::Vector2f &position);

    void draw(sf::RenderWindow &window, sf::Font &font);

    void update(sf::RenderWindow &window, sf::Font &font);

    void updateLogic();

    explicit Packman(sf::Vector2f position);
};


#endif //THE_CORP_GAME_PACKMAN_H
