#include <cmath>
#include <iostream>
#include <fstream>
#include "includes/firework.hpp"

const float FIREWORK_PARTICLE_SIZE = 2.0f;

Firework::Firework(const sf::Vector2f& origin, const sf::Vector2f& destination, std::vector<sf::Image*>* patterns): vDestination(destination), vOrigin(origin), vPosition(origin), fLifetime(0.0f), cColor(sf::Color::Yellow), bExploded(false), imageHandle(patterns){
    fFuse = (rand() / (float)RAND_MAX) * 2.0f + 1.0f;
    shape = sf::CircleShape(2.0f);
    shape.setFillColor(cColor);
    fScale = (rand() / (float)RAND_MAX) * 1.5f + 1.0f;
    //fAngle = (rand() / (float)RAND_MAX) * 3.1415f - 1.5705;
    fAngle = atan2f((vDestination.y - vOrigin.y), (vDestination.x - vOrigin.x)) + 1.5705;
}

void Firework::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if (!bExploded){
        target.draw(shape, states);
    }else{
        for (auto item: particles){
            target.draw(*item, states);
        }
    }
}

void Firework::update(sf::Time timeElapsed){
    fLifetime += timeElapsed.asSeconds();
    if (fLifetime >= fFuse){
        if (!bExploded){
            // Explode
            // Create 4 corner particles
            //
            float fFuseTimer = (rand() / (float)RAND_MAX) * 1.0f + 0.5f;

            sf::Image* img;
            int rnd = (rand() / (float)RAND_MAX) * imageHandle->size();
            img = (*imageHandle)[rnd];
            sf::Vector2u size = img->getSize();
            //std::cout << "Image Size: " << size.x << ", " << size.y << std::endl;

            sf::Uint8 r = (rand() / (float)RAND_MAX) * 128 + 127;
            sf::Uint8 g = (rand() / (float)RAND_MAX) * 128 + 127;
            sf::Uint8 b = (rand() / (float)RAND_MAX) * 128 + 127;
            //std::cout << r << " " << g << " " << b << std::endl;
            sf::Color clr = sf::Color(r, g, b, 255);

            for (unsigned int j = 0; j < size.y; j++){
                for (unsigned int i = 0; i < size.x; i++){
                    sf::Color pixel =img->getPixel(i,j);
                    if (pixel == sf::Color::Black){
                        // If black, use the random color
                        sf::Vector2f dest_offset = sf::Vector2f(
                            fScale * 10 * ((int) i - (((int) size.x - 1) / 2)),
                            fScale * 10 * ((int) j - (((int) size.y - 1) / 2))
                        );
                        sf::Vector2f rotated_dest_offset = sf::Vector2f(
                            (dest_offset.x * cosf(fAngle)) - (dest_offset.y * sinf(fAngle)),
                            (dest_offset.x * sinf(fAngle)) + (dest_offset.y * cosf(fAngle))
                        );
                        particles.push_back(
                            new particle(sf::Vector2f(vPosition),
                                    vPosition + rotated_dest_offset,
                                    clr,
                                    FIREWORK_PARTICLE_SIZE,
                                    fFuseTimer
                            )
                        );
                    }else if (pixel != sf::Color::Transparent){
                        // If different from black, use the defined color
                        sf::Vector2f dest_offset = sf::Vector2f(
                            fScale * 10 * ((int) i - (((int) size.x - 1) / 2)),
                            fScale * 10 * ((int) j - (((int) size.y - 1) / 2))
                        );
                        sf::Vector2f rotated_dest_offset = sf::Vector2f(
                            (dest_offset.x * cosf(fAngle)) - (dest_offset.y * sinf(fAngle)),
                            (dest_offset.x * sinf(fAngle)) + (dest_offset.y * cosf(fAngle))
                        );
                        particles.push_back(
                            new particle(sf::Vector2f(vPosition),
                                    vPosition + rotated_dest_offset,
                                    pixel,
                                    FIREWORK_PARTICLE_SIZE,
                                    fFuseTimer
                            )
                        );
                        //particles.push_back(
                            //new particle(sf::Vector2f(vPosition),
                                    //vPosition + sf::Vector2f(
                                        //fScale * 10 * ((int) i - (((int) size.x - 1) / 2)),
                                        //fScale * 10 * ((int) j - (((int) size.y - 1) / 2))
                                    //),
                                    //pixel,
                                    //3.0f,
                                    //fFuseTimer
                            //)
                        //);
                    }
                }
            }


            //particles.push_back(
                //new particle(sf::Vector2f(vPosition),
                         //vPosition + sf::Vector2f(-20, -20),
                         //sf::Color::White,
                         //3.0f,
                         //fFuseTimer
                //)
            //);
            //particles.push_back(
                //new particle(sf::Vector2f(vPosition),
                         //vPosition + sf::Vector2f(20, -20),
                         //sf::Color::White,
                         //3.0f,
                         //fFuseTimer
                //)
            //);
            //particles.push_back(
                //new particle(sf::Vector2f(vPosition),
                         //vPosition + sf::Vector2f(-20, 20),
                         //sf::Color::White,
                         //3.0f,
                         //fFuseTimer
                //)
            //);
            //particles.push_back(
                //new particle(sf::Vector2f(vPosition),
                         //vPosition + sf::Vector2f(20, 20),
                         //sf::Color::White,
                         //3.0f,
                         //fFuseTimer
                //)
            //);
            bExploded = true;
        }else{
            // Already exploded: Update particles
            for (auto part: particles){
                part->update(timeElapsed);
            }
        }
    }else{
        float factor = 1 - std::pow((1 - (fLifetime / fFuse)), 2.0f);
        vPosition = vOrigin + (vDestination - vOrigin) * factor;
    }
    shape.setPosition(vPosition);
}

bool Firework::isExtinguished() const{
    if (bExploded){
        bool bExtinguished = true;
        if (particles.size() > 0){
            for(auto item = particles.begin(); bExtinguished && item != particles.end(); item++){
                /*
                 * Extinguished when ALL particles are extinguished
                 * means NOT extinguished when there is at least one particle alive
                 */
                bExtinguished = ((*item)->bExtinguished);
            }
        }
        return bExtinguished;
    }
    return false;
}
