/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef flood_fill_h
	#define flood_fill_h

    /* Function that implements the Flood Fill Algorithm to fill polygons */
    void floodFillAlgorithm(int x1, int y1, float* oldColor, float* newColor, forward_list<vertex>* vertexs)
    {
        // Check if this pixel has already been processed by the algorithm
        bool alreadyProcessed = false;
        for (auto it_v = vertexs -> begin(); it_v != vertexs -> end(); it_v++)
        {
            if (it_v->x == x1 && it_v->y == y1)
            {
                alreadyProcessed = true;
                break;
            }
        }

        // If not, proceed with the check
        if (!alreadyProcessed)
        {
            // Get the color of the current pixel
            float currentPixelColor[3];
            glReadPixels(x1, y1, 1, 1, GL_RGB, GL_FLOAT, currentPixelColor);

            // If the pixel is of the old color
            if (currentPixelColor[0] == oldColor[0] &&
                currentPixelColor[1] == oldColor[1] &&
                currentPixelColor[2] == oldColor[2])
            {
                // Paint the pixel with the new color
                glColor3f(newColor[0], newColor[1], newColor[2]);
                drawPixel(x1, y1);

                // Save the vertex in the list of processed vertices
                vertex v{
                    v.x = x1,
                    v.y = y1
                };
                vertexs -> push_front(v);

                // Recursively call the function for its cardinal neighbors (4-neighborhood FloodFill)
                floodFillAlgorithm(x1 + 1, y1, oldColor, newColor, vertexs);
                floodFillAlgorithm(x1, y1 + 1, oldColor, newColor, vertexs);
                floodFillAlgorithm(x1 - 1, y1, oldColor, newColor, vertexs);
                floodFillAlgorithm(x1, y1 - 1, oldColor, newColor, vertexs);
            }
        }
    }

#endif /* flood_fill_h */