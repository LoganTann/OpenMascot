#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>

bool setShape(Window wnd, const sf::Image& image);
bool defaultProp(Window window);
//bool setTransparency(Window wnd, unsigned char alpha);
//std::string exec(const char* cmd);
bool net_get_workarea(Display* display, int& x, int& y, int& w, int& h);

#undef None
#endif
