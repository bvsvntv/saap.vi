#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <SDL2/SDL.h>

#include "./game.h"
#include "./logic.h"
#include "./rendering.h"

int main() {
    srand(time(0));
    init_saap();
    generate_food();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Saap",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH,
                                          WINDOW_HEIGHT,
                                          SDL_WINDOW_SHOWN
                                          );
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED |
                                                SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    int grid_x = (WINDOW_WIDTH - (COLS * CELL_SIZE)) / 2;
    int grid_y = (WINDOW_HEIGHT - (ROWS * CELL_SIZE)) / 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    render_grid(renderer, grid_x, grid_y);
    render_saap(renderer, grid_x, grid_y);
    render_food(renderer, grid_x, grid_y);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    int quit = 0;
    int game_started = 0;
    while (!quit) {
        while (!game_started && !quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) quit = 1;
                if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_i) game_started = 1;
            }
        }
        if (quit) break;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: quit = 1; break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE: quit = 1; break;
                        case SDLK_h: if(head->direction != RIGHT) head->direction = LEFT; break;
                        case SDLK_j: if(head->direction != UP)    head->direction = DOWN; break;
                        case SDLK_k: if(head->direction != DOWN)  head->direction = UP;   break;
                        case SDLK_l: if(head->direction != LEFT)  head->direction = RIGHT;break;
                    }
                    break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        move_saap();
        if (check_collision()) {
            quit = 1;
            break;
        } else {
            eat_food();
        }
        render_grid(renderer, grid_x, grid_y);
        render_saap(renderer, grid_x, grid_y);
        render_food(renderer, grid_x, grid_y);
        SDL_RenderPresent(renderer);
        SDL_Delay(SPEED);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
