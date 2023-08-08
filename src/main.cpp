#include <SDL3/SDL.h>

#include "libra.h"

#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 730

bool init(SDL_Window *&window, SDL_Surface *&surface);
bool loadMedia(SDL_Surface *&media);
void close(SDL_Window *&window, SDL_Surface *&media);

int main(int argc, char *args[])
{
    // Declaring SDL Window
    SDL_Window *window = nullptr;

    // The display inside of the window
    SDL_Surface *windowSurface = nullptr;

    // Media to show on the screen
    SDL_Surface *libraImage = nullptr;

    // Starts SDL and creates window
    if (!init(window, windowSurface))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to Initialize\n");
    }
    else
    {
        // Loads media
        if (!loadMedia(libraImage))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load media\n");
        }
        else
        {
            SDL_Event e;
            bool quit = false;

            // Main loop
            while (!quit)
            {
                // Handles events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_EVENT_QUIT)
                        quit = true;
                }

                // Apply image to surface
                SDL_BlitSurface(libraImage, NULL, windowSurface, NULL);

                // Update the window surface
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Free resources and close SDL
    close(window, libraImage);

    return 0;
}

bool init(SDL_Window *&window, SDL_Surface *&surface)
{
    // Set initialisation success flag
    bool success = true;

    // Initialize SDL
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        // Log Error if initialisation fails
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL: %s", SDL_GetError());
        success = false;
    }
    else
    {
        // Create SDL window
        window = SDL_CreateWindow("Libra Project", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);

        // Check if window creation was successful
        if (!window)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s", SDL_GetError());
            success = false;
        }
        else
        {
            // Get a surface for window
            surface = SDL_GetWindowSurface(window);
        }
    }

    // Return initialisation success
    return success;
}

bool loadMedia(SDL_Surface *&media)
{
    // Set loading success flag
    bool success = true;

    // Load image
    media = SDL_LoadBMP("assets/libra.bmp");

    // Check if image loaded successfully
    if (!media)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image: %s", SDL_GetError());
        success = false;
    }

    return success;
}

void close(SDL_Window *&window, SDL_Surface *&media)
{
    // Deallocate surface
    SDL_DestroySurface(media);
    media = nullptr;

    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit all subsystems
    SDL_Quit();
}