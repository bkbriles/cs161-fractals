#include <iostream>
#include <stdio.h>
#include <SDL2/SDL.h>

using namespace std;

// function prototype/s
int isBounded(double Cr, double Ci);
void draw(double xO, double yO, double Z, SDL_Renderer* renderer);
void zoom(double& xO, double& yO, double& Z, int x, int y);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[])
{
    // Init vars
    double Z = 4;
    double xO = 0;
    double yO = 0;

    //Main loop flag
    bool quit = false;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    // Renderer
    SDL_Renderer* renderer = NULL;

    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    //Create window
    window = SDL_CreateWindow( "Mandelbrot Fractal", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( window == NULL )
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    }

    // Setup Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    // Draw the initial fractal
    draw(xO, yO, Z, renderer);

    //Update the renderer
    SDL_RenderPresent(renderer);

    while(!quit)
    {
        // Event Handler
        SDL_Event event;

        //Handle events on queue
        while(SDL_WaitEvent(&event))
        {
            switch (event.type)
            {
            // User requests quit
            case SDL_QUIT:
                quit = true;
                break;
            // Mouse events to handle zoom
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // Get mouse pos
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    zoom(xO, yO, Z, x, y);

                    draw(xO, yO, Z, renderer);

                    //Update the renderer
                    SDL_RenderPresent(renderer);
                }
                break;
            }

            // If quit flag is up, break out of WaitEvent loop and close
            if (quit)
            {
                break;
            }
        }
    }

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();
    return 0;
}

// function definition/s
void zoom(double& xO, double& yO, double& Z, int x, int y)
 {
    // move the origin and zoom
    xO = xO + Z*x/SCREEN_WIDTH - Z/2;
    yO = yO - Z*y/SCREEN_HEIGHT + Z/2;
    Z /= 10;
}

void draw(double xO, double yO, double Z, SDL_Renderer* renderer)
{
    for(int y = 0; y < SCREEN_HEIGHT; y++)
        {
        for(int x = 0; x < SCREEN_WIDTH; x++) {
            double Cr = xO + Z*x/SCREEN_WIDTH - Z/2;
            double Ci = yO - Z*y/SCREEN_HEIGHT + Z/2;

            if (isBounded(Cr, Ci))
            {
                int n = isBounded(Cr, Ci);
                SDL_SetRenderDrawColor(renderer, 10 * n, 20 * n, 30 * n, 0);
                SDL_RenderDrawPoint(renderer, x, y);
            }

        }
    }
}

int isBounded(double Cr, double Ci)
{
    // init our sequence point to zero
    double Mr = 0;
    double Mi = 0;
    double temp;

    // check the first 100 terms in the sequence for boundedness
    int i;
    for(i = 0; i < 100; i++)
    {
        // do the formula M = M*M + C
        temp = Mr;
        Mr = Mr*Mr - Mi*Mi + Cr;
        Mi = 2*temp*Mi + Ci;

        // check to see if we're outside the boundary
        // boundary is a circle of rad 4 around the origin
        if(Mr*Mr + Mi*Mi > 4)
        {
            return i;
        }
    }

    // if the bound is never exceeded, say it's bounded
    return i;
}

