/* Copyright (C) 2003-2005  Martin Förg

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Contact:
 *   martin.o.foerg@googlemail.com
 *
 */

#ifndef types_h
#define types_h

#include <complex>
#include <iterator>
#include <boost/spirit/home/qi/nonterminal/nonterminal_fwd.hpp>
#include <boost/spirit/home/karma/nonterminal/nonterminal_fwd.hpp>

#ifndef HAVE_LIBMKL_INTEL_LP64
#ifndef CBLAS_ENUM_DEFINED_H
   #define CBLAS_ENUM_DEFINED_H
   enum CBLAS_ORDER {CblasRowMajor=101, CblasColMajor=102 };
   enum CBLAS_TRANSPOSE {CblasNoTrans=111, CblasTrans=112, CblasConjTrans=113,
                         AtlasConj=114};
   enum CBLAS_UPLO  {CblasUpper=121, CblasLower=122};
   enum CBLAS_DIAG  {CblasNonUnit=131, CblasUnit=132};
   enum CBLAS_SIDE  {CblasLeft=141, CblasRight=142};
#endif
#define CBLAS_INDEX int

#ifndef ATLAS_ENUM_H
   #define ATLAS_ENUM_H
   #define ATLAS_ORDER CBLAS_ORDER
      #define AtlasRowMajor CblasRowMajor
      #define AtlasColMajor CblasColMajor
   #define ATLAS_TRANS CBLAS_TRANSPOSE
      #define AtlasNoTrans CblasNoTrans
      #define AtlasTrans CblasTrans
      #define AtlasConjTrans CblasConjTrans
   #define ATLAS_UPLO CBLAS_UPLO
      #define AtlasUpper CblasUpper
      #define AtlasLower CblasLower
   #define ATLAS_DIAG CBLAS_DIAG
      #define AtlasNonUnit CblasNonUnit
      #define AtlasUnit CblasUnit
   #define ATLAS_SIDE CBLAS_SIDE
      #define AtlasLeft  CblasLeft
      #define AtlasRight CblasRight
#endif
#else
#include "mkl_cblas.h"
#endif

namespace boost {
  namespace spirit {
    template<typename Elem, typename Traits> class basic_istream_iterator;
    typedef basic_istream_iterator<char, std::char_traits<char>> istream_iterator;
  }
}

namespace fmatvec {

  /***** initialization types *****/

  class Noinit { };
  class Init { };
  class Eye { };

  static Noinit NONINIT = Noinit();
  static Init INIT = Init();
  static Eye EYE = Eye();

  /***** matrix/vector (sub) types *****/

  class Ref {
  };

  class Var {
  };

  template<int M> class Fixed {
  };

//  class General {
//  };
//
//  class GeneralBand {
//  };
//
//  class Symmetric {
//  };
//
//  class Diagonal {
//  };
//
//  class Sparse {
//  };
//
//  /*! 
//   *  \brief Basic shape class for matrices.
//   *
//   * Class BasicType is the basic shape type.
//   * */
//  template<class Shape, class Mem>
//  class Type {
//  };

  /*! 
   *  \brief Shape class for general matrices.
   *
   * Class General is a shape class for general matrices.
   * */
  class General {
  };

  /*! 
   *  \brief Shape class for general band matrices.
   *
   * Class GeneralBand is a shape class for general band matrices.
   * */
  class GeneralBand {
  };

  /*! 
   *  \brief Shape class for symmetric matrices.
   *
   * Class Symmetric is a shape class for symmetric matrices.
   * */
  class Symmetric {
  };

  /*! 
   *  \brief Shape class for rotation matrices.
   *
   * Class Rotation is a shape class for rotation matrices.
   * */
  class Rotation {
  };

  /*! 
   *  \brief Shape class for diagonal matrices.
   *
   * Class Diagonal is a shape class for diagonal matrices.
   * */
  class Diagonal {
  };

  /*! 
   *  \brief Shape class for sparse matrices.
   *
   * Class Sparse is a shape class for sparse matrices.
   * */
  class Sparse {
  };

//  template<int M, int N>
//  class GeneralFixed: public BasicType {
//  };
//
//  template<int M>
//  class SymmetricFixed: public BasicType {
//  };
//
//  class GeneralVar: public BasicType {
//  };
//
//  class SymmetricVar: public BasicType {
//  };
//
//  template<int M>
//  class GeneralFixedVar: public BasicType {
//  };
//
//  template<int N>
//  class GeneralVarFixed: public BasicType {
//  };

  template<class AT1, class AT2> struct OperatorResult;
  
  #define FMATVEC_OPERATORRESULT1(AT, ATRes) \
  template<> struct OperatorResult<AT, AT> { typedef ATRes Type; };

  #define FMATVEC_OPERATORRESULT2(AT1, AT2, ATRes) \
  template<> struct OperatorResult<AT1, AT2> { typedef ATRes Type; }; \
  template<> struct OperatorResult<AT2, AT1> { typedef ATRes Type; };
  
  FMATVEC_OPERATORRESULT1(double, double)
  FMATVEC_OPERATORRESULT1(int, int)
  FMATVEC_OPERATORRESULT1(std::complex<double>, std::complex<double>)

  FMATVEC_OPERATORRESULT2(double, std::complex<double>, std::complex<double>)
  FMATVEC_OPERATORRESULT2(int, std::complex<double>, std::complex<double>)
  FMATVEC_OPERATORRESULT2(int, double, double)

  template<class AT>
  boost::spirit::qi::rule<boost::spirit::istream_iterator, AT()>& getBoostSpiritQiRule();

  template<class AT>
  boost::spirit::karma::rule<std::ostream_iterator<char>, AT()>& getBoostSpiritKarmaRule();

}

#endif
