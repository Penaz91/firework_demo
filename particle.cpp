#include "includes/particle.hpp"
#include <iostream>
#include <cmath>

particle::particle(const sf::Vector2f& position, const sf::Vector2f& destination, const sf::Color& color, const float& radius, const float& fuseTimer): bExtinguished(false), vPosition(position), fLifetime(0.0f), fFuse(fuseTimer), cColor(color), vDestination(destination), vStartPosition(position){
    shape = sf::CircleShape(radius);
    shape.setFillColor(cColor);
    shape.setPosition(vPosition);
    fDescentSpeed = (rand() / (float)RAND_MAX) * 50 + 10;
    //std::cout << "Particle created at ("<< vStartPosition.x << ", " << vStartPosition.y << ") directed towards ("<< vDestination.x << ", " << vDestination.y << ")" << std::endl;
}

void particle::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    if (!bExtinguished){
        target.draw(shape, states);
    }
}

void particle::update(sf::Time timeElapsed){
    fLifetime += timeElapsed.asSeconds();
    if (fLifetime >= fFuse + 2.0f){
        // Extinguished
        bExtinguished = true;
    }else if (fLifetime >= fFuse){
        // Extinguishing
        float factor = 1 - std::pow((1 - ((fLifetime - fFuse) / 2.0f)), 2.0f);
        sf::Uint8 red = cColor.r + ((- cColor.r) * factor);
        sf::Uint8 green = cColor.g + ((-cColor.g) * factor);
        sf::Uint8 blue = cColor.b + ((-cColor.b) * factor);
        shape.setFillColor(sf::Color(red, green, blue));
        float xDisplacement = (rand() / (float)RAND_MAX) * 27 - 13;
        vPosition += sf::Vector2f(xDisplacement, fDescentSpeed) * timeElapsed.asSeconds();
    }else{
        float factor = 1 - std::pow((1 - (fLifetime / fFuse)), 2.0f);
        vPosition = vStartPosition + (vDestination - vStartPosition) * factor;
    }
    shape.setPosition(vPosition);
    //std::cout << "Moving to (" << vPosition.x << ", " << vPosition.y << ")" << std::endl;
}
