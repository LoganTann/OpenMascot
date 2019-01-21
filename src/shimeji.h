#ifndef SHIMEJI_H
#define SHIMEJI_H

class Shimeji {

public:
	Shimeji();
	int update();
	int changeImg(int index=0);
	int fall(bool on=true);

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
        scrw = sf::VideoMode::getDesktopMode().width,
        scrh = sf::VideoMode::getDesktopMode().height - taskbarW,
    	x = 10 + (rand() % static_cast<int>(scrw-138 - 10 + 1)),
        y = 0 - 120,
        initialy = y,
        initialx = x,
        initialWinx, initialWiny,
        initialMousex, initialMousey;

    sf::Vector2i grabbedOffset;
    //float g = 0.5;

    bool falling = true, mousePressing = false, shapeOk = false;
};


#endif