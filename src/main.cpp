#include <SDL3/SDL.h>

#include "libra.h"

// Screen dimension defaults
const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 800;

int main(int argc, char *args[])
{
    // Declaring SDL Window
    SDL_Window *window = nullptr;

    // The display inside of the window
    SDL_Surface *windowSurface = nullptr;

    // Current displayed image
    SDL_Surface *stretchedSurface = nullptr;

    // Start SDL and create window
    if (!Init(window, windowSurface, WINDOW_WIDTH, WINDOW_HEIGHT))
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to Initialize\n");
    }
    else
    {
        // Load media
        if (!LoadMedia(stretchedSurface, windowSurface))
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
                    if (e.type == SDL_EVENT_QUIT)
                        quit = true;
                    else if (e.type == SDL_EVENT_KEY_DOWN)
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "You pressed: %s", SDL_GetKeyName(e.key.keysym.sym));
                }

                // Apply the image stretched
                SDL_Rect destRect;
                destRect.x = 0;
                destRect.y = 0;
                destRect.w = WINDOW_WIDTH;
                destRect.h = WINDOW_HEIGHT;

                SDL_BlitSurfaceScaled(stretchedSurface, NULL, windowSurface, &destRect);

                // Update the window surface
                SDL_UpdateWindowSurface(window);
            }
        }
    }

    // Free resources and Close SDL
    Close(window, stretchedSurface);

    return 0;
}

// Use WinMain entry point if compiling for windows
#ifdef _WINDOWS
#include "Windows.h"

// Windows entry point
int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    return main(__argc, __argv);
}
#endif
