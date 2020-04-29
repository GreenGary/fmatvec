using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using FMatVecClr;

namespace EigvalClr
{
    class EigvalClrClass
    {
        static void Main(string[] args)
        {

            LinearAlgebraDouble linalg = new LinearAlgebraDouble();
            double[] squareMatrix = { 2.0, 30.0, 20.0, 4.0  };
            double[] eigValVec = linalg.eigval(2, squareMatrix);
            foreach (double ev in eigValVec)
            {
                Console.WriteLine(ev);
            }
        }
    }
}
