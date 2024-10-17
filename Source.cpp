#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <cmath>
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
    std::cout << "Insert a number for the coesficient c: ";
    std::cin >> c;

    //roots are the points on which the line meets the x intercept in real quadratics
    //but the actual x point is = -b/2a
    quadratic(a,b,c,&delta,  &root1, &root2, &complexAnswer);
    
    if(complexAnswer==false && a != 0){
        std::cout << "\nRoot 1: " << root1 << "\nRoot 2: " << root2;
    }else if(complexAnswer==true && a != 0){
        std::cout << "\nImaginary roots = " << root1 << " ± " << delta << "i\n";
    }else{
        std::cout << "\nError: the coeficient \"a\" cannot be = 0";
    }
    
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
    SDL_RenderSetScale(renderer, 1.0, 1.0);
    
    
    // Set background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    
    //Grid, lets me use the alpha value to make grid opaque 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    for(int i = 1; i <=25; i++){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 120);
        SDL_RenderDrawLine(renderer, 24.65*i, 0, 24.65*i, 480);
        SDL_RenderDrawLine(renderer, 0, 26.7*i, 640, 26.7*i);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawLine(renderer, 0, 480/2, 640, 480/2);
    SDL_RenderDrawLine(renderer, 640/2, 0, 640/2, 480);
    
    
    //makes a map to make pixels relative to points on graph
    std::map<float,float> coordinatesX;
    std::map<float,float> coordinatesY;
    //x
    for(float i = -12.0f; i <= 25.0f; i+=0.5f){
        coordinatesX[i] = (24.65*i)+(24.65*13);
    }
    //y
    float counter=0;
    for(float i = 9.0f; i >= -9.0f; i-=0.5f){
        coordinatesY[i] = (26.7*counter);
        counter+= 0.5f;
    }
    
    
    //draws quadratic
    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    int h = (b*-1)/(2*a);
    int k = (a*(pow(h,2)))+(b*h)+c;
    if(a > 0){
        thickPoint(renderer, coordinatesX[h], coordinatesY[k]);
        std::cout << std::endl << "Vertex: (" << h << "," << k << ")" << std::endl;
        for(float i=root1; i < windowHeight; i+=0.5f){
            
        }
    }
    if(a < 0){
        
    }
    
    
    //presenta the screen
    SDL_RenderPresent(renderer);
    //loop to keep it running
    SDL_Event e;
    Uint16 pos,pos2;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            // Check if the user wants to quit
            if (e.type == SDL_QUIT) {
                quit = true;
                restart(&running);
            }
            if(e.type == SDL_MOUSEBUTTONUP){
                if(e.button.button == SDL_BUTTON_LEFT){
                    pos = e.button.x;
                    pos2 = e.button.y;
                    std::cout << pos << "  " << pos2;
                }
            }
        }
    }
    
    //quit sdl
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
}
