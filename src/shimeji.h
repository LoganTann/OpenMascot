#ifndef SHIMEJI_H
#define SHIMEJI_H

class Shimeji {

public:
	Shimeji();
	int update();
	int changeImg(int index=0);

private :
	//sfml
	sf::RenderWindow window;
	sf::Clock clock;
	sf::Time startFalling;
	std::vector<sf::Image> framesI;
	std::vector<sf::Texture> frames;
	//std::vector<std::string> frameName;
	sf::Sprite toDisplay;

	int taskbarW = 40,
        spritew = 128,
        spriteh = 128,
    	x = (scrw - spritew) / 2,
        y = 0 - spriteh,
        scrw, scrh, //value in init
        initialWinx, initialWiny,
        initialMousex, initialMousey;

    float g = 0.0005;

    bool falling = true, mousePressing = false, shapeOk = false;
};


#endif