
#include "graphics.h"
#include "balises.h"
#include "stylesheet.h"
#include "renderer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "styles.h"

char* DEFAULT_BACKCOLOR = "#FFFFFF";
char* DEFAULT_LAYOUT = "column";
char* DEFAULT_WIDTH = "0";
char* DEFAULT_HEIGHT = "0";

void renderBalise(balise_t* balise, stylesheet_t* stylesheet, int calculatedX, int calculateY, int calculatedWidth, int calculatedHeiht);


void renderContainer(balise_t* balise, style_t* style, stylesheet_t* stylesheet, int calculatedX, int calculateY, int calculatedWidth, int calculatedHeiht){

    // Get container layout (vertical or horizontal)
    css_layout_t layout = css_compile_layout(get_style_attribute(style, "layout", DEFAULT_LAYOUT));

    // Create offset variables
    int childX = calculatedX;
    int childY = calculateY;

    // Render each child
    for (int i = 0; i < get_child_count(balise); i++){

        // Get child
        balise_t* child = get_child(balise, i);

        // Get child style
        style_t* child_style = get_style(stylesheet, get_attribute_default(child, "style", NULL));

        // Get child width
        css_size_t width = css_compile_size(get_style_attribute(child_style, "width", DEFAULT_WIDTH));

        // Get child height
        css_size_t height = css_compile_size(get_style_attribute(child_style, "height", DEFAULT_HEIGHT));

        // Calculate child width
        int childWidth;
        if (width.type == SIZE_PERCENT){
            childWidth = calculatedWidth * width.value / 100;
        } else {
            childWidth = width.value;
        }

        // Calculate child height
        int childHeight;
        if (height.type == SIZE_PERCENT){
            childHeight = calculatedHeiht * height.value / 100;
        } else {
            childHeight = height.value;
        }

        // Out of bound
        if (childX + childWidth > calculatedX + calculatedWidth){
            childWidth = calculatedX + calculatedWidth - childX;
        }
        if (childY + childHeight > calculateY + calculatedHeiht){
            childHeight = calculateY + calculatedHeiht - childY;
        }

        // Render child
        renderBalise(child, stylesheet, childX, childY, childWidth, childHeight);

        // Calculate next child position
        if (layout == LAYOUT_HORIZONTAL){
            childX += childWidth;
        } else {
            childY += childHeight;
        }

    }

}

void renderBalise(balise_t* balise, stylesheet_t* stylesheet, int calculatedX, int calculateY, int calculatedWidth, int calculatedHeiht){

    // Null balise
    if (balise == NULL){
        fprintf(stderr, "Balise is NULL\n");
        return;
    }

    // Get balise style
    style_t* style = get_style(stylesheet, get_attribute_default(balise, "style", NULL));

    // Get background color default
    const char* backcolor = get_style_attribute(style, "backcolor", DEFAULT_BACKCOLOR);
    color_t color = css_compile_style_color(backcolor);

    // Draw rectangle
    drawRectangle(calculatedX, calculateY, calculatedWidth, calculatedHeiht, color);

    // Handle tagname specific rendering
    if (IS_CONTAINER(balise)){
        renderContainer(balise, style, stylesheet, calculatedX, calculateY, calculatedWidth, calculatedHeiht);
    }

}

void renderRoot(balise_t* root, stylesheet_t* stylesheet){

    // Error
    if (root == NULL){
        fprintf(stderr, "Root balise is NULL\n");
        return;
    }

    // Begin frame
    beginFrame();

    // Render window child balise
    renderBalise(get_child(root, 0), stylesheet, 0, 0, getWidth(), getHeight());

    // End frame
    endFrame();

}
