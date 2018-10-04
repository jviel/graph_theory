## Dependencies
1. g++ compiler
2. gsl, gslcblas libraries for linking

## How to test this tool
This is not the cleanest code, I admit. But it's reasonably easy to test:
1. build with `$ make ./`
2. run with `$ ./main`
3. All graph adjacency matrices are in main.cpp. You can enter any graph data you like
   for the various tests, as long as it follows the same array format. Then recompile.
3. The Hamiltonian circuit was the hardest part to code, but it's also the coolest ;)
