#include <iostream>
#include <SFML/Graphics.hpp>
#include "shimeji.h"
#include "system.h"

Shimeji::Shimeji(){
	window.create(sf::VideoMode(128,128, 32), "Shimeji", sf::Style::None);
	defaultProp(window.getSystemHandle());
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

	fall();
}

int Shimeji::update(){
    sf::Event event;
    bool grabbedWindow = false;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            return -1;
        else if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (!mousePressing) {
                    mousePressing = true;
                	grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                	fall(false);
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (mousePressing) mousePressing = false;
            	fall();
            }
        }
        else if (event.type == sf::Event::MouseMoved) {
            if (mousePressing){
            	sf::Vector2i pos = sf::Mouse::getPosition() + grabbedOffset;
            	x = pos.x;
            	y = pos.y;
            	window.setPosition(pos);
            }
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        }

    }
    if (falling) {
        float t = clock.getElapsedTime().asMilliseconds()-startFalling.asMilliseconds();
        y = initialy + 0.0001 * (t*t); 
        if (y>scrh-spriteh) {
            y = scrh-spriteh; 
            fall(false);
        }
        window.setPosition(sf::Vector2i( x, y));
    }

    window.clear(sf::Color::Transparent);
    window.draw(toDisplay);
    window.display();
    return 0;
}

int Shimeji::fall(bool on){
	if (on) {
		initialy = y;
		initialx = x;
		startFalling = clock.getElapsedTime();
		falling=true;
        changeImg(1);
	} else {
		falling=false;
		changeImg(0);
	}
	return 0;
}

int Shimeji::changeImg(int index){
	toDisplay.setTexture(frames[index]);
	shapeOk = setShape(window.getSystemHandle(), framesI[index]);
	return 0;
}