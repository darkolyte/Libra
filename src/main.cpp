#include <SDL3/SDL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *args[])
{
    // Declaring SDL Window
    SDL_Window *window = NULL;

    // The display inside of the window
    SDL_Surface *windowSurface = NULL;

    // Initialize SDL video subsystem
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }

    // Create SDL Window
    window = SDL_CreateWindow("Libra Project", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Get a surface for the window
        windowSurface = SDL_GetWindowSurface(window);

        // Window won't close until a quit event
        SDL_Event e;
        bool quit = false;
        while (quit == false)
        {
            while (SDL_PollEvent(&e))
            {
                if (e.type == SDL_EVENT_QUIT)
                    quit = true;
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}