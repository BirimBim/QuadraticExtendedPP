#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
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

void numberGraph(int windowHeight, int windowWidht, SDL_Renderer* renderer, TTF_Font* Font){
    SDL_Color White = {255, 255, 255};
    SDL_Rect grid_rect;
    
    grid_rect.x = -17;
    grid_rect.y = (windowHeight/2)+5;
    grid_rect.w = 15;
    grid_rect.h = 10;
    std::stringstream num;
    //numbering graph
    for(int i = -12; i <= -10; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.x += 27;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    for(int i = -9; i <= -1; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.x += 24;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    
    grid_rect.w = 8;
    grid_rect.h = 8;
    SDL_Surface* numText = TTF_RenderText_Solid(Font, "0", White);
    SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
    grid_rect.x += 37;
    SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
    for(int i = 1; i <= 5; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.x += 25;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    
    for(int i = 6; i <= 9; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.x += 23;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    
    for(int i = 10; i <= 12; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.x += 27;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    
    grid_rect.x = (windowWidht/2)+3;
    grid_rect.y = -26;
    for(int i = 9; i > 0; i--){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.y += 26;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
    
    grid_rect.x -=2;
    grid_rect.y += 26;
    grid_rect.w = 12;
    grid_rect.h = 9;
    for(int i = -1; i > -9; i--){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        grid_rect.y += 27;
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        
        SDL_FreeSurface(numText);
        num.str("");
    }
}