/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef scanline_polygon_fill_algorithm_h
	#define scanline_polygon_fill_algorithm_h

    #include <tuple>
    #include <algorithm>

    // Função para criar a tabela de arestas
    std::vector<std::vector<double>> createEdgeTable(const std::vector<double>& x, const std::vector<double>& y) {
        std::vector<std::vector<double>> edgeTable;
        int numVertices = x.size();

        for (int i = 0; i < numVertices; ++i) {
            int next = (i + 1) % numVertices;
            if (y[i] == y[next]) continue; // Ignorar arestas horizontais

            double yMin = std::min(y[i], y[next]);
            double yMax = std::max(y[i], y[next]);
            double x_yMin = (y[i] < y[next]) ? x[i] : x[next];
            double mInverse = (x[next] - x[i]) / (y[next] - y[i]);

            edgeTable.push_back({ yMin, yMax, x_yMin, mInverse });
        }

        return edgeTable;
    }

    // Função para ordenar a tabela de arestas pela coordenada y_min
    void sortEdgeTable(std::vector<std::vector<double>>& edgeTable) {
        std::sort(edgeTable.begin(), edgeTable.end(), [](const std::vector<double>& a, const std::vector<double>& b) {
            return a[0] < b[0];
            });
    }

    // Função para ordenar a tabela de arestas ativa pela coordenada x_yMin
    void sortActiveEdgeTable(std::vector<std::vector<double>>& activeEdgeTable) {
        std::sort(activeEdgeTable.begin(), activeEdgeTable.end(), [](const std::vector<double>& a, const std::vector<double>& b) {
            return a[2] < b[2];
            });
    }

    // Função para adicionar spans à lista de vértices
    void addSpansToVertexList(std::forward_list<vertex>& vertexList, const std::vector<std::vector<double>>& activeEdgeTable, int scanline) {
        for (size_t i = 0; i < activeEdgeTable.size(); i += 2) {
            // Verifique se o próximo índice existe
            if (i + 1 >= activeEdgeTable.size()) {
                break;
            }

            for (size_t i = 0; i < activeEdgeTable.size() - 1; ++i) {
                double xStart = activeEdgeTable[i][2];
                double xEnd = activeEdgeTable[i + 1][2];

                for (int x = xStart; x <= xEnd; ++x) {
                    vertexList.push_front(vertex{ x, scanline });
                }
            }
        }
    }

    // Função para remover arestas completadas
    void removeCompletedEdges(std::vector<std::vector<double>>& activeEdgeTable, int scanline) {
        activeEdgeTable.erase(std::remove_if(activeEdgeTable.begin(), activeEdgeTable.end(),
            [scanline](const std::vector<double>& edge) {
                return edge[1] <= scanline;
            }), activeEdgeTable.end());
    }

    // Função para atualizar a tabela de arestas ativa
    void updateActiveEdgeTable(std::vector<std::vector<double>>& activeEdgeTable) {
        for (auto& edge : activeEdgeTable) {
            edge[2] += edge[3]; // Atualizar x_yMin
        }
    }

    // Função principal do algoritmo Scan-line Polygon fill
    std::forward_list<vertex> fillPolygon(const std::vector<double>& x, const std::vector<double>& y) {
        auto edgeTable = createEdgeTable(x, y);
        sortEdgeTable(edgeTable);
        std::forward_list<vertex> vertexList;
        std::vector<std::vector<double>> activeEdgeTable;
        int scanline = static_cast<int>(std::ceil(edgeTable.front()[0]));
        int maxY = static_cast<int>(std::floor(edgeTable.back()[1]));

        for (; scanline <= maxY; ++scanline) {
            for (auto it = edgeTable.begin(); it != edgeTable.end();) {
                if ((*it)[0] <= scanline) {
                    activeEdgeTable.push_back(*it);
                    it = edgeTable.erase(it);
                }
                else {
                    ++it;
                }
            }
            sortActiveEdgeTable(activeEdgeTable);
            addSpansToVertexList(vertexList, activeEdgeTable, scanline);
            removeCompletedEdges(activeEdgeTable, scanline);
            updateActiveEdgeTable(activeEdgeTable);
        }

        return vertexList;
    }

#endif /* scanline_polygon_fill_algorithm_h */