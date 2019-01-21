#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>

bool setShape(Window wnd, const sf::Image& image);
bool defaultProp(Window window);
//bool setTransparency(Window wnd, unsigned char alpha);

#undef None
#endif