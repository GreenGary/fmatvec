#include <complex>


#include "fmatvec/linear_algebra_double.h"
//#include "fmatvec/fmatvec.h"

#include "wrapper.h"


using namespace std;
using namespace fmatvec;


void eigval(std::size_t s, double* in, double* out) {
  const SquareMatrix<Ref, double> A(s, in);
  Vector<Ref, std::complex<double>> eigenValues = eigval(A);
  
  for (const complex<double> ev : eigenValues)
  {
      *out = ev.real();
      out++;
  }

}
