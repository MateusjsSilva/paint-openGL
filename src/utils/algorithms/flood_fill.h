/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef flood_fill_h
	#define flood_fill_h

    /*
    * Funcao que implementa o Algoritmo Flood Fill para preenchimento de poligonos
    */
    void algoritmoFloodFill(int x1, int y1, float* corAntiga, float* corNova, forward_list<vertex>* vertices)
    {
        // Verifica se este pixel ja foi analisado pelo algoritmo
        bool jaAnalisado = false;
        for (forward_list<vertex>::iterator it_v = vertices->begin(); it_v != vertices->end(); it_v++)
        {
            if (it_v->x == x1 && it_v->y == y1)
            {
                jaAnalisado = true;
                break;
            }
        }


        // Se nao tenha sido, faz a verificacao
        if (jaAnalisado == false)
        {
            // Guarda a cor do pixel analisado
            float corPixelAtual[3];
            glReadPixels(x1, y1, 1, 1, GL_RGB, GL_FLOAT, corPixelAtual);

            // Caso o pixel seja da cor antiga
            if (corPixelAtual[0] == corAntiga[0] &&
                corPixelAtual[1] == corAntiga[1] &&
                corPixelAtual[2] == corAntiga[2])
            {
                // Pinta o pixel com a nova cor
                glColor3f(corNova[0], corNova[1], corNova[2]);
                drawPixel(x1, y1, 0);


                // Salva o vertice na lista de vertices ja analisados
                vertex v;
                v.x = x1;
                v.y = y1;
                vertices->push_front(v);


                // Chamadas recursivas pros seus vizinhos cardeais (FloodFill com vizinhanca 4)
                algoritmoFloodFill(x1 + 1, y1, corAntiga, corNova, vertices);
                algoritmoFloodFill(x1, y1 + 1, corAntiga, corNova, vertices);
                algoritmoFloodFill(x1 - 1, y1, corAntiga, corNova, vertices);
                algoritmoFloodFill(x1, y1 - 1, corAntiga, corNova, vertices);
            }
        }
    }
#endif /* flood_fill_h */