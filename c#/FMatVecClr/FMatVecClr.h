#pragma once

using namespace System;

namespace FMatVecClr {
	public ref class LinearAlgebraDouble
	{
        public:
            void eigval(int size, double* in, double* eigValVec);
	};
}
