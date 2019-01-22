SHIMEJI-RE
===================

**A shimeji software rewriting by zero in cpp.**

I noticed the original software "Shimeji" is very very slow... mostly in linux systems.  
Because i love this sofware, i'm trying to make a rewrite of this software in cpp, but with a different system (I'm not based with the original system, it is my own).

Development status : Working on... (no beta version...)

### Compiling

Linux:
g++ main.cpp system.cpp shimeji.cpp -lsfml-graphics -lsfml-window -lsfml-system -lX11 -lXext --std=c++17 -O3


No windows/mac version ATM