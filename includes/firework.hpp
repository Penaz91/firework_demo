#ifndef FIREWORK_H
#define FIREWORK_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include "particle.hpp"
#include <cmath>
#include <list>
#include <vector>

class Firework: public sf::Drawable {
    private:
        sf::Vector2f vDestination;
        sf::Vector2f vOrigin;
        sf::Vector2f vPosition;
        float fLifetime;
        float fFuse;
        sf::CircleShape shape;
        sf::Color cColor;
        bool bExploded;
        std::list<particle*> particles;
        float fScale;
        std::vector<sf::Image*>* imageHandle;
        float fAngle;

    public:
        Firework(const sf::Vector2f& origin, const sf::Vector2f& destination, std::vector<sf::Image*>* patterns);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void update(sf::Time timeElapsed);
        virtual ~Firework() = default;
        bool isExtinguished() const;
};

#endif /* FIREWORK_H */
