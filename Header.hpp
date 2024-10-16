#include <SDL2/SDL.h>
void restart(bool *running, SDL_Renderer* renderer, SDL_Window* window);
void quadratic(double a, double b, double c, double *delta, double *root1, double *root2, bool *complexAnswer);
void thickPoint(SDL_Renderer* renderer, int x, int y);