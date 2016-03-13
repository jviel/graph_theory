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
    cout << "test 1" << endl;
    cout << "------------------" << endl;
    test1();
    cout << "test 2" << endl;
    cout << "------------------" << endl;
    test2();
    cout << "test 3" << endl;
    cout << "------------------" << endl;
    test3();
    cout << "test 4" << endl;
    cout << "------------------" << endl;
    test4();
    cout << "test 5" << endl;
    cout << "------------------" << endl;
    test5();
    cout << "test 6" << endl;
    cout << "------------------" << endl;
    test6();
    cout << "test 8" << endl;
    cout << "------------------" << endl;
    test8();
    cout << "test 9" << endl;
    cout << "------------------" << endl;
    test9();
    return 0;
}

void doTests( graph & gr ); // receives a graph struct with adjacency matrix initialized

void test1()
{
    const int n = 8;
    graph graph1(n,n);
    double data1[n*n] = {
        
            0,1,0,0,1,0,0,0,
            1,0,1,1,0,1,1,0,
            0,1,0,0,0,1,0,0,
            0,1,0,0,1,1,0,0,
            1,0,0,1,0,1,0,0,
            0,1,1,1,1,0,0,1,
            0,1,0,0,0,0,0,1,
            0,0,0,0,0,1,1,0
    };
    graph1.adj = gsl_matrix_alloc(n,n);
    graph1.adj->data = data1;
    doTests( graph1 );
}

void test2()
{
    const int n = 12;
    graph graph2(n,n);
    double data2[n*n] = {

        0,1,1,0,1,1,0,0,1,0,1,1,
        1,0,1,0,0,1,0,1,1,1,0,1,
        1,1,0,1,1,0,1,1,1,1,0,1,
        0,0,1,0,1,1,1,0,1,1,1,1,
        1,0,1,1,0,1,0,1,1,0,0,1,
        1,1,0,1,1,0,1,0,1,1,1,1,
        0,0,1,1,0,1,0,1,1,1,1,0,
        0,1,1,0,1,0,1,0,1,1,1,1,
        1,1,1,1,1,1,1,1,0,0,1,0,
        0,1,1,1,0,1,1,1,0,0,1,1,
        1,0,0,1,0,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,1,0,1,0,0
    };
    graph2.adj = gsl_matrix_alloc(n,n);
    graph2.adj->data = data2;
    doTests( graph2 );
}

void test3()
{
    const int n = 10;
    graph gr(n,n);
    double data[n*n] = {

            0,0,1,0,0,0,0,0,0,0,
            0,0,0,0,0,1,1,1,0,0,
            1,0,0,0,0,0,1,0,0,0,
            0,0,0,0,1,0,0,0,1,1,
            0,0,0,1,0,0,1,0,0,1,
            0,1,0,0,0,0,0,1,0,0,
            0,1,1,0,1,0,0,1,0,1,
            0,1,0,0,0,1,1,0,1,1,
            0,0,0,1,0,0,0,1,0,0,
            0,0,0,1,1,0,1,1,0,0
    };
    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    doTests( gr );
}

void test4()
{
    const int n = 10;
    graph gr(n,n);
    double data[n*n] = {

            0,0,0,1,1,1,0,0,1,1,
            0,0,0,0,0,0,1,1,0,1,
            0,0,0,0,0,0,0,0,0,0,
            1,0,0,0,0,0,0,1,0,0,
            1,0,0,0,0,0,1,0,1,0,
            1,0,0,0,0,0,1,0,0,0,
            0,1,0,0,1,1,0,0,1,1,
            0,1,0,1,0,0,0,0,1,0,
            1,0,0,0,1,0,1,1,0,0,
            1,1,0,0,0,0,1,0,0,0
    };
    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    MatrixCompliment( gr.adj, gr.comp );
    gsl_matrix_memcpy( gr.adj, gr.comp );
    doTests( gr );
}

void test5()
{
    const int n = 10;
    graph gr(n,n);
    double data[n*n] = {

            0,1,1,1,0,0,1,0,0,0,
            1,0,0,0,1,0,0,0,0,0,
            1,0,0,0,0,0,0,0,0,0,
            1,0,0,0,1,0,0,0,0,0,
            0,1,0,1,0,0,1,0,1,1,
            0,0,0,0,0,0,0,0,0,0,
            1,0,0,0,1,0,0,0,0,0,
            0,0,0,0,0,0,0,0,0,0,
            0,0,0,0,1,0,0,0,0,0,
            0,0,0,0,1,0,0,0,0,0
    };
    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    MatrixCompliment( gr.adj, gr.comp );
    gsl_matrix_memcpy( gr.adj, gr.comp );
    doTests( gr );
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
    IncidenceMat( gr.adj, gr.inc );
    HamiltonianCircuit( gr.inc, n, n );
    MatrixCompliment( gr.adj, gr.comp );
    gsl_matrix_memcpy( gr.adj, gr.comp );
    doTests( gr );
}

void test7()
{
    // not connected
}

void test8()
{
    const int n = 12;
    graph gr(n,n);
    double data[n*n] = {

        0,1,1,0,1,1,0,0,1,0,1,1,
        1,0,1,0,0,1,0,1,1,1,0,1,
        1,1,0,1,1,0,1,1,1,1,0,1,
        0,0,1,0,1,1,1,0,1,1,1,1,
        1,0,1,1,0,1,0,1,1,0,0,1,
        1,1,0,1,1,0,1,0,1,1,1,1,
        0,0,1,1,0,1,0,1,1,1,1,0,
        0,1,1,0,1,0,1,0,1,1,1,1,
        1,1,1,1,1,1,1,1,0,0,1,0,
        0,1,1,1,0,1,1,1,0,0,1,1,
        1,0,0,1,0,1,1,1,1,1,0,0,
        1,1,1,1,1,1,0,1,0,1,0,0
    };
    gr.adj = gsl_matrix_alloc(n,n);
    gr.adj->data = data;
    DegreeMat( gr.adj, gr.deg );
    DegSumAdj( gr.adj, gr.deg );
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
    DegSumAdj( gr.adj, gr.deg );
    doTests( gr );
}

void test10()
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
    IncidenceMat( gr.adj, gr.inc );
    HamiltonianCircuit( gr.inc, n, n );
    MatrixCompliment( gr.adj, gr.comp );
    gsl_matrix_memcpy( gr.adj, gr.comp );
    doTests( gr );
}

void doTests( graph & gr )
{
    MatrixCompliment( gr.adj, gr.comp );
    DegreeMat( gr.adj, gr.deg );
    Laplacian( gr.adj, gr.deg, gr.lap );
    cout << "laplacian:" << endl;
    MatrixPrint( gr.lap );
    MatrixEigen( gr.lap, gr.evals );

    // save algebraic connectivity to member variable of graph
    GSL_SET_COMPLEX( &gr.algCon, GSL_REAL(gsl_vector_complex_get( gr.evals, 1 )), GSL_IMAG(gsl_vector_complex_get( gr.evals, 1 )));
    
    IncidenceMat( gr.adj, gr.inc );
    EulerCircuit( *gr.deg, gr.inc );
    MinSpanTree( gr );
}
