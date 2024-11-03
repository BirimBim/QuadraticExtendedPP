#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include "Header.hpp"

bool running = true;
int main()
{
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    
    double a, b, c, delta, root1, root2;
    bool complexAnswer=false;

    //Introduction
    std::cout << "\nThis program will calculate a quadratic equation (ax^2±bx±c = 0)\nUsing the quadratic formula(x = (-b ± √Δ)÷2a)(Δ=b^-4ac).";
    std::cout << "\nKeep in mind that: If a = 0 you do not have a quadratic equation.\n\nInsert a number for the coeficient a: ";
    std::cin >> a;
    std::cout << "Insert a number for the coeficient b: ";
    std::cin >> b;
    std::cout << "Insert a number for the coeficient c: ";
    std::cin >> c;

    //roots are the points on which the line meets the x intercept in real quadratics
    //but the actual x vertex is = -b/2a
    quadratic(a,b,c,&delta,  &root1, &root2, &complexAnswer);
    
    if(complexAnswer==false && a != 0){
        std::cout << "\nRoot 1: " << root1 << "\nRoot 2: " << root2;
    }else if(complexAnswer==true && a != 0){
        std::cout << "\nImaginary roots = " << root1 << " ± " << delta << "i\n";
    }else{
        std::cout << "\nError: the coeficient \"a\" cannot be = 0";
        return -1;
    }
    
    //x vertex
    float h = (b*-1)/(2*a);
    //y vertex
    float k = (a*(pow(h,2)))+(b*h)+c;
    //y intercept
    float yInter = (a*(pow(0,2)))+(b*0)+c;
    
    float xGraph = root2-1;
    float yGraph;
    float drawX, drawY;
    
    std::cout << std::endl << "Vertex: (" << h << "," << k << ")" << std::endl;
    std::cout << "y-intercept: " << "(0," << yInter << ")" << std::endl;
    std::cout << "x-intercepts: " << "(" << root2 << ",0)";
    std::cout << " (" << root1 << ",0)";
    
    //graph
    //initialize with error checking
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
    }
    const int windowHeight = 480;
    const int windowWidth = 640;
    
    //creates window and renderer with error checking
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight, 0, &window, &renderer) != 0) {
        std::cout << "Window/Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
    }
    SDL_SetWindowTitle(window,"Quadratic Graph");
    
    //text
    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -1;
    }

    TTF_Font* Font = TTF_OpenFont("GraphFont.ttf", 100);
    if (Font == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return -1;
    }
    
    //set background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    //number graph
    numberGraph(windowHeight, windowWidth, renderer, Font);
    
    //grid, lets me use the alpha value to make grid opaque 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(int i = 1; i <=25; i++){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
        SDL_RenderDrawLine(renderer, 24.65*i, 0, 24.65*i, 480);
        SDL_RenderDrawLine(renderer, 0, 26.7*i, 640, 26.7*i);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 480/2, 640, 480/2);
    SDL_RenderDrawLine(renderer, 640/2, 0, 640/2, 480);
    
    //draw quadratic
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    float scaleX = 24.65; 
    float scaleY = 26.7;  
    for (float x = -12; x <= 12; x += 0.1f) {
        float y = (a * pow(x, 2)) + (b * x) + c;
        thickPoint(renderer, (x * scaleX) + (windowWidth / 2), (y * -scaleY) + (windowHeight / 2));
    }
    
    //presenta the screen
    SDL_RenderPresent(renderer);
    //loop to keep it running
    SDL_Event e;
    Uint16 pos,pos2;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            //check if the user wants to quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }
    
    //quit sdl
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
