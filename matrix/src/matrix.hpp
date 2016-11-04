#pragma once

#include <list>
#include <initializer_list>
#include <iostream>

// Forward declaration of Matrix so it can be used in the overloading operators
template <typename Scalar, int dim1, int dim2> class Matrix;

/**
 * Overloading operator<<
 * Declared outside as a friend function of Matrix
 */
template<typename Scalar, int dim1, int dim2>
std::ostream& operator<<(std::ostream& os, const Matrix<Scalar,dim1,dim2>& M){
    os << "[[";
    int i = 0;
    for(const Scalar *p = M.coefs_; p != M.coefs_ + (dim1 * dim2); ++p, ++i){
      if(i % dim2 == 0 && i != dim1 * dim2 && i!= 0) os<< "],[";
      os << *p ;
      if(i % dim2 < dim2-1) os << ", ";
      //++i;
    }
    os << "]]";
  return os;
  };

/**
 * Addition operation of matrix
 * Overloading operator+
 */
template<typename Scalar, int dim1, int dim2>
Matrix<Scalar, dim1,dim2> operator+(const Matrix<Scalar,dim1,dim2>& A, const Matrix<Scalar,dim1,dim2>& B){
    Matrix<Scalar, dim1, dim2>C;
    int k = 0;
    for(Scalar *p = C.coefs_; p != C.coefs_ + dim1*dim2; ++p){
      *p = A.coefs_[k] + B.coefs_[k];
      ++k;
    }
    return C;
};

/**
 * Matrix Class
 */
template <typename Scalar, int dim1, int dim2>
class Matrix{
  /**
   * A scalar array to store each entry matrix in a one dimensional array
   * It could have been stored in a 2D array, but pointers would have been harder to manage
   */
  Scalar coefs_[dim1*dim2];
  
  /**
   * Operator<< to output the matrix 
   */
  friend std::ostream& operator<< <Scalar, dim1,dim2>(std::ostream& os, const Matrix<Scalar,dim1,dim2>& M);

  /**
   * Operator + to compute matrix addition
   */
  friend Matrix operator+ <Scalar, dim1, dim2>(const Matrix& A, const Matrix& B);

  
public:
  /**
   * Default constructor
   */
  Matrix();
  /**
   * Copy Constructor i.e takes as input a reference to an object of the same type
   */
  Matrix(const Matrix& M);
  /**
   * Custom constructor to enable instantiating a Matrix with a list
   */
  Matrix(const std::initializer_list< std::list<Scalar > >& l);

  /**
   * Coefficient accessor operator
   */ 
  Scalar& operator()(int, int);
  
  /**
   * Compose has to access Matrix members
   * Compose is the class that implements the matrix product
   * This is needed because two matrix of different sizes belong to two different classes
   */
  template <typename Scalar2, int dim12, int dim22, int dim13> friend class Compose;
  
  /**
   * Matrix product method 
   */
  template<int dim3>
  Matrix<Scalar, dim1, dim3> operator*(const Matrix<Scalar, dim2, dim3>&) const;

};

/**
 * Class used to compute a matrix product 
 */
template<typename Scalar, int dim1, int dim2, int dim3>
class Compose{
  public:
    /**
     * Multiply two matrices 
     */
    static Matrix<Scalar, dim1, dim3> multiply(const Matrix<Scalar, dim1, dim2>& A, const Matrix<Scalar, dim2, dim3>& B){
      Matrix<Scalar, dim1, dim3> C;
      Scalar *pr = C.coefs_;
      for (int i = 0; i != dim1; ++i)
      {
        for (int j = 0; j != dim3; ++j, ++pr)
        {
          const Scalar *p1 = A.coefs_ + i * dim2;
          const Scalar *p2 = B.coefs_ + j;
          for (int k = 0; k != dim2; ++k, ++p1, p2 += dim3)
            *pr += *p1 * *p2;
        }
      }
      return C;
    } 
};

template<typename Scalar, int dim1, int dim2>
Matrix<Scalar,dim1,dim2>::Matrix() //: coefs_(new Scalar[dim1*dim2])
{
  for(Scalar *p = coefs_; p != coefs_ + dim1*dim2; ++p) *p = 0;
}

template<typename Scalar, int dim1, int dim2>
Matrix<Scalar,dim1,dim2>::Matrix(const Matrix& M) //: coefs_(M.coefs_)
{
  int i = 0;
  for(Scalar *p = coefs_; p != coefs_ + (dim1 *dim2); ++p){
       *p = M.coefs_[i];
       ++i;   
  }
}

template<typename Scalar, int dim1, int dim2>
Matrix<Scalar, dim1, dim2>::Matrix(const std::initializer_list< std::list<Scalar > >& l)
{
  //coefs_ = new Scalar[l.size() * l.begin().size()];
  int i = 0;
  for (auto it=l.begin(); it != l.end(); ++it){
     for(auto el=it->begin(); el != it->end(); ++el){
       coefs_[i] = *el;
       ++i;
     }
  }
}

template<typename Scalar, int dim1, int dim2>
Scalar& Matrix<Scalar, dim1, dim2>::operator()(int i, int j) {
  return coefs_[i*j];
}

// Operator * for Matrix product
template<typename Scalar, int dim1, int dim2>
template<int dim3>
Matrix<Scalar, dim1, dim3> Matrix<Scalar, dim1, dim2>::operator*(const Matrix<Scalar, dim2, dim3>& other) const {
  return Compose<Scalar, dim1, dim2, dim3>::multiply(*this, other);
}