#include <iostream>
#include <SFML/Graphics.hpp>
#include "system.h"
#include "shimeji.h"

int main(){
    std::cout<<"CPP SHIMEJI\n";
    std::cout<<"C++ shimeji rewriting for linux (and soon, cross platform)\n";
    std::cout<<"Under the MIT license. Copyright (c) 2019 Logan Tann/KageTeam[Fr]\n\n";

    bool open(1);

    Shimeji shime1,shime2;

    while (open) {
        if (shime1.update()==-1) open=false;
        if (shime2.update()==-1) open=false;
    }
    return 0;
}

