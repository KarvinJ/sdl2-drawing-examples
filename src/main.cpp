#include "sdl_starter.h"

Mix_Chunk *sound = nullptr;

bool isGameRunning = true;
int part = 0;
int colorIndex = 0;
int screenColorIndex = 7;
const int COLORS_SIZE = 8;

SDL_Color colors[] = {
    {255, 255, 255, 255}, // white
    {255, 0, 0, 255},     // red
    {0, 255, 0, 255},     // green
    {0, 0, 255, 255},     // blue
    {0, 255, 255, 255},   // cyan
    {255, 255, 0, 0},     // brown
    {255, 0, 255, 0},     // purple
    {0, 0, 0, 255},       // dark
};

void handleEvents()
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
                if (colorIndex < COLORS_SIZE)
                {
                    colorIndex++;
                }
                else
                {
                    colorIndex = 0;
                }
            }

            if (event.key.keysym.sym == SDLK_f)
            {
                if (screenColorIndex == COLORS_SIZE - 1)
                {
                    screenColorIndex = 0;
                }
                else
                {
                    screenColorIndex = COLORS_SIZE - 1;
                }
            }

            if (event.key.keysym.sym == SDLK_RIGHT && part <= 8)
            {
                part++;
                Mix_PlayChannel(-1, sound, 0);
            }

            else if (event.key.keysym.sym == SDLK_LEFT && part > 0)
            {
                part--;
                Mix_PlayChannel(-1, sound, 0);
            }
        }

        if (event.type == SDL_CONTROLLERBUTTONDOWN)
        {
            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_A)
            {
                isGameRunning = false;
            }

            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_START)
            {
                if (colorIndex < COLORS_SIZE)
                {
                    colorIndex++;
                }
                else
                {
                    colorIndex = 0;
                }
            }

            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_BACK)
            {
                if (screenColorIndex == COLORS_SIZE - 1)
                {
                    screenColorIndex = 0;
                }
                else
                {
                    screenColorIndex = COLORS_SIZE - 1;
                }
            }

            if (event.cbutton.button == SDL_CONTROLLER_BUTTON_RIGHTSHOULDER && part <= 8)
            {
                part++;
                Mix_PlayChannel(-1, sound, 0);
            }

            else if (event.cbutton.button == SDL_CONTROLLER_BUTTON_LEFTSHOULDER && part > 0)
            {
                part--;
                Mix_PlayChannel(-1, sound, 0);
            }
        }
    }
}

void renderEverything(SDL_Renderer *renderer, bool shouldRenderMultiColor)
{
    SDL_Point diagnonalPoint1 = {8, 8};
    SDL_Point diagonalPoint2 = {SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8};

    SDL_RenderFillCircle(renderer, diagnonalPoint1.x, diagnonalPoint1.y, 8);
    SDL_RenderFillCircle(renderer, diagonalPoint2.x, diagonalPoint2.y, 8);
    SDL_RenderDrawLine(renderer, diagnonalPoint1.x, diagnonalPoint1.y, diagonalPoint2.x, diagonalPoint2.y);

    SDL_Point diagnonal2Point1 = {8, SCREEN_HEIGHT - 8};
    SDL_Point diagonal2Point2 = {SCREEN_WIDTH - 8, 8};

    SDL_RenderFillCircle(renderer, diagnonal2Point1.x, diagnonal2Point1.y, 8);
    SDL_RenderFillCircle(renderer, diagonal2Point2.x, diagonal2Point2.y, 8);
    SDL_RenderDrawLine(renderer, diagnonal2Point1.x, diagnonal2Point1.y, diagonal2Point2.x, diagonal2Point2.y);

    SDL_Point topPoint = {SCREEN_WIDTH / 2, 8};
    SDL_Point bottomPoint = {SCREEN_WIDTH / 2, SCREEN_HEIGHT - 8};
    SDL_RenderFillCircle(renderer, topPoint.x, topPoint.y, 8);
    SDL_RenderFillCircle(renderer, bottomPoint.x, bottomPoint.y, 8);
    SDL_RenderDrawLine(renderer, topPoint.x, topPoint.y, bottomPoint.x, bottomPoint.y);

    SDL_Point rightPoint = {8, SCREEN_HEIGHT / 2};
    SDL_Point leftPoint = {SCREEN_WIDTH - 8, SCREEN_HEIGHT / 2};
    SDL_RenderFillCircle(renderer, rightPoint.x, rightPoint.y, 8);
    SDL_RenderFillCircle(renderer, leftPoint.x, leftPoint.y, 8);
    SDL_RenderDrawLine(renderer, leftPoint.x, leftPoint.y, rightPoint.x, rightPoint.y);

    int radius = 100;

    for (size_t i = 0; i < COLORS_SIZE - 1; i++)
    {
        if (shouldRenderMultiColor)
        {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        }

        SDL_RenderDrawCircle(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, radius);
        radius += 80;
    }
}

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

    sound = loadSound("res/sounds/magic.wav");
    Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 4);

    SDL_Rect bounds = {SCREEN_WIDTH / 2 - 128 / 2, SCREEN_HEIGHT / 2 - 128 / 2, 128, 128};
    SDL_Point point1 = {10, 10};
    SDL_Point point2 = {SCREEN_WIDTH - 10, SCREEN_HEIGHT - 10};
    SDL_Point circlePosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};

    while (isGameRunning)
    {
        handleEvents();

        SDL_SetRenderDrawColor(renderer, colors[screenColorIndex].r, colors[screenColorIndex].g, colors[screenColorIndex].b, colors[screenColorIndex].a);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, colors[colorIndex].r, colors[colorIndex].g, colors[colorIndex].b, colors[colorIndex].a);

        switch (part)
        {

        case 1:

            SDL_RenderDrawPoint(renderer, point1.x, point1.y);
            SDL_RenderDrawPoint(renderer, point2.x, point2.y);
            break;
        case 2:

            SDL_RenderFillCircle(renderer, point1.x, point1.y, 8);
            SDL_RenderFillCircle(renderer, point2.x, point2.y, 8);
            break;

        case 3:

            SDL_RenderFillCircle(renderer, point1.x, point1.y, 8);
            SDL_RenderFillCircle(renderer, point2.x, point2.y, 8);
            SDL_RenderDrawLine(renderer, point1.x, point1.y, point2.x, point2.y);
            break;

        case 4:

            SDL_RenderDrawCircle(renderer, circlePosition.x, circlePosition.y, 80);
            break;

        case 5:

            SDL_RenderFillCircle(renderer, circlePosition.x, circlePosition.y, 80);
            break;

        case 6:

            SDL_RenderDrawRect(renderer, &bounds);
            break;

        case 7:

            SDL_RenderFillRect(renderer, &bounds);
            break;

        case 8:

            renderEverything(renderer, false);
            break;

        case 9:

            renderEverything(renderer, true);
            break;

        default:
            break;
        }

        SDL_RenderPresent(renderer);
    }

    Mix_FreeChunk(sound);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    stopSDLSystems();

    return 0;
}