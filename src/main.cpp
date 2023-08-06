#include <iostream>
#include <SDL.h>

int main(int argc, char *args[])
{
    std::cout << argc << args[0] << std::endl;
    SDL_Log("Hello, World!");
    return 0;
}