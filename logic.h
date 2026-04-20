#ifndef LOGIC_H_
#define LOGIC_H_

#include <stdbool.h>

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct Saap {
    int x;
    int y;
    Direction direction;
    struct Saap *next;
} Saap;

typedef struct {
    int x;
    int y;
} Food;

extern Saap *head;
extern Saap *tail;
extern Food food;

void init_saap();
void add_segment();
void move_saap();
void generate_food();
void eat_food();
bool check_collision();

#endif
