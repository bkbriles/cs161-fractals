// This will draw a Sierpinski Fractal

#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

using namespace std;

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // Init vars
    int x = 0;
    int y = 0;

    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // Init Renderer
    SDL_Renderer* renderer = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    }

    // Setup Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    // for loop controls how many points there are
    for(int i = 0; i < 100000; i++)
    {
        // pick one of the three points at random
        switch(rand()%3)
        {
            case 0:
                // compute midpoint between current point and interest point
                x = (x + SCREEN_WIDTH/2) / 2;
                y = (y + 0) / 2;
                break;
            case 1:
                // compute midpoint between current point and interest point
                x = (x + 0) / 2;
                y = (y + SCREEN_HEIGHT) / 2;
                break;
            case 2:
                // compute midpoint between current point and interest point
                x = (x + SCREEN_WIDTH) / 2;
                y = (y + SCREEN_HEIGHT) / 2;
                break;
        }

        // draw a point
        SDL_RenderDrawPoint(renderer, x, y);
    }

    //Update the surface
    SDL_RenderPresent(renderer);

    //Wait 10 seconds
    SDL_Delay(10000);

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    return 0;
}

