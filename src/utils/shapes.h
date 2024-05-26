/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once
#include <iostream>

#ifndef shapes_h
    #define shapes_h

    /* Function responsible for drawing a line */
    void drawLine(const std::vector<double>& x, const std::vector<double>& y)
    {
        forward_list<vertex> vertices = bresenhamLine(x[0], y[0], x[1], y[1]);
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            double drawX = it->x;
            double drawY = it->y;
            drawPixel(drawX, drawY);
        }
    }

    /* Function responsible for drawing a rectangle */
    void drawRectangle(double* x, double* y)
    {
        for (int k = 0; k < 4; k++)
        {
            forward_list<vertex> vertexs;
            if (k != 3)
            {
                vertexs = bresenhamLine(x[k], y[k], x[k + 1], y[k + 1]);
            }
            else
            {
                vertexs = bresenhamLine(x[k], y[k], x[0], y[0]);
            }

            for (auto it = vertexs.begin(); it != vertexs.end(); ++it)
            {
                double drawX = it->x;
                double drawY = it->y;
                drawPixel(drawX, drawY);
            }
        }
    }

    /* Function responsible for drawing a triangle */
    void drawTriangle(double* x, double* y)
    {
        for (int j = 0; j < 3; j++)
        {
            forward_list<vertex> vertexs;
            if (j != 2)
            {
                vertexs = bresenhamLine(x[j], y[j], x[j + 1], y[j + 1]);
            }
            else
            {
                vertexs = bresenhamLine(x[j], y[j], x[0], y[0]);
            }

            for (auto it = vertexs.begin(); it != vertexs.end(); ++it)
            {
                double drawX = it->x;
                double drawY = it->y;
                drawPixel(drawX, drawY);
            }
        }
    }

    /* Function responsible for drawing a polygon */
    void drawPolygon(const std::vector<double>& x, const std::vector<double>& y)
    {
        int numVertexs = x.size();
        forward_list<vertex> vertexs;
        for (int j = 0; j < numVertexs - 1; j++)
        {
            vertexs = bresenhamLine(x[j], y[j], x[j + 1], y[j + 1]);

            for (const auto& v : vertexs)
            {
                double vertexX = v.x;
                double vertexY = v.y;
                drawPixel(vertexX, vertexY);
            }
        }
    }

    /* Function responsible for drawing a circle */
    void drawCircle(double* x, double* y)
    {
        // Generate the vertexs of the circle using Bresenham's circle algorithm
        forward_list<vertex> vertexs = bresenhamCircle(x[1], y[1], x[0], y[0]);

        // Iterate through the list of vertices and draw each pixel
        for (auto v = vertexs.begin(); v != vertexs.end(); ++v)
        {
            double drawX = v->x;
            double drawY = v->y;
            drawPixel(drawX, drawY);
        }
    }

    /* Function responsible for filling a shape with a new color */
    void fillShape(double x, double y, float* oldColor, float* newColor)
    {
        // List to store vertexs affected by the flood fill algorithm
        forward_list<vertex> affectedVertexs;

        // Apply flood fill algorithm to fill the shape with the new color
        floodFillAlgorithm(x, y, oldColor, newColor, &affectedVertexs);
    }

    /* Function responsible for drawing a filled rectangle */
    void drawFilledRectangle(std::vector<double> x, std::vector<double> y)
    {
        // Generate the vertexs of the filled rectangle using the fillPolygon algorithm
        forward_list<vertex> vertexs = fillPolygon(x, y);

        // Iterate through the list of vertexs and draw each pixel
        for (auto v = vertexs.begin(); v != vertexs.end(); ++v)
        {
            double drawX = v->x;
            double drawY = v->y;
            drawPixel(drawX, drawY);
        }
    }

    /* Function responsible for drawing a filled triangle */
    void drawFilledTriangle(std::vector<double> x, std::vector<double> y)
    {
        // Generate the vertexs of the filled triangle using the fillPolygon algorithm
        forward_list<vertex> vertexs = fillPolygon(x, y);

        // Iterate through the list of vertexs and draw each pixel
        for (auto v = vertexs.begin(); v != vertexs.end(); ++v)
        {
            double drawX = v->x;
            double drawY = v->y;
            drawPixel(drawX, drawY);
        }
    }

    /* Function responsible for drawing a filled polygon */
    void drawFilledPolygon(std::vector<double> x, std::vector<double> y)
    {
        // Generate the vertices of the filled polygon using the fillPolygon algorithm
        forward_list<vertex> vertexs = fillPolygon(x, y);

        // Iterate through the list of vertices and draw each pixel
        for (auto v = vertexs.begin(); v != vertexs.end(); ++v)
        {
            double drawX = v->x;
            double drawY = v->y;
            drawPixel(drawX, drawY);
        }
    }

#endif /* shapes_h */