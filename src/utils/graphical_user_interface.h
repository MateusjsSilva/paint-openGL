/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef graphical_user_interface_h
	#define graphical_user_interface_h

    void drawColorBars();
    void drawColorSquare();
    void drawButtonsBar(int x, int y, int width, int height, int qntBotoes, int selectedModo);
    void drawTransformationButtons();
    void drawAdditionalButtons();
    void drawRectangle(int x, int y, int width, int height);
    void fillRectangle(int x, int y, int width, int height);

    /* Function responsible for drawing the vertexs */
    void drawVertex(const std::forward_list<vertex>& vertexs)
    {
        // Iterate through the list of vertexs and draw each one
        for (const auto& vertex : vertexs)
        {
            drawPixel(vertex.x, vertex.y);
        }
    }

    // Function responsible for designing the window GUI
    void drawGUI() {
        // Set the drawing color to a light gray
        glColor3f(0.75f, 0.75f, 0.75f);

        // Draw the bottom bar
        for (int k = 0; k <= width; k++) {
            for (int l = 0; l <= 64; l++) {
                drawPixel(k, height - 65 + l);
            }
        }

        // Draw RGB color bars
        drawColorBars();

        // Draw a square with the selected color for visualization
        drawColorSquare();

        // Draw the bottom buttons bar
        drawButtonsBar(70, height - 45, 140, 19, 3, shapeMode);

        // Draw the top buttons bar
        drawButtonsBar(110, height - 25, 60, 19, 3, shapeMode - 5);

        // Draw columns of geometric transformations if the current mode is 0
        if (shapeMode == 0) {
            drawTransformationButtons();
        }

        // Draw additional buttons
        drawAdditionalButtons();
    }

    // Function to draw RGB color bars
    void drawColorBars() {
        float increment;
        int whiteX;
        for (int i = 0; i < 3; i++) {
            // Set the color of the bar (green)
            glColor3f(0.0, 1.0, 0.0);
            drawRectangle(width - 91, height - 16 - (15 * i), 82, 12);

            increment = 0.0;
            whiteX = width - 88;
            for (int j = width - 90; j <= width - 10; j++) {
                switch (i) {
                case 0:
                    if ((0.0 + increment) < redColor) whiteX = j;
                    glColor3f(0.0 + increment, 0.0, 0.0);
                    break;
                case 1:
                    if ((0.0 + increment) < greenColor) whiteX = j;
                    glColor3f(0.0, 0.0 + increment, 0.0);
                    break;
                case 2:
                    if ((0.0 + increment) < blueColor) whiteX = j;
                    glColor3f(0.0, 0.0, 0.0 + increment);
                    break;
                }
                for (int k = 0; k <= 10; k++) {
                    drawPixel(j, height - 15 - (15 * i) + k);
                }
                increment += 0.0125;
            }

            // Draw the white indicator line on the color bar
            glColor3f(1.0, 1.0, 1.0);
            for (int k = 0; k <= 10; k++) {
                drawPixel(whiteX, height - 15 - (15 * i) + k);
            }
        }
    }

    // Function to draw a square with the selected color
    void drawColorSquare() {
        // Draw the outer black square
        glColor3f(0.0, 0.0, 0.0);
        drawRectangle(width - 131, height - 36, 27, 27);

        // Fill the inner square with the selected color
        glColor3f(redColor, greenColor, blueColor);
        fillRectangle(width - 130, height - 35, 25, 25);
    }

    // Function to draw a bar of buttons
    void drawButtonsBar(int x, int y, int width, int height, int numButtons, int selectedMode) {
        // Set the drawing color to gray
        glColor3f(0.57, 0.58, 0.58);
        drawRectangle(x, y, width, height);

        // Fill the bar with a slightly darker gray
        fillRectangle(x + 1, y + 1, width - 2, height - 2);

        // Draw individual buttons
        for (int i = 0; i < 20 * numButtons; i += 20) {
            if (i / 20 == selectedMode) {
                // Highlight the selected button in red
                glColor3f(1.0, 0.0, 0.0);
            }
            else {
                // Set other buttons to black
                glColor3f(0.0, 0.0, 0.0);
            }
            drawRectangle(x + 1 + i, y + 1, 18, 17);
        }
    }

    // Function to draw buttons for geometric transformations
    void drawTransformationButtons() {
        int numTransformationButtons = 5;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j <= (numTransformationButtons - i) % 3; j++) {
                // Set the drawing color to gray
                glColor3f(0.57, 0.58, 0.58);
                drawRectangle(250 + (20 * i), height - 17 - (15 * j), 15, 15);
                fillRectangle(251 + (20 * i), height - 17 - (15 * j), 13, 13);

                // Highlight the selected transformation button in red
                if ((i == (transformationMode - 10) / 3) && (j == (transformationMode - 10) % 3)) {
                    glColor3f(1.0, 0.0, 0.0);
                }
                else {
                    glColor3f(0.0, 0.0, 0.0);
                }
                drawRectangle(251 + (20 * i), height - 16 - (15 * j), 13, 13);
            }
        }
    }

    // Function to draw additional buttons
    void drawAdditionalButtons() {
        // Draw the brightness button
        glColor3f(0.57, 0.58, 0.58);
        drawRectangle(0, height - 25, 25, 24);

        float increment = 0.0;
        for (int j = 0; j <= 22; j++) {
            glColor3f(0.02, 0.02, 0.15 + increment);
            for (int i = 0; i <= 23; i++) {
                drawPixel(1 + i, height - 24 + j);
            }
            increment += 0.0138;
        }

        // Draw the reset button
        drawRectangle(25, height - 25, 25, 24);
        increment = 0.0;
        for (int j = 0; j <= 22; j++) {
            glColor3f(0.02, 0.02, 0.15 + increment);
            for (int i = 0; i <= 23; i++) {
                drawPixel(26 + i, height - 24 + j);
            }
            increment += 0.0138;
        }

        // Draw the save button
        drawRectangle(0, height - 50, 25, 24);
        increment = 0.0;
        for (int j = 0; j <= 23; j++) {
            glColor3f(0.9, 0.30 + increment, 0.0);
            for (int i = 0; i <= 23; i++) {
                drawPixel(1 + i, height - 49 + j);
            }
            increment += 0.0136;
        }
    }

    // Function to draw a rectangle outline
    void drawRectangle(int x, int y, int width, int height) {
        for (int i = 0; i <= width; i++) {
            drawPixel(x + i, y);
            drawPixel(x + i, y + height);
        }
        for (int j = 0; j <= height; j++) {
            drawPixel(x, y + j);
            drawPixel(x + width, y + j);
        }
    }

    // Function to fill a rectangle with pixels
    void fillRectangle(int x, int y, int width, int height) {
        for (int i = 0; i <= width; i++) {
            for (int j = 0; j <= height; j++) {
                drawPixel(x + i, y + j);
            }
        }
    }



    /*
     * Funcao responsavel por todos os desenhos envolvendo textos no projeto
    */
    void desenhaTextos()
    {
        /* ====== Desenha o par de coordenadas na tela ====== */
        if (m_y < height - 50)
        {
            glColor3f(0.0, 0.0, 0.0);

            draw_text_stroke(0, 3, "(" + to_string(m_x) + "," + to_string(m_y) + ")", 0.1);
        }



        /* ====== Mouse em um botao de forma ====== */
        double mouse_x = m_x, mouse_y = m_y;

        // Botao MOU
        if (m_x > 70 && m_x < 90)
        {
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != MOUSE)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 40, mouse_x + 40, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Mouse", 0.08);
            }
        }

        // Botao LIN
        else if (m_x > 90 && m_x < 110)
        {
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != LINE)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 35, mouse_x + 35, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Linha", 0.08);
            }
        }

        else if (m_x > 110 && m_x < 130)
        {
            // Botao RET
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != RECTANGLE)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 56, mouse_x + 56, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Retangulo", 0.08);
            }

            // Botao RETp
            else if (m_y >= height - 25 && m_y <= height - 5 && shapeMode != FILLED_RECT)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 116, mouse_x + 116, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Retangulo Preenchido", 0.08);
            }
        }

        else if (m_x > 130 && m_x < 150)
        {
            // Botao TRI
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != TRIANGLE)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 53, mouse_x + 53, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Triangulo", 0.08);
            }

            // Botao TRIp
            else if (m_y >= height - 25 && m_y <= height - 5 && shapeMode != FILLED_TRI)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 112, mouse_x + 112, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Triangulo Preenchido", 0.08);
            }
        }

        else if (m_x > 150 && m_x < 170)
        {
            // Botao POL
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != POLYGON)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 50, mouse_x + 50, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Poligono", 0.08);
            }

            // Botao POLp
            else if (m_y >= height - 25 && m_y <= height - 5 && shapeMode != FILLED_POLY)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 110, mouse_x + 110, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Poligono Preenchido", 0.08);
            }
        }

        // Botao CIR
        else if (m_x > 170 && m_x < 190)
        {
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != CIRCLE)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 78, mouse_x + 78, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Circunferencia", 0.08);
            }
        }

        // Botao BAL
        else if (m_x > 190 && m_x < 210)
        {
            if (m_y >= height - 45 && m_y <= height - 25 && shapeMode != PAINT_BUCKET)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 35, mouse_x + 35, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Balde", 0.08);
            }
        }




        /* ====== Mouse em um botao de transformacao ====== */
        else if (m_x > 250 && m_x < 265)
        {
            if (shapeMode == MOUSE || shapeMode > TRANSLATION)
            {
                // Botao TRAN
                if (m_y >= height - 17 && m_y <= height - 2 && transformationMode  != TRANSLATION)
                {
                    std::vector<double> x = { mouse_x + 8 , mouse_x + 60, mouse_x + 60, mouse_x + 8 };
                    std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                    glColor3f(1.0, 1.0, 0.0);
                    forward_list<vertex> v = preenchePoligono(x, y, 4);
                    drawVertex(v);

                    glColor3f(0.0, 0.0, 0.0);
                    draw_text_stroke(mouse_x + 10, mouse_y - 25, "Translacao", 0.08);
                }

                // Botao ESCA
                else if (m_y >= height - 32 && m_y <= height - 17 && transformationMode  != SCALING)
                {
                    std::vector<double> x = { mouse_x + 8 , mouse_x + 40, mouse_x + 40, mouse_x + 8 };
                    std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                    glColor3f(1.0, 1.0, 0.0);
                    forward_list<vertex> v = preenchePoligono(x, y, 4);
                    drawVertex(v);

                    glColor3f(0.0, 0.0, 0.0);
                    draw_text_stroke(mouse_x + 10, mouse_y - 25, "Escala", 0.08);
                }

                // Botao CISA
                else if (m_y >= height - 47 && m_y <= height - 32 && transformationMode  != SHEARING)
                {
                    std::vector<double> x = { mouse_x + 8 , mouse_x + 72, mouse_x + 72, mouse_x + 8 };
                    std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                    glColor3f(1.0, 1.0, 0.0);
                    forward_list<vertex> v = preenchePoligono(x, y, 4);
                    drawVertex(v);

                    glColor3f(0.0, 0.0, 0.0);
                    draw_text_stroke(mouse_x + 10, mouse_y - 25, "Cisalhamento", 0.08);
                }
            }
        }

        else if (m_x > 270 && m_x < 285)
        {
            if (shapeMode == MOUSE || shapeMode > TRANSLATION)
            {
                // Botao REFL
                if (m_y >= height - 17 && m_y <= height - 2 && transformationMode  != REFLECTION)
                {
                    std::vector<double> x = { mouse_x + 8 , mouse_x + 48, mouse_x + 48, mouse_x + 8 };
                    std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                    glColor3f(1.0, 1.0, 0.0);
                    forward_list<vertex> v = preenchePoligono(x, y, 4);
                    drawVertex(v);

                    glColor3f(0.0, 0.0, 0.0);
                    draw_text_stroke(mouse_x + 10, mouse_y - 25, "Reflexao", 0.08);
                }

                // Botao ROTA
                else if (m_y >= height - 32 && m_y <= height - 17 && transformationMode  != ROTATION)
                {
                    std::vector<double> x = { mouse_x + 8 , mouse_x + 48, mouse_x + 48, mouse_x + 8 };
                    std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                    glColor3f(1.0, 1.0, 0.0);
                    forward_list<vertex> v = preenchePoligono(x, y, 4);
                    drawVertex(v);

                    glColor3f(0.0, 0.0, 0.0);
                    draw_text_stroke(mouse_x + 10, mouse_y - 25, "Rotacao", 0.08);
                }
            }
        }




        /* ====== Mouse em uma barra RGB ====== */
        else if (m_x >= width - 90 && m_x <= width - 10)
        {
            // Barra R
            if (m_y > height - 15 && m_y < height - 5)
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

                std::vector<double> x = { mouse_x + 8 , mouse_x + 32, mouse_x + 32, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, to_string(corEscolhida[0]).substr(0, 4), 0.08);
            }

            // Barra G
            else if (m_y > height - 30 && m_y < height - 20)
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

                std::vector<double> x = { mouse_x + 8 , mouse_x + 32, mouse_x + 32, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, to_string(corEscolhida[1]).substr(0, 4), 0.08);
            }

            // Barra B
            else if (m_y > height - 45 && m_y < height - 35)
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

                std::vector<double> x = { mouse_x + 8 , mouse_x + 32, mouse_x + 32, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };


                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, to_string(corEscolhida[2]).substr(0, 4), 0.08);
            }
        }




        /* ====== Mouse no quadrado de cor ====== */
        else if (m_y > height - 36 && m_y < height - 9)
        {
            if (m_x > width - 131 && m_x < width - 104)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 85, mouse_x + 85, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "(" + to_string(redColor).substr(0, 4) + ","
                    + to_string(greenColor).substr(0, 4) + ","
                    + to_string(blueColor).substr(0, 4) + ")", 0.08);
            }
        }




        /* ====== Mouse em um botao especial ====== */
        if (m_y >= height - 25 && m_y <= height - 1)
        {
            // Botao de claridade
            if (m_x > 0 && m_x < 25)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 102, mouse_x + 102, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Alternar pra Noite", 0.08);
            }

            // Botao de reset
            else if (m_x > 25 && m_x < 50)
            {
                std::vector<double> x = { mouse_x + 8 , mouse_x + 37, mouse_x + 37, mouse_x + 8 };
                std::vector<double> y = { mouse_y - 27, mouse_y - 27, mouse_y - 15, mouse_y - 15 };

                glColor3f(1.0, 1.0, 0.0);
                forward_list<vertex> v = preenchePoligono(x, y, 4);
                drawVertex(v);

                glColor3f(0.0, 0.0, 0.0);
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Reset", 0.08);
            }
        }
    }

#endif /* graphical_user_interface_h */