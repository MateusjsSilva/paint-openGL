/*
 * Computacao Grafica
 * Codigo Exemplo: Rasterizacao de Segmentos de Reta com GLUT/OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#include "config/config.h"
#include "config/glut_text.h"
#include "utils/data_structures.h"
#include "config/global_variables.h"
#include "utils/algorithms.h"
#include "utils/shapes.h"
#include "utils/transformations.h"
#include "utils/graphical_user_interface.h"

/* Function forward declarations (function signatures) */
void init(void);
void reshape(int w, int h);
void display(void);
void menu_popup(int value);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void mousePassiveMotion(int x, int y);
void pushShape(int type, bool front);
void pushVertex(int x, int y, bool front);
void pushTransformation(int type, const std::vector<double>& values);

/*  Main function */
int main(int argc, char** argv) 
{
    glutInit(&argc, argv);                                     // Passagem de parametros C para o glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);               // Selecao do modo do Display e do sistema de cor utilizado
    glutInitWindowSize(width, height);                         // Tamanho da janela do OpenGL
    glutInitWindowPosition(100, 100);                          // Posicao inicial da janela do OpenGL
    glutCreateWindow("Paint");                                 // Da nome para uma janela OpenGL

    init();                                                    // Chama a funcao init()

    glutReshapeFunc(reshape);                                  // Callback para redesenhar a tela
    glutKeyboardFunc(keyboard);                                // Callback do teclado
    glutMouseFunc(mouse);                                      // Callback do mouse
    glutPassiveMotionFunc(mousePassiveMotion);                 // Callback do movimento passivo do mouse
    glutDisplayFunc(display);                                  // Callback de desenho

    // Define o menu pop-up
    int subMenuShapes = glutCreateMenu(menu_popup);

    glutAddMenuEntry("Linha", LINE);
    glutAddMenuEntry("Retangulo", RECTANGLE);
    glutAddMenuEntry("Triangulo", TRIANGLE);
    glutAddMenuEntry("Poligono", POLYGON);
    glutAddMenuEntry("Circunferencia", CIRCLE);
    glutAddMenuEntry("Balde de tinta", PAINT_BUCKET);
    glutAddMenuEntry("Retangulo preenchido", FILLED_RECT);
    glutAddMenuEntry("Triangulo preenchido", FILLED_TRI);
    glutAddMenuEntry("Poligono preenchido", FILLED_POLY);

    int subMenuTransforms = glutCreateMenu(menu_popup);

    glutAddMenuEntry("Translacao", TRANSLATION);
    glutAddMenuEntry("Escala", SCALING);
    glutAddMenuEntry("Cisalhamento", SHEARING);
    glutAddMenuEntry("Reflexao", REFLECTION);
    glutAddMenuEntry("Rotacao", ROTATION);

    glutCreateMenu(menu_popup);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutAddMenuEntry("Mouse", MOUSE);
    glutAddSubMenu("Formas", subMenuShapes);
    glutAddSubMenu("Transformacoes", subMenuTransforms);
    glutAddMenuEntry("Sair", 0);

    glutMainLoop();                                 // Executa o loop do OpenGL
    return EXIT_SUCCESS;                            // Eetorna 0 para o tipo inteiro da funcao main();
}

/* Initializes some GLUT parameters */
void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

/* Controls the pop-up menu  */
void menu_popup(int value) {
    if (value == 0)
        exit(EXIT_SUCCESS);
    shapeMode = value;
}

/* Adjusts the projection for window redesign */
void reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);    // Muda pro modo de projecao
    glLoadIdentity();               // Carrega a matriz identidade
    glViewport(0, 0, w, h);
    width = w; height = h;
    glOrtho(0, w, 0, h, -1, 1); 
}

/* Control of common keyboard keys */
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case ESC: 
            exit(EXIT_SUCCESS);
        break;
    }
}

