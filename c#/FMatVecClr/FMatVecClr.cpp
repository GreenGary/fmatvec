#include "FMatVecClr.h"
#include <iostream>

#include "fmatvec/linear_algebra_double.h"

//using namespace std;
using namespace fmatvec;

namespace FMatVecClr {
    array<double>^ LinearAlgebraDouble::eigval(int size, array<double>^ in)
    {
        // maybe a more elegant way than this
        double* inC{ new double[size] };
        for (int i = 0; i < (size*size); ++i) 
            inC[i] = in[i];

        const SquareMatrix<Ref, double> A(size, inC);
        Vector<Ref, std::complex<double>> eigenValues = fmatvec::eigval(A);
        delete[] inC;

        array< double >^ result = gcnew array< double >(size);
        int cnt = 0;
        for (const std::complex<double> ev : eigenValues)
        {
            std::cout << ev.real() << std::endl;
            result[cnt] = ev.real();
            ++cnt;
        }
        return result;
    }
}

