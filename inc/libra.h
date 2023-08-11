#pragma once

// Initialise SDL
bool Init(SDL_Window *&window, SDL_Renderer *&renderer, const int width, const int height);

// Loads image as texture
SDL_Texture *LoadTexture(char *path, SDL_Renderer *&renderer);

// Loads image to display on surface
bool LoadMedia(SDL_Texture *&texture, SDL_Renderer *&renderer);

// Frees all resources and closes SDL
void Close(SDL_Texture *&texture, SDL_Renderer *&renderer, SDL_Window *&window);