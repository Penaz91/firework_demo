#include "includes/star.hpp"

float sineApprox(const float& v) {
    return (4 * v * (3.1415 - v)) / (49.345111 - (4 * v * (3.1415 - v)));
}

Star::Star(const sf::Vector2f& position, const float& radius)
    : fRadius(radius), vPosition(position) {
    std::uint8_t red_dim = (rand() / (float)RAND_MAX) * 32;
    std::uint8_t red_bright = (rand() / (float)RAND_MAX) * 128 + 64;
    std::uint8_t green_dim = (rand() / (float)RAND_MAX) * 85;
    std::uint8_t green_bright = 255;
    std::uint8_t blue = 255;
    cBrightColor = sf::Color(red_bright, green_bright, blue);
    cDimColor = sf::Color(red_dim, green_dim, blue);
    cColorDiff = cBrightColor - cDimColor;
    fOffset = (rand() / (float)RAND_MAX) * 3.1415;
    shape = sf::CircleShape(fRadius);
    fLifeTime = fOffset;
    float sn = sineApprox(fLifeTime);
    cCurrentColor =
        cDimColor + sf::Color(sn * cBrightColor.r, sn * cBrightColor.g,
                              sn * cBrightColor.b);
    shape.setFillColor(cCurrentColor);
    shape.setPosition(vPosition);
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

void Star::update(sf::Time timeElapsed) {
    fLifeTime += timeElapsed.asSeconds();
    if (fLifeTime > 3.1415) {
        fLifeTime -= 3.1415;
    }
    float sn = sineApprox(fLifeTime);
    cCurrentColor =
        cDimColor + sf::Color(sn * cBrightColor.r, sn * cBrightColor.g,
                              sn * cBrightColor.b);
    shape.setFillColor(cCurrentColor);
}
