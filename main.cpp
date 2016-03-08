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
    cout << endl << "A is a " << rows << " x " << cols << " matrix" << endl << endl << fixed << setprecision(2);
    for( int i=0; i<rows; i++ ){
        cout << "   |";
        for( int j=0; j<cols; j++ )
            cout << setw(6) << gsl_matrix_get( &mat, i, j );
        cout << " |";
        cout << endl;
    }
}

bool MatrixEigen( matrix *& mat )
{
    int sz = mat->size1;
    gsl_eigen_nonsymm_workspace *ws = gsl_eigen_nonsymm_alloc( sz );
    gsl_matrix_view mv = gsl_matrix_view_array( mat->data, sz, sz );
    gsl_vector_complex *eval = gsl_vector_complex_alloc( sz );
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
    if( GSL_REAL(algCon) > 0 )
        cout << endl << "Algebraic connectivity of A: " << GSL_REAL(algCon) << endl;
    else{
        cout << endl << "A is not connected!" << endl;
        return false;
    }
    gsl_vector_complex_free( eval );
    gsl_eigen_nonsymm_free( ws );
    return true;
}

void DegreeMat( matrix & src, matrix *& dest )
{
    double rowsum;
    int rows = src.size1;
    int cols = src.size2;
    for( int i=0; i<rows; i++ )
    {
        rowsum = 0;
        for( int j=0; j<cols; j++ )
            rowsum += gsl_matrix_get(&src, i, j);
        gsl_matrix_set( dest, i, i, rowsum ); // sets diagonal entry
    }    
}

void Laplacian( matrix &mat, matrix *&lap )
{
    int rows = mat.size1;
    int cols = mat.size2;
    matrix *deg = gsl_matrix_calloc( mat.size1, mat.size2 );
    DegreeMat( mat, deg );
    lap = gsl_matrix_alloc( mat.size1, mat.size2 );
    gsl_matrix_memcpy( lap, deg ); // copy matrix otherwise mat will be changed

    for( int i=0; i<rows; i++ )
    {
        for( int j=0; j<cols; j++ ){
            if( i != j ){ // sets non-diagonal entries
                if( gsl_matrix_get(&mat,i,j) == 0 )
                    gsl_matrix_set( lap,i,j,0 );
                else
                    gsl_matrix_set( lap,i,j, (gsl_matrix_get(&mat,i,j) * -1) );
            }
        }
    }    
    gsl_matrix_free( deg );
}

void IncidenceMat( matrix *& adjMat )
{
}

bool EulerCircut( matrix *& incMat )
{
    int rows = incMat->size1;
    int cols = incMat->size2;
    int deg;
    // Check degree of each node. if any are odd, no circuit can be made
    for( int i=0; i<rows; i++ ){
        deg = 0;
        for( int j=0; j<cols; j++ )
            deg += gsl_matrix_get(incMat,i,j);
        if( (deg % 2) != 0 ){ // odd node degree
            cout << endl << "no Euler circuit: one or more nodes has an odd degree" << endl;
            return false;
        }
    }
    // Nodes all of even degree. Attempt traversal
    matrix *incMatCopy = gsl_matrix_alloc( rows, cols );
    matrix *incEmpty   = gsl_matrix_calloc( rows, cols );
    gsl_matrix_memcpy( incMatCopy, incMat );
//    int maxChecks = (rows*cols) - rows;
    int coord[2] = {0,0};
    string circuit;
    for( int i=0; i<maxChecks; i++ ) // max number of checks
    {
        //traverse row
        while( 
        if( gsl_matrix_get(incMatCopy,coord[0],coord[1]) == 1 ){
            circuit += (coord[0]+1) + " -> ";
            
        }
    }
    if( gsl_matrix_equal( inMatCopy, incEmpty )){
        //print path;
        cout << "an Euler circuit:" << endl;
        cout << circuit << endl;
    }
    else
        cout << "no Euler circuit exists" << endl;
    gsl_matrix_free( incMatCopy );
}

int main()
{
    matrix matA, *lapA, *incA;
    MatrixGet( matA );
    Laplacian( matA, lapA );
    MatrixPrint( *lapA );
    if( !MatrixEigen( lapA ));
        return -1;
    return 0;
}
