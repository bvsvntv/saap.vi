#include "./rendering.h"
#include "./game.h"
#include "./logic.h"

void render_grid(SDL_Renderer * renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0xCC, 0xCC, 0xCC, 255);
    SDL_Rect cell;
    cell.w = CELL_SIZE;
    cell.h = CELL_SIZE;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cell.x = x + (i * CELL_SIZE);
            cell.y = y + (j * CELL_SIZE);
            SDL_RenderDrawRect(renderer, &cell);
        }
    }
}

void render_saap(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0x45, 0xFE, 0x02, 255);
    SDL_Rect segment;
    segment.w = CELL_SIZE;
    segment.h = CELL_SIZE;
    Saap *current = head;
    while (current != NULL) {
        segment.x = x + current->x;
        segment.y = y + current->y;
        SDL_RenderFillRect(renderer, &segment);
        current = current->next;
    }
}

void render_food(SDL_Renderer *renderer, int x, int y) {
    SDL_SetRenderDrawColor(renderer, 0xFA, 0x4E, 0x58, 255);
    SDL_Rect foodRect;
    foodRect.w = CELL_SIZE;
    foodRect.h = CELL_SIZE;
    foodRect.x = x + food.x * CELL_SIZE;
    foodRect.y = y + food.y * CELL_SIZE;
    SDL_RenderFillRect(renderer, &foodRect);
}
