/* file: main.cpp
 * description: entry point of the program
 */

#include "header/ui.h"

int main() {
  auto a = ui::getSquareMatrix("Weighted Adjacency Matrix");

  cout << "Algebraic connectivity = " << algebraicConnectivity(a);

  newline(2);

  matrix<double> anorm(a.size(), vector<double>(a.size(), 0));
  for (unsigned long r = 0; r < a.size(); r++)
    for (unsigned long c = 0; c < a.size(); c++)
      anorm[r][c] = a[r][c] != 0 ? 1 : 0;

  if (algebraicConnectivity(anorm) < 0) {
    cout << "The graph is not connected, ending program";
    newline();
    return 0;
  }

  auto ec = eulerCircuit(a);
  if (ec.size() == 0) {
    cout << "No Euler Circuit exists for this graph";
  } else {
    cout << "Euler Circuit - "
         << "path using index of node as it appears in the adjacency matrix";

    newline();

    for (unsigned long i = 0; i < ec.size(); i++) {
      cout << ec[i];

      if (i < ec.size() - 1)
        cout << " -> ";
    }
  }

  newline(2);

  auto mst = minimalSpanningTree(a);
  if (mst.size() == 0) {
    cout << "No Minimal Spanning Tree exists for this graph";
  } else {
    auto cost = costOfRoute(a, mst);

    cout << "Minimal spanning tree adjacency matrix" << endl;
    println(adjacency(a, mst));
    cout << endl << "Total cost of tree = " << cost << endl;
  }

  return 0;
}
