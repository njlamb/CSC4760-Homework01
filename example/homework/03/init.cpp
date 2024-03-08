#include <Kokkos_Core.hpp>
#include <cstdio>
#include <iostream>

using namespace std;
// Declare a 5 ∗ 7 ∗ 12 ∗ n View

int main(int argc, char* argv[]) {
  Kokkos::initialize(argc, argv);
  {
    int n;
    cout << "Enter nth dimension: ";
    cin >> n;
  // Make View
  Kokkos::View<int*[5][7][12]> view("view", n);
  
  // print name
  cout << "View label: " << view.label() << endl;
  // print dimensions
  cout << "View dimensions: " << view.extent(0) << "x" << view.extent(1) << "x" << view.extent(2) << "x" << view.extent(3) << endl;
  }
  Kokkos::finalize();
}
