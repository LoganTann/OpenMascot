#ifndef SHIMEJI_H
#define SHIMEJI_H

class Shimeji {

public:
	Shimeji();
	int update();
	int changeImg(int index=0);
	int fall(bool on=true);
	int animate(std::string state);//animating the sprite texture, not the sprite pos ATM !!

private :
	//sfml
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time startFalling,startAnimating;
	std::vector<sf::Image> framesI;
	std::vector<sf::Texture> frames;
	//std::vector<std::string> frameName;
	sf::Sprite toDisplay;
	std::vector<int> animation;

	int taskbarW = 40,
        spritew = 128,
        spriteh = 128,
        scrw = sf::VideoMode::getDesktopMode().width,
        scrh = sf::VideoMode::getDesktopMode().height - taskbarW,
    	x = 10 + (std::rand() % static_cast<int>(scrw-138 - 10 + 1)), //not random after compilation !!
        y = 0 - 120,
        initialy = y,
        initialx = x,
        befIndex = 0,
        befy,
        initialWinx, initialWiny,
        initialMousex, initialMousey;

    sf::Vector2i grabbedOffset;
    float animationFrameIter = 0;
    //float g = 0.5;

    bool falling = true, mousePressing = false, shapeOk = false;
};


#endif