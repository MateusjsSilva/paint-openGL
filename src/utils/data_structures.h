/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef data_structures_h
	#define data_structures_h

    struct vertex
    {
        int x, y;
    };

    struct transformation
    {
        int type; double vertexF[2];
    };

    struct shapes
    {
        int type{};
        float red{}, green{}, blue{};
        forward_list<vertex> vertexs;
        forward_list<transformation> transformations;
    };

    // Types of geometric shapes
    enum shape_type
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
        FILLED_POLY     // Filled Polygon
    };

    // Types of geometric transformations
    enum transformation_types
    {
        TRANSLATION = 11,   // Translation
        SCALING,            // Scaling
        SHEARING,           // Shearing
        REFLECTION,         // Reflection
        ROTATION            // Rotation
    };

#endif /* data_structures_h */