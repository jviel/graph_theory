// graphtheory.h
// written by Johnny Viel 3.6.16
#pragma once
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

struct graph {
    unsigned int       numNodes,
                       numEdges;
    gsl_matrix         *adj,      // adjacency matrix
                       *comp,     // complement matrix
                       *lap,      // Laplacian matrix
                       *deg,      // degree matrix
                       *inc;      // incidence matrix
    gsl_vector_complex *evals;    // eigenvalues of Laplacian matrix
    double             algCon;

    // default constructor
    graph( int nodes = 0, int edges = 0){
        adj = comp = lap = deg = inc = nullptr;
        evals = nullptr;
        numNodes = nodes;
        numEdges = edges;
    }
    // destructor
    ~graph(){
        gsl_matrix_free( adj  );
        gsl_matrix_free( comp );
        gsl_matrix_free( lap  );
        gsl_matrix_free( deg  );
        gsl_matrix_free( inc  );
        gsl_vector_complex_free( evals );
    }
};

void MatrixGet( matrix *& mat )
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
    
    mat = gsl_matrix_alloc( rows, cols );
    double* cur = tempArr;
    for( int i=0; i<rows; i++ ){
        for( int j=0; j<cols; j++ )
            gsl_matrix_set( mat, i, j, *cur++);
    }
}

void MatrixPrint( const matrix * mat )
{
    int cols = mat->size2;
    int rows = mat->size1;
   // cout << endl << "A is a " << rows << " x " << cols << " matrix" << endl << endl << fixed << setprecision(0);
    for( int i=0; i<rows; i++ ){
        cout << "   |";
        for( int j=0; j<cols; j++ )
            cout << setw(3) << gsl_matrix_get( mat, i, j );
        cout << " |";
        cout <<  endl;
    }
}

bool MatrixEigen( const matrix * mat, gsl_vector_complex *& eval )
{
    bool ret = true;
    int sz = mat->size1;
    gsl_eigen_nonsymm_workspace *ws = gsl_eigen_nonsymm_alloc( sz );
//    gsl_matrix_view mv = gsl_matrix_view_array( mat->data, sz, sz );
    eval = gsl_vector_complex_alloc( sz );
    gsl_eigen_nonsymm( &mv.matrix, eval, ws );
    gsl_matrix_complex *evec = gsl_matrix_complex_calloc( sz, sz );
    gsl_eigen_nonsymmv_sort( eval, evec, GSL_EIGEN_SORT_ABS_ASC );
    gsl_complex algCon;
    for( int i=0; i<sz; ){
         if( (i+1) != sz && GSL_REAL(gsl_vector_complex_get( eval, i)) != GSL_REAL(gsl_vector_complex_get( eval, i+1 ))){
            algCon = gsl_vector_complex_get( eval, i+1 );
            i=sz;
         }
         else if( (i+1) == sz && GSL_REAL(gsl_vector_complex_get( eval, i)) == GSL_REAL(gsl_vector_complex_get( eval, i-1 ))){
            GSL_SET_COMPLEX( &algCon,-1,0 );
            i=sz;
         }
         else
            i++;
    }
    cout << endl << "Algebraic connectivity of A: " << GSL_REAL(algCon) << endl;
    if( GSL_REAL(algCon) <= 0 ){
        cout << "A is not connected!" << endl;
        ret = false;
    }
    gsl_eigen_nonsymm_free( ws );
    return ret;
}

void DegreeMat( const matrix * src, matrix *& dest )
{
    double rowsum;
    int rows = src->size1;
    int cols = src->size2;
    dest = gsl_matrix_calloc( rows, cols );
    for( int i=0; i<rows; i++ )
    {
        rowsum = 0;
        for( int j=0; j<cols; j++ )
            rowsum += gsl_matrix_get(src, i, j);
        gsl_matrix_set( dest, i, i, rowsum ); // sets diagonal entry
    }    
}

