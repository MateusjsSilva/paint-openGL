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
void drawShapes();
void onButtonClick(int mouseX, int mouseY);
void pushShape(int type, bool front);
void pushVertex(int x, int y, bool front);
void pushTransformation(int type, double values[2]);

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
    if (value == -1)
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

            // Clique
            if (state == GLUT_UP)
            {
                mouseClick_x1 = x;
                mouseClick_y1 = height - y - 1;
                printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);

                switch (transformationMode)
                {
                case 0:
                {
                    onButtonClick(mouseClick_x1, mouseClick_y1);
                }
                break;

                case TRANSLATION:
                {
                    if (mouseClick_y1 <= height - 50)
                    {
                        double vetorDeslocamento[2];
                        printf("Digite os valores de translacao para x e y: ");
                        scanf_s("%lf %lf", &vetorDeslocamento[0], &vetorDeslocamento[1]);

                        pushTransformation(TRANSLATION, vetorDeslocamento);
                        printf("ADICIONOU!!!!!!\n");

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
                }
                break;

                case SCALING:
                {
                    if (mouseClick_y1 <= height - 50)
                    {
                        double vetorDeslocamento[2];
                        printf("Digite os valores de escala para x e y: ");
                        scanf_s("%lf %lf", &vetorDeslocamento[0], &vetorDeslocamento[1]);

                        pushTransformation(SCALING, vetorDeslocamento);
                        printf("ADICIONOU!!!!!!\n");

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
                }
                break;

                case SHEARING:
                {
                   /* if (mouseClick_y1 <= height - 50)
                    {
                        char dados[2];
                        printf("Digite o eixo e o valor de cisalhamento (ex: \"x 3\"): ");
                        scanf_s(" %c %c", &dados[0], &dados[1]);

                        double vetorDeslocamento[2];
                        vetorDeslocamento[0] = (double)dados[0];
                        vetorDeslocamento[1] = (double)dados[1];

                        pushTransformacao(CISA, vetorDeslocamento);
                        printf("ADICIONOU!!!!!!\n");

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        verificaCliqueBotao(mouseClick_x1, mouseClick_y1);
                    }
                    */
                }
                break;

                case REFLECTION:
                {
                    /*if (mouseClick_y1 <= height - 50)
                    {
                        char eixo;
                        printf("Digite o eixo de reflexao (\"x\", \"y\" ou \"0\"): ");
                        scanf_s(" %c", &eixo);

                        double vetorDeslocamento[2];
                        vetorDeslocamento[0] = (double)eixo;
                        vetorDeslocamento[1] = 0;

                        pushTransformacao(REFL, vetorDeslocamento);
                        printf("ADICIONOU!!!!!!\n");

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        verificaCliqueBotao(mouseClick_x1, mouseClick_y1);
                    }*/
                }
                break;

                case ROTATION:
                {
                   /* if (mouseClick_y1 <= height - 50)
                    {
                        int grauRotacao;
                        printf("Digite o grau de rotacao: ");
                        scanf_s("%d", &grauRotacao);

                        // Converte graus em radianos
                        // (funcoes trig da math.h trabalham com radianos)
                        double vetorDeslocamento[2];

                        vetorDeslocamento[0] = grauRotacao * M_PI / 180.0;
                        vetorDeslocamento[1] = 0;

                        pushTransformacao(ROTA, vetorDeslocamento);
                        printf("ADICIONOU!!!!!!\n");

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        verificaCliqueBotao(mouseClick_x1, mouseClick_y1);
                    }*/
                }
                break;
                }
            }
            break;

        case LINE:
            if (state == GLUT_UP) {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    // Verifica se o clique nao foi na area de opcoes
                    if (mouseClick_y2 <= height - 50)
                    {
                        click1 = false;
                        contCoordenadas = 0;

                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        pushVertex(mouseClick_x2, mouseClick_y2, 0);

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        // Verifica se o clique foi em algum botao
                        onButtonClick(mouseClick_x2, mouseClick_y2);
                    }

                    printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    // Verifica se o clique nao foi na area de opcoes
                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                    }
                    else
                    {
                        // Verifica se o clique foi em algum botao
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }

                    printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                }
            }
            break;

        case RECTANGLE:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        click1 = false;
                        contCoordenadas = 0;

                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y2, 0);
                        pushVertex(mouseClick_x2, mouseClick_y2, 0);
                        pushVertex(mouseClick_x2, mouseClick_y1, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x2, mouseClick_y2);
                    }

                    printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }

                    printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                }
            }
            break;

        case TRIANGLE:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        if (contCoordenadas == 1)
                        {
                            click1 = true;
                            contCoordenadas++;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                        }
                        else
                        {
                            click1 = false;
                            contCoordenadas = 0;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique 3(%d, %d)\n", mouseClick_x2, mouseClick_y2);

                            // Muda o titulo da janela (alteracoes nao salvas)
                            glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                        }
                    }
                    else
                    {
                        onButtonClick(x, height - y - 1);
                    }
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
                }
            }
            break;

        case POLYGON:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        if (contCoordenadas > 3)
                        {
                            if (mouseClick_x2 == mouseClick_x1 && mouseClick_y2 == mouseClick_y1)
                            {
                                click1 = false;
                                contCoordenadas = 0;
                                pushVertex(mouseClick_x2, mouseClick_y2, 0);

                                // Muda o titulo da janela (alteracoes nao salvas)
                                glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                            }
                            else
                            {
                                contCoordenadas++;
                                pushVertex(mouseClick_x2, mouseClick_y2, 0);
                                printf("Clique %d(%d, %d)\n", contCoordenadas, mouseClick_x2, mouseClick_y2);
                            }
                        }
                        else
                        {
                            contCoordenadas++;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique %d(%d, %d)\n", contCoordenadas, mouseClick_x2, mouseClick_y2);
                        }
                    }
                    else
                    {
                        onButtonClick(x, height - y - 1);
                    }
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
                }
            }
            break;

        case CIRCLE:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        click1 = false;
                        contCoordenadas = 0;

                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        pushVertex(mouseClick_x2, mouseClick_y2, 0);

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x2, mouseClick_y2);
                    }

                    printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }

                    printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                }
            }
            break;

        case PAINT_BUCKET:
            if (state == GLUT_UP)
            {
                if (click1 == false)
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        pushShape(PAINT_BUCKET, 1);
                        pushVertex(mouseClick_x1, mouseClick_y1, 1);

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }

                    printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                }
            }
            break;

        case FILLED_RECT:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        click1 = false;
                        contCoordenadas = 0;

                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y2, 0);
                        pushVertex(mouseClick_x2, mouseClick_y2, 0);
                        pushVertex(mouseClick_x2, mouseClick_y1, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);

                        // Muda o titulo da janela (alteracoes nao salvas)
                        glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                    }
                    else
                    {
                        onButtonClick(mouseClick_x2, mouseClick_y2);
                    }

                    printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }

                    printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                }
            }
            break;

        case FILLED_TRI:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        if (contCoordenadas == 1)
                        {
                            click1 = true;
                            contCoordenadas++;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique 2(%d, %d)\n", mouseClick_x2, mouseClick_y2);
                        }
                        else
                        {
                            click1 = false;
                            contCoordenadas = 0;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique 3(%d, %d)\n", mouseClick_x2, mouseClick_y2);

                            // Muda o titulo da janela (alteracoes nao salvas)
                            glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                        }
                    }
                    else
                    {
                        onButtonClick(x, height - y - 1);
                    }
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
                }
            }
            break;

        case FILLED_POLY:
            if (state == GLUT_UP)
            {
                if (click1 == true)
                {
                    mouseClick_x2 = x;
                    mouseClick_y2 = height - y - 1;

                    if (mouseClick_y2 <= height - 50)
                    {
                        if (contCoordenadas > 3)
                        {
                            if (mouseClick_x2 == mouseClick_x1 && mouseClick_y2 == mouseClick_y1)
                            {
                                click1 = false;
                                contCoordenadas = 0;

                                // Muda o titulo da janela (alteracoes nao salvas)
                                glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
                            }
                            else
                            {
                                contCoordenadas++;
                                pushVertex(mouseClick_x2, mouseClick_y2, 0);
                                printf("Clique %d(%d, %d)\n", contCoordenadas, mouseClick_x2, mouseClick_y2);
                            }
                        }
                        else
                        {
                            contCoordenadas++;
                            pushVertex(mouseClick_x2, mouseClick_y2, 0);
                            printf("Clique %d(%d, %d)\n", contCoordenadas, mouseClick_x2, mouseClick_y2);
                        }
                    }
                    else
                    {
                        onButtonClick(x, height - y - 1);
                    }
                }
                else
                {
                    mouseClick_x1 = x;
                    mouseClick_y1 = height - y - 1;

                    if (mouseClick_y1 <= height - 50)
                    {
                        click1 = true;
                        contCoordenadas++;
                        pushShape(shapeMode, 0);
                        pushVertex(mouseClick_x1, mouseClick_y1, 0);
                        printf("Clique 1(%d, %d)\n", mouseClick_x1, mouseClick_y1);
                    }
                    else
                    {
                        onButtonClick(mouseClick_x1, mouseClick_y1);
                    }
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


/*
 * Controla os desenhos na tela
 */
void display(void)
{
    glMatrixMode(GL_MODELVIEW);     // Muda pro modo de desenho
    glClear(GL_COLOR_BUFFER_BIT);   // Limpa o Buffer de Cores
    glLoadIdentity();               // Carrega a matriz identidade


    // Variaveis que pegam medidas atuais da janela
    float wi = glutGet(GLUT_WINDOW_WIDTH);
    float he = glutGet(GLUT_WINDOW_HEIGHT);


    // Carrega a GUI do app
    drawGUI();

    // Desenha texto com as coordenadas da posicao do mouse
    desenhaTextos();

    // Desenha as formas geometricas da lista
    drawShapes();

    // Troca os buffers
    glutSwapBuffers();
}




/*
 * Funcao que desenha a lista de formas geometricas
 */
void drawShapes()
{
    // Altera a cor das linhas conforme durante o processo de desenho
    if (contCoordenadas == 0)
    {
        // Desenho concluido = usa a cor escolhida
        glColor3f(redColor, greenColor, blueColor);
    }
    else
    {
        // Desenho em progresso
        if (redColor > greenColor && redColor > blueColor)
        {
            glColor3f(1.0, 0.0, 1.0);   // (roxo)
        }
        else
        {
            glColor3f(1.0, 0.0, 0.0);   // (vermelho)
        }
    }


    // Preview da forma a ser desenhada
    if (click1 == true)
    {
        switch (shapeMode)
        {
        case LINE:
        {
            std::vector<double> x = { (double)mouseClick_x1, (double)m_x };
            std::vector<double> y = { (double)mouseClick_y1, (double)m_y };

            // Desenha a preview da linha
            desenhaLinha(x, y);
        }
        break;

        case RECTANGLE:
        {
            double x[] = { (double)mouseClick_x1, (double)mouseClick_x1, (double)m_x, (double)m_x };
            double y[] = { (double)mouseClick_y1, (double)m_y, (double)m_y, (double)mouseClick_y1 };

            // Desenha a preview do retangulo
            desenhaRetangulo(x, y);
        }
        break;

        case TRIANGLE:
        {
            if (contCoordenadas == 1)
            {
                std::vector<double> x = { (double)mouseClick_x1, (double)m_x };
                std::vector<double> y = { (double)mouseClick_y1, (double)m_y };

                desenhaLinha(x, y);
            }
            else if (contCoordenadas == 2)
            {
                double x[] = { (double)mouseClick_x1, (double)mouseClick_x2, (double)m_x };
                double y[] = { (double)mouseClick_y1, (double)mouseClick_y2, (double)m_y };

                // Desenha a preview do triangulo
                desenhaTriangulo(x, y);
            }
        }
        break;

        case POLYGON:
        {
            forward_list<shapes>::iterator f = listShapes.begin();

            // Conta o numero atual de vertices do poligono
            int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(numVertices + 1), y(numVertices + 1);

            x[0] = (double)m_x;
            y[0] = (double)m_y;

            // Salva todas as coordenadas
            int i = 1;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
            {
                x[i] = v->x;
                y[i] = v->y;
            }

            // Muda a cor das linhas ao passar pelo vertice inicial
            if (m_x == x[numVertices] && m_y == y[numVertices])
            {
                if (f->blue > f->red && f->blue > f->green)
                {
                    glColor3f(0.0, 1.0, 0.0);   // (verde)
                }
                else
                {
                    glColor3f(0.0, 0.0, 1.0);   // (azul)
                }
            }

            // Desenha a preview do poligono
            desenhaPoligono(x, y, numVertices + 1);
        }
        break;

        case CIRCLE:
        {
            double x[] = { (double)m_x, (double)mouseClick_x1 };
            double y[] = { (double)m_y, (double)mouseClick_y1 };

            // Desenha a preview da circunferencia
            desenhaCircunferencia(x, y);
        }
        break;

        case FILLED_RECT:
        {
            std::vector<double> x = { (double)mouseClick_x1, (double)mouseClick_x1, (double)m_x, (double)m_x };
            std::vector<double> y = { (double)mouseClick_y1, (double)m_y, (double)m_y, (double)mouseClick_y1 };

            // Desenha a preview do retangulo preenchido
            desenhaRetanguloPreenchido(x, y);
        }
        break;

        case FILLED_TRI:
        {
            if (contCoordenadas == 1)
            {
                std::vector<double> x = { (double)mouseClick_x1, (double)m_x };
                std::vector<double> y = { (double)mouseClick_y1, (double)m_y };

                desenhaLinha(x, y);
            }
            else if (contCoordenadas == 2)
            {
                std::vector<double> x = { (double)mouseClick_x1, (double)mouseClick_x2, (double)m_x };
                std::vector<double> y = { (double)mouseClick_y1, (double)mouseClick_y2, (double)m_y };


                // Desenha a preview do triangulo preenchido
                desenhaTrianguloPreenchido(x, y);
            }
        }
        break;

        case FILLED_POLY:
        {
            forward_list<shapes>::iterator f = listShapes.begin();

            // Conta o numero atual de vertices do poligono
            int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(numVertices + 1), y(numVertices + 1);

            x[0] = (double)m_x;
            y[0] = (double)m_y;

            // Salva todas as coordenadas
            int i = 1;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
            {
                x[i] = v->x;
                y[i] = v->y;
            }

            // Muda a cor das linhas ao passar pelo vertice inicial
            if (m_x == x[numVertices] && m_y == y[numVertices])
            {
                if (f->blue > f->red && f->blue > f->green)
                {
                    glColor3f(0.0, 1.0, 0.0);   // (verde)
                }
                else
                {
                    glColor3f(0.0, 0.0, 1.0);   // (azul)
                }
            }

            if (numVertices == 1)
            {
                desenhaLinha(x, y);
            }
            else
            {
                // Desenha a preview do poligono preenchido
                desenhaPoligonoPreenchido(x, y, numVertices + 1);
            }
        }
        break;
        }
    }


    // Percorre a lista de formas geometricas para desenhar
    for (forward_list<shapes>::iterator f = listShapes.begin(); f != listShapes.end(); f++) {
        glColor3f(f->red, f->green, f->blue);

        switch (f->type) {
        case LINE:
        {
            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(2), y(2);

            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
            {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= 2;
            centroY /= 2;

            // Aplica as transformacoes armazenadas na forma
            for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
            {
                aplicaTransformacao(&x[0], &y[0], centroX, centroY, tr);
                aplicaTransformacao(&x[1], &y[1], centroX, centroY, tr);
            }

            // Desenha a linha
            desenhaLinha(x, y);
        }
        break;

        case RECTANGLE:
        {
            // Listas com os x e y de cada vertice da forma
            double x[4], y[4];
            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= 4;
            centroY /= 4;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < 4; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha o retangulo
            if (i == 4)
            {
                desenhaRetangulo(x, y);
            }
        }
        break;

        case TRIANGLE:
        {
            // Listas com os x e y de cada vertice da forma
            double x[3], y[3];
            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= 3;
            centroY /= 3;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < 3; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha o triangulo
            if (i == 3)
            {
                desenhaTriangulo(x, y);
            }
        }
        break;

        case POLYGON:
        {
            // Conta o numero atual de vertices do poligono
            int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(numVertices), y(numVertices);

            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
            {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= numVertices;
            centroY /= numVertices;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < numVertices; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha o poligono
            desenhaPoligono(x, y, numVertices);
        }
        break;

        case CIRCLE:
        {
            // Listas com os x e y de cada vertice da forma
            int i = 0;
            double x[2], y[2];
            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice da forma
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                x[i] = v->x;
                y[i] = v->y;
            }

            // Identifica o centro do poligono
            centroX = x[0];
            centroY = y[0];

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < 2; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha a circunferencia
            desenhaCircunferencia(x, y);
        }
        break;

        case PAINT_BUCKET:
        {
            // Coordenadas x e y do clique inicial
            double x, y;

            // Salva as coordenadas do vertice do pixel clicado
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++) {
                x = v->x;
                y = v->y;
            }

            // Aplica as transformacoes armazenadas na forma
            for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
            {
                aplicaTransformacao(&x, &y, x, y, tr);
            }

            // Determina a cor do pixel clicado
            float corAntiga[3];
            glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, corAntiga);

            // Determina a cor nova
            float corNova[] = { f->red, f->green, f->blue };

            // Colore a area
            desenhaBalde(x, y, corAntiga, corNova);
        }
        break;

        case FILLED_RECT:
        {
            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(4), y(4);

            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= 4;
            centroY /= 4;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < 4; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha o retangulo preenchido
            if (i == 4)
            {
                desenhaRetanguloPreenchido(x, y);
            }
        }
        break;

        case FILLED_TRI:
        {
            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(3), y(3);
            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++) {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= 3;
            centroY /= 3;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < 3; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            // Desenha o triangulo preenchido
            if (i == 3)
            {
                desenhaTrianguloPreenchido(x, y);
            }
        }
        break;

        case FILLED_POLY:
        {
            // Conta o numero atual de vertices do poligono
            int numVertices = distance(f->vertexs.begin(), f->vertexs.end());

            // Listas com os x e y de cada vertice da forma
            std::vector<double> x(numVertices), y(numVertices);

            int centroX = 0, centroY = 0;

            // Salva as coordenadas de cada vertice
            int i = 0;
            for (forward_list<vertex>::iterator v = f->vertexs.begin(); v != f->vertexs.end(); v++, i++)
            {
                x[i] = v->x;
                y[i] = v->y;

                centroX += (int)x[i];
                centroY += (int)y[i];
            }

            // Identifica o centro do poligono pela media aritmetica dos vertices
            centroX /= numVertices;
            centroY /= numVertices;

            // Aplica as transformacoes armazenadas na forma
            for (int k = 0; k < numVertices; k++)
            {
                for (forward_list<transformation>::iterator tr = f->transformations.begin(); tr != f->transformations.end(); tr++)
                {
                    aplicaTransformacao(&x[k], &y[k], centroX, centroY, tr);
                }
            }

            if (numVertices == 2)
            {
                desenhaLinha(x, y);
            }
            else if (numVertices > 2)
            {
                // Muda a cor do poligono temporariamente ao passar pelo vertice inicial
                if (numVertices >= 4 && m_x == x[numVertices - 1] && m_y == y[numVertices - 1])
                {
                    if (f->blue > f->red && f->blue > f->green)
                    {
                        glColor3f(0.0, 1.0, 0.0);   // (verde)
                    }
                    else
                    {
                        glColor3f(0.0, 0.0, 1.0);   // (azul)
                    }
                }

                // Desenha o poligono preenchido
                desenhaPoligonoPreenchido(x, y, numVertices);
            }
        }
        break;
        }
    }
}


/*
 * Funcao responsavel por tratar interacoes do mouse com os botoes da GUI
 */
void onButtonClick(int mouseX, int mouseY)
{
    /* ====== Clique em um botao de forma ====== */
    bool clicouForma = false;

    // Botao MOU
    if (mouseX > 70 && mouseX < 90)
    {
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != MOUSE)
        {
            printf("CLIQUE!!!!!\n");
            shapeMode = MOUSE;
            clicouForma = true;
        }
    }

    // Botao LIN
    else if (mouseX > 90 && mouseX < 110)
    {
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != LINE)
        {
            printf("LINHA!!!!!\n");
            shapeMode = LINE;
            clicouForma = true;
        }
    }

    else if (mouseX > 110 && mouseX < 130)
    {
        // Botao RET
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != RECTANGLE)
        {
            printf("RETANGULO!!!!!\n");
            shapeMode = RECTANGLE;
            clicouForma = true;
        }

        // Botao RETp
        else if (mouseY >= height - 25 && mouseY <= height - 5 && shapeMode != FILLED_RECT)
        {
            printf("RETANGULO_RASTERIZADO!!!!!\n");
            shapeMode = FILLED_RECT;
            clicouForma = true;
        }
    }

    else if (mouseX > 130 && mouseX < 150)
    {
        // Botao TRI
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != TRIANGLE)
        {
            printf("TRIANGULO!!!!!\n");
            shapeMode = TRIANGLE;
            clicouForma = true;
        }

        // Botao TRIp
        else if (mouseY >= height - 25 && mouseY <= height - 5 && shapeMode != FILLED_TRI)
        {
            printf("TRIANGULO_RASTERIZADO!!!!!\n");
            shapeMode = FILLED_TRI;
            clicouForma = true;
        }
    }

    else if (mouseX > 150 && mouseX < 170)
    {
        // Botao POL
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != POLYGON)
        {
            printf("POLIGONO!!!!!\n");
            shapeMode = POLYGON;
            clicouForma = true;
        }

        // Botao POLp
        else if (mouseY >= height - 25 && mouseY <= height - 5 && shapeMode != FILLED_POLY)
        {
            printf("POLIGONO_RASTERIZADO!!!!!\n");
            shapeMode = FILLED_POLY;
            clicouForma = true;
        }
    }

    // Botao CIR
    else if (mouseX > 170 && mouseX < 190)
    {
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != CIRCLE)
        {
            printf("CIRCULO!!!!!\n");
            shapeMode = CIRCLE;
            clicouForma = true;
        }
    }

    // Botao BAL
    else if (mouseX > 190 && mouseX < 210)
    {
        if (mouseY >= height - 45 && mouseY <= height - 25 && shapeMode != PAINT_BUCKET)
        {
            printf("BALDE!!!!!\n");
            shapeMode = PAINT_BUCKET;
            clicouForma = true;
        }
    }


    /* ====== Clique em um botao de transformacao ====== */
    else if (mouseX > 250 && mouseX < 265)
    {
        if (shapeMode == MOUSE)
        {
            // Botao de translacao
            if (mouseY >= height - 17 && mouseY <= height - 2 && transformationMode != TRANSLATION)
            {
                printf("TRANSLACAO!!!!!\n");
                transformationMode = TRANSLATION;
            }

            // Botao de escala
            else if (mouseY >= height - 32 && mouseY <= height - 17 && transformationMode != SCALING)
            {
                printf("ESCALA!!!!!\n");
                transformationMode = SCALING;
            }

            // Botao de cisalhamento
            else if (mouseY >= height - 47 && mouseY <= height - 32 && transformationMode != SHEARING)
            {
                printf("CISALHAMENTO!!!!!\n");
                transformationMode = SHEARING;
            }
        }
    }

    else if (mouseX > 270 && mouseX < 285)
    {
        if (shapeMode == MOUSE)
        {
            // Botao de reflexao
            if (mouseY >= height - 17 && mouseY <= height - 2 && transformationMode != REFLECTION)
            {
                printf("REFLEXAO!!!!!\n");
                transformationMode = REFLECTION;
            }

            // Botao de rotacao
            else if (mouseY >= height - 32 && mouseY <= height - 17 && transformationMode != ROTATION)
            {
                printf("ROTACAO!!!!!\n");
                transformationMode = ROTATION;
            }
        }
    }


    /* ====== Clique em uma das barras RGB ====== */
    else if (mouseX >= width - 90 && mouseX <= width - 10)
    {
        // Barra de cor R
        if (mouseY > height - 15 && mouseY < height - 5)
        {
            float corEscolhida[3];
            glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

            redColor = corEscolhida[0];
        }

        // Barra de cor G
        else if (mouseY > height - 30 && mouseY < height - 20)
        {
            float corEscolhida[3];
            glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

            greenColor = corEscolhida[1];
        }

        // Barra de cor B
        else if (mouseY >= height - 45 && mouseY <= height - 35)
        {
            float corEscolhida[3];
            glReadPixels(mouseX, mouseY, 1, 1, GL_RGB, GL_FLOAT, corEscolhida);

            blueColor = corEscolhida[2];
        }
    }


    /* ====== Clique nos botoes especiais ====== */
    else if (mouseY >= height - 25 && mouseY <= height - 1)
    {
        // Botao de reset
        if (mouseX > 25 && mouseX < 50)
        {
            // Limpa a lista de formas
            listShapes.clear();
            // Muda o titulo da janela (alteracoes nao salvas)
            glutSetWindowTitle("*img.ppm - Computacao Grafica: Paint");
        }
    }

    // Reinicia variaveis em caso de clique de forma
    if (clicouForma == true)
    {
        contCoordenadas = 0;
        transformationMode = 0;
    }
}

// Function to store a geometric shape in the list of shapes
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

// Function to store a vertex in the shape of the beginning of the list of geometric shapes
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

// Function to store a transformation in each form in the list
static void pushTransformation(int type, double values[2])
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