#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <assert.h>

const int INF_ROOTS = (-10);                       

const int NO_ROOTS = (-100);

const double EPS = 0.0000001;

int SolveSquare(double, double, double, double*, double*);        

void test_square();

void input(double*, double*, double*);

int cmp_with_0(double);

int main()                                                       
{
    double a = 0, b = 0, c = 0;

    test_square();

    input(&a, &b, &c);

    double x1 = 0, x2 = 0;
    int nRoots = SolveSquare(a, b, c, &x1, &x2);

    if (nRoots == 1)
    {
        printf("\n 1 Root\n %lg", x1);
    }
    if (nRoots == 2)
    {
        printf("\n 2 Roots\n %lg, %lg", x1, x2);                  
    }
    if (nRoots == 0)
    {
        printf("\n no Roots\n ");
    }
    if (nRoots == INF_ROOTS)
    {
        printf("\n any Roots\n");
    }
    return 0;
}

//----------------------------------------------------------------
//!  Function solves square equation (a) * x^2 + (b) * x + (c) = 0           // doxyden
//!  @param_in a - coefficient
//!  @param_in b - coefficient
//!  @param_in c - coefficient
//!  @param_out x1 - first root
//!
//!  @param_out x2 - second root
//!  @param_out x - one root (x1 = x2 = x)
//!
//!  @return Number of roots
//!
//!  @note if infinite number of roots returns INF_ROOTS
//----------------------------------------------------------------
int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (cmp_with_0(a) == 0)     // if a != 0
    {
        double disc = b * b - 4 * a * c;

        if (disc > 0)
        {
            *x1 = ((-b) - sqrt (disc)) / (2 * a);
            *x2 = ((-b) + sqrt (disc)) / (2 * a);
            return 2;
        }
        else
        {
            if (cmp_with_0(disc) != 0)
            {
                if (cmp_with_0(c) != 0)
                {
                    *x1 = *x2 = 0;
                    return 1;
                }

                else
                {
                    *x1 = *x2 = (-b) / (2 * a);
                    return 1;
                }
            }
            else
            {
                *x1 = *x2 = NO_ROOTS;
                return 0;
            }
        }

    }
    else
    {
        if ((cmp_with_0(b) == 0) && (cmp_with_0(c) == 0))
        {
            *x1 = *x2 = -(c / b);
            return 1;
        }
        if (cmp_with_0(b) != 0)
        {
            if (cmp_with_0(c) != 0)
            {
                *x1 = *x2 = INF_ROOTS;
                return INF_ROOTS;
            }
            else
            {
                *x1 = *x2 = NO_ROOTS;
                return 0;
            }
        }
        if (cmp_with_0(c) != 0)
        {
            *x1 = *x2 = 0;
            return 1;
        }
    }
 }

void test_square()                                             // Unittests for int SolveSquare()
{
    double A[10] = {1, 1, 1, 0, 1, 1, 1, 1, 0, 0};
    double B[10] = {0, -7, -8, 0, 0, 1, 1, 0, 1, 0};
    double C[10] = {-4, 12, 15, 0, 0, 0, 1, 1, 1, 1};

    double X1[10] = {-2, 3, 3, INF_ROOTS, 0, -1, NO_ROOTS, NO_ROOTS, -1, NO_ROOTS};
    double X2[10] = {2, 4, 5, INF_ROOTS, 0, 0, NO_ROOTS, NO_ROOTS, -1, NO_ROOTS};

    double x1 = 0;
    double x2 = 0;

    int i;

    for (i = 0; i < 10; i++)
    {
        SolveSquare(A[i], B[i], C[i], &x1, &x2);

        if ((x1 == X1[i]) && (x2 == X2[i]))
        {
            if ((X1[i] == INF_ROOTS) && (X2[i] == INF_ROOTS))
            {
                printf("TEST.%d OK Any roots\n\n", (i + 1));
            }
            if ((cmp_with_0(X1[i]) != 0) && (cmp_with_0(X2[i]) != 0))
            {
                printf("TEST.%d OK x = %lg\n\n", (i + 1), x1);
            }
            if ((X1[i] != INF_ROOTS) && (X2[i] != INF_ROOTS) && (cmp_with_0(X1[i]) == 0)
               && (X1[i] != NO_ROOTS))
            {
                printf("TEST.%d OK 2 roots x1 = %lg, x2 = %lg; a = %lg, b = %lg, c = %lg\n\n",
                (i + 1), X1[i], X2[i], A[i], B[i], C[i]);
            }
            if ((X1[i] == NO_ROOTS) && (X2[i] == NO_ROOTS))
            {
                printf("TEST.%d OK NO ROOTS a = %lg, b = %lg, c = %lg\n\n",
                (i + 1), A[i], B[i], C[i]);
            }
        }

        if ((x1 != X1[i]) || (x2 != X2[i]))
        {
            printf("TEST.%d BAD\n", (i + 1));
            printf("ERROR: WRONG ROOTS %lg, %lg\n", x1, x2);
            printf("EXPECTED: %lg, %lg \n\n", X1[i], X2[i]);
        }

    }
}

void input(double* a, double* b, double* c)                   
{
    printf(" a = ");
    scanf("%lg", a);

    printf(" b = ");
    scanf("%lg", b);

    printf(" c = ");
    scanf("%lg", c);

    printf(" (%lg) * x^2 + (%lg) * x + (%lg) = 0", *a, *b, *c);
}

int cmp_with_0(double a)
{
    return (fabs(a - 0) < EPS);   
}                                 
                                
