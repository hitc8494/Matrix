#include "matrix.h"

Matrix::Matrix(){
  resize( 0, 0 );
  
  _error = 0;
  _det_up_to_date = 0;
}

Matrix::Matrix( uint rows, uint columns ){
  resize( rows, columns );
  
  _error = 0;
  _det_up_to_date = 0;
}

Matrix::Matrix( vector<vector<double> > input ){
  resize( input.size(), input[0].size() ); //Eeeehhh....
  _data = input;
  _error = 0;
  _det_up_to_date = 0;
}

Matrix::Matrix( vector<double> input ){
  resize( 1, input.size() );
  _data[0] = input;
  _error = 0;
  _det_up_to_date = 0;
}

Matrix::Matrix( const Matrix& m, uint row ){
  resize( 1, m._data[0].size() );
  _data[0] = m._data[row];
  _error = 0;
  _det_up_to_date = 0;
}

Matrix::Matrix( const Matrix& m ){
  *this = m;
}

Matrix::~Matrix(){

}

void Matrix::resize( uint rows, uint cols ){
  _m_in = _n_in = _m_out = _n_out = 0; //Reset all IO iterators.
  _m = rows;
  _n = cols;
  if( _data.size() == 0 || _data[0].size() == 0 ){
    //The compiler should jump out after the first one, evading an error.
    _data.clear();
    _data.assign( rows, vector<double>(cols, 0.0 ) );
    return;
  }
  if( cols > _data[0].size() ){
    for( uint i = 0; i < cols-_data[0].size(); i++ ){
      for( uint j = 0; j < _data.size(); j++ ){
	_data[j].push_back( 0.0 );
      }
    }
  }
  else if ( cols < _data[0].size() ){
    for( uint i = 0; i < _data[0].size()-cols; i++ ){
      for( uint j = 0; j < _data.size(); j++ ){
	_data[j].pop_back();
      }
    }
  }
  if( rows > _data.size() ){
    for( uint i = 0; i < rows-_data.size(); i++ ){
      _data.push_back( vector<double>(cols, 0.0 ) );
    }
  }
  else if( rows < _data.size() ){
    for( uint i = 0; i < _data.size()-rows; i++ ){
      _data.pop_back();
    }
  }
}

bool Matrix::operator == ( const Matrix& rhs ){
  if( _m != rhs._m || _n != rhs._n || _error || rhs._error ){
    return 0;
  }
  bool result = 1;
  for( uint i = 0; i < m(); i++ ){
    for( uint j = 0; j < n(); j++ ){
      if( _data[i][j] != rhs._data[i][j] )
	result = false;
    }
  }
  return result;
}
bool Matrix::operator != ( const Matrix& rhs ){
  return !(*this == rhs);
}

Matrix& Matrix::operator << ( double input ){
  //The IO iterators can be an issue here. Currently, resize() handles that.
  if( _m == 0 || _n == 0 || _error ){
    _print_error( "Attempting to input into an empty matrix." );
    _error = 1;
  }
  _data[_m_in][_n_in] = input;
  _n_in++;
  if( _n_in == _n ){
    _n_in = 0;
    _m_in++;
  }
  if( _m_in == _m ){
    _m_in = 0;
  }
  _det_up_to_date = 0;
  return *this;
}

void Matrix::clear(){
  _m_in = _n_in = _m_out = _n_out = 0; //Reset all IO iterators.
  _error = 0;
  for( uint i = 0; i < _m; i++ ){
    for( uint j = 0; j < _n; j++ ){
      _data[i][j] = 0.0;
    }
  }
  _det_up_to_date = 0;
}

void Matrix::print(){
  for( uint i = 0; i < _m; i++ ){
    for( uint j = 0; j < _n; j++ ){
      cout << _data[i][j] << " ";  
    }
    cout << endl;
  }
}

string Matrix::print_test(){
  std::stringstream ss;
  for( uint i = 0; i < _m; i++ ){
    for( uint j = 0; j < _n; j++ ){
      ss << _data[i][j] << " ";  
    }
  }
  string s = ss.str();
  return s.substr(0, s.size()-1);
}