void Laplacian( const matrix * mat, matrix *& deg, matrix *& lap )
{
    int rows = mat->size1;
    int cols = mat->size2;
    deg = gsl_matrix_calloc( rows, cols );
    lap = gsl_matrix_alloc(  rows, cols );
    DegreeMat( mat, deg );
    gsl_matrix_memcpy( lap, deg ); // copy matrix otherwise degree matrix will be changed

    for( int i=0; i<rows; i++ )
    {
        for( int j=0; j<cols; j++ ){
            if( i != j ){ // sets non-diagonal entries
                if( gsl_matrix_get( mat,i,j) == 0 )
                    gsl_matrix_set( lap,i,j,0 );
                else
                    gsl_matrix_set( lap,i,j, (gsl_matrix_get( mat,i,j) * -1) );
            }
        }
    }    
}

void MatrixCompliment( const matrix * src, matrix *& dest )
{
    int size = src->size1;
    dest = gsl_matrix_calloc( size, size );
    // set univ graph adjacency matrix to all 1s except for main diag.
    for( int i=0; i<size; i++ ){
        for( int j=0; j<size; j++ ){
            if( i != j )
                gsl_matrix_set( dest,i,j,1 );
        }
    }
    gsl_matrix_sub( dest, src );
}

void IncidenceMat( matrix * adjMat, matrix *& incMat )
{
    int rows = adjMat->size1;
    int cols = 0, curCel;
    matrix adjUpperTri = *gsl_matrix_alloc( rows, rows );
    gsl_matrix_memcpy( &adjUpperTri, adjMat );

    // create upper triangular matrix from adjMatrix, and count # edges
    for( int i=0; i<rows; i++ ){
        for( int j=0; j<rows; j++ ){
            if( j > i ){ // upper triangle only
                curCel = gsl_matrix_get( &adjUpperTri, i, j );
                if( curCel != 0 )
                    cols++;
            }
            else
                gsl_matrix_set( &adjUpperTri,i,j,0 );
        }
    }

    incMat = gsl_matrix_calloc( rows, cols );
    int curCol = 0;
    // fill incidence matrix
    for( int i=0; i<rows; i++ ){
        for( int j=i+1; j<rows; j++ ){ // j = i so it doesn't even search lower tri
            if( gsl_matrix_get(&adjUpperTri,i,j) != 0 ){ // edge exists
                gsl_matrix_set( incMat, i, curCol,   1 );
                gsl_matrix_set( incMat, j, curCol++, 1 );
            }
        }
    }

}

bool EulerCircut( matrix & degMat, matrix *& incMat )
{
    int rows = incMat->size1;
    int cols = incMat->size2;
    // Check degree of each node. if any are odd, no circuit can be made
    for( int i=0; i<rows; i++ ){
        if( (int)gsl_matrix_get(&degMat,i,i) % 2 != 0 ){
            cout << endl << "no Euler circuit: one or more nodes has an odd degree" << endl;
            return false;
        }
    }

    // Nodes all of even degree. Attempt traversal
    matrix *incMatCopy = gsl_matrix_alloc( rows, cols );
    matrix *incEmpty   = gsl_matrix_calloc( rows, cols );
    gsl_matrix_memcpy( incMatCopy, incMat );
    int r=0, c=0, rowTries=0;
    cout << endl << "Incidence Matrix: " << endl;
    MatrixPrint( incMatCopy );
    string circuitString = "A"; 
    while( rowTries<=cols )
    {
        rowTries++;
        if( gsl_matrix_get(incMatCopy,r,c) == 1 ){
            rowTries = 0;
            gsl_matrix_set(incMatCopy,r,c,0); // set visited end of edge to 0

            // traverse column, should always find a different 1 in col
            while( gsl_matrix_get(incMatCopy,r,c) != 1 )
                ++r %= rows; // wraps to first row

            gsl_matrix_set(incMatCopy,r,c,0); // set visited end of edge to 0
            circuitString += " -> ";
            circuitString += (char)(r+65);
            cout << endl << circuitString << endl;
            MatrixPrint( incMatCopy );
        }
        ++c %= cols; // wraps to first col
    }
    if( gsl_matrix_equal( incMatCopy, incEmpty )){
        //print path;
        cout << "Euler circuit successful!" << endl;
        cout << circuitString << endl;
    }
    else
        cout << "no Euler circuit exists" << endl;
    gsl_matrix_free( incMatCopy );
    gsl_matrix_free( incEmpty );
}

void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
