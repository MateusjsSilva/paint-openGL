/*
 * Computacao Grafica
 * Codigo Exemplo: Paint OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 * Mofificado por: Mateus Silva
 */

#pragma once

#ifndef transformations_h
	#define transformations_h
	
    /*
    * Function: applyTranslation
    * ---------------------------
    * Applies translation transformation to a given vertex.
    */
    void applyTranslation(double* x, double* y, double Tx, double Ty)
    {
        // Translation matrix
        double matrix[] = { 1 , 0 , 0,
                            0 , 1 , 0,
                            Tx, Ty, 1 };

        // Apply transformation
        *x += matrix[6];
        *y += matrix[7];
    }

    /*
     * Function: applyScaling
     * -----------------------
     * Applies scaling transformation to a given vertex.
     */
    void applyScaling(double* x, double* y, double Sx, double Sy)
    {
        // Scaling matrix
        double matrix[] = { Sx, 0 , 0,
                            0 , Sy, 0,
                            0 , 0 , 1 };

        *x *= matrix[0];
        *y *= matrix[4];
    }

    /*
     * Function: applyShearing
     * ------------------------
     * Applies shearing transformation to a given vertex along the specified axis.
     */
    void applyShearing(double* x, double* y, double axis, double value)
    {
        switch ((char)axis)
        {
            case 'x':
            {
                double c = value - 48;

                // Shearing matrix
                double matrix[] = { 1, 0, 0,
                                    c, 1, 0,
                                    0, 0, 1 };

                *x += (*y * matrix[3]);
                *y = *y;
            }
            break;

            case 'y':
            {
                double c = value - 48;

                // Shearing matrix
                double matrix[] = { 1, c, 0,
                                    0, 1, 0,
                                    0, 0, 1 };

                *x = *x;
                *y += (*x * matrix[1]);
            }
            break;
        }
    }

    /*
     * Function: applyReflection
     * --------------------------
     * Applies reflection transformation to a given vertex along the specified axis.
     */
    void applyReflection(double* x, double* y, double axis)
    {
        switch ((char)axis)
        {
            case 'x':
            {
                // Reflection matrix
                double matrix[] = { 1,  0, 0,
                                    0, -1, 0,
                                    0,  0, 1 };

                *x = *x;
                *y *= matrix[4];
            }
            break;

            case 'y':
            {
                // Reflection matrix
                double matrix[] = { -1, 0, 0,
                                     0, 1, 0,
                                     0, 0, 1 };

                *x *= matrix[0];
                *y = *y;
            }
            break;

            case '0':
            {
                // Reflection matrix
                double matrix[] = { -1,  0, 0,
                                     0, -1, 0,
                                     0,  0, 1 };

                *x *= matrix[0];
                *y *= matrix[4];
            }
            break;
        }
    }

    /*
     * Function: applyRotation
     * ------------------------
     * Applies rotation transformation to a given vertex by the specified angle.
     */
    void applyRotation(double* x, double* y, double theta)
    {
        // Rotation matrix
        double matrix[] = { cos(theta), sin(theta), 0,
                           -sin(theta), cos(theta), 0,
                                     0,         0, 1 };

        double tempX = (*x * matrix[0]) + (*y * matrix[3]);
        double tempY = (*x * matrix[1]) + (*y * matrix[4]);

        *x = tempX;
        *y = tempY;
    }

    /*
     * Function: applyTransformation
     * ------------------------------
     * Applies the specified transformation to a vertex based on the transformation type.
     */
    void applyTransformation(double* x, double* y, int centerX, int centerY, forward_list<transformation>::iterator tr)
    {
        switch (tr->type)
        {
            case TRANSLATION:
                applyTranslation(x, y, tr-> vertexF[0], tr-> vertexF[1]);
                break;

            case SCALING:
                applyScaling(x, y, tr-> vertexF[0], tr-> vertexF[1]);
                break;

            case SHEARING:
                applyShearing(x, y, tr-> vertexF[0], tr-> vertexF[1]);
                break;

            case REFLECTION:
                applyReflection(x, y, tr-> vertexF[0]);
                switch ((char)tr-> vertexF[0])
                {
                    case 'x':
                        applyTranslation(x, y, 0, 2 * centerY);
                        break;

                    case 'y':
                        applyTranslation(x, y, 2 * centerX, 0);
                        break;

                    case '0':
                        applyTranslation(x, y, 2 * centerX, 2 * centerY);
                        break;
                }
                break;

            case ROTATION:
                applyTranslation(x, y, -centerX, -centerY);
                applyRotation(x, y, tr -> vertexF[0]);
                applyTranslation(x, y, centerX, centerY);
                break;
        }
    }

#endif /* transformations_h */