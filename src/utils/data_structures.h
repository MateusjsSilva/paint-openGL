/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef data_structures_h
	#define data_structures_h

    // Structure to represent a vertex (a point in 2D space)
    struct vertex
    {
        int x, y;
    };

    // Structure to represent a geometric transformation
    struct transformation
    {
        int type; double vertexF[2];
    };

    // Structure to represent a geometric shape
    struct shapes
    {
        int type{};
        float red{}, green{}, blue{};
        forward_list<vertex> vertexs;
        forward_list<transformation> transformations;
    };

    // menu options
    enum menu_options
    {
        MOUSE = 1,      // Mouse (Placeholder)
        LINE,           // Line
        RECTANGLE,      // Rectangle
        TRIANGLE,       // Triangle
        POLYGON,        // Polygon
        CIRCLE,         // Circle
        PAINT_BUCKET,   // Paint Bucket (Flood Fill)
        FILLED_RECT,    // Filled Rectangle
        FILLED_TRI,     // Filled Triangle
        FILLED_POLY,     // Filled Polygon
        TRANSLATION,   // Translation
        SCALING,            // Scaling
        SHEARING,           // Shearing
        REFLECTION,         // Reflection
        ROTATION            // Rotation
    };

#endif /* data_structures_h */