#include <iostream>
#include <SFML/Graphics.hpp>
#include "shimeji.h"
#include "system.h"

Shimeji::Shimeji(){
	window.create(sf::VideoMode(128,128, 32), "Shimeji", sf::Style::None);
	defaultProp(window.getSystemHandle());
    scrw = sf::VideoMode::getDesktopMode().width;
    scrh = sf::VideoMode::getDesktopMode().height - taskbarW;
    x = 10 + (rand() % static_cast<int>(scrw-138 - 10 + 1));
    window.setPosition(sf::Vector2i(x, y));
	window.setFramerateLimit(60);

	/*   fallingImg.loadFromFile("img/shime4.png");
    simpleImg.loadFromFile("img/shime1.png");*/
    sf::Image newImg;
	sf::Texture newFrame;
    frames.push_back(newFrame);
    frames.push_back(newFrame);
    framesI.push_back(newImg);
    framesI.push_back(newImg);
    framesI[0].loadFromFile("img/shime1.png");
    framesI[1].loadFromFile("img/shime4.png");
    frames[0].loadFromImage(framesI[0]);
    frames[1].loadFromImage(framesI[1]);

    changeImg(1);

	startFalling = clock.getElapsedTime();
}

int Shimeji::update(){
    sf::Event event;
    sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            return -1;
        else if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (!mousePressing) {
                    mousePressing = true;
                	grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (mousePressing) mousePressing = false;
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (mousePressing){
            	window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
            }
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }

    }
    if (falling) {
        //pos=(1/2)*Acceleration*temps
        int t( clock.getElapsedTime().asMilliseconds()-startFalling.asMilliseconds() );
        y = 0.5*g*(t*t); 
        if (y>scrh-spriteh) {
            falling = false;
            y = scrh-spriteh; 
            changeImg(0);
        }
        window.setPosition(sf::Vector2i( x, y));
    }
    else if (y<scrh-spriteh && !mousePressing){
        startFalling = clock.getElapsedTime();
        falling = true;
    }

    window.clear(sf::Color::Transparent);
    window.draw(toDisplay);
    window.display();
    return 0;
}

int Shimeji::changeImg(int index){
	toDisplay.setTexture(frames[index]);
	shapeOk = setShape(window.getSystemHandle(), framesI[index]);
	return 0;
}