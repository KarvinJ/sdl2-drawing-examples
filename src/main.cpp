#include "sdl_starter.h"

int main(int argc, char *args[])
{
    SDL_Window *window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (startSDLSystems(window, renderer) > 0)
    {
        return 1;
    }

    if (SDL_NumJoysticks() > 0 && SDL_IsGameController(0))
    {
        SDL_GameControllerOpen(0);
    }

    Mix_Chunk *sound = loadSound("res/sounds/magic.wav");
    Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 2);

    SDL_Rect playerBounds = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 64, 64};

    int colorIndex = 0;
    int part = 0;

    SDL_Color colors[] = {
        {255, 255, 255, 0}, // white
        {255, 0, 0, 0},     // red
        {0, 255, 0, 0},     // green
        {0, 0, 255, 0},     // blue
        {0, 255, 255, 0},   // cyan
    };

    bool isGameRunning = true;

    while (isGameRunning)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                isGameRunning = false;
            }

            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_SPACE)
                {
                    if (colorIndex < 4)
                    {
                        colorIndex++;
                    }
                    else
                    {
                        colorIndex = 0;
                    }
                }

                if (event.key.keysym.sym == SDLK_RIGHT && part <= 5)
                {
                    part++;
                    Mix_PlayChannel(-1, sound, 0);
                }

                else if (event.key.keysym.sym == SDLK_LEFT && part >= 0)
                {
                    part++;
                    Mix_PlayChannel(-1, sound, 0);
                }
            }

            if (event.type == SDL_CONTROLLERBUTTONDOWN)
            {
                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
                {
                    if (colorIndex < 4)
                    {
                        colorIndex++;
                    }
                    else
                    {
                        colorIndex = 0;
                    }
                }

                if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER && part <= 5)
                {
                    part++;
                    Mix_PlayChannel(-1, sound, 0);
                }

                else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER && part >= 0)
                {
                    part--;
                    Mix_PlayChannel(-1, sound, 0);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, 255);

        SDL_RenderFillRect(renderer, &playerBounds);

        // SDL_RenderFillCircle(renderer, 100, 100, 20);
        // SDL_RenderDrawCircle(renderer, 400, 400, 20);

        SDL_RenderPresent(renderer);

        // capFrameRate(currentFrameTime);
    }

    Mix_FreeChunk(sound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    stopSDLSystems();

    return 0;
}