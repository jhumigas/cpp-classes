#include <iostream>
#include <complex>

#include "Matrix.hpp"

int main(int argc, char** argv) {
  Matrix<int,4,3> M1;
  std::cout << "M1 = " << M1 << std::endl;
  std::cout << "M1(1,2) = " << M1(1,2) << std::endl;

  Matrix<int,4,3> M2 ={{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 2, 3}};
  std::cout << "M2 = " << M2 << std::endl;

  Matrix<int,2,3> M3{{1, 0, 4}, {0, 3, 0}};
  std::cout << "M3(2,3) = " << M3(2,3) << std::endl;
  
  return 0;
}