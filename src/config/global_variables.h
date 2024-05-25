/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef global_variables_h
	#define global_variables_h

	// Verifica se foi realizado o primeiro clique do mouse
	bool click1 = false;

	// Largura e altura da janela
	int width = 600, height = 600;

	// Indica o tipo de forma geometrica ativa para desenhar
	int shapeMode = 1, transformationMode = 0;

	// Contador de vertices
	int contCoordenadas = 0;

	// Coordenadas da posicao atual do mouse
	int m_x, m_y;

	// Coordenadas do primeiro clique e do segundo clique do mouse
	int mouseClick_x1, mouseClick_y1, mouseClick_x2, mouseClick_y2;

	// Cor selecionada pro desenho
	float redColor = 0, greenColor = 0, blueColor = 0;

	// Linked list of geometric shapes
	forward_list<shapes> listShapes;

#endif /* global_variables_h */