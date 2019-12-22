#ifndef STAR_H
#define STAR_H

#include<SFML/Graphics.hpp>

class Star: public sf::Drawable{
private:
    sf::CircleShape shape;
    float fRadius;
    sf::Color cBrightColor;
    sf::Color cDimColor;
    sf::Color cColorDiff;
    sf::Color cCurrentColor;
    float fOffset;
    float fLifeTime;
    sf::Vector2f vPosition;

public:
    Star(const sf::Vector2f& position = sf::Vector2f(0,0), const float& radius = 2.0f);
    virtual ~Star() = default;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time timeElapsed);
};

#endif /* STAR_H */
