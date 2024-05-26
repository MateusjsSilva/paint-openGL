/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef global_variables_h
	#define global_variables_h

	// Checks whether the first mouse click was made
	bool click = false;

	// Window width and height
	int width = 600, height = 600;

	// Indicates the type of active geometric shape to draw
	int shapeMode = 2;

	// Vertex counter
	int contVertex = 0;

	// Coordinates of the current mouse position
	int m_x, m_y;

	// Coordinates of the first mouse click and second mouse click
	int mouse_x1, mouse_y1, mouse_x2, mouse_y2;

	// Color selected for the design
	float redColor = 0, greenColor = 0, blueColor = 0;

	// Linked list of geometric shapes
	forward_list<shapes> listShapes;

#endif /* global_variables_h */