#pragma once

// Initialise SDL
bool Init(SDL_Window *&window, SDL_Surface *&surface, const int width, const int height);

// Loads image to display on surface
bool LoadMedia(SDL_Surface *&media, SDL_Surface *surface);

// Loads an optimized image
SDL_Surface *LoadSurface(char *path, SDL_Surface *surface);

// Frees all resources and closes SDL
void Close(SDL_Window *&window, SDL_Surface *&media);