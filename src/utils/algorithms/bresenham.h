/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef bresenham_h
    #define bresenham_h

    /* Function that implements the Bresenham Algorithm for rasterization of line segments */
    std::forward_list<vertex> bresenhamLine(double x1, double y1, double x2, double y2)
    {
        // List of vertices to be drawn
        forward_list<vertex> vertexList;

        // Original coordinates
        int xStart = static_cast<int>(x1);
        int yStart = static_cast<int>(y1);

        vertex v1{
            x1, y1 
        };
        vertexList.push_front(v1);

        int xEnd = static_cast<int>(x2);
        int yEnd = static_cast<int>(y2);

        vertex v2{
            x2, y2 
        };
        vertexList.push_front(v2);

        // Variables - part 1
        int deltaX = xEnd - xStart;
        int deltaY = yEnd - yStart;

        // Reduction to the first octant
        int tmp = 0;

        // Check if the slope is negative
        bool symmetric = false;

        int slope = deltaX * deltaY;
        if (slope < 0)
        {
            symmetric = true;

            // Change the sign of the Y coordinates
            yStart *= (-1);
            yEnd *= (-1);
            deltaY *= (-1);
        }

        // Check if the slope is greater than 1
        bool steep = false;

        if (abs(deltaX) < abs(deltaY))
        {
            steep = true;

            // Swap the position of x and y in each coordinate
            std::swap(xStart, yStart);
            std::swap(xEnd, yEnd);
            std::swap(deltaX, deltaY);
        }

        // Check if xStart is greater than xEnd
        if (xStart > xEnd)
        {
            // Swap the order of the coordinates
            std::swap(xStart, xEnd);
            std::swap(yStart, yEnd);
            deltaX *= (-1);
            deltaY *= (-1);
        }

        // Variables - part 2
        int d = (2 * deltaY) - deltaX;
        int incE = (2 * deltaY);
        int incNE = 2 * (deltaY - deltaX);

        // Bresenham Algorithm
        int bresenhamX, bresenhamY, Yi = yStart;

        for (int Xi = xStart; Xi <= xEnd; Xi++)
        {
            if (Xi == xStart)           // First point
            {
                bresenhamX = xStart;
                bresenhamY = yStart;
            }
            else if (Xi == xEnd)        // Last point
            {
                bresenhamX = xEnd;
                bresenhamY = yEnd;
            }
            else                        // Remaining
            {
                bresenhamX = Xi;

                if (d <= 0)
                {
                    d += incE;      // Move to the East
                }
                else
                {
                    d += incNE;    // Move to the Northeast
                    Yi += 1;
                }
                bresenhamY = Yi;
            }

            // Inverse transformation
            if (steep == true)
                std::swap(bresenhamX, bresenhamY);

            if (symmetric == true)
                bresenhamY *= (-1);

            vertex v{ bresenhamX, bresenhamY };
            vertexList.push_front(v);
        }
        return vertexList;
    }

    /* Function that implements the Bresenham Algorithm for rasterization of circles */
    forward_list<vertex> bresenhamCircle(double x1, double y1, double x2, double y2)
    {
        forward_list<vertex> vertexList;

        // Original coordinates
        int xCenter = static_cast<int>(x1);
        int yCenter = static_cast<int>(y1);
        int xRadius = static_cast<int>(x2);
        int yRadius = static_cast<int>(y2);

        // Variables    
        int d = 1 - yRadius;
        int incE = 3;
        int incSE = (-2 * yRadius) + 5;

        // Bresenham Algorithm
        int bresenhamX, bresenhamY;
        int Yi = yRadius;

        for (int Xi = 0; Yi > Xi; Xi++)
        {
            // First point and Last point
            if (Xi == 0 || Xi == Yi)
            {
                bresenhamX = Xi;
                bresenhamY = Yi;
            }
            else
            {
                bresenhamX = Xi;

                if (d < 0)
                {
                    d += incE;      // Move to the East
                    incE += 2;
                    incSE += 2;
                }
                else
                {
                    d += incSE;     // Move to the Southeast
                    incE += 2;
                    incSE += 4;
                    Yi--;
                }
                bresenhamY = Yi;
            }

            vertex v;
            if (Xi == 0)
            {
                v.x = xCenter + bresenhamX; v.y = yCenter + bresenhamY;
                vertexList.push_front(v);
                v.x = xCenter + bresenhamX; v.y = yCenter - bresenhamY;
                vertexList.push_front(v);
                v.x = xCenter + bresenhamY; v.y = yCenter + bresenhamX;
                vertexList.push_front(v);
                v.x = xCenter - bresenhamY; v.y = yCenter - bresenhamX;
                vertexList.push_front(v);
            }
            else
            {
                v.x = xCenter + bresenhamX; v.y = yCenter + bresenhamY;
                vertexList.push_front(v);
                v.x = xCenter + bresenhamY; v.y = yCenter + bresenhamX;
                vertexList.push_front(v);
                v.x = xCenter + bresenhamY; v.y = yCenter - bresenhamX;
                vertexList.push_front(v);
                v.x = xCenter + bresenhamX; v.y = yCenter - bresenhamY;
                vertexList.push_front(v);

                v.x = xCenter - bresenhamX; v.y = yCenter - bresenhamY;
                vertexList.push_front(v);
                v.x = xCenter - bresenhamY; v.y = yCenter - bresenhamX;
                vertexList.push_front(v);
                v.x = xCenter - bresenhamY; v.y = yCenter + bresenhamX;
                vertexList.push_front(v);
                v.x = xCenter - bresenhamX; v.y = yCenter + bresenhamY;
                vertexList.push_front(v);
            }
        }
        return vertexList;
    }

#endif /* bresenham_h */