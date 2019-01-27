#include <iostream>
#include <SFML/Graphics.hpp>

/*#if defined (SFML_SYSTEM_WINDOWS)
    #include <windows.h>

    bool setShape(HWND hWnd, const sf::Image& image)
    {
        const sf::Uint8* pixelData = image.getPixelsPtr();
        HRGN hRegion = CreateRectRgn(0, 0, image.getSize().x, image.getSize().y);

        // Determine the visible region
        for (unsigned int y = 0; y < image.getSize().y; y++)
        {
            for (unsigned int x = 0; x < image.getSize().x; x++)
            {
                if (pixelData[y * image.getSize().x * 4 + x * 4 + 3] == 0)
                {
                    HRGN hRegionPixel = CreateRectRgn(x, y, x+1, y+1);
                    CombineRgn(hRegion, hRegion, hRegionPixel, RGN_XOR);
                    DeleteObject(hRegionPixel);
                }
            }
        }

        SetWindowRgn(hWnd, hRegion, true);
        DeleteObject(hRegion);
        return true;
    }

    bool setTransparency(HWND hWnd, unsigned char alpha)
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
        return true;
    }

#elif defined (SFML_SYSTEM_LINUX)*/
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

    Atom skip_taskbar = XInternAtom(display, "_NET_WM_STATE_SKIP_TASKBAR", True);
    Atom wm_state     = XInternAtom(display, "_NET_WM_STATE", True);

    if(wm_state == None) {
        std::cerr << "Oopsie on _NET_WM_STATE\n";
        return false;
    } else if(skip_taskbar == None) {
        std::cerr << "Oopsie on _NET_WM_STATE_SKIP_TASKBAR\n";
        return false;
    }

    XChangeProperty(display,   /* connection to x server */
                             window,    /* window whose property we want to change */
                             wm_state,   /* property name */
                             XA_ATOM, /* type of property */
                             32,      /* format of prop; can be 8, 16, 32 */
                             PropModeAppend,
                             reinterpret_cast<const unsigned char *>(&skip_taskbar), /* actual data */
                             1         /* number of elements */
                            );

    XCloseDisplay(display);
    return true;
}


/*    int wininit(Window wnd){
        
        retrun 0;
    }

/*    bool setTransparency(Window wnd, unsigned char alpha)
    {
        Display* display = XOpenDisplay(NULL);
        unsigned long opacity = (0xffffffff / 0xff) * alpha;
        Atom property = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", false);
        if (property != None)
        {
            XChangeProperty(display, wnd, property, XA_CARDINAL, 32, PropModeReplace, (unsigned char*)&opacity, 1);
            XFlush(display);
            XCloseDisplay(display);
            return true;
        }
        else
        {
            XCloseDisplay(display);
            return false;
        }
    }*/
#undef None // None conflicts with SFML
/*    
#elif defined (SFML_SYSTEM_MACOS)
    bool setShape(sf::WindowHandle handle, const sf::Image& image);
    bool setTransparency(sf::WindowHandle handle, unsigned char alpha);
#else
    bool setShape(sf::WindowHandle handle, const sf::Image& image)
    {
        return false;
    }

    bool setTransparency(sf::WindowHandle handle, unsigned char alpha)
    {
        return false;
    }
#endif*/
