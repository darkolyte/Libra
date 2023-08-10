#include <SDL3/SDL.h>
#include "libra.h"

bool Init(SDL_Window *&window, SDL_Surface *&surface, const int width, const int height)
{
    // Set Initialisation success flag
    bool success = true;

    // Initialize SDL
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        // Log Error if Initialisation fails
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't Initialize SDL: %s", SDL_GetError());
        success = false;
    }
    else
    {
        // Create SDL window
        window = SDL_CreateWindow("Libra Project", width, height, SDL_EVENT_WINDOW_SHOWN);

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

    // Return Initialisation success
    return success;
}

void Close(SDL_Window *&window, SDL_Surface *&media)
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

SDL_Surface *LoadSurface(char *path, SDL_Surface *surface)
{
    // Final optimized image
    SDL_Surface *optimizedSurface = nullptr;

    // Load image at specified path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path);

    // Check if image loaded successfully
    if (!loadedSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image: %s", SDL_GetError());
    }
    else
    {
        // Convert surface to screen format
        optimizedSurface = SDL_ConvertSurface(loadedSurface, surface->format);

        if (!optimizedSurface)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to optimize image: %s", SDL_GetError());
        }

        // Get rid of old loaded surface
        SDL_DestroySurface(loadedSurface);
    }

    return optimizedSurface;
}

bool LoadMedia(SDL_Surface *&media, SDL_Surface *surface)
{
    // Set loading success flag
    bool success = true;

    // Path of image
    char *path = SDL_strdup("assets/libra.bmp");

    // Load optimized stretching surface
    media = LoadSurface(path, surface);

    // Check if image loaded successfully
    if (!media)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image: %s", SDL_GetError());
        success = false;
    }

    return success;
}