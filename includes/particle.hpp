#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include<SFML/Graphics.hpp>

class particle: public sf::Drawable
{
public:
    particle(const sf::Vector2f& position = sf::Vector2f(0,0), const sf::Vector2f& destination = sf::Vector2f(0,0), const sf::Color& color = sf::Color::White, const float& radius = 5.0f, const float& fuseTimer = 2.0f);
    virtual ~particle () = default;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(sf::Time timeElapsed);
    bool bExtinguished;
    float fDescentSpeed;

private:
    /* data */
    sf::Vector2f vPosition;
    float fLifetime;
    float fFuse;
    sf::Color cColor;
    sf::CircleShape shape;
    sf::Vector2f vDestination;
    sf::Vector2f vStartPosition;
};
#endif /* end of include guard: PARTICLE_HPP */
