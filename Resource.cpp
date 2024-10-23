#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>
#include "Header.hpp"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_ttf.h"

using namespace std;

void restart(bool *running){
    int choice;
    cout << "\n\nPress:\n1.To restart: \n2.To quit: \n";
    cin >> choice;
    if(choice == 1){
        *running = true;
    }else if(choice == 2){
        *running = false;
    }else{
        cout << "This is not a valid choice";
    }
}

void quadratic(double a, double b, double c, double *delta, double *root1, double *root2, bool *complexAnswer){
            *delta = (b*b)+(-4*(a*c));
            if(*delta<0){
                *complexAnswer=true;
                *delta = *delta*(-1);
                *delta = sqrt(*delta)/2*a;
                *root1 = (-b)/(2*a);
            }else{
            *root1 = (-b+sqrt(*delta))/(2*a);
            *root2 = (-b-sqrt(*delta))/(2*a);
            }
}
//\nError: Δ is negative in this equation making it impossible to square root. Given this equation has no real solution:
void thickPoint(SDL_Renderer* renderer, int x, int y){
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderDrawPoint(renderer, x+1, y-1);
    SDL_RenderDrawPoint(renderer, x-1, y+1);
    SDL_RenderDrawPoint(renderer, x+1, y+1);
    SDL_RenderDrawPoint(renderer, x-1, y-1);
    SDL_RenderDrawPoint(renderer, x+1, y);
    SDL_RenderDrawPoint(renderer, x-1, y);
    SDL_RenderDrawPoint(renderer, x, y-1);
    SDL_RenderDrawPoint(renderer, x, y+1);
}
