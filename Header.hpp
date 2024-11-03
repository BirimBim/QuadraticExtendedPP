#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
void restart(bool *running);
void quadratic(double a, double b, double c, double *delta, double *root1, double *root2, bool *complexAnswer);
void thickPoint(SDL_Renderer* renderer, int x, int y);
void numberGraph(int windowHeight, int windowWidht, SDL_Renderer* renderer, TTF_Font* Font);