#include <SFML/Graphics.hpp>
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <list>
#include <vector>
#include "includes/firework.hpp"
#include "includes/star.hpp"

namespace fs = std::filesystem;

int main() {
    sf::RenderWindow rWindow(sf::VideoMode({1280, 960}), "Fireworks!");
    sf::Clock cClock;
    std::list<Firework*> fws;
    std::vector<sf::Image*>* images = new std::vector<sf::Image*>();
    sf::Music music;
    std::list<Star*>* starList = new std::list<Star*>();
    for (int i = 0; i < 1000; ++i) {
        starList->push_back(new Star(
            sf::Vector2f((rand() / (float)RAND_MAX) * rWindow.getSize().x,
                         (rand() / (float)RAND_MAX) * rWindow.getSize().y),
            (rand() / (float)RAND_MAX) * 1.0f + 1.0));
    }
    bool music_playing = false;
    if (!music.openFromFile("./resources/music/track.ogg")) {
        std::cout << "Error while loading song" << std::endl;
    }
    // Getting images
    std::string path = "./resources/patterns/";
    for (auto p : fs::directory_iterator(path)) {
        // std::cout << p << std::endl;
        sf::Image* tmp = new sf::Image();
        if (tmp->loadFromFile(p.path())) {
            images->push_back(tmp);
        }
    }
    rWindow.setFramerateLimit(60);
    // particle part = particle(sf::Vector2f(400,200), sf::Vector2f(600,300));
    music.play();
    music_playing = true;
    while (rWindow.isOpen()) {
        sf::Time tElapsedTime = cClock.restart();
        // Event Polling
        while (const std::optional event = rWindow.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                rWindow.close();
            }
            if (const auto* mouseButton =
                    event->getIf<sf::Event::MouseButtonReleased>()) {
                fws.push_back(
                    new Firework(sf::Vector2f((int)(rWindow.getSize().x / 2),
                                              (int)(rWindow.getSize().y)),
                                 sf::Vector2f(mouseButton->position.x,
                                              mouseButton->position.y),
                                 images));
            }
            if (const auto* keyreleased =
                    event->getIf<sf::Event::KeyReleased>()) {
                if (keyreleased->code == sf::Keyboard::Key::M) {
                    if (music_playing) {
                        music.stop();
                        music_playing = false;
                    } else {
                        music_playing = true;
                        music.play();
                    }
                }
            }
        }

        // Updating
        for (auto fw : fws) {
            fw->update(tElapsedTime);
        }
        for (auto s : *starList) {
            s->update(tElapsedTime);
        }
        // part.update(tElapsedTime);

        // Window Drawing
        rWindow.clear(sf::Color::Black);
        for (auto fw : fws) {
            rWindow.draw(*fw);
        }
        for (auto s : *starList) {
            rWindow.draw(*s);
        }
        // rWindow.draw(part);
        rWindow.display();

        // Clean up extinguished fireworks
        if (fws.size() > 0) {
            auto it = std::remove_if(fws.begin(), fws.end(),
                                     [](const Firework* fw) -> bool {
                                         return fw->isExtinguished();
                                     });
            if (it != fws.end()) {
                fws.erase(it);
            }
        }
    }
    return 0;
}
