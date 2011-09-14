#include "matrix.h"

int spaces = 0;
int passed = 0;
int failed = 0;

void header( string message ){
  string s; s.assign( spaces, ' ' );
  cout << s << message << endl;
  spaces = spaces + 3;
}

void footer(){ spaces = spaces - 3; }

void test( bool pass, std::string message ){
  string s; s.assign( spaces, ' ' );
  cout << s;
  if( pass ){
    cout << "Passed - "; passed++;
  }
  else {
    cout << "FAILED - "; failed++;
  }
  cout << message << endl;
}

int main(){
  header( "Basic assignment" );{
    header( "Constructors" );{
      Matrix a;
      test( a.m() == 0 && a.n() == 0, "Test the base constructor." );
      Matrix b( 1, 1 );
      test( b.m() == 1 && b.n() == 1, "Test the common constructor." );
      Matrix c(b);
      test( c.m() == 1 && c.n() == 1, "Test the copy constructor." );
    }
    footer();
    header( "Input" );{
      Matrix a( 4, 4 );
      test( a.print_test() == "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0", "Empty matrix." );
      Matrix b;
      { Matrix c( 4, 4 );
	c <<  1 <<  2 <<  3 <<  4
	  <<  5 <<  6 <<  7 <<  8 
	  <<  9 << 10 << 11 << 12
	  << 13 << 14 << 15 << 16;
	test( c.print_test() == "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16", "Basic 4x4." );
	b = c;
      }
      test( b.print_test() == "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16", "Op = test" );
    }
    footer();
    header( "Resize" );{
      Matrix a( 2, 2 );
      a << 1 << 2 
	<< 3 << 4;
      a.resize( 2, 2 );
      test( a.print_test() == "1 2 3 4", "Same size resize." );
      a.resize( 3, 3 );
      test( a.print_test() == "1 2 0 3 4 0 0 0 0", "Scaled up resize." );
      a.print();
      a.resize( 1, 1 );
      test( a.print_test() == "1", "Scaled down resize." );
      a.resize( 2, 2 );
    }
    footer();
    header( "Submatrix" );{
      Matrix a( 3, 3 );
      a << 1 << 2 << 3
	<< 4 << 5 << 6 
	<< 7 << 8 << 9;
      Matrix b = a.submatrix(1,1,2,2);
      test( b.print_test() == "1 2 4 5", "Basic submatrix" );
      Matrix c = a.submatrix(2,2,2,2);
      test( c.print_test() == "5 6 8 9", "Basic submatrix #2" );
      test( a.SUBMATRIX(1,1,2,3).print_test() == "1 2 3 4 5 6", "Immediate submatrix" );
      test( a.SUBMATRIX(1,1,2,1).print_test() == "1 4", "Immediate submatrix #2" );
    }
    footer();
  }
  footer();
  header( "Mathematical functions" );{
    header( "Addition" );{
      Matrix a(2, 2);
      a << 1 << 2
	<< 3 << 4;
      Matrix b(2, 2);
      b << 4 << 3
	<< 2 << 1;
      Matrix c = b + a;
      test( c.print_test() == "5 5 5 5", "Basic addition" );
      c = a + b;
      test( c.print_test() == "5 5 5 5", "Addition is transitive" );
      b.resize(1, 1);
      c = b + a;
      test( c.error() == true, "Unable to add unlike matrices" );
      b.resize(2, 2);
      c = a + b;
      test( c.print_test() == "5 2 3 4", "Basic addition after a resize" );
      test( a.print_test() == "1 2 3 4", "  A is unchanged by addition" );
      a += b;
      test( a.print_test() == "5 2 3 4", "Immediate addition." );
    }
    footer();
    header( "Subtraction" );{
      Matrix a( 2, 2 );
      a << 1 << 2 << 3 << 4;
      Matrix b( 2, 2 );
      b << 1 << 1 << 1 << 1;
      Matrix c( 1, 1 );
      test( (a - b).print_test() == "0 1 2 3", "Basic subtraction" );
      test( (b - a).print_test() != "0 1 2 3", "Subtraction is NOT transitive" );
      c = b + c;
      test( c.error() == true, "Unable to subtract unlike matrices" );
      a -= b;
      test( a.print_test() == "0 1 2 3", "Immediate subtraction." );
    }
    footer();
    header( "Multiplication" );{
      Matrix a( 2, 3 );
      a <<  2 <<  4 <<  3 
	<< -2 <<  3 <<  1;
      Matrix b( 3, 4 );
      b <<  2 <<  4 <<  5 <<  6 
	<< -2 <<  1 << -2 <<  1 
	<< -9 << -9 << -9 <<  1;
      Matrix c( 2, 2 );
      c << 1 << 2
	<< 4 << 1;
      Matrix d( 2, 2 );
      d << 3 << 1
	<< 3 << 0;
      test( (a * b).print_test()=="-31 -15 -25 19 -19 -14 -25 -8","Basic multiplication");
      test( (b*a).error() == true, "Can NOT multiply improper matrices" );
      test( (c*d).print_test() != (d*c).print_test(), "Multiplication is NOT transitive");
      test( (a * 2).print_test() == "4 8 6 -4 6 2", "Basic scalar multiplication" );
      test( a.print_test() == "2 4 3 -2 3 1", "  A is unchanged by multiplication" );
      c *= a;
      test( c.print_test() == "-2 10 5 6 19 13","Immediate multiplication");
      c *= 2;
      test( c.print_test() == "-4 20 10 12 38 26", "Immediate scalar multiplication" );
    }
    footer();
    header( "Division" );{
      
      
    }
    footer();
    header( "Exponent" );{
      
    }
    footer();
    header( "Transpose" );{
      Matrix a( 2, 3 );
      a << 4 << 3 << 2
	<< 1 << 5 << 6;
      Matrix b = +a;
      test( a.m() == b.n() && a.n() == b.m(), "Basic transpose" );
      ++a;
      test( a == b, "Immediate transpose" );
    }
    footer();
    header( "Inverse" );{
      Matrix a( 3,3 );
      a << 0 << 1 << 2 
	<< 1 << 0 << 3
	<< 4 << -3 << 8;
      Matrix b = ~a;
      test( b.print_test() == "-4.5 7 -1.5 -2 4 -1 1.5 -2 0.5", "Inverse" );
      test( (!a).print_test() == "-4.5 7 -1.5 -2 4 -1 1.5 -2 0.5", "Immediate inverse" );
    }
    footer();
    header( "Determinant" );{
      Matrix c(1,1);
      c << 1;
      test( c.det() == 1, "Determinant test 1x1" );
      Matrix b(2,2);
      b << 3 << 4 
	<< 1 << 2;
      test( b.det() == 2, "Determinant test 2x2" );
      Matrix a(3,3);
      a << 1 << 2 << 0
	<< 4 << 5 << 6 
	<< 7 << 8 << 9;
      test( a.det() == 9, "Determinant test 3x3" );
      Matrix d(6,6);
      d << 0 << 9 << 3 << 4 << 1 << 2
	<< 0 << 2 << 1 << 5 << 5 << 2
	<< 3 << 4 << 1 << 1 << 7 << 3
	<< 9 << 4 << 2 << 4 << 7 << 6
	<< 6 << 1 << 8 << 2 << 7 << 3
	<< 3 << 7 << 2 << 7 << 3 << 4;
      test( d.det() == 330, "Determinant test 6x6" );
    }
    footer();
  }
  footer();
  
  cout << endl
       << "Tests passed: " << passed << endl
       << "Tests failed: " << failed << endl;
  return 0;
}

