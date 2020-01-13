#include <iostream>
#include <SFML/Graphics.hpp>
#include "mascot.h"
#include "system.h"

Mascot::Mascot(){
	// Create Window
	window.create( sf::VideoMode(128,128, 32), "Shimeji", sf::Style::None );
	// Hide taskbar icon if possible
	defaultProp(window.getSystemHandle());
	// Set window params
	window.setFramerateLimit(60);
	// Get cursor position
	const sf::Vector2i position = sf::Mouse::getPosition();
	// Set the X position to mouse X position
	x = position.x;

	// Image loading
	sf::Image newImg;
	sf::Texture newFrame;
	std::string spritesImg[] = {"img/shime1.png","img/shime4.png","img/shime1.png", "img/shime18.png", "img/shime19.png", "img/shime20.png", "img/shime29.png" };

	for (int i(0); i<std::size(spritesImg);i++){
		// Load and store all images defined by spritesImg[]
		frames.push_back(newFrame);
		framesI.push_back(newImg);
		framesI[i].loadFromFile(spritesImg[i]);
		frames[i].loadFromImage(framesI[i]);
	}
	currentFrame = sf::Sprite(frames[0]);
}

std::string Mascot::update(){
	sf::Event event;
	const int dt = tick();

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)){
			return "quit";

		} else if (event.type == sf::Event::MouseButtonPressed){

			if (not grabbing or clickTime > 200){
				// the moves averages are computed in 200ms max. After, it will reset.
				clickTime = 0;
				pos0 = sf::Mouse::getPosition();
				grabbing = true;
			} else {
				clickTime += dt;
			}

		} else if (event.type == sf::Event::MouseButtonReleased){

			grabbing = false;
			v0 = (sf::Mouse::getPosition() - pos0)); // determine velocity per seconds based on mouse movment
			std::cout<<std::endl<<"v0X = "<<v0.x<<" v0Y = "<<v0.y<<std::endl;

		} else if (event.type == sf::Event::MouseMoved) {
		}
	}

	window.clear(sf::Color::Transparent);
	window.draw(currentFrame);
	window.display();
	return "fine";
}

int Mascot::tick(){
	const int currentTime = clock.getElapsedTime().asMilliseconds();
	const int dt = currentTime - lastTime;
	lastTime = currentTime;
	return dt;
}
