/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef graphical_user_interface_h
	#define graphical_user_interface_h

    bool isMenuBar(int position);
    void drawColorBars();
    void drawColorSquare();
    void drawButtonsBar(int x, int y, int qntBotoes, int selectedModo);
    void drawAdditionalButtons();
    void drawRectangle(int x, int y, int width, int height);
    void fillRectangle(int x, int y, int width, int height);
    void drawText(const char* text, int x, int y, void* font);

    /* Check if it is in the options menu */
    bool isMenuBar(int position)
    {
        if (position <= height - 60)
            return true;
        return false;
    }

    /* Function responsible for drawing the vertexs */
    void drawVertex(const std::forward_list<vertex>& vertexs)
    {
        // Iterate through the list of vertexs and draw each one
        for (const auto& vertex : vertexs)
        {
            drawPixel(vertex.x, vertex.y);
        }
    }
    
    /* Paint the bar */
    void paintBar() 
    {
        glColor3f(0.0f, 0.0f, 0.0f);

        // Draw the black line at the bottom of the gray bar
        glBegin(GL_LINES);
        glVertex2i(0, height - 65);
        glVertex2i(width, height - 65);
        glEnd();

        glColor3f(0.75f, 0.75f, 0.75f);

        // Draw the bottom bar
        glBegin(GL_POINTS);
        for (int k = 0; k <= width; k++) {
            for (int l = 0; l < 64; l++) {
                glVertex2i(k, height - 64 + l);
            }
        }
        glEnd();
    }

    /* Function responsible for designing the window GUI  */
    void drawGUI() {
        paintBar();
        drawColorBars();
        drawColorSquare();
        drawButtonsBar(70, height - 50, 10, shapeMode);
        drawAdditionalButtons();
    }

    /* Function to draw RGB bars  */
    void drawColorBars() 
    {
        float inc; int whiteX;
        for (int i = 0; i < 3; i++) 
        {
            glColor3f(0.0, 0.0, 0.0);
            drawRectangle(width - 91, height - 26 - (15 * i), 82, 12);

            inc = 0.0; whiteX = width - 88;
            for (int j = width - 90; j <= width - 10; j++) {
                switch (i) 
                {
                    case 0:
                        if ((0.0 + inc) < redColor) 
                            whiteX = j;
                        glColor3f(0.0 + inc, 0.0, 0.0);
                    break;
                    case 1:
                        if ((0.0 + inc) < greenColor) 
                            whiteX = j;
                        glColor3f(0.0, 0.0 + inc, 0.0);
                    break;
                    case 2:
                        if ((0.0 + inc) < blueColor) 
                            whiteX = j;
                        glColor3f(0.0, 0.0, 0.0 + inc);
                    break;
                }
                for (int k = 0; k <= 10; k++) {
                    drawPixel(j, height - 25 - (15 * i) + k);
                }
                inc += 0.0125;
            }

            glColor3f(1.0, 1.0, 1.0);
            for (int k = 0; k <= 10; k++) {
                drawPixel(whiteX, height - 25 - (15 * i) + k);
            }
        }
    }

    /* Function to draw a square with the selected color */
    void drawColorSquare() 
    {
        // Fill the inner square with the selected color
        glColor3f(redColor, greenColor, blueColor);
        fillRectangle(width - 130, height - 50, 29, 29);
    }

    /* Function to draw a bar of buttons */
    void drawButtonsBar(int x, int y, int numButtons, int selectedMode) {
        for (int i = 0, buttonNum = 1; i < 25 * numButtons; i += 25, buttonNum++) {
            glColor3f(0.0, 0.0, 0.0);

            int textPosX = x + i + 7;
            int textPosY = y + 6;
            void* font = GLUT_BITMAP_HELVETICA_18;

            std::string text = std::to_string(buttonNum);
            drawText(text.c_str(), textPosX, textPosY, font);
            drawRectangle(x + 3 + i, y + 3, 20, 20);
        }
    }

    /* Function to draw additional buttons */
    void drawAdditionalButtons() 
    {
        drawRectangle(13, height - 47, 21, 21);
        for (int j = 0; j <= 19; j++) {
            glColor3f(1.0, 1.0, 1.0);
            for (int i = 0; i <= 19; i++) {
                drawPixel(14 + i, height - 46 + j);
            }
        }
     
        glColor3f(1.0f, 0.0f, 0.0f);

        int textPosX = 17, textPosY = height - 44;
        void* font = GLUT_BITMAP_HELVETICA_18;

        drawText("R", textPosX, textPosY, font);
    }

    /* Function to draw a rectangle outline */
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

    /* Function to fill a rectangle with pixels */
    void fillRectangle(int x, int y, int width, int height) {
        for (int i = 0; i <= width; i++) {
            for (int j = 0; j <= height; j++) {
                drawPixel(x + i, y + j);
            }
        }
    }

    /* Preview of shapes*/
    void preview(int shapeMode)
    {
        if (click)
        {
            switch (shapeMode)
            {
            case LINE: // ok
            {
                std::vector<double> x = { (double)mouse_x1, (double)m_x };
                std::vector<double> y = { (double)mouse_y1, (double)m_y };
                drawLine(x, y);
            }
            break;

            case RECTANGLE: //ok
            {
                double x[] = { (double)mouse_x1, (double)mouse_x1, (double)m_x, (double)m_x };
                double y[] = { (double)mouse_y1, (double)m_y, (double)m_y, (double)mouse_y1 };
                drawRectangle(x, y);
            }
            break;

            case TRIANGLE: // ok
            {
                if (contVertex == 1)
                {
                    std::vector<double> x = { (double)mouse_x1, (double)m_x };
                    std::vector<double> y = { (double)mouse_y1, (double)m_y };
                    drawLine(x, y);
                }
                else if (contVertex == 2)
                {
                    double x[] = { (double)mouse_x1, (double)mouse_x2, (double)m_x };
                    double y[] = { (double)mouse_y1, (double)mouse_y2, (double)m_y };
                    drawTriangle(x, y);
                }
            }
            break;

            case POLYGON: // ok
            {
                forward_list<shapes>::iterator f = listShapes.begin();

                // Count the current number of vertices in the polygon
                int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

                // Lists with the x and y coordinates of each vertex of the shape
                std::vector<double> x(numVertices + 1), y(numVertices + 1);

                // Assign the new vertex coordinates to the first position
                x[0] = m_x;
                y[0] = m_y;

                // Save all existing vertex coordinates
                int i = 1;
                for (auto v = f->vertexs.begin(); v != f->vertexs.end(); ++v, ++i)
                {
                    x[i] = v->x;
                    y[i] = v->y;
                }

                drawPolygon(x, y);
            }
            break;

            case CIRCLE: // ok
            {
                double x[] = { (double)m_x, (double)mouse_x1 };
                double y[] = { (double)m_y, (double)mouse_y1 };
                drawCircle(x, y);
            }
            break;

            case FILLED_RECT: // ok
            {
                /*
                std::vector<double> x = { (double)mouse_x1, (double)mouse_x1, (double)m_x, (double)m_x };
                std::vector<double> y = { (double)mouse_y1, (double)m_y, (double)m_y, (double)mouse_y1 };
                //drawFilledRectangle(x, y);
                */
            }
            break;

            case FILLED_TRI: // ok
            {
                /*if (contVertex == 1)
                {
                    
                    std::vector<double> x = { (double)mouse_x1, (double)m_x };
                    std::vector<double> y = { (double)mouse_y1, (double)m_y };
                    drawLine(x, y);
                   
                }
                else if (contVertex == 2)
                {
                    std::vector<double> x = { (double)mouse_x1, (double)mouse_x2, (double)m_x };
                    std::vector<double> y = { (double)mouse_y1, (double)mouse_y2, (double)m_y };
                    drawFilledTriangle(x, y);
                }
                 */
            }
            break;

            case FILLED_POLY:
            {
                /*
                forward_list<shapes>::iterator f = listShapes.begin();

                // Count the current number of vertices in the polygon
                int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(numVertices + 1), y(numVertices + 1);

                // Save all coordinates
                int i = 1;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
                {
                    x[i] = v->x;
                    y[i] = v->y;
                }

                // If the polygon has only one vertex, draw a line; otherwise, draw a filled polygon
                if (numVertices == 1)
                    drawLine(x, y);
                else
                    drawFilledPolygon(x, y);
                */
            }
            break;
            }
        }
    }

    /* Function that draws the list of geometric shapes */
    void drawShapes()
    {
        if (contVertex != 0)
            glColor3f(1.0, 0.0, 0.0);
        else
            glColor3f(redColor, greenColor, blueColor);

        preview(shapeMode);

        // Iterate through the list of geometric shapes to draw
        for (forward_list<shapes>::iterator f = listShapes.begin(); f != listShapes.end(); f++)
        {
            glColor3f(f->red, f->green, f->blue);

            switch (f->type)
            {
            case LINE: // 0
            {
                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(2), y(2);

                // Variables to calculate the center of the shape
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex and calculate the center
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
                {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= 2;
                centerY /= 2;

                // Apply transformations stored in the shape
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    applyTransformation(&x[0], &y[0], centerX, centerY, tr);
                    applyTransformation(&x[1], &y[1], centerX, centerY, tr);
                }

                drawLine(x, y);
            }
            break;

            case RECTANGLE: // ok
            {
                // Arrays to store the x and y coordinates of each vertex of the shape
                double x[4], y[4];

                // Variables to calculate the center of the shape
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex and calculate the center
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
                {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= 4;
                centerY /= 4;

                // Apply transformations stored in the shape
                for (int k = 0; k < 4; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                if (i == 4)
                    drawRectangle(x, y);
            }
            break;

            case TRIANGLE: // ok
            {
                // Arrays to store the x and y coordinates of each vertex of the triangle
                double x[3], y[3];

                // Variables to calculate the center of the triangle
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex and calculate the center
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= 3;
                centerY /= 3;

                // Apply the transformations stored in the shape
                for (int k = 0; k < 3; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                if (i == 3)
                    drawTriangle(x, y);
            }
            break;

            case POLYGON: // ok
            {
                // Count the current number of vertices in the polygon
                int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(numVertices), y(numVertices);

                // Variables to calculate the center of the polygon
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex and calculate the center
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
                {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= numVertices;
                centerY /= numVertices;

                // Apply the transformations stored in the shape
                for (int k = 0; k < numVertices; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                drawPolygon(x, y);
            }
            break;

            case CIRCLE: // ok
            {
                // Lists to store the x and y coordinates of each vertex of the shape
                double x[2], y[2];

                // Coordinates of the center of the circle
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex of the shape
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                    x[i] = v->x;
                    y[i] = v->y;
                }
                centerX = x[0];
                centerY = y[0];

                // Apply the transformations stored in the shape
                for (int k = 0; k < 2; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                drawCircle(x, y);
            }
            break;

            case PAINT_BUCKET: // ok
            {
                // Coordinates (x, y) of the initial click
                double x, y;

                // Save the coordinates of the pixel clicked
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++) {
                    x = v->x;
                    y = v->y;
                }

                // Apply the transformations stored in the shape
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    applyTransformation(&x, &y, x, y, tr);
                }

                // Determine the color of the clicked pixel
                float oldColor[3];
                glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, oldColor);

                // Determine the new color
                float newColor[] = { f->red, f->green, f->blue };

                fillShape(x, y, oldColor, newColor);
            }
            break;

            case FILLED_RECT: // ok
            {
                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(4), y(4);

                // Coordinates of the center of the rectangle
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex of the shape
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= 4;
                centerY /= 4;

                // Apply the transformations stored in the shape
                for (int k = 0; k < 4; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                if (i == 4)
                    drawFilledRectangle(x, y);
            }
            break;

            case FILLED_TRI: // ok
            {
                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(3), y(3);
                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex of the shape
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }
                centerX /= 3;
                centerY /= 3;

                // Apply the transformations stored in the shape
                for (int k = 0; k < 3; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                if (i == 3)
                    drawFilledTriangle(x, y);
            }
            break;

            case FILLED_POLY: // ok
            {
                // Count the current number of vertices of the polygon
                int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

                // Lists to store the x and y coordinates of each vertex of the shape
                std::vector<double> x(numVertices), y(numVertices);

                int centerX = 0, centerY = 0;

                // Save the coordinates of each vertex
                int i = 0;
                for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
                {
                    x[i] = v->x;
                    y[i] = v->y;

                    centerX += (int)x[i];
                    centerY += (int)y[i];
                }

                // Identify the center of the polygon by the arithmetic mean of its vertices
                centerX /= numVertices;
                centerY /= numVertices;

                // Apply the transformations stored in the shape
                for (int k = 0; k < numVertices; k++)
                {
                    for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                    {
                        applyTransformation(&x[k], &y[k], centerX, centerY, tr);
                    }
                }

                if (numVertices == 2)
                {
                    drawLine(x, y);
                }
                else if (numVertices > 2)
                {
                    drawFilledPolygon(x, y);
                }
            }
            break;
            }
        }
    }

    /* Function to draw text */
    void drawText(const char* text, int x, int y, void* font)
    {
        // Define a posição inicial do texto
        glRasterPos2i(x, y);

        // Desenha o texto caractere por caractere
        for (const char* c = text; *c != '\0'; c++)
        {
            glutBitmapCharacter(font, *c);
        }
    }

    /* Function responsible for all text designs */
    void drawTexts()
    {
        glColor3f(0.0, 0.0, 0.0);
        draw_text_stroke(1, 5, "(" + to_string(m_x) + "," + to_string(m_y) + ")", 0.1);

        double mouse_x = m_x, mouse_y = m_y;
        
        glColor3f(0.0, 0.0, 0.0);

        if (m_x > 70 && m_x < 95)   // mouse
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Mouse", 0.1);
        }
        else if (m_x > 95 && m_x < 120) // line
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Linha", 0.1);
        }
        else if (m_x > 120 && m_x < 145) // retang
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Retangulo", 0.1);
        }
        else if (m_x > 145 && m_x < 170) // retang fill
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Retangulo Preenchido", 0.1);
        }
        else if (m_x > 170 && m_x < 195) // triangle
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Triangulo", 0.1); 
        }
        else if (m_x > 195 && m_x < 220) // triangle fill
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Triangulo Preenchido", 0.1);
        }
        else if (m_x > 220 && m_x < 245)
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Poligono", 0.1);        
        }
        else if (m_x > 245 && m_x < 270)
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Poligono Preenchido", 0.1);
        }
        else if (m_x > 270 && m_x < 295)
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Circunferencia", 0.1);
        }
        else if (m_x > 295 && m_x < 320)
        {
            if (m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Balde de tinta", 0.1);
        }
        else if (m_x >= width - 90 && m_x <= width - 10) // rgb
        {
            glColor3f(1.0, 0.0, 0.0);
            
            if (m_y > height - 25 && m_y < height - 15) // red
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                draw_text_stroke(width - 80, height - 80, "red: " + to_string(corEscolhida[0]).substr(0, 4), 0.1);
            }
            else if (m_y > height - 39 && m_y < height - 26) // green
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                draw_text_stroke(width - 80, height - 80, "green: " + to_string(corEscolhida[1]).substr(0, 4), 0.1);
            }
            else if (m_y > height - 60 && m_y < height - 40) // blue
            {
                float corEscolhida[3];
                glReadPixels(m_x, m_y, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                draw_text_stroke(width - 80, height - 80, "blue: " + to_string(corEscolhida[2]).substr(0, 4), 0.1);
            }
        }
        else if (m_x >= 13 && m_x <= 33) // reset
        {
            if(m_y >= height - 50 && m_y <= height - 25)
                draw_text_stroke(mouse_x + 10, mouse_y - 25, "Reset", 0.1);
        }
    }

    /* Function handling interactions with buttons */
    void onButtonClick(int mouseX, int mouseY)
    {
        bool clear = false;

        if (mouseX > 70 && mouseX < 95)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = MOUSE;
                clear = true;
            }
        }
        else if (mouseX > 95 && mouseX < 120)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = LINE;
                clear = true;
            }
        }
        else if (mouseX > 120 && mouseX < 145)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = RECTANGLE;
                clear = true;
            }
        }
        else if (mouseX > 145 && mouseX < 170)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = FILLED_RECT;
                clear = true;
            }
        }
        else if (mouseX > 170 && mouseX < 195)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = TRIANGLE;
                clear = true;
            }
        }
        else if (mouseX > 195 && mouseX < 220)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = FILLED_TRI;
                clear = true;
            }
        }
        else if (mouseX > 220 && mouseX < 245)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = POLYGON;
                clear = true;
            }
        }
        else if (mouseX > 245 && mouseX < 270)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = FILLED_POLY;
                clear = true;
            }
        }
        else if (mouseX > 270 && mouseX < 295)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = CIRCLE;
                clear = true;
            }
        }
        else if (mouseX > 295 && mouseX < 320)
        {
            if (mouseY >= height - 50 && mouseY <= height - 25)
            {
                shapeMode = PAINT_BUCKET;
                clear = true;
            }
        }
        else if (mouseX >= 13 && mouseX <= 33)
        {
            if (mouseY >= height - 50 && mouseX <= height - 25) {
                listShapes.clear();
                clear = true;
            }     
        }
        else if (mouseX >= width - 90 && mouseX <= width - 10)
        {
            if (mouseY > height - 25 && mouseY < height - 15)
            {
                float corEscolhida[3];
                glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                redColor = corEscolhida[0];
            }
            else if (mouseY > height - 39 && mouseY < height - 26)
            {
                float corEscolhida[3];
                glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                greenColor = corEscolhida[1];
            }
            else if (mouseY > height - 60 && mouseY < height - 40)
            {
                float corEscolhida[3];
                glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);
                blueColor = corEscolhida[2];
            }
        }

        if (clear) {
            contVertex = 0;
        }
    }

#endif /* graphical_user_interface_h */