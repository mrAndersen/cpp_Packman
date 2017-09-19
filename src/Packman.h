#ifndef THE_CORP_GAME_PACKMAN_H
#define THE_CORP_GAME_PACKMAN_H


#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <States.h>
#include <SFML/Graphics/VertexArray.hpp>

class Packman {
protected:
    sf::Vector2f position;
    States state;
    sf::VertexArray verticies;
    sf::Clock clock;
    int animationResolution = 100;
public:
    const sf::Vector2f &getPosition() const;

    void setPosition(const sf::Vector2f &position);

    void draw(sf::RenderWindow &window);

    explicit Packman(sf::Vector2f position);
};


#endif //THE_CORP_GAME_PACKMAN_H
