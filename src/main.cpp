#include <SDL3/SDL.h>

#include "libra.h"

// Screen dimension defaults
const static int WINDOW_WIDTH = 680;
const static int WINDOW_HEIGHT = 730;

int main(int argc, char *args[])
{
    // Declaring SDL Window
    SDL_Window *window = nullptr;

    // The window renderer
    SDL_Renderer *windowRenderer = nullptr;

    // Current displayed texture
    SDL_Texture *displayTexture = nullptr;

    // Start SDL and create window
    if (!Init(window, windowRenderer, WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to Initialize\n");
    }
    else
    {
        // Load media
        if (!LoadMedia(displayTexture, windowRenderer))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load media\n");
        }
        else
        {
            // Event Handler
            SDL_Event e;

            // Main loop flag
            bool quit = false;

            // Main loop
            while (!quit)
            {
                // Handle events on queue
                while (SDL_PollEvent(&e) != 0)
                {
                    // Handle quit event
                    if (e.type == SDL_EVENT_QUIT)
                        quit = true;
                }

                // Clear screen
                SDL_RenderClear(windowRenderer);

                // Render texture to screen
                SDL_RenderTexture(windowRenderer, displayTexture, NULL, NULL);

                // Update screen
                SDL_RenderPresent(windowRenderer);
            }
        }
    }

    // Free resources and Close SDL
    Close(displayTexture, windowRenderer, window);

    return 0;
}

// Entry point for windows
#if defined(_WIN32)
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
}
#endif