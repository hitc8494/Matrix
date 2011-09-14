#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <sstream>
#include <thread>
#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::setw;
using std::vector;

class Matrix {
 public:
  Matrix();
  Matrix( uint rows, uint columns ); //Define an m by n Matrix.
  Matrix( vector<vector<double> > input );
  Matrix( vector<double> input );
  Matrix( const Matrix& m, uint row ); //1xn matrix ONLY.
  Matrix( const Matrix& m );
  ~Matrix();
  
  //*****Bookkeeping functions*****
  uint m(){ return _m; }
  uint n(){ return _n; }
  uint rows(){ return _m; }
  uint cols(){ return _n; }
  
  void resize( uint rows, uint cols );
  
  char type(){ return _type; }
  void type( char type ){ _type = type; }
  
  bool good(){ return !_error; }
  bool error(){ return _error; }
  
  bool error_reporting(){ return _error_verbose; }
  void error_reporting( bool b ){ _error_verbose = b; }
  
  bool operator == ( const Matrix& rhs );
  bool operator != ( const Matrix& rhs );
    
  Matrix& operator << ( double input );
  Matrix& operator >> ( int& i );
  Matrix& operator >> ( float& f );
  Matrix& operator >> ( double& d );
  
  Matrix& copy();
  void clear();
  void print();
  string print_test();
  
  //*****Mathematical functions*****
  Matrix operator - () const;
  
  Matrix addToRow( const Matrix& rhs, const uint row );
  Matrix switchRows( const uint row1, const uint row2 );
  Matrix multiplyRow( const double d, const uint row );
  Matrix& ADDToRow( const Matrix& rhs, const uint row );
  Matrix& SWITCHRows( const uint row1, const uint row2 );
  Matrix& MULTIPLYRow( const double d, const uint row );
  
  Matrix upperTriangular();
  Matrix lowerTriangular();
  Matrix& UPPERTriangular();
  Matrix& LOWERTriangular();
  
  void backSubstitution(Matrix& b);
  void forwardSubstitution(Matrix& b);

  Matrix ref(); //Reduced echelon form
  Matrix& REF();
  
  Matrix submatrix( uint row, uint col, uint rows, uint cols );
  Matrix& SUBMATRIX( uint row, uint col, uint rows, uint cols );

  Matrix add( const Matrix& rhs );        // Addition
  Matrix operator + ( const Matrix& rhs );//
  Matrix& ADD( const Matrix& rhs );         // Immediate addition
  Matrix& operator += ( const Matrix& rhs );//
  Matrix sub( const Matrix& rhs );        // Subtraction
  Matrix operator - ( const Matrix& rhs );//  
  Matrix& SUB( const Matrix& rhs );         // Immediate subtraction
  Matrix& operator -= ( const Matrix& rhs );//       
  Matrix mul( const Matrix& rhs );        // Multiplication
  Matrix operator * ( const Matrix& rhs );//       
  Matrix mul( const double& in );        // Scalar multiplication
  Matrix operator * ( const double& in );//       
  Matrix& MUL( const Matrix& rhs );         // Immediate multiplication
  Matrix& operator *= ( const Matrix& rhs );//
  Matrix& MUL( const double& in );         // Immediate scalar multiplication
  Matrix& operator *= ( const double& in );//
  Matrix div( const Matrix& rhs );        // Division
  Matrix operator / ( const Matrix& rhs );//       
  Matrix div( const double& in );        // Scalar division
  Matrix operator / ( const double& in );//  
  Matrix& DIV( const Matrix& rhs );         // Immediate division
  Matrix& operator /= ( const Matrix& rhs );//
  Matrix& DIV( const double& in );         // Immediate scalar division
  Matrix& operator /= ( const double& in );//
  
  Matrix exp( const int power );        //Exponent (float exponents allowed?)
  Matrix operator ^ ( const int power );//
  Matrix& EXP( const int power );         //Immediate exponent
  Matrix& operator ^= ( const int power );//

  Matrix inv();        //Inverse
  Matrix operator ~ ();//
  Matrix& INV();        //Immediate inverse.
  Matrix& operator ! ();//
  
  Matrix trans();      //Transpose
  Matrix operator + ();//
  Matrix& TRANS();       //Immediate transpose.
  Matrix& operator ++ ();//
  
  
  double det();
  //******************************** 
 private:
  void _print_error( string s ){if(_error_verbose)cout<<s<<endl;}
  double _det( Matrix in ); //Auxiliary recursive function to calculate determinant.
  vector<vector<double> > _data;
  
  uint _m; //Rows in the matrix. Starts at 1.
  uint _n;
  
  uint _m_in; //Iterators for m and n ( Operator << )
  uint _n_in; //Starts at 0.
  uint _m_out; //Iterators for m and n ( Operator >> )
  uint _n_out; //Starts at 0.
  
  char _type;

  bool _error;
  bool _error_verbose;
  
  int _determinant;
  bool _det_up_to_date;
};

#endif
