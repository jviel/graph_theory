// Graph Theory Programming Proficiency
// CS 251 - Winter 2016
// Written by Johnny Viel 3.6.16
#include "graphtheory.h"

int main()
{
//    graph gr;
//    MatrixGet( gr.adj );
//    Laplacian( gr.adj, gr.lap );
//    if( !MatrixEigen( comp ));
//        return -1;
    test4();
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
        0,4,0,0, /*A*/
        4,0,6,1, /*B*/
        0,6,0,5, /*C*/
        0,1,5,0, /*D*/};

    graph2.adj = gsl_matrix_alloc(n,n);
    graph2.adj->data = data2;
    doTests( graph2 );
}

void test3()
{
    const int n = 4;
    graph gr(n,n);
    double data[n*n] = {
     /* A B C D */
        0,1,1,2, /*A*/
        1,0,4,1, /*B*/
        1,4,0,6, /*C*/
        2,1,6,0  /*D*/};

    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    doTests( gr );
}

// TEST HAMILTONIAN CIRCUIT
void test4()
{
    const int n = 4;
    graph gr(n,n);
    double data[n*n] = {

            0,1,1,1,
            1,0,1,1,
            1,1,0,1,
            1,1,1,0 
    };
    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    IncidenceMat( gr.adj, gr.inc );
    HamiltonianCircuit( gr );
}

void test5()
{
}
void test6()
{
    const int n = 11;
    graph gr(n,n);
    double data[n*n] = {
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

    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    MatrixCompliment( gr.adj, gr.comp );
    gsl_matrix_memcpy( gr.adj, gr.comp );
    MatrixPrint( gr.adj );
    doTests( gr );
}
void test9()
{
    const int n = 11;
    graph gr(n,n);
    double data[n*n] = {
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

    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    DegreeMat( gr.adj, gr.deg );
    MatrixPrint( gr.deg );
    // set wt of each edge to the sum of the degrees of the nodes it connects
    for( int i=0; i<gr.numNodes; i++ ){
        for( int j=0; j<gr.numNodes; j++ ){
            if( gsl_matrix_get(gr.adj,i,j) != 0 ){
                int deg1 = gsl_matrix_get( gr.deg,i,i );
                int deg2 = gsl_matrix_get( gr.deg,j,j );
                gsl_matrix_set( gr.adj,i,j, (deg1+deg2) );
            }
        }
    }
    MatrixPrint( gr.adj );
    doTests( gr );
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
    MinSpanTree( gr );
}
