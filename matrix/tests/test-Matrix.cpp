#include <iostream>
#include <complex>

#include "matrix.hpp"

int main(int argc, char** argv) {

  Matrix<double,4,3> M1{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 2, 3}};
  Matrix<double,3,2> M2{{1, 0}, {0, 1}, {1, 1}};
  Matrix<double,2,2> M3{{1, 0}, {0, 1}};
  Matrix<double,3,1> V{{1}, {1}, {1}};
  Matrix<double,1,3> L{{1, 1, 1}};

  // Test des opérations de base
  std::cout << "M1 = " << std::endl << M1 << std::endl;
  std::cout << "M2 = " << std::endl << M2 << std::endl;
  std::cout << "M1 + M1 = " << std::endl << M1 + M1 << std::endl;
  std::cout << "M1 * M2 = " << std::endl << M1 * M2 << std::endl;

  // // Test des matrices complexes
  Matrix<std::complex<double>,2,2> Mc { {1., {0.,1.}}, {{0.,-1.}, 1.} };
  Matrix<std::complex<double>,2,1> Vc { {{0.,1.}}, {-1.} };
  std::cout << "Mc * Vc = " << std::endl << Mc * Vc << std::endl;
    
  // // Test des spécialisations de la multiplication
  std::cout << "M1 * V = " << std::endl << M1 * V << std::endl;
  std::cout << "L * M2 = " << std::endl << L * M2 << std::endl;
  std::cout << "L * V = " << std::endl << L * V << std::endl;
  std::cout << std::endl;
  
  return 0;
}

