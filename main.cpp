// Graph Theory Programming Proficiency
// CS 251 - Winter 2016
// Written by Johnny Viel 3.6.16
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_permutation.h>
using namespace std;

typedef gsl_matrix matrix;
const static int MAX_MATRIX_SIZE = 1000;

void MatrixGet( matrix & mat )
{
    int cols, rows=1, numElems=0;
    double tempArr[MAX_MATRIX_SIZE];
    string input;
    istringstream inbuf;

    cout << "Enter a weighted adjacency matrix:" << endl;    
    getline( cin, input );

    // parse first row to determine width of matrix
    inbuf.str( input );
    while( inbuf.peek() != EOF )
        inbuf >> tempArr[numElems++];
    cols = numElems;

    // parse rest of matrix
    while( rows < cols ){
        cin.clear();
        getline( cin, input );
        inbuf.clear();
        inbuf.str( input );
        while( inbuf.peek() != EOF )
            inbuf >> tempArr[numElems++];
        rows++;
    }
    
    mat = *gsl_matrix_alloc( rows, cols );
    double* cur = tempArr;
    for( int i=0; i<rows; i++ ){
        for( int j=0; j<cols; j++ )
            gsl_matrix_set( &mat, i, j, *cur++);
    }
}

void MatrixPrint( const matrix & mat )
{
    int cols = mat.size2;
    int rows = mat.size1;
    cout << " is a " << rows << " x " << cols << " matrix" << endl << endl << fixed << setprecision(2);
    for( int i=0; i<rows; i++ ){
        cout << "   |";
        for( int j=0; j<cols; j++ )
            cout << setw(6) << gsl_matrix_get( &mat, i, j );
        cout << " |";
        cout << endl;
    }
}

void MatrixEigen( matrix & mat )
{
    int sz = mat.size1;
    if( sz != mat.size2 ){
        cout << " does not compute: matrix is not square" << endl;
        return;
    }
    gsl_eigen_nonsymm_workspace *ws = gsl_eigen_nonsymm_alloc( sz );
    gsl_matrix_view mv = gsl_matrix_view_array( mat.data, sz, sz );
    gsl_vector_complex *eval = gsl_vector_complex_alloc( sz );
    gsl_eigen_nonsymm( &mv.matrix, eval, ws );
    gsl_complex eval_i;
    cout << "are" << endl << endl << setprecision(10);
    for( int i=0; i<sz; i++ ){
        eval_i = gsl_vector_complex_get( eval, i );
        cout << "   " << (i+1) << ": " << GSL_REAL(eval_i) << "  +  " << GSL_IMAG(eval_i) << " i" << endl;
    }
    gsl_vector_complex_free( eval );
    gsl_eigen_nonsymm_free( ws );
}

void DegreeMat( matrix *& src, matrix *& dest )
{
    int rowsum;
    int rows = src->size1;
    int cols = src->size2;
    for( int i=0; i<rows; i++ )
    {
        rowsum = 0;
        for( int j=0; j<cols; j++ )
            rowsum += gsl_matrix_get(src, i, j);
        gsl_matrix_set( dest, i, i, rowsum ); // sets diagonal entry
    }    
}

void Laplacian( matrix &mat, matrix *&lap )
{
    int rows = mat.size1;
    int cols = mat.size2;
    matrix *deg = gsl_matrix_calloc( mat.size1, mat.size2 );
    DegreeMat( &mat, deg )
    lap = gsl_matrix_alloc( mat.size1, mat.size2 );
    gsl_matrix_memcpy( lap, deg ); // copy matrix otherwise mat will be changed

    for( int i=0; i<rows; i++ )
    {
        for( int j=0; j<cols; j++ ){
            if( i != j ) // sets non-diagonal entries
                gsl_matrix_set( dest,i,j, (gsl_matrix_get(src,i,j) * -1) );
        }
    }    
}

int main()
{
    matrix matA, *lapA, *incA;
    MatrixGet( matA );
    Laplacian( matA, lapA );
    MatrixPrint( *lapA );
    return 0;
}
