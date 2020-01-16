#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
/*#elif defined (SFML_SYSTEM_LINUX)*/
    #include <X11/Xatom.h>
    #include <X11/extensions/shape.h>

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
    return true;
}

#undef None // None conflicts with SFML
