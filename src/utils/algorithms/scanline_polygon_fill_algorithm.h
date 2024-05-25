/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef scanline_polygon_fill_algorithm_h
	#define scanline_polygon_fill_algorithm_h

     /*
      * Funcao que implementa o Algoritmo de Preenchimento de Poligonos
      * para o desenho de poligonos coloridos
     */
   /* forward_list<vertex> preenchePoligono(double x[], double y[], int tamanhoVetor)
    {
        // Lista de vertices a serem desenhados
        forward_list<vertex> listaVertices;


        // Descobre a quantidade de arestas a serem analisadas no poligono
        int contArestas = 0;
        for (int i = 0; i < tamanhoVetor; i++)
        {
            double x0, y0, x1, y1;

            if (i != tamanhoVetor - 1)
            {
                x0 = x[i];
                y0 = y[i];
                x1 = x[i + 1];
                y1 = y[i + 1];
            }
            else
            {
                x0 = x[i];
                y0 = y[i];
                x1 = x[0];
                y1 = y[0];
            }

            // Verifica se os pontos formam uma aresta horizontal
            // Se sim, nao conta a aresta
            if (x0 != x1 && y0 == y1)
            {
                continue;
            }
            else
            {
                contArestas++;
            }
        }


        // Listas com os vertices das arestas validas
        double coordsX[2 * contArestas], coordsY[2 * contArestas];
        int k = 0;
        for (int i = 0; i < tamanhoVetor; i++)
        {
            double x0, y0, x1, y1;

            if (i != tamanhoVetor - 1)
            {
                x0 = x[i];
                y0 = y[i];
                x1 = x[i + 1];
                y1 = y[i + 1];
            }
            else
            {
                x0 = x[i];
                y0 = y[i];
                x1 = x[0];
                y1 = y[0];
            }


            if (x0 != x1 && y0 == y1)
            {
                continue;
            }
            else
            {
                coordsX[k] = x0;
                coordsY[k] = y0;
                coordsX[k + 1] = x1;
                coordsY[k + 1] = y1;
                k += 2;
            }
        }




        // Cria a Tabela de Arestas
        // Cada linha eh uma aresta com os dados: [yMin | yMax | x_yMin | mInvert]
        double ta[contArestas][4];

        int pos = 0;
        double menorY = 1.79769e+308, maiorY = 0.0;
        for (int i = 0; i < 2 * contArestas; i += 2)
        {
            double x0 = coordsX[i];
            double y0 = coordsY[i];
            double x1 = coordsX[i + 1];
            double y1 = coordsY[i + 1];

            // Calcula as variaveis de cada aresta
            double yMin, yMax, x_yMin, mInvert;
            if (y1 <= y0)
            {
                yMin = y1;
                yMax = y0;
                x_yMin = x1;
            }
            else
            {
                yMin = y0;
                yMax = y1;
                x_yMin = x0;
            }


            // Encontra mInvert, evitando a divisao 0/0
            if (x1 != x0 && y1 != y0)
            {
                mInvert = (x1 - x0) / (y1 - y0);
            }
            else
            {
                mInvert = 0.0;
            }


            // Salva o menor e o maior Y dentre todos os vertices
            // (usados futuramente como intervalo no algoritmo da TAA)
            if (yMin < menorY)
            {
                menorY = yMin;
            }

            if (yMax > maiorY)
            {
                maiorY = yMax;
            }


            // Insere na tabela
            ta[pos][0] = yMin;
            ta[pos][1] = yMax;
            ta[pos][2] = x_yMin;
            ta[pos][3] = mInvert;
            pos++;
        }



        // Ordenacoes pra garantir a seguinte leitura dos vertices das arestas na TA


        // Ordena a TA com base nos yMin (InsertionSort)
        for (int i = 1; i < contArestas; i++)
        {
            double yMin = ta[i][0], yMax = ta[i][1], x_yMin = ta[i][2], mInvert = ta[i][3];
            int j = i - 1;

            while (j >= 0 && yMin < ta[j][0])
            {
                ta[j + 1][0] = ta[j][0];
                ta[j + 1][1] = ta[j][1];
                ta[j + 1][2] = ta[j][2];
                ta[j + 1][3] = ta[j][3];
                j--;
            }

            ta[j + 1][0] = yMin;
            ta[j + 1][1] = yMax;
            ta[j + 1][2] = x_yMin;
            ta[j + 1][3] = mInvert;
        }


        // Ordena a TA com base nos yMax de mesmo yMin (InsertionSort)
        int pos_yMin = 0;
        double yMinAtual = menorY;
        for (int i = 0; i < contArestas; i++)
        {
            if (ta[i][0] != yMinAtual)
            {
                for (int j = pos_yMin + 1; j < i; j++)
                {
                    double yMin = ta[j][0], yMax = ta[j][1], x_yMin = ta[j][2], mInvert = ta[j][3];
                    int k = j - 1;

                    while (k >= pos_yMin && yMax < ta[k][1])
                    {
                        ta[k + 1][0] = ta[k][0];
                        ta[k + 1][1] = ta[k][1];
                        ta[k + 1][2] = ta[k][2];
                        ta[k + 1][3] = ta[k][3];
                        k--;
                    }

                    ta[k + 1][0] = yMin;
                    ta[k + 1][1] = yMax;
                    ta[k + 1][2] = x_yMin;
                    ta[k + 1][3] = mInvert;
                }

                yMinAtual = ta[i][0];
                pos_yMin = i;
            }

            else if (i == contArestas - 1)
            {
                for (int j = pos_yMin + 1; j <= i; j++)
                {
                    double yMin = ta[j][0], yMax = ta[j][1], x_yMin = ta[j][2], mInvert = ta[j][3];
                    int k = j - 1;

                    while (k >= pos_yMin && yMax < ta[k][1])
                    {
                        ta[k + 1][0] = ta[k][0];
                        ta[k + 1][1] = ta[k][1];
                        ta[k + 1][2] = ta[k][2];
                        ta[k + 1][3] = ta[k][3];
                        k--;
                    }

                    ta[k + 1][0] = yMin;
                    ta[k + 1][1] = yMax;
                    ta[k + 1][2] = x_yMin;
                    ta[k + 1][3] = mInvert;
                }
            }
        }




        // Cria a Tabela de Arestas Ativas
        double taa[contArestas][4];
        for (int i = 0; i < contArestas; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                taa[i][j] = -1;
            }
        }

        // Registra a posicao da maior linha da TAA com uma aresta carregada
        int indexTAA = -1;




        // Algoritmo de Rasterizacao
        for (int i = menorY; i < maiorY; i++)
        {

            // Atualiza o indexTAA
            for (int j = 0; j < contArestas; j++)
            {
                if (taa[j][0] == -1 && taa[j][1] == -1 && taa[j][2] == -1 && taa[j][3] == -1)
                {
                    indexTAA = j;
                    break;
                }
                else if (j == contArestas - 1)
                {
                    indexTAA = j;
                }
            }


            // Carrega as arestas da TA na TAA a cada y
            for (int j = 0; j < contArestas; j++)
            {
                if (ta[j][0] == i)
                {
                    taa[indexTAA][0] = ta[j][0];
                    taa[indexTAA][1] = ta[j][1];
                    taa[indexTAA][2] = ta[j][2];
                    taa[indexTAA][3] = ta[j][3];

                    ta[j][0] = -1;
                    ta[j][1] = -1;
                    ta[j][2] = -1;
                    ta[j][3] = -1;

                    indexTAA++;
                }
            }


            // Indica TAA vazia (fim do algoritmo)
            if (indexTAA == 0)
            {
                break;
            }


            // Ordena a TAA pelo x_yMin (InsertionSort)
            for (int j = 1; j < indexTAA; j++)
            {
                double yMin0 = taa[j][0], yMax0 = taa[j][1], x_yMin0 = taa[j][2], mInvert0 = taa[j][3];
                double yMin1 = taa[j + 1][0], yMax1 = taa[j + 1][1], x_yMin1 = taa[j + 1][2], mInvert1 = taa[j + 1][3];
                int k = j - 1;

                while (k >= 0 && x_yMin0 < taa[k][2])
                {
                    taa[k + 1][0] = taa[k][0];
                    taa[k + 1][1] = taa[k][1];
                    taa[k + 1][2] = taa[k][2];
                    taa[k + 1][3] = taa[k][3];
                    k--;
                }

                taa[k + 1][0] = yMin0;
                taa[k + 1][1] = yMax0;
                taa[k + 1][2] = x_yMin0;
                taa[k + 1][3] = mInvert0;
            }


            // Adiciona os vertices da scanline na tabela de vertices
            for (int j = 0; j < indexTAA; j += 2)
            {
                int span0, span1;

                // Verifica se necessita truncar pra cima o primeiro span
                // (casting sozinho trunca pra baixo)
                if (taa[j][2] != (int)taa[j][2])
                {
                    span0 = (int)taa[j][2] + 1;
                }
                else
                {
                    span0 = (int)taa[j][2];
                }

                // Trunca pra baixo o segundo span
                span1 = (int)taa[j + 1][2];


                // Adiciona o span de vertices na lista
                for (int k = span0; k <= span1; k++)
                {
                    vertex v;
                    v.x = k; v.y = i;
                    listaVertices.push_front(v);
                }
            }


            // Remove da TAA todas as arestas onde y = yMax-1
            int quantRemovidos = 0;
            for (int j = 0; j < indexTAA; j++)
            {
                if (i + 1 == taa[j][1])
                {
                    for (int k = j; k < indexTAA; k++)
                    {
                        taa[k][0] = taa[k + 1][0];
                        taa[k][1] = taa[k + 1][1];
                        taa[k][2] = taa[k + 1][2];
                        taa[k][3] = taa[k + 1][3];
                    }
                    j--;
                    indexTAA--;
                }
            }


            // Incrementa os x_yMin de cada aresta da TAA
            // (para cada aresta na TAA, incrementa seu x_yMin com seu mInvert)
            for (int j = 0; j < indexTAA; j++)
            {
                taa[j][2] += taa[j][3];
            }


            // Reordena a TAA pelo x_yMin (necessario p/ poligonos intersectantes) (InsertionSort)
            for (int j = 1; j < indexTAA; j++)
            {
                double yMin0 = taa[j][0], yMax0 = taa[j][1], x_yMin0 = taa[j][2], mInvert0 = taa[j][3];
                double yMin1 = taa[j + 1][0], yMax1 = taa[j + 1][1], x_yMin1 = taa[j + 1][2], mInvert1 = taa[j + 1][3];
                int k = j - 1;

                while (k >= 0 && x_yMin0 < taa[k][2])
                {
                    taa[k + 1][0] = taa[k][0];
                    taa[k + 1][1] = taa[k][1];
                    taa[k + 1][2] = taa[k][2];
                    taa[k + 1][3] = taa[k][3];
                    k--;
                }

                taa[k + 1][0] = yMin0;
                taa[k + 1][1] = yMax0;
                taa[k + 1][2] = x_yMin0;
                taa[k + 1][3] = mInvert0;
            }
        }

        return listaVertices;
    }
    */
#endif /* scanline_polygon_fill_algorithm_h */