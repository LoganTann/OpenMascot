#include "system.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <X11/Xatom.h>
#include <X11/Xproto.h>
#include <X11/extensions/shape.h>
// Window params
bool defaultProp(Window window) {
    Display* display = XOpenDisplay(NULL);

    Atom skip_taskbar = XInternAtom(display, "_NET_WM_STATE_ABOVE", True);
    Atom wm_state     = XInternAtom(display, "_NET_WM_STATE", True);

    if(wm_state == 0) {
        std::cerr << "Oopsie on _NET_WM_STATE\n";
        return false;
    } else if (skip_taskbar == 0) {
        std::cerr << "Oopsie on _NET_WM_STATE_SKIP_TASKBAR\n";
        return false;
    }
	int x,y,w,h;
	net_get_workarea(display, x,y, w,h);

    XChangeProperty(display,   /* connection to x server */
                             window,    /* window whose property we want to change */
                             wm_state,   /* property name */
                             XA_ATOM, /* type of property */
                             32,      /* format of prop; can be 8, 16, 32 */
                             PropModeReplace,
                             (unsigned char*) &skip_taskbar, /* actual data */
                             1         /* number of elements */
                            );
	//XRaiseWindow(display, window); //too strong :/
	XFlush(display);
    XCloseDisplay(display);
	std::cout<<XA_CARDINAL<<std::endl;
    return true;
}

bool setShape(Window wnd, const sf::Image& image) {
	const sf::Uint8* pixelData = image.getPixelsPtr();
	Display* display = XOpenDisplay(NULL);

	// Try to set the window shape
	int event_base;
	int error_base;
	if (XShapeQueryExtension(display, &event_base, &error_base))
	{
		Pixmap pixmap = XCreatePixmap(display, wnd, image.getSize().x, image.getSize().y, 1);
		GC gc = XCreateGC(display, pixmap, 0, NULL);

		XSetForeground(display, gc, 1);
		XFillRectangle(display, pixmap, gc, 0, 0, image.getSize().x, image.getSize().y);
		XSetForeground(display, gc, 0);

		for (unsigned int y = 0; y < image.getSize().y; y++)
		{
			for (unsigned int x = 0; x < image.getSize().x; x++)
			{
				if (pixelData[y * image.getSize().x * 4 + x * 4 + 3] == 0)
					XFillRectangle(display, pixmap, gc, x, y, 1, 1);
			}
		}

		XShapeCombineMask(display, wnd, ShapeBounding, 0, 0, pixmap, ShapeSet);
		XFreeGC(display, gc);
		XFreePixmap(display, pixmap);
		XFlush(display);
		XCloseDisplay(display);
		return true;
	}

	XCloseDisplay(display);
}

// Utils

bool net_get_workarea(Display* display, int& x, int& y, int& w, int& h){
	Atom XA_NET_WM_WORKAREA = XInternAtom(display, "_NET_WORKAREA", False);
	x = y = w = h = 0;
	// un-used :
	Atom typeReturn;
	int format;
	unsigned long n, extra;
	unsigned char* prop;

	int status = XGetWindowProperty( display, DefaultRootWindow(display), XA_NET_WM_WORKAREA,
				0L, 1L, False, XA_CARDINAL, &typeReturn, &format, &n, &extra, (unsigned char**)&prop);
	if (status == Success) {
		CARD32* val = (CARD32*) prop;
		if (val){
			std::cerr<<"_NET_WORKAREA : X: "<<val[0]<<" Y: "<<val[1]<<" W: "<<val[2]<<" H:"<<val[3]<<std::endl;
			x = val[0]; y = val[1];
			w = val[2]; h = val[3];
			XFree((char*) val);
			return true;
		} else {
			std::cerr<<"net_get_workarea:CARD32 val failed !!"<<std::endl;
		}
	} else {
		std::cerr<<"net_get_workarea:XGetWindowProperty failed !!"<<std::endl;
	}
	return false;
}
#undef None // None conflicts with SFML
