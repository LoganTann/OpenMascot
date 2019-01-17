#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
//#include "shime.h"

int main(){
    std::cout<<"CPP SHIMEJI\n";
    std::cout<<"C++ shimeji rewriting for linux (and soon, cross platform)\n";
    std::cout<<"Under the MIT license. Copyright (c) 2019 Logan Tann/KageTeam[Fr]\n\n";

    // Change this to the wanted transparency
    const unsigned char opacity = 255;

    // Create the window and center it on the screen
    sf::RenderWindow window(sf::VideoMode(128,128, 32), "Shimeji1", sf::Style::None);
    window.setFramerateLimit(60);


    // Load an image with transparent parts that will define the shape of the window
    sf::Image fallingImg,simpleImg;
    fallingImg.loadFromFile("img/shime4.png");
    simpleImg.loadFromFile("img/shime1.png");

    // These functions return false on an unsupported OS or when it is not supported on linux (e.g. display doesn't support shape extention)
    bool shapeOk = setShape(window.getSystemHandle(), fallingImg),
         transOK = setTransparency(window.getSystemHandle(), opacity);
    int taskbarW(40);

    std::cout<< std::boolalpha 
            <<"Shape supported : "<<shapeOk<<"\n"
            <<"Transparency supported : "<<transOK<<"\n"
            <<"Custom Taskbar width : "<<taskbarW<<"\n";

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    backgroundTexture.loadFromImage(fallingImg);
    backgroundSprite.setTexture(backgroundTexture);
    int scrw = sf::VideoMode::getDesktopMode().width,
        scrh = sf::VideoMode::getDesktopMode().height - taskbarW,
        spritew = 128,
        spriteh = 128;

    int x((scrw - spritew) / 2),
        y(0- spriteh);
    float g(0.0005);

    window.setPosition(sf::Vector2i(x, y));

    bool falling = true;

    sf::Clock clock; // démarre le chrono

    sf::Time startFalling = clock.getElapsedTime();

    // Main loop to display the image while the window is open (pressing the escape key to close the window)
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        if (falling) {
            //pos=(1/2)*Acceleration*temps
            int t( clock.getElapsedTime().asMilliseconds()-startFalling.asMilliseconds() );
            y = 0.5*g*(t*t); 
            if (y>scrh-spriteh) {
                falling = false;
                y = scrh-spriteh; 
                //
                backgroundTexture.loadFromImage(simpleImg);
                backgroundSprite.setTexture(backgroundTexture);
                if (shapeOk) setShape(window.getSystemHandle(), simpleImg);
            }
            window.setPosition(sf::Vector2i( x, y));
        }
        window.clear(sf::Color::Transparent);
        window.draw(backgroundSprite);
        window.display();
        window.setActive();
    }

    return 0;
}