Matrix Matrix::operator - () const {
  Matrix result = *this;
  return result * -1;
}

Matrix Matrix::addToRow( const Matrix& rhs, const uint row ){
  if( (row > 0 && row <= _m) || rhs._m != 1 ){
    Matrix result = *this;
    for( uint i = 0; i < _n; i++ ){
      result._data[row-1][i] = result._data[row-1][i] + rhs._data[0][i];
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix& Matrix::ADDToRow( const Matrix& rhs, const uint row ){
  if( (row > 0 && row <= _m) || rhs._m != 1 ){
    for( uint i = 0; i < _n; i++ ){
      _data[row-1][i] = _data[row-1][i] + rhs._data[0][i];
    }
  }
  else {
    _error = 1;
  }
  return *this;
}
Matrix Matrix::switchRows( const uint row1, const uint row2 ){
  Matrix result = *this;
  vector<double> temp = result._data[row1-1];
  result._data[row1-1] = result._data[row2-1];
  result._data[row2-1] = temp;
  return result;
}
Matrix& Matrix::SWITCHRows( const uint row1, const uint row2 ){
  vector<double> temp = _data[row1-1];
  _data[row1-1] = _data[row2-1];
  _data[row2-1] = temp;
  return *this;
}
Matrix Matrix::multiplyRow( const double d, const uint row ){
  if( row > 0 && row <= _m ){
    Matrix result = *this;
    for( uint i = 0; i < _n; i++ ){
      result._data[row-1][i] = result._data[row-1][i] * d;
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix& Matrix::MULTIPLYRow( const double d, const uint row ){
  if( row > 0 && row <= _m ){
    for( uint i = 0; i < _n; i++ ){
      _data[row-1][i] = _data[row-1][i] * d;
    }
  }
  else {
    _error = 1;
  }
  return *this;
}

Matrix Matrix::upperTriangular(){
  if( _m == _n ){
    Matrix result = *this;
    //*****For each leading 1...
    for( uint i = 0; i < _m; i++ ){
      //*****Put a leading nonzero in the current row.
      if( result._data[i][i] == 0 ){
	for( uint j = i+1; j < _m; j++ ){
	  if( result._data[j][i] != 0 ){
	    result.SWITCHRows( i+1, j+1 );
	    break;
	  }
	}
      }
      if( result._data[i][i] == 0 ){ //All 0s in the column. Not possible.
	_error = 1;
	return *this;
      }
      //*****Multiply current row by 1/value to give it a leading 1.
      double value = result._data[i][i];
      result.MULTIPLYRow( 1/value, i+1 );
      //*****Clean the column so the leading 1 is the only number in the column.
      Matrix res( result, i );
      for( uint j = 0; j < _m; j++ ){
	if( i != j ){
	  double coeff = result._data[j][i];
	  result.ADDToRow( (res*-coeff), j+1 );
	}
      }
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix& Matrix::UPPERTriangular(){
  *this = upperTriangular();
  return *this;
}

Matrix Matrix::lowerTriangular(){
  return *this;
}
Matrix& Matrix::LOWERTriangular(){
  return *this;
}

Matrix Matrix::ref(){
  return *this;
}
Matrix& Matrix::REF(){
  return *this;
}

Matrix Matrix::submatrix( uint row, uint col, uint rows, uint cols ){
  if( row + rows - 1 <= _m && col + cols - 1 <= _n && rows != 0 && cols != 0 ){
    Matrix result( rows, cols );
    for( uint i = 0; i < rows; i++ ){
      for( uint j = 0; j < cols; j++ ){
	result._data[i][j] = _data[i+row-1][j+col-1];
      }
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix& Matrix::SUBMATRIX( uint row, uint col, uint rows, uint cols ){
  *this = submatrix( row, col, rows, cols );
  return *this;
}

Matrix Matrix::add( const Matrix& rhs ){
  if( _m == rhs._m && _n == rhs._n ){
    Matrix result = *this;
    for( uint i = 0; i < _m; i++ ){
      for( uint j = 0; j < _n; j++ ){
	result._data[i][j] = result._data[i][j] + rhs._data[i][j];
      }
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix Matrix::operator + ( const Matrix& rhs ){
  return add( rhs );
}

Matrix& Matrix::ADD( const Matrix& rhs ){
  *this = *this + rhs;
  _det_up_to_date = 0;
  return *this;
}
Matrix& Matrix::operator += ( const Matrix& rhs ){
  return ADD( rhs );
}

Matrix Matrix::sub( const Matrix& rhs ){
  Matrix result = *this;
  return result.add( -rhs );
}
Matrix Matrix::operator - ( const Matrix& rhs ){
  return sub( rhs );
}

Matrix& Matrix::SUB( const Matrix& rhs ){
  return *this += -rhs;
}
Matrix& Matrix::operator -= ( const Matrix& rhs ){
  return SUB( rhs );
}

Matrix Matrix::mul( const Matrix& rhs ){
  if( _n == rhs._m ){
    Matrix result( _m, rhs._n );
    for( uint i = 0; i < _m; i++ ){
      for( uint j = 0; j < rhs._n; j++ ){
	int sum = 0;
	for( uint k = 0; k < _n; k++ ){
	  sum = sum + ( _data[i][k] * rhs._data[k][j] );
	}
	result._data[i][j] = sum;
      }
    }
    return result;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix Matrix::operator * ( const Matrix& rhs ){
  return mul( rhs );
} 

Matrix Matrix::mul( const double& in ){
  Matrix result = *this;
  for( uint i = 0; i < _m; i++ ){
    for( uint j = 0; j < _n; j++ ){
      result._data[i][j] = result._data[i][j] * in;
    }
  }
  return result;
}
Matrix Matrix::operator * ( const double& in ){
  return mul( in );
}

Matrix& Matrix::MUL( const Matrix& rhs ){
  *this = *this * rhs;
  _det_up_to_date = 0;
  return *this;
}
Matrix& Matrix::operator *= ( const Matrix& rhs ){
  return MUL(rhs);
}

Matrix& Matrix::MUL( const double& in ){
  *this = *this * in;
  _det_up_to_date = 0;
  return *this;
}
Matrix& Matrix::operator *= ( const double& in ){
  return MUL( in );
}

Matrix Matrix::div( const Matrix& rhs ){return *this;}
Matrix Matrix::operator / ( const Matrix& rhs ){return *this;}

Matrix Matrix::div( const double& in ){return *this;}
Matrix Matrix::operator / ( const double& in ){return *this;}

Matrix& Matrix::DIV( const Matrix& rhs ){return *this;}
Matrix& Matrix::operator /= ( const Matrix& rhs ){return *this;}

Matrix& Matrix::DIV( const double& in ){return *this;}
Matrix& Matrix::operator /= ( const double& in ){return *this;}

//If power is 0, what does this return? 
Matrix Matrix::exp( const int power ){
  if( _m == _n && power > 0){
    Matrix result = *this;
    for( int i = 1; i < power; i++ ){
      result *= *this;
    }
    return result;
  }
  else {
    if( power == -1 ){ //Special case: Return the inverse.
      //return ~*this;
      return *this;
    }
    else {
      _error = 1;
      return *this;
    }
  }
}
Matrix Matrix::operator ^ ( const int power ){
  return exp( power );
}

Matrix& Matrix::EXP( const int power ){
  if( _m == _n && power > 0){
    Matrix result = *this;
    for( int i = 1; i < power; i++ ){
      *this *= result;
    }
    return *this;
  }
  else {
    if( power == -1 ){ //Special case: Return the inverse.
      //return !*this;
      return *this;
    }
    else {
      _error = 1;
      return *this;
    }
  }
}
Matrix& Matrix::operator ^= ( const int power ){
  return EXP( power );
}

Matrix Matrix::inv(){
  if( _m == _n ){
    //*****Create a matching identity matrix to mirror our row operations.
    Matrix identity( _m, _n );
    for( uint i = 0; i < _m; i++ ) 
      identity._data[i][i] = 1;
    
    Matrix result = *this;
    //*****For each leading 1...
    for( uint i = 0; i < _m; i++ ){
      //*****Put a leading nonzero in the current row.
      if( result._data[i][i] == 0 ){
	for( uint j = i+1; j < _m; j++ ){
	  if( result._data[j][i] != 0 ){
	    identity.SWITCHRows( i+1, j+1 );
	    result.SWITCHRows( i+1, j+1 );
	    break;
	  }
	}
      }
      if( result._data[i][i] == 0 ){ //All 0s in the column. No inverse possible.
	_error = 1;
	return *this;
      }
      //*****Multiply current row by 1/value to give it a leading 1.
      double value = result._data[i][i];
      result.MULTIPLYRow( 1/value, i+1 );
      identity.MULTIPLYRow( 1/value, i+1 );
      //*****Clean the column so the leading 1 is the only number in the column.
      Matrix res( result, i );
      Matrix ide( identity, i );
      for( uint j = 0; j < _m; j++ ){
	if( i != j ){
	  double coeff = result._data[j][i];
	  result.ADDToRow( (res*-coeff), j+1 );
	  identity.ADDToRow( (ide*-coeff), j+1 );
	}
      }
    }
    return identity;
  }
  else {
    _error = 1;
    return *this;
  }
}
Matrix Matrix::operator ~ (){
  return inv(); 
}

Matrix& Matrix::INV(){
  *this = ~*this;
  return *this;
}
Matrix& Matrix::operator ! (){
  return INV();
}

Matrix Matrix::trans(){
  Matrix result( _n, _m );
  for( uint i = 0; i < _m; i++ ){
    for( uint j = 0; j < _n; j++ ){
      result._data[j][i] = _data[i][j];
    }
  }
  return result;
}
Matrix Matrix::operator + (){
  return trans();
}

Matrix& Matrix::TRANS(){
  *this = +*this;
  return *this;
}
Matrix& Matrix::operator ++ (){
  return TRANS();
}

double Matrix::det(){
  if( _det_up_to_date )
    return _determinant;
  else {
    if( _m != _n ){
      return 0;
    }
    _det_up_to_date = true;
    _determinant = _det( *this );
    return _determinant;
  }
}

double Matrix::_det( Matrix in ){  
  uint rows = in._m;
  uint cols = in._n;
  if( rows == 2 ){
    return in._data[0][0]*in._data[1][1] - in._data[1][0]*in._data[0][1];
  }
  if( rows == 1 ){
    return in._data[0][0];
  }
  double sum = 0.0;
  int sign = 1;
  for( uint iter = 0; iter < in._m; iter++ ){
    Matrix out( rows - 1, cols - 1 );
    for( uint i = 1; i < in._m; i++ ){
      for( uint j = 0; j < in._n; j++ ){
	if( j != iter ){
	  out << in._data[i][j];
	}
      }
    }
    sum = sum + in._data[0][iter] * sign * _det( out );
    sign = sign * -1;
  }
  return sum;
}

void Matrix::backSubstitution(Matrix& b){
  for( uint i = rows()-1; i > -1; i-- ){
    for( uint j = 0; j < rows(); j++ ){
      if( j != i ){
	addToRow( Matrix( _data[i] ) * _data[j][i], j );
	b.addToRow( Matrix( b._data[i] ) * b._data[j][i], j );
      }
    }    
  }
}

void Matrix::forwardSubstitution(Matrix& b){
  for( uint i = rows()-1; i > -1; i++ ){
    for( uint j = 0; j < rows(); j++ ){
      if( j != i ){
	addToRow( Matrix( _data[i] ) * _data[j][i] , j );
	b.addToRow( Matrix( b._data[i] ) * b._data[j][i] , j );
      }
    }    
  }
}
