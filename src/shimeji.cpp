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
	std::string spritesImg[] = {"img/shime1.png","img/shime4.png","img/shime01.png", "img/shime18.png", "img/shime19.png", "img/shime20.png", "img/shime29.png" };

	for (int i(0); i<std::size(spritesImg);i++){
    	frames.push_back(newFrame);
    	framesI.push_back(newImg);
        framesI[i].loadFromFile(spritesImg[i]);
    	frames[i].loadFromImage(framesI[i]);
	}

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
    //ANIMATIONS
        if (falling) {
            int t = clock.getElapsedTime().asMilliseconds()-startFalling.asMilliseconds();
            y = initialy + 0.0009 * (t*t); 
            if (y>scrh-spriteh) {
                y = scrh-spriteh; 
                fall(false);
                animate("bouncing");
            }
            window.setPosition(sf::Vector2i( x, y));
        }
        if (!animation.empty()){
            float t = clock.getElapsedTime().asSeconds()-startAnimating.asSeconds();
            if (t>animationFrameIter){
                animationFrameIter+=0.25;
                if (animationFrameIter*4==animation.size()) {
                    animation.clear();
                    changeImg(0);
                } else{
                    changeImg(animation[animationFrameIter*4]);
                }
            }
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
        if (mousePressing)
          changeImg(2);
        else 
		  changeImg(0);
	}
	return 0;
}

int Shimeji::changeImg(int index){
    if (befIndex!=index){
	   toDisplay.setTexture(frames[index]);
	   shapeOk = setShape(window.getSystemHandle(), framesI[index]);
       befIndex = index;
    }
	return 0;
}

int Shimeji::animate(std::string state){ 
    animation.clear();
    if (state=="bouncing"){
        //0 will not be interpreted
        animation = {3,4,4,3,5,5,5,6};
    }
    else
        return 1;
    animationFrameIter = 0;
    changeImg(animation[0]);
    startAnimating = clock.getElapsedTime() - sf::seconds(0.25f);
    //startAnimating -= ;
};