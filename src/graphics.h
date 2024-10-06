#ifndef GRAPHICS_H
#define GRAPHICS_H

// Color
typedef struct {
    int r;
    int g;
    int b;
} color_t;

// Initialize the graphics context
void init();

// Cleanup the graphics context
void deinit();

// Delay
void delay(int ms);

// Set the width of the window
void setWidth(int width);

// Get the width of the window
int getWidth();

// Set the height of the window
void setHeight(int height);

// Get the height of the window
int getHeight();

// Set the title of the window
void setTitle(const char* title);

// Get the title of the window
const char* getTitle();

// Set the background color of the window
void setBackgroundColor(color_t color);

// Get the background color of the window
color_t getBackgroundColor();

// Create new frame
void beginFrame();

// End frame drawing and update window
void endFrame();

// Draw a rectangle
void drawRectangle(int x, int y, int width, int height, color_t color);

#endif // GRAPHICS_H