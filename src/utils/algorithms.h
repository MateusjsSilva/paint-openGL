/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef algorithms_h
	#define algorithms_h

    /*
    * Function to draw a single pixel on the screen
    */
    void drawPixel(int x, int y)
    {
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    }

	#include "algorithms/bresenham.h"
	#include "algorithms/scanline_polygon_fill_algorithm.h"
	#include "algorithms/flood_fill.h"

#endif /* algorithms_h */