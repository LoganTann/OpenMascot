#ifndef SHIMEJI_H
#define SHIMEJI_H

class Mascot {
	//actually, not implemented to make more than 1 mascot.
public:
	Mascot();
	std::string update();
	int tick();

private :
	//sfml
	sf::RenderWindow window;
	sf::Clock clock;
	//sf::Time startFalling,startAnimating;

	// Frames loaded
	std::vector<sf::Image> framesI;
	std::vector<sf::Texture> frames;

	sf::Sprite currentFrame;

	unsigned int lastTime, physics_t;
	int x,y, clickTime;
	bool pressing, grabbing;
	sf::Vector2i v0, pos0;
};


#endif
