/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef transformations_h
	#define transformations_h
	
    /*
    * Funcao responsavel por calcular a transformacao de translacao de um determinado vertice
    */
    void translacao(double* desenhoX, double* desenhoY, double Tx, double Ty)
    {
        double matriz[] = { 1 , 0 , 0,
                           0 , 1 , 0,
                           Tx, Ty, 1 };

        // Coordenadas
        *desenhoX = *desenhoX + matriz[6];
        *desenhoY = *desenhoY + matriz[7];
    }


    /*
     * Funcao responsavel por calcular a transformacao de escala de um determinado vertice
    */
    void escala(double* desenhoX, double* desenhoY, double Sx, double Sy)
    {
        double matriz[] = { Sx, 0 , 0,
                           0 , Sy, 0,
                           0 , 0 , 1 };

        // Coordenadas
        *desenhoX = (*desenhoX * matriz[0]);
        *desenhoY = (*desenhoY * matriz[4]);
    }


    /*
     * Funcao responsavel por calcular a transformacao de cisalhamento de um determinado vertice
    */
    void cisalhamento(double* desenhoX, double* desenhoY, double eixo, double valor)
    {
        switch ((char)eixo)
        {
        case 'x':
        {
            double c = valor - 48;

            double matriz[] = { 1, 0, 0,
                               c, 1, 0,
                               0, 0, 1 };

            // Coordenadas
            *desenhoX = *desenhoX + (*desenhoY * matriz[3]);
            *desenhoY = *desenhoY;
        }
        break;

        case 'y':
        {
            double c = valor - 48;

            double matriz[] = { 1, c, 0,
                               0, 1, 0,
                               0, 0, 1 };

            // Coordenadas
            *desenhoX = *desenhoX;
            *desenhoY = *desenhoY + (*desenhoX * matriz[1]);
        }
        break;
        }
    }


    /*
     * Funcao responsavel por calcular a transformacao de reflexao de um determinado vertice
    */
    void reflexao(double* desenhoX, double* desenhoY, double eixo)
    {
        switch ((char)eixo)
        {
        case 'x':
        {
            double matriz[] = { 1,  0, 0,
                               0, -1, 0,
                               0,  0, 1 };

            // Coordenadas
            *desenhoX = *desenhoX;
            *desenhoY *= matriz[4];
        }
        break;

        case 'y':
        {
            double matriz[] = { -1, 0, 0,
                                0, 1, 0,
                                0, 0, 1 };

            // Coordenadas
            *desenhoX *= matriz[0];
            *desenhoY = *desenhoY;
        }
        break;

        case '0':
        {
            double matriz[] = { -1,  0, 0,
                                0, -1, 0,
                                0,  0, 1 };

            // Coordenadas
            *desenhoX *= matriz[0];
            *desenhoY *= matriz[4];
        }
        break;
        }
    }


    /*
     * Funcao responsavel por calcular a transformacao de rotacao de um determinado vertice
    */
    void rotacao(double* desenhoX, double* desenhoY, double teta)
    {
        double matriz[] = { cos(teta), sin(teta), 0,
                           -sin(teta), cos(teta), 0,
                                    0,         0, 1 };

        double tempX = (*desenhoX * matriz[0]) + (*desenhoY * matriz[3]);
        double tempY = (*desenhoX * matriz[1]) + (*desenhoY * matriz[4]);

        // Coordenadas
        *desenhoX = tempX;
        *desenhoY = tempY;
    }

    /*
     * Funcao responsavel por aplicar as transformacoes da forma em cada vertice da mesma
     */
    void aplicaTransformacao(double* desenhoX, double* desenhoY, int centroX, int centroY, forward_list<transformation>::iterator tr)
    {
        // Aplica a transformacao geometrica com base no tipo
        switch (tr->type)
        {
        case TRANSLATION:
        {
            translacao(desenhoX, desenhoY, tr->vertexF[0], tr->vertexF[1]);
        }
        break;

        case SCALING:
        {
            escala(desenhoX, desenhoY, tr->vertexF[0], tr->vertexF[1]);
        }
        break;

        case SHEARING:
        {
            cisalhamento(desenhoX, desenhoY, tr->vertexF[0], tr->vertexF[1]);
        }
        break;

        case REFLECTION:
        {
            reflexao(desenhoX, desenhoY, tr->vertexF[0]);
            switch ((char)tr->vertexF[0])
            {
            case 'x': translacao(desenhoX, desenhoY, 0, 2 * centroY);
                break;

            case 'y': translacao(desenhoX, desenhoY, 2 * centroX, 0);
                break;

            case '0': translacao(desenhoX, desenhoY, 2 * centroX, 2 * centroY);
                break;
            }
        }
        break;

        case ROTATION:
        {
            translacao(desenhoX, desenhoY, -centroX, -centroY);
            rotacao(desenhoX, desenhoY, tr->vertexF[0]);
            translacao(desenhoX, desenhoY, centroX, centroY);
        }
        break;
        }
    }

#endif /* transformations_h */