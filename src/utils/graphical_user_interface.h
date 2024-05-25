/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef graphical_user_interface_h
	#define graphical_user_interface_h

    // Function prototype
    void drawPixel(int x, int y);
    void drawFormas();

    // List of geometric shapes
    forward_list<shapes> shapeList;

    // Window dimensions
    int windowWidth = 512;
    int windowHeight = 512;

    // Flag to check if the first mouse click was made
    bool isFirstClick = false;

    // Current mouse coordinates
    int mouseX;
    int mouseY;

    // Current drawing and transformation mode
    int drawMode;
    int transformMode;

    // Coordinates of the first and second mouse click
    int firstClickX;
    int firstClickY;
    int secondClickX;
    int secondClickY;

    // RGB colors selected for the drawing
    float selectedRed = 0;
    float selectedGreen = 0;
    float selectedBlue = 0;

    /**
     * @brief Draws a single pixel on the screen at the specified 2D coordinates.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     */
    void drawPixel(int x, int y)
    {
        glBegin(GL_POINTS);
            glVertex2i(x, y);
        glEnd();
    }


    /*
     * Funcao que desenha a lista de formas geometricas
     */
    void drawShapes() 
    {
        if (isFirstClick)
            bresenham(firstClickX, firstClickY, secondClickX, secondClickY);

        // Percorre a lista de formas geometricas para desenhar
        for (forward_list<shapes>::iterator f = shapeList.begin(); f != shapeList.end(); f++) {
            switch (f -> type) {
            case LINE:
                int i = 0, x[2]{}, y[2];

                // Percorre a lista de vertices da forma linha para desenhar
                for (forward_list<vertex>::iterator v = f->v.begin(); v != f->v.end(); v++, i++) {
                    x[i] = v->x;
                    y[i] = v->y;
                }

                // Desenha o segmento de reta apos dois cliques
                bresenham(x[0], y[0], x[1], y[1]);
                break;
            }
        }
    }

    /*
    *
    */
    void drawVertex(forward_list<vertex> v)
    {
        for (forward_list<vertex>::iterator it_v = v.begin(); it_v != v.end(); it_v++)
        {
            drawPixel(it_v->x, it_v->y, 1);
        }
    }



    /*
     * Funcao responsavel pelo desenho da GUI da janela
    */
    void drawGUI()
    {
        forward_list<vertex> v;

        glColor3f(1.0, 1.0, 1.0);                       // branco


        glutPostRedisplay();
    }
#endif /* graphical_user_interface_h */