/*  Mouse button control  */
void mouse(int button, int state, int x, int y)
{
    switch (button)
    {   
        case GLUT_LEFT_BUTTON:
            switch (shapeMode)
            {
                case MOUSE:
                    if (state == GLUT_UP)
                    {
                        mouse_x1 = x; mouse_y1 = height - y - 1;
                        contVertex = 0;
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                    break;

                case LINE: // ok
                    if (state == GLUT_UP) {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                click = false; contVertex = 0;

                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                                pushVertex(mouse_x2, mouse_y2, true);
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case RECTANGLE: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                click = false; contVertex = 0;

                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y2, true);
                                pushVertex(mouse_x2, mouse_y2, true);
                                pushVertex(mouse_x2, mouse_y1, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case TRIANGLE: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                if (contVertex == 1)
                                {
                                    click = true; contVertex++;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                                else
                                {
                                    click = false; contVertex = 0;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                            }
                            else
                            {
                                onButtonClick(mouse_x1, mouse_y1);
                            }
                        }
                    }
                    break;

                case POLYGON: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                if (contVertex > 3)
                                {
                                    if (mouse_x2 == mouse_x1 && mouse_y2 == mouse_y1)
                                    {
                                        click = false; contVertex = 0;
                                        pushVertex(mouse_x2, mouse_y2, true);
                                    }
                                    else
                                    {
                                        contVertex++;
                                        pushVertex(mouse_x2, mouse_y2, true);
                                    }
                                }
                                else
                                {
                                    contVertex++;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                            }
                            else
                                onButtonClick(x, height - y - 1);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case CIRCLE: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                click = false; contVertex = 0;
                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                                pushVertex(mouse_x2, mouse_y2, true);
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case PAINT_BUCKET: // ok
                    if (state == GLUT_UP)
                    {
                        if (!click)
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                pushShape(PAINT_BUCKET, false);
                                pushVertex(mouse_x1, mouse_y1, false);
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case FILLED_RECT: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                click = false; contVertex = 0;
                                pushShape(shapeMode, false);
                                pushVertex(mouse_x1, mouse_y2, false);
                                pushVertex(mouse_x2, mouse_y2, false);
                                pushVertex(mouse_x2, mouse_y1, false);
                                pushVertex(mouse_x1, mouse_y1, false);
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case FILLED_TRI: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (isMenuBar(mouse_y2))
                            {
                                if (contVertex == 1)
                                {
                                    click = true; contVertex++;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                                else
                                {
                                    click = false; contVertex = 0;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case FILLED_POLY: // ok
                    if (state == GLUT_UP)
                    {
                        if (click)
                        {
                            mouse_x2 = x; mouse_y2 = height - y - 1;
                            if (mouse_y2 <= height - 50)
                            {
                                if (contVertex > 3)
                                {
                                    if (mouse_x2 == mouse_x1 && mouse_y2 == mouse_y1)
                                    {
                                        click = false; contVertex = 0;
                                    }
                                    else
                                    {
                                        contVertex++;
                                        pushVertex(mouse_x2, mouse_y2, true);
                                    }
                                }
                                else
                                {
                                    contVertex++;
                                    pushVertex(mouse_x2, mouse_y2, true);
                                }
                            }
                            else
                                onButtonClick(mouse_x2, mouse_y2);
                        }
                        else
                        {
                            mouse_x1 = x; mouse_y1 = height - y - 1;
                            if (isMenuBar(mouse_y1))
                            {
                                click = true; contVertex++;
                                pushShape(shapeMode, true);
                                pushVertex(mouse_x1, mouse_y1, true);
                            }
                            else
                                onButtonClick(mouse_x1, mouse_y1);
                        }
                    }
                    break;

                case TRANSLATION:
                {
                    if (isMenuBar(mouse_y1))
                    {
                        std::vector<double> v(2);
                        std::cout << "Digite os valores de translacao (x y), ex: 1 2: ";

                        if (!(std::cin >> v[0] >> v[1])) {
                            std::cerr << "Erro ao ler os valores de translacao. Certifique-se de digitar dois numeros.\n";
                        }

                        pushTransformation(TRANSLATION, v);
                        shapeMode = MOUSE;
                    }
                    else
                    {
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                    break;
                }
                case SCALING:
                {
                    if (isMenuBar(mouse_y1))
                    {
                        std::vector<double> v(2);
                        std::cout << "Digite os valores de escala (x y), ex: 1 2: ";

                        if (!(std::cin >> v[0] >> v[1])) {
                            std::cerr << "Erro ao ler os valores de translacao. Certifique-se de digitar dois numeros.\n";
                        }

                        pushTransformation(SCALING, v);
                        shapeMode = MOUSE;
                    }
                    else
                    {
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                    break;
                }
                break;

                case SHEARING:
                {
                    if (isMenuBar(mouse_y1))
                    {
                        std::vector<char> d(2);

                        std::cout << "Digite o eixo e o valor de cisalhamento (ex: \"x 5\"): ";
                        std::cin >> d[0] >> d[1];

                        std::vector<double> vetorD(2);
                        vetorD[0] = static_cast<double>(d[0]);
                        vetorD[1] = static_cast<double>(d[1]);

                        pushTransformation(SHEARING, vetorD);
                        shapeMode = MOUSE;
                    }
                    else
                    {
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                }
                break;

                case REFLECTION:
                {
                    if (isMenuBar(mouse_y1))
                    {
                        char eixo;
                        std::cout << "Digite o eixo de reflexao (\"x\", \"y\" ou \"0\"): ";
                        std::cin >> eixo;

                        if (eixo != 'x' && eixo != 'y' && eixo != '0') {
                            std::cerr << "Erro: eixo invalido. Use 'x', 'y' ou '0'.\n";
                            return;
                        }

                        std::vector<double> vetorD(2, 0.0);
                        vetorD[0] = eixo;

                        pushTransformation(REFLECTION, vetorD);
                        shapeMode = MOUSE;
                    }
                    else
                    {
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                }
                break;

                case ROTATION:
                {
                    if (isMenuBar(mouse_y1))
                    {
                        int grauRotacao;
                        std::cout << "Digite o grau de rotacao: ";
                        std::cin >> grauRotacao;

                        if (std::cin.fail()) {
                            std::cerr << "Erro: entrada invalida. Digite um número inteiro.\n";
                            return;
                        }

                        double radianos = grauRotacao * M_PI / 180.0;

                        std::vector<double> vetorD(2, 0.0);
                        vetorD[0] = radianos;

                        pushTransformation(ROTATION, vetorD);
                        shapeMode = MOUSE;
                    }
                    else
                    {
                        onButtonClick(mouse_x1, mouse_y1);
                    }
                }
                break;
            }
        break;
    }
}

/* Mouse cursor position control */
void mousePassiveMotion(int x, int y) {
    m_x = x; m_y = height - y - 1;
    glutPostRedisplay();
}

/* Controls the drawings on the screen */
void display(void)  
{
    glMatrixMode(GL_MODELVIEW);     // Muda pro modo de desenho
    glClear(GL_COLOR_BUFFER_BIT);   // Limpa o Buffer de Cores
    glLoadIdentity();               // Carrega a matriz identidade
    drawGUI();                      // Carrega a GUI
    drawTexts();                    // Desenha texto com as coordenadas da posicao do mouse
    drawShapes();                   // Desenha as formas geometricas da lista
    glutSwapBuffers();              // Troca os buffers
}

/* Function to store a geometric shape in the list of shapes */
static void pushShape(int type, bool front = true)
{
    shapes newShape{
        newShape.type = type,
        newShape.red = redColor,
        newShape.green = greenColor,
        newShape.blue = blueColor
    };

    if (front) {
        listShapes.push_front(newShape);
    }
    else
    {
        listShapes.reverse();
        listShapes.push_front(newShape);
        listShapes.reverse();
    }
}

/* Function to store a vertex in the shape of the beginning of the list of geometric shapes */
static void pushVertex(int x, int y, bool front = true) {
    vertex newVertex{
        newVertex.x = x,
        newVertex.y = y
    };

    if (front) {
        listShapes.front().vertexs.push_front(newVertex);
    }
    else {
        listShapes.reverse();
        listShapes.front().vertexs.push_front(newVertex);
        listShapes.reverse();
    }
}

/* Function to store a transformation in each form in the list */
static void pushTransformation(int type, const std::vector<double>& values)
{
    transformation newTransformation{
        newTransformation.type = type
    };

    for (int i = 0; i < 2; i++)
    {
        newTransformation.vertexF[i] = values[i];
    }

    // Adds the transformation to all shapes drawn up to that point
    for (forward_list<shapes>::iterator it = listShapes.begin(); it != listShapes.end(); ++it)
    {
        it -> transformations.push_front(newTransformation);
    }
}