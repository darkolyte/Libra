#include <SDL3/SDL.h>

#include "libra.h"

// Screen dimension defaults
static int window_width = 680;
static int window_height = 730;

namespace Libra
{
    int Main(int argc, char *args[])
    {
        // Declaring SDL Window
        SDL_Window *window = nullptr;

        // The window renderer
        SDL_Renderer *window_renderer = nullptr;

        // Current displayed texture
        SDL_Texture *display_texture = nullptr;

        // Start SDL and create window
        if (!Init(window, window_renderer, window_width, window_height))
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to Initialize\n");
        }
        else
        {
            // Load media
            if (!LoadMedia(display_texture, window_renderer))
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
                        {
                            quit = true;
                            goto Quit;
                        }
                        else if (e.type == SDL_EVENT_WINDOW_RESIZED)
                        {
                            SDL_GetWindowSize(window, &window_width, &window_height);
                        }
                    }

                    // Clear screen
                    SDL_SetRenderDrawColor(window_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(window_renderer);

                    // Render texture to screen
                    // SDL_RenderTexture(window_renderer, display_texture, NULL, NULL);

                    // Render red filled quad
                    SDL_FRect filled_rect = {(float)window_width / 4, (float)window_height / 4, (float)window_width / 2, (float)window_height / 2};
                    SDL_SetRenderDrawColor(window_renderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(window_renderer, &filled_rect);

                    // Update screen
                    SDL_RenderPresent(window_renderer);
                }
            }
        }

    Quit:

        // Free resources and Close SDL
        Close(display_texture, window_renderer, window);

        return 0;
    }
}

// Entry point for windows
#if defined(_WIN32)
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    return Libra::Main(__argc, __argv);
}
#else
int main(int argc, char *args[])
{
    return Libra::Main(argc, args);
}
#endif