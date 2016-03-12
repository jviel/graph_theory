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
                       *inc,      // incidence matrix
                       *minSpan;  // minimum spanning tree( adjacency matrix )
    gsl_vector_complex *evals;    // eigenvalues of Laplacian matrix
    gsl_complex        algCon;

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
    matrix matCopy = *gsl_matrix_alloc(sz,sz);
    gsl_matrix_memcpy( &matCopy, mat );
    gsl_eigen_nonsymmv_workspace *ws = gsl_eigen_nonsymmv_alloc( sz );
    gsl_matrix_view mv = gsl_matrix_view_array( matCopy.data, sz, sz );
    eval = gsl_vector_complex_alloc( sz );
    gsl_matrix_complex *evec = gsl_matrix_complex_calloc( sz, sz );
    gsl_eigen_nonsymmv( &mv.matrix, eval, evec, ws );
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
    for( int i=0; i<eval->size; i++ )
        cout << "lambda " << i << ": " << GSL_REAL(gsl_vector_complex_get(eval,i)) << endl;
    if( GSL_REAL(algCon) <= 0 ){
        cout << "A is not connected!" << endl;
        ret = false;
    }
    gsl_eigen_nonsymmv_free( ws );
    return ret;
}

void DegreeMat( const matrix * src, matrix *& dest )
{
    int rowsum;
    int rows = src->size1;
    int cols = src->size2;
    dest = gsl_matrix_calloc( rows, cols );
    for( int i=0; i<rows; i++ )
    {
        rowsum = 0;
        for( int j=0; j<cols; j++ ){
            if( gsl_matrix_get(src,i,j) != 0 )
                rowsum++;
        }
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
    if( dest ){gsl_matrix_free( dest );}

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

bool EulerCircuit( matrix & degMat, matrix *& incMat )
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
    if( gsl_matrix_equal( incMatCopy, incEmpty ) && r == 0 ){ // all edges traversed and back to origin
        cout << "Euler circuit successful!" << endl;
        cout << circuitString << endl;
    }
    else
        cout << "no Euler circuit exists" << endl;
    gsl_matrix_free( incMatCopy );
    gsl_matrix_free( incEmpty );
}

/* This function uses Prim's algorithm for finding the minimum spanning tree */
/* Set A begins with an arbitrary node. Set B is the set of all other nodes in graph */
/* The cheapest path from A to any node in B is added. The new node is removed from set B Now nodes (a,b) are part of set A */
/* repeat until all nodes are part of set A */
void MinSpanTree( graph & gr )
{
    if( GSL_REAL(gr.algCon) <= 0 ){ return; } // if graph not connected

    double totalWeight = 0;
    double cur, cheapest;
    int ij[2];     // [ i, j ] coord of cheapest edge 
    int numVisited = 1, 
        rows = gr.numNodes;
    int visited[rows] = {0}; // hash table. Each cell represents a node. If 1, it has been visited
    visited[0] = 1;
    auto set = [](int* ij, int i, int j ){ ij[0]=i; ij[1]=j; };  // lambda fxn to set ij

    gr.minSpan = gsl_matrix_calloc( rows,rows ); // initializes minSpan adj matrix to all 0s
    matrix adjCpy = *gsl_matrix_alloc( rows,rows );
    gsl_matrix_memcpy( &adjCpy, gr.adj ); // copies adj to adjCpy. Keeps orig adj matrix

    while( numVisited < rows )
    {
        set( ij, 0, 1 ); // resets ij for each traversal
        cheapest = 0;
        // traverse to find cheapest edge
        for(int i=0; i<rows; i++ ){
            if( !visited[i] ){continue;} // skips origin nodes not in set A
            for( int j=i+1; j<rows; j++ ){ // only search upper tri
                cur = gsl_matrix_get( &adjCpy,i,j );
                if( (cur != 0) && (cheapest == 0 || cur < cheapest) ){ // makes ij the cheapest non-zero edge
                    set( ij, i, j );
                    cheapest = cur;
                }
            }
        }
        if( !(visited[ ij[0] ] && visited[ ij[1] ]) ){ // if one or both of the two nodes have not been visited
            if( visited[ ij[0] ] == 0 )
                numVisited++;
            if( visited[ ij[1] ] == 0 )
                numVisited++;
            visited[ ij[0] ] = 1; // sets node as visited
            visited[ ij[1] ] = 1;
            totalWeight += cheapest;
            gsl_matrix_set( gr.minSpan,ij[0],ij[1],cheapest ); // sets both cells of minSpan to wt of corresponding added edge
            gsl_matrix_set( gr.minSpan,ij[1],ij[0],cheapest );
        }
        for( auto item : visited )
            cout << item << ", ";
        cout << " visited: " << numVisited << " total wt: " << totalWeight << endl;
        gsl_matrix_set( &adjCpy, ij[0], ij[1], 0 );      // removes edge from upper tri of adjCpy
   }
   cout << endl << "Minimum Spanning Tree (total edge wt = " << totalWeight << "):" << endl;
   MatrixPrint( gr.minSpan );
}

// test prototypes
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
void test7();
void test8();
void test9();
