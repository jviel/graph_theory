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

void doTests( graph & gr ); // receives a graph struct with adjacency matrix initialized

void test1()
{
    /*
        A - B
         \ /  
          C
         / \
        D - E
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
    doTests( graph1 );
}

void test2()
{
    const int n = 4;
    graph graph2(n,n);
    double data2[n*n] = {
     /* A B C D */
        0,1,1,0, /*A*/
        1,0,0,1, /*B*/
        1,0,0,1, /*C*/
        0,1,1,0, /*D*/};

    graph2.adj = gsl_matrix_alloc(n,n);
    graph2.adj->data = data2;
    doTests( graph2 );
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
    graph graph6(n,n);
    double data6[n*n] = {
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
        0,0,0,1,0,0,1,1,0,1,0  };

    graph6.adj = gsl_matrix_alloc(n,n);
    graph6.adj->data = data6;
    doTests( graph6 );
}

void doTests( graph & gr )
{
    MatrixCompliment( gr.adj, gr.comp );
    DegreeMat( gr.adj, gr.deg );
    Laplacian( gr.adj, gr.deg, gr.lap );
    MatrixEigen( gr.lap, gr.evals );

    // save algebraic connectivity to member variable of graph
    GSL_SET_COMPLEX( &gr.algCon, GSL_REAL(gsl_vector_complex_get( gr.evals, 1 )), GSL_IMAG(gsl_vector_complex_get( gr.evals, 1 )));
    
    IncidenceMat( gr.adj, gr.inc );
    EulerCircuit( *gr.deg, gr.inc );
}
