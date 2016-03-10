/* file: main.cpp
 * description: entry point of the program
 */

#include "header/ui.h"

int main() {
  ui::launch();
  return 0;
  matrix<double> a =
    {{0, 5, 3, 0, 0}
    ,{5, 0, 2, 0, 0}
    ,{3, 2, 0, 1, 3}
    ,{0, 0, 1, 0, 4}
    ,{0, 0, 3, 4, 0}};

  auto mst = minimalSpanningTree(a);
  println(mst);

  auto cost = costOfRoute(a, mst);
  println(cost);

  return 0;
}
