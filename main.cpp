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
//    test1();
    test2();
    return 0;
}

void test1()
{
    /*
        A -- B
        |  /  
         C
        |  \
        D -- E
    */
    const int n = 5;
    graph graph1(n,n);
    double data1[n*n] = {
     /* A B C D E */
        0,1,1,0,0, /*A*/
        1,0,1,0,0, /*B*/
        1,1,0,1,1, /*C*/
        0,0,1,0,1, /*D*/
        0,0,1,1,0, /*E*/ };

    graph1.adj = gsl_matrix_alloc(n,n);
    graph1.adj->data = data1;
    MatrixCompliment( graph1.adj, graph1.comp );
    cout << "adjacency: " << endl; MatrixPrint( graph1.adj );
    MatrixEigen( graph1.adj, graph1.evals );
    IncidenceMat( graph1.adj, graph1.inc );
    DegreeMat( graph1.adj, graph1.deg );
}

void test2()
{
    const int n = 4;
    graph graph1(n,n);
    double data1[n*n] = {
     /* A B C D */
        0,1,0,1, /*A*/
        1,0,1,0, /*B*/
        0,1,0,1, /*C*/
        1,0,1,0, /*D*/};

    graph1.adj = gsl_matrix_alloc(n,n);
    graph1.adj->data = data1;
    MatrixCompliment( graph1.adj, graph1.comp );
    cout << "adjacency: " << endl; MatrixPrint( graph1.adj );
    MatrixEigen( graph1.adj, graph1.evals );
    cout << "adj again: " << endl;
    MatrixPrint( graph1.adj );
    IncidenceMat( graph1.adj, graph1.inc );
    DegreeMat( graph1.adj, graph1.deg );
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
}
