#include <SDL3/SDL.h>
#include "libra.h"

bool Init(SDL_Window *&window, SDL_Renderer *&renderer, const int width, const int height)
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
        window = SDL_CreateWindow("Libra Project", width, height, SDL_WINDOW_RESIZABLE);

        // Check if window creation was successful
        if (!window)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window: %s", SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

            // Check if renderer was created
            if (!renderer)
            {
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Renderer failed to create: %s", SDL_GetError());
                success = false;
            }
            else
            {
                // Set color for drawing operations for the renderer
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
            }
        }
    }

    // Return Initialisation success
    return success;
}

SDL_Texture *LoadTexture(char *path, SDL_Renderer *&renderer)
{
    // Texture to load
    SDL_Texture *texture = nullptr;

    // Load image from path
    SDL_Surface *loadedSurface = SDL_LoadBMP(path);

    // Check if image loaded successfully
    if (!loadedSurface)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image (%s)!\nSDL Error: %s", path, SDL_GetError());
    }
    else
    {
        // Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        // Check if texture was created
        if (!texture)
        {
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to create texture form %s!\nSDL Error: %s", path, SDL_GetError());
        }

        // Free loaded surface from memory
        SDL_DestroySurface(loadedSurface);
    }

    return texture;
}

bool LoadMedia(SDL_Texture *&texture, SDL_Renderer *&renderer)
{
    // Set loading success flag
    bool success = true;

    // Path of image
    char *path = SDL_strdup("assets/libra.bmp");

    // Load texture
    texture = LoadTexture(path, renderer);

    // Check if texture loaded successfully
    if (!texture)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load image: %s", SDL_GetError());
        success = false;
    }

    return success;
}

void Close(SDL_Texture *&texture, SDL_Renderer *&renderer, SDL_Window *&window)
{
    // Free loaded image
    SDL_DestroyTexture(texture);
    texture = nullptr;

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    // Quit SDL
    SDL_Quit();
}