#ifndef RENDERING_H_
#define RENDERING_H_

#include <SDL2/SDL.h>

void render_saap(SDL_Renderer *renderer, int x, int y);
void render_food(SDL_Renderer *renderer, int x, int y);
void render_grid(SDL_Renderer * renderer, int x, int y);

#endif
