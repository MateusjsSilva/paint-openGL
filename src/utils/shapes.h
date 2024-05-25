/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef shapes_h
    #define shapes_h

    /*
     * Funcao responsavel por desenhar uma linha no editor grafico
     */
    void desenhaLinha(std::vector<double> x, std::vector<double> y)
    {
        forward_list<vertex> vertices = bresenhamLine(x[0], y[0], x[1], y[1]);
        for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
        {
            double desenhoX = v->x;
            double desenhoY = v->y;
            drawPixel(desenhoX, desenhoY);
        }
    }


    /*
     * Funcao responsavel por desenhar um retangulo no editor grafico
     */
    void desenhaRetangulo(double* x, double* y)
    {
        forward_list<vertex> vertices;
        for (int k = 0; k < 4; k++)
        {
            if (k != 3)
            {
                vertices = bresenhamLine(x[k], y[k], x[k + 1], y[k + 1]);
            }
            else
            {
                vertices = bresenhamLine(x[k], y[k], x[0], y[0]);
            }

            for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
            {
                double desenhoX = v->x;
                double desenhoY = v->y;
                drawPixel(desenhoX, desenhoY);
            }
        }
    }


    /*
     * Funcao responsavel por desenhar um triangulo no editor grafico
     */
    void desenhaTriangulo(double* x, double* y)
    {
        forward_list<vertex> vertices;
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
            {
                vertices = bresenhamLine(x[j], y[j], x[j + 1], y[j + 1]);
            }
            else
            {
                vertices = bresenhamLine(x[j], y[j], x[0], y[0]);
            }

            for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
            {
                double desenhoX = v->x;
                double desenhoY = v->y;
                drawPixel(desenhoX, desenhoY);
            }
        }
    }


    /*
     * Funcao responsavel por desenhar um poligono no editor grafico
     * O modo se encerra quando o poligono possui no minimo quatro vertices,
     * e o usuario clica no vertice inicial
     */
    void desenhaPoligono(std::vector<double> x, std::vector<double> y, int numVertices)
    {
        forward_list<vertex> vertices;
        for (int j = 0; j < numVertices - 1; j++)
        {
            vertices = bresenhamLine(x[j], y[j], x[j + 1], y[j + 1]);

            for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
            {
                double desenhoX = v->x;
                double desenhoY = v->y;
                drawPixel(desenhoX, desenhoY);
            }
        }
    }


    /*
     * Funcao responsavel por desenhar uma circunferencia no editor grafico
     */
    void desenhaCircunferencia(double* x, double* y)
    {
        forward_list<vertex> vertices = bresenhamCircle(x[1], y[1], x[0], y[0]);
        for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
        {
            double desenhoX = v->x;
            double desenhoY = v->y;
            drawPixel(desenhoX, desenhoY);
        }
    }


    /*
     * Funcao responsavel por colorir o interior de uma forma
     */
    void desenhaBalde(double x, double y, float* corAntiga, float* corNova)
    {
        forward_list<vertex> vertices;
        algoritmoFloodFill(x, y, corAntiga, corNova, &vertices);
    }



    /*
     * Funcao responsavel por desenhar um retangulo preenchido no editor grafico
     */
    void desenhaRetanguloPreenchido(std::vector<double> x, std::vector<double> y)
    {
        forward_list<vertex> vertices = preenchePoligono(x, y, 4);
        for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
        {
            double desenhoX = v->x;
            double desenhoY = v->y;
            drawPixel(desenhoX, desenhoY);
        }
    }


    /*
     * Funcao responsavel por desenhar um triangulo preenchido no editor grafico
     */
    void desenhaTrianguloPreenchido(std::vector<double> x, std::vector<double> y)
    {
        forward_list<vertex> vertices = preenchePoligono(x, y, 3);
        for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
        {
            double desenhoX = v->x;
            double desenhoY = v->y;
            drawPixel(desenhoX, desenhoY);
        }
    }


    /*
     * Funcao responsavel por desenhar um poligono preenchido no editor grafico
     * O modo se encerra quando o poligono possui no minimo quatro vertices,
     * e o usuario clica no vertice inicial
     */
    void desenhaPoligonoPreenchido(std::vector<double> x, std::vector<double> y, int numVertices)
    {
        forward_list<vertex> vertices = preenchePoligono(x, y, numVertices);
        for (forward_list<vertex>::iterator v = vertices.begin(); v != vertices.end(); v++)
        {
            double desenhoX = v->x;
            double desenhoY = v->y;
            drawPixel(desenhoX, desenhoY);
        }
    }

#endif /* shapes_h */