#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/Xatom.h>
#include <X11/extensions/shape.h>

bool setShape(Window wnd, const sf::Image& image);
bool defaultProp(Window window);
//bool setTransparency(Window wnd, unsigned char alpha);
static const char *
Get_Window_Property_Data_And_Type (Display* display, Window target_win, Atom atom,
                                   long *length, Atom *type, int *size);
#undef None
#endif
