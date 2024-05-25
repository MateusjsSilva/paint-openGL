#pragma once

/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#ifndef bresenham_h
    #define bresenham_h

    /*
    * Function that implements the Bresenham Algorithm (considering all the octants)
    */
    forward_list<vertex> bresenham(double x1, double y1, double x2, double y2)
    {
        // Lista de vertices a serem desenhados
        forward_list<vertex> listaVertices;

        // Coordenadas originais
        int xInicio = (int)x1;
        int yInicio = (int)y1;
        vertex v1; v1.x = x1; v1.y = y1;
        listaVertices.push_front(v1);

        int xFim = (int)x2;
        int yFim = (int)y2;
        vertex v2; v2.x = x2; v2.y = y2;
        listaVertices.push_front(v2);

        // Variaveis - parte 1
        int variacaoX = xFim - xInicio;
        int variacaoY = yFim - yInicio;

        // Reducao ao primeiro octante
        int tmp;

        // Verifica se o declive eh negativo
        bool simetrico = false;

        int coeficienteAngular = variacaoX * variacaoY;
        if (coeficienteAngular < 0)
        {
            simetrico = true;

            // Troca o sinal das coordenadas Y
            yInicio *= (-1);
            yFim *= (-1);
            variacaoY *= (-1);
        }

        // Verifica se o declive eh superior a 1
        bool declive = false;

        if (abs(variacaoX) < abs(variacaoY))
        {
            declive = true;

            // Troca a posicao de x e y em cada coordenada
            tmp = xInicio;
            xInicio = yInicio;
            yInicio = tmp;

            tmp = xFim;
            xFim = yFim;
            yFim = tmp;

            tmp = variacaoX;
            variacaoX = variacaoY;
            variacaoY = tmp;
        }

        // Verifica se xInicio eh maior que xFim
        if (xInicio > xFim)
        {
            // Troca a ordem das coordenadas
            tmp = xInicio;
            xInicio = xFim;
            xFim = tmp;

            tmp = yInicio;
            yInicio = yFim;
            yFim = tmp;

            variacaoX *= (-1);
            variacaoY *= (-1);
        }

        // Variaveis - parte 2
        int d = (2 * variacaoY) - variacaoX;
        int incE = (2 * variacaoY);
        int incNE = 2 * (variacaoY - variacaoX);

        // Algoritmo de Bresenham
        int bresenhamX, bresenhamY;
        int Yi = yInicio;

        for (int Xi = xInicio; Xi <= xFim; Xi++)
        {
            // Primeiro ponto
            if (Xi == xInicio)
            {
                bresenhamX = xInicio;
                bresenhamY = yInicio;
            }

            // Ultimo ponto
            else if (Xi == xFim)
            {
                bresenhamX = xFim;
                bresenhamY = yFim;
            }

            // Restante
            else
            {
                bresenhamX = Xi;

                if (d <= 0)
                {
                    d += incE;      // Avanco pro Leste
                }
                else
                {
                    d += incNE;    // Avanco pro Nordeste
                    Yi += 1;
                }
                bresenhamY = Yi;
            }

            // Transformacao inversa
            if (declive == true)
            {
                tmp = bresenhamX;
                bresenhamX = bresenhamY;
                bresenhamY = tmp;
            }

            if (simetrico == true)
            {
                bresenhamY *= (-1);
            }

            vertex v;
            v.x = bresenhamX;
            v.y = bresenhamY;
            listaVertices.push_front(v);
        }
        return listaVertices;
    }

#endif /* bresenham_h */