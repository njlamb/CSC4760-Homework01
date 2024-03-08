#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

using namespace std;

// Create a program that does matrix addition between a 2D View and a 1D View with at least one loop of parallelism.
// For a test case:
// a = [130, 137, 115]   b = [221]
//     [224, 158, 187]       [12]
//     [ 54, 211, 120]       [157]
// Extra credit: make a function and check for correct shape/dimensions

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
  // Make View and add values
  Kokkos::View<int**> a("a", 3, 3);
    a(0,0) = 130;
    a(0,1) = 147;
    a(0,2) = 115;
    a(1,0) = 224;
    a(1,1) = 158;
    a(1,2) = 187;
    a(2,0) = 54;
    a(2,1) = 158;
    a(2,2) = 120;
    Kokkos::View<int*> b("b", 3);
    b(0) = 221;
    b(1) = 12;
    b(2) = 157;
    Kokkos::View<int**> soln("soln", 3, 3);
    /*soln = [351, 159, 272]
             [445, 170, 344]
             [275, 170, 277]
    */
  // Do a matrix add
  if (a.extent(1) != b.extent(0)){
      cout << "Matrix dimensions do not match for addition" << endl;
      return 1;
    }
    for(int i=0; i<a.extent(0); i++){
      Kokkos::parallel_for("matrix add", a.extent(1), KOKKOS_LAMBDA(const int& j){
        soln(i,j) = a(i,j) + b(j);
      });
    }
    Kokkos::fence();
  // Output addition 
  for (int i=0; i<a.extent(0); i++){
      for (int j=0; j<a.extent(1); j++){
        cout << a(i,j) << " ";
      }
      cout << endl;
    }
    cout << "   +   " << endl;
    for (int i=0; i<b.extent(0); i++){
      cout << b(i) << " ";
    }
    cout << endl;
    cout << "   =   " << endl;

    for(int i=0; i<soln.extent(0); i++){
      for(int j=0; j<soln.extent(1); j++){
        cout << soln(i,j) << " ";
      }
      cout << endl;
    }
  }
  Kokkos::finalize();
}
