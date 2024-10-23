#include <iostream>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include "Header.hpp"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"

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
    //but the actual x point is = -b/2a
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
    std::cout << "y-intercept: " << "(0," << yInter << ")";
    std::cout << "(" << h+h << "," << yInter << ")" << std::endl;
    std::cout << "x-intercept: " << "(" << root2 << ",0)";
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
    SDL_RenderSetScale(renderer, 1.0, 1.0);
    
    
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
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, "In development", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    
    SDL_Rect Message_rect;
    Message_rect.x = 0;
    Message_rect.y = windowHeight-20;
    Message_rect.w = 170;
    Message_rect.h = 20;
    
    
    
    // Set background color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    
    SDL_Rect grid_rect;
    
    grid_rect.x = 20;
    grid_rect.y = windowHeight/2;
    grid_rect.w = 200;
    grid_rect.h = 200;
    std::stringstream num;
    //numbering graph
    for(int i = 1; i <= 13; i++){
        num << i;
        SDL_Surface* numText = TTF_RenderText_Solid(Font, num.str().c_str(), White);
        SDL_Texture* numTexture = SDL_CreateTextureFromSurface(renderer, numText);
        SDL_RenderCopy(renderer, numTexture, NULL, &grid_rect);
        SDL_FreeSurface(numText);
    }
    
   
    
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
    /* 
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
    */
    
    //draws quadratic
    SDL_SetRenderDrawColor(renderer, 0,255,0,255);
    //Upward curve
    if(a > 0){
        for(float y=k; y <= 13; y+=0.1f){
            xGraph += 0.1f;
            yGraph = (a*(pow(xGraph,2)))+(b*xGraph)+c;
            thickPoint(renderer, xGraph*28, yGraph*18);
        }
    }
    /* 
    //Downward curve
    if(a < 0){
        for(float y=k; y > -16; y-=0.5f){
            xGraph -= 0.5f;
            yGraph = (a*(pow(xGraph,2)))+(b*xGraph)+c;
            thickPoint(renderer, coordinatesX[xGraph], coordinatesY[yGraph]);
        }
    }
    */
    
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
    TTF_Quit();
    SDL_Quit();
    
    
}
