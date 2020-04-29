#pragma once

using namespace System;

namespace FMatVecClr {
	public ref class LinearAlgebraDouble
	{
        public:
            array<double>^ eigval(int size, array<double>^ in);
	};
}
