#include <iostream>
#include <SFML/Graphics.hpp>
#include "shimeji.h"
#include "system.h"

Shimeji::Shimeji(){
	window.create(sf::VideoMode(128,128, 32), "Shimeji", sf::Style::None);
    scrw = sf::VideoMode::getDesktopMode().width;
    scrh = sf::VideoMode::getDesktopMode().height - taskbarW;
    window.setPosition(sf::Vector2i(x, y));
	window.setFramerateLimit(60);

	/*   fallingImg.loadFromFile("img/shime4.png");
    simpleImg.loadFromFile("img/shime1.png");*/
	sf::Image newFrame;
    frames.push_back(newFrame);
    frames.push_back(newFrame);
    frames[0].loadFromFile("img/shime1.png");
    frames[1].loadFromFile("img/shime4.png");

    changeImg(1);

	startFalling = clock.getElapsedTime();
}

int Shimeji::update(){
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            return -1;
        else if (event.type == sf::Event::MouseButtonPressed){
            if (event.mouseButton.button == sf::Mouse::Left){
                if (!mousePressing) {
                    mousePressing = true;
                    initialWinx = x - event.mouseButton.x;
                    initialWiny = y - event.mouseButton.y;
                    initialMousex = event.mouseButton.x;
                    initialMousey = event.mouseButton.y;
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
                /*std::cout << "initialWinx: " << initialWinx << std::endl;
                std::cout << "initialWiny: " << initialWiny << std::endl;
                std::cout << "initialMousex: " << initialMousex << std::endl;
                std::cout << "initialMousey: " << initialMousey << std::endl;
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;*/
                x -= initialMousex - event.mouseMove.x;
                y -= initialMousey - event.mouseMove.y;
                window.setPosition(sf::Vector2i(x, y));
            }
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
	toDisplay = frames[index];
	shapeOk = setShape(window.getSystemHandle(), toDisplay);
	return 0;
}