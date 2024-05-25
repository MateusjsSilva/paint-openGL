/*
 * Computacao Grafica
 * Codigo Exemplo: Rasterizacao de Segmentos de Reta com GLUT/OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#include "config.h"
#include "glut_text.h"
#include "utils/data_structures.h"
#include "utils/algorithms.h"
#include "utils/graphical_user_interface.h"
// #include "utils/shapes.h"



// Function to store a geometric shape in the list of shapes
void pushShape(int type, bool front = true) 
{
    shapes newShape {
        newShape.type = type,
        newShape.red = redColor,
        newShape.green = greenColor,
        newShape.blue = blueColor
    };
   
    if (front) {
        ListShapes.push_front(newShape);
    }
    else
    {
        ListShapes.reverse();
        ListShapes.push_front(newShape);
        ListShapes.reverse();
    }
}

// Function to store a vertex in the shape of the beginning of the list of geometric shapes
void pushVertex(int x, int y, bool front = true) {
    vertex newVertex {
        newVertex.x = x,
        newVertex.y = y
    };

    if (front) {
        ListShapes.front().v.push_front(newVertex);
    }
    else {
        ListShapes.reverse();
        ListShapes.front().v.push_front(newVertex);
        ListShapes.reverse();
    }
}

// Function to store a transformation in each form in the list
void pushTransformation(int type, double values[2])
{
    transformation newTransformation{
        newTransformation.type = type
    };

    for (int i = 0; i < 2; i++)
    {
        newTransformation.vertexF[i] = values[i];
    }

    // Adds the transformation to all shapes drawn up to that point
    for (forward_list<shapes>::iterator it = ListShapes.begin(); it != ListShapes.end(); ++it)
    {
        it->t.push_front(newTransformation);
    }
}

/* Function prototype  */
void init(void);
void reshape(int w, int h);
void display(void);
void menu_popup(int value);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mousePassiveMotion(int x, int y);


/*  Main function */
int main(int argc, char** argv) 
{
    glutInit(&argc, argv);                          // Passagens de parametro C para o glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);    // Selecao do Modo do Display e do Sistema de cor
    glutInitWindowSize(width, height);              // Tamanho da janela do OpenGL
    glutInitWindowPosition(100, 100);               // Posicao inicial da janela do OpenGL
    glutCreateWindow("Paint");                      // Da nome para uma janela OpenGL

    init();                                         // Chama funcao init();

    glutReshapeFunc(reshape);                       // funcao callback para redesenhar a tela
    glutKeyboardFunc(keyboard);                     // funcao callback do teclado
    glutMouseFunc(mouse);                           // funcao callback do mouse
    glutPassiveMotionFunc(mousePassiveMotion);      // funcao callback do movimento passivo do mouse
    glutDisplayFunc(display);                       // funcao callback de desenho

    // Define o menu pop-up
    int subMenuShapes = glutCreateMenu(menu_popup);

    glutAddMenuEntry("Linha", LINE);
    glutAddMenuEntry("Retângulo", RECTANGLE);
    glutAddMenuEntry("Triângulo", TRIANGLE);
    glutAddMenuEntry("Polígono", POLYGON);
    glutAddMenuEntry("Circunferência", CIRCLE);
    glutAddMenuEntry("Balde de tinta", PAINT_BUCKET);
    glutAddMenuEntry("Retângulo preenchido", FILLED_RECT);
    glutAddMenuEntry("Triângulo preenchido", FILLED_TRI);
    glutAddMenuEntry("Polígono preenchido", FILLED_POLY);

    int subMenuTransforms = glutCreateMenu(menu_popup);

    glutAddMenuEntry("Translação", TRANSLATION);
    glutAddMenuEntry("Escala", SCALING);
    glutAddMenuEntry("Cisalhamento", SHEARING);
    glutAddMenuEntry("Reflexão", REFLECTION);
    glutAddMenuEntry("Rotação", ROTATION);

    glutCreateMenu(menu_popup);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddSubMenu("Formas", subMenuShapes);
    glutAddSubMenu("Transformações", subMenuTransforms);
    glutAddMenuEntry("Sair", 0);

    glutMainLoop();                                 // executa o loop do OpenGL
    return EXIT_SUCCESS;                            // retorna 0 para o tipo inteiro da funcao main();
}

/* Initializes some GLUT parameters */
void init(void) 
{
    glClearColor(1.0, 1.0, 1.0, 1.0);               // Limpa a tela com a cor branca;
}

/* Adjusts the projection for window redesign */
void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);        // Muda para o modo de projecao e reinicializa o sistema de coordenadas
    glLoadIdentity();

    glViewport(0, 0, w, h);             // Definindo o Viewport para o tamanho da janela

    width = w;
    height = h;
    glOrtho(0, w, 0, h, -1, 1);
    
    glMatrixMode(GL_MODELVIEW);         // muda para o modo de desenho
    glLoadIdentity();
}

/* Controls the drawings on the screen */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);       // Limpa o buffer de cores e reinicia a matriz
    glColor3f(0.0, 0.0, 0.0);           // Seleciona a cor default como preto

    drawGUI();

    drawFormas();                       // Desenha as formas geometricas da lista
 
    draw_text_stroke(0, 0, "(" + to_string(m_x) + "," + to_string(m_y) + ")", 0.2);
    glutSwapBuffers();                  // manda o OpenGl renderizar as primitivas
}

/* Controls the pop-up menu */
void menu_popup(int value) 
{
    if (value == 0)
        exit(EXIT_SUCCESS);
    mode = value;
}

/* Control of common keyboard keys */
void keyboard(unsigned char key, int x, int y) 
{
    switch (key) {                      // key - variavel que possui valor ASCII da tecla precionada
        case ESC: 
            exit(EXIT_SUCCESS); 
        break;
    }
}

/* Mouse button control */
void mouse(int button, int state, int x, int y) 
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            switch (mode) {
                case LINE:
                    if (state == GLUT_UP) {
                        if (click1) {
                            x_2 = x;
                            y_2 = height - y - 1;

                            // Verifica se o clique nao foi na area de opcoes
                            if (y_2 <= height - 50)
                            {
                                click1 = false;
                                pushShape(mode, 0);
                                pushVertex(x_1, y_1);
                                pushVertex(x_2, y_2);
                            }
                            printf("Clique 2(%d, %d)\n", x_2, y_2);
                            //push(x_1, y_1, x_2, y_2);
                            click1 = false;
                            glutPostRedisplay();
                        }
                        else {
                            x_1 = x;
                            y_1 = height - y - 1;

                            // Verifica se o clique nao foi na area de opcoes
                            if (y_1 <= height - 50)
                            {
                                click1 = true;
                            }
                            printf("Clique 1(%d, %d)\n", x_1, y_1);
                        }
                    }
                break;
            }
        break;
    }
}

/*
 * Controle da posicao do cursor do mouse
 */
void mousePassiveMotion(int x, int y) {
    m_x = x; m_y = height - y - 1;
    glutPostRedisplay();
}