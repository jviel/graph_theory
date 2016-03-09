// Graph Theory Programming Proficiency
// CS 251 - Winter 2016
// Written by Johnny Viel 3.6.16
#include "graphtheory.h"

int main()
{
//    matrix *lapA, *incA, *univ, *comp;
//    MatrixGet( matA );
//    Laplacian( matA.matrix, lapA );
//    MatrixPrint( *lapA );
//    if( !MatrixEigen( comp ));
//        return -1;
    test1();
    return 0;
}

void test1()
{
    /*
        A -- B
        |    |
        |    |
        D -- C
    */
    matrix *comp, *incMat, *degMat;
    gsl_matrix_view A;
    const int n = 4;
    double graph1[n*n] = {
     /* A B C D */
        0,1,1,1, /*A*/
        1,0,1,1, /*B*/
        1,1,0,1, /*C*/
        1,1,1,0, /*D*/
        };
    A = gsl_matrix_view_array( graph1, n, n );
    MatrixCompliment( A.matrix, comp );
    cout << "adjacency: " << endl; MatrixPrint( A.matrix );
    cout << "compliment:" << endl; MatrixPrint( *comp );
//    MatrixEigen( comp );
    IncidenceMat( A.matrix, incMat );
    DegreeMat( A.matrix, degMat );
    if( EulerCircut( *degMat, incMat ) )
        cout << "Euler circuit passed!" << endl;
    else
        cout << "Euler circuit failed!" << endl;
}

void test2()
{
}
void test3()
{
}
void test4()
{
}
void test5()
{
}
void test6()
{
    matrix *comp;
    gsl_matrix_view A;
    const int n = 11;
    double graph6[n*n] = {
        0,1,0,1,1,0,1,0,0,0,0,
        1,0,1,0,0,0,0,1,0,1,0,
        0,1,0,1,0,1,0,0,0,0,0,
        1,0,1,0,0,0,0,0,1,0,1,
        1,0,0,0,0,1,0,0,0,1,0,
        0,0,1,0,1,0,1,1,1,0,0,
        1,0,0,0,0,1,0,0,0,0,1,
        0,1,0,0,0,1,0,0,0,0,1,
        0,0,0,1,0,1,0,0,0,1,0,
        0,1,0,0,1,0,0,0,1,0,1,
        0,0,0,1,0,0,1,1,0,1,0
        };
    A = gsl_matrix_view_array( graph6, n, n );
    MatrixCompliment( A.matrix, comp );
}
