#include "graphics.h"
#include <SDL.h>
#include <string.h>

static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static int windowWidth = 800;
static int windowHeight = 600;
static char windowTitle[256] = "SDL2 Window";
static color_t backgroundColor = {0, 0, 0};

void init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }
    window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Could not create window: %s", SDL_GetError());
        SDL_Quit();
        return;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }
}

void setWidth(int width) {
    windowWidth = width;
    SDL_SetWindowSize(window, windowWidth, windowHeight);
}

int getWidth() {
    return windowWidth;
}

void setHeight(int height) {
    windowHeight = height;
    SDL_SetWindowSize(window, windowWidth, windowHeight);
}

int getHeight() {
    return windowHeight;
}

void setTitle(const char* title) {
    strncpy(windowTitle, title, sizeof(windowTitle) - 1);
    windowTitle[sizeof(windowTitle) - 1] = '\0';
    SDL_SetWindowTitle(window, windowTitle);
}

const char* getTitle() {
    return windowTitle;
}

void setBackgroundColor(color_t color) {
    backgroundColor = color;
}

color_t getBackgroundColor() {
    return backgroundColor;
}

void beginFrame() {
    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, 255);
    SDL_RenderClear(renderer);
}

void endFrame() {
    SDL_RenderPresent(renderer);
}

void drawRectangle(int x, int y, int width, int height, color_t color) {
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void delay(int ms) {
    SDL_Delay(ms);
}

void deinit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}