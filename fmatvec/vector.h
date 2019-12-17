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

#ifndef vector_h
#define vector_h

#include "general_matrix.h"
#include <vector>
#include <cstring>

namespace fmatvec {

  /*! 
   *  \brief This is a vector class of general shape in dense storage format.
   *
   * Template class Vector of type General<Ref,Ref>, id. shape is general
   * and storage form is dense. The template parameter AT defines the
   * atomic type of the vector. Valid types are int, float,
   * double, complex<float> and complex<double> 
   * */
  template <class AT> class Vector<Ref,AT> : public Matrix<General,Ref,Ref,AT> {
    using Matrix<General,Ref,Ref,AT>::m;
    using Matrix<General,Ref,Ref,AT>::n;
    using Matrix<General,Ref,Ref,AT>::lda;
    using Matrix<General,Ref,Ref,AT>::ele;
    using Matrix<General,Ref,Ref,AT>::tp;
    using Matrix<General,Ref,Ref,AT>::memory;
    using Matrix<General,Ref,Ref,AT>::elePtr;

    public:

    typedef AT* iterator;
    typedef const AT* const_iterator;

    typedef AT value_type;

    /// @cond NO_SHOW

    template <class T> friend RowVector<Ref,T> trans(const Vector<Ref,T> &x); 
    template <class T> friend Vector<Ref,T> trans(const RowVector<Ref,T> &x);     
    
    friend class RowVector<Ref,AT>;

    friend Vector<Ref,AT> Matrix<General,Ref,Ref,AT>::col(int i);
    friend const Vector<Ref,AT> Matrix<General,Ref,Ref,AT>::col(int i) const;

    protected:

    inline Vector<Ref,AT>& copy(const Vector<Ref,AT> &x);
    template<class Row> inline Vector<Ref,AT>& copy(const Vector<Row,AT> &x);

    AT* elePtr(int i) {
      return tp ? ele+lda*i : ele+i;
    };

    const AT* elePtr(int i) const {
      return tp ? ele+lda*i : ele+i;
    };

    explicit Vector(int n_, int lda_, bool tp, Memory<AT> memory, const AT* ele_) : Matrix<General,Ref,Ref,AT>(n_, 1, lda_, tp, memory, ele_) { }

    /// @endcond
    
    public:

      /*! \brief Standard constructor
       *
       * Constructs a vector with no size. 
       * */
      explicit Vector() : Matrix<General,Ref,Ref,AT>() { n=1; }

      explicit Vector(int m, Noinit ini) : Matrix<General,Ref,Ref,AT>(m,1,ini) { } 
      explicit Vector(int m, Init ini=INIT, const AT &a=AT()) : Matrix<General,Ref,Ref,AT>(m,1,ini,a) { } 

      /*! \brief Copy Constructor
       *
       * Constructs a copy of the vector \em x.
       * \param x The vector that will be copied.
       * */
      Vector(const Vector<Ref,AT> &x) : Matrix<General,Ref,Ref,AT>(x) {
      }

      template<class Row>
      Vector(const Vector<Row,AT> &x) : Matrix<General,Ref,Ref,AT>(x) {
      }

      template<class Type, class Row, class Col>
      explicit Vector(const Matrix<Type,Row,Col,AT> &x) : Matrix<General,Ref,Ref,AT>(x) {
	assert(x.cols()==1);
      }

      /*! \brief Regular Constructor
       *
       * Constructs a vector of size m with the pyhsical memory given by \em ele_;
       * \param m The size.
       * \param ele The physical memory the vector will point to.
       * */
      explicit Vector(int m, AT* ele) : Matrix<General,Ref,Ref,AT>(m,1,ele) { 
      }

      /*! \brief String Constructor. 
       *
       * Constructs and initializes a vector with a string in a matlab-like
       * notation. The entries are seperated by semicolons.
       * For example
       * \code 
       * Vector<double> x("[3;1;2]");
       * \endcode
       * constructs the vector
       * \f[ x=\begin{pmatrix}3\\ 1 \\ 2\end{pmatrix}  \f]
       * \param str The string the vector will be initialized with. 
       * */
      Vector(const char *str) : Matrix<General,Ref,Ref,AT>(str) {
	assert(n==1);
      }

      Vector<Ref,AT>& resize(int m, Noinit) {
        Matrix<General,Ref,Ref,AT>::resize(m,1,Noinit());
        return *this;
      }

      Vector<Ref,AT>& resize(int m, Init ini=INIT, const AT &a=AT()) {
        Matrix<General,Ref,Ref,AT>::resize(m,1,ini,a);
        return *this;
      }

      /*! \brief Assignment operator
       *
       * Copies the vector given by \em x.
       * \param x The vector to be assigned.
       * \return A reference to the calling vector.
       * */
      inline Vector<Ref,AT>& operator=(const Vector<Ref,AT> &x) {
        assert(m == x.size());
        return copy(x);
      }

      /*! \brief Assignment operator
       *
       * Copies the vector given by \em x.
       * \param x The vector to be assigned.
       * \return A reference to the calling vector.
       * */
      template <class Row>
      inline Vector<Ref,AT>& operator=(const Vector<Row,AT> &x) {
        assert(m == x.size());
        return copy(x);
      }

      /*! \brief Reference operator
       *
       * References the vector given by \em x.
       * \param x The vector to be referenced.
       * \return A reference to the calling vector.
       * */
      inline Vector<Ref,AT>& operator&=(const Vector<Ref,AT> &x) {
        m = x.m; 
        n = 1;
        memory = x.memory;
        ele = x.ele;
        lda = x.lda;
        tp = x.tp; 
        return *this;
      }

      /*! \brief Reference operator
       *
       * References the matrix given by \em x.
       * \param x The matrix to be referenced.
       * \return A reference to the calling vector.
       * */
      inline Vector<Ref,AT>& operator&=(const Matrix<General,Ref,Ref,AT> &A) {
        assert(A.cols() == 1);
        m = A.rows(); 
        n = 1;
        memory = A.memory;
        ele = A.ele;
        lda = A.lda;
        tp = A.tp; 
        return *this;
      }

      /*! \brief Vector assignment
       *
       * Copies the vector given by \em x.
       * \param x The vector to be copied.
       * \return A reference to the calling vector.
       * */
      template <class Row>
      inline Vector<Ref,AT>& assign(const Vector<Row,AT> &x) {
        resize(x.size(),NONINIT);
        return copy(x);
      }

      /*! \brief Vector reassignment
       *
       * Copies the vector given by \em x.
       * \param x The vector to be copied.
       * \return A reference to the calling vector.
       * */
      template <class Row>
      inline Vector<Ref,AT>& reassign(const Vector<Row,AT> &x) {
        if(m!=x.size()) resize(x.size(),NONINIT);
        return copy(x);
      }

      template <class AT2>
      operator Vector<Ref,AT2>() const {
        Vector<Ref,AT2> ret(size());
        for(size_t i=0; i<size(); ++i)
          ret(i) = (*this)(i);
        return ret;
      }

      /*! \brief Element operator
       *
       * Returns a reference to the i-th element. 
       * \param i The i-th element.
       * \return A reference to the element x(i).
       * \remark The bounds are checked in debug mode.
       * \sa operator()(int) const
       * */
      AT& operator()(int i) {

	assert(i>=0);
	assert(i<m);

	return e(i);
      };

      /*! \brief Element operator
       *
       * See operator()(int) 
       * */
      const AT& operator()(int i) const {

	assert(i>=0);
	assert(i<m);

	return e(i);
      };

      iterator begin() { return &ele[0]; }
      iterator end() { return &ele[m]; }
      const_iterator begin() const { return &ele[0]; }
      const_iterator end() const { return &ele[m]; }
      const_iterator cbegin() const noexcept { return &ele[0]; }
      const_iterator cend() const noexcept { return &ele[m]; }

      AT& er(int i) {
	return ele[i];
      };

      const AT& er(int i) const {
	return ele[i];
      };

      AT& et(int i) {
	return ele[i*lda];
      };

      const AT& et(int i) const {
	return ele[i*lda];
      };

       AT& e(int i) {
	return tp ? et(i) : er(i);
      };

      const AT& e(int i) const {
	return tp ? et(i) : er(i);
      };

      /*! \brief Initialization.
       *
       * Initializes all elements of the calling vector
       * with the value given by \em a.
       * \param a Value all elements will be initialized with.
       * \return A reference to the calling vector.
       * */
      inline Vector<Ref,AT>& init(const AT& val=AT()); 
      inline Vector<Ref,AT>& init(Init, const AT& a=AT()) { return init(a); }
      inline Vector<Ref,AT>& init(Noinit, const AT& a=AT()) { return *this; }

      /*! \brief Size.
       *
       * \return The size of the vector.
       * */
      int size() const {return m;};

      /*! \brief Increment.
       *
       * \todo Docu
       *
       * \return The increment.
       * */
      int inc() const {return tp?lda:1;};

      /*! \brief Subvector operator.
       *
       * Returns a subvector of the calling vector. 
       * \attention The subvector and the
       * calling vector will share the same physical memory.
       * \param i1 The starting element. 
       * \param i2 The ending element.
       * \return A subvector of the calling vector.
       * */
      inline Vector<Ref,AT> operator()(int i1, int i2);

      /*! \brief Subvector operator.
       *
       * See operator()(int,int);
       * */
      inline const Vector<Ref,AT> operator()(int i1, int i2) const;

      /*! \brief Subvector operator.
       *
       * Returns a subvector of the calling vector. 
       * \attention The subvector and the
       * calling vector will share the same physical memory.
       * \param I Range containing the starting and the ending element.
       * \return A subvector of the calling vector.
       * */
      inline Vector<Ref,AT> operator()(const Range<Var,Var> &I);

      /*! \brief Subvector operator.
       *
       * See operator()(const Range<Var,Var>&)
       * */
      inline const Vector<Ref,AT> operator()(const Range<Var,Var> &I) const;

      using Matrix<General,Ref,Ref,AT>::operator();

      /*! \brief Cast to std::vector<AT>.
       *
       * \return The std::vector<AT> representation of the vector
       * */
      inline operator std::vector<AT>() const;

      /*! \brief std::vector<AT> Constructor.
       * Constructs and initializes a vector with a std::vector<AT> object.
       * \param v The std::vector<AT> the vector will be initialized with. 
       * */
      inline Vector(std::vector<AT> v);

      RowVector<Ref,AT> T() {
        return RowVector<Ref,AT>(m,lda,tp?false:true,memory,ele);
      };

      const RowVector<Ref,AT> T() const {
        return RowVector<Ref,AT>(m,lda,tp?false:true,memory,ele);
      }

  };

  template <class AT>
    inline Vector<Ref,AT>& Vector<Ref,AT>::init(const AT &val) {
      if(tp) 
        for(int i=0; i<m; i++) 
          et(i) = val;
      else 
        for(int i=0; i<m; i++) 
          er(i) = val;
      return *this;
    }

  template <class AT>
    inline Vector<Ref,AT> Vector<Ref,AT>::operator()(int i1, int i2) {
    return operator()(Range<Var,Var>(i1,i2));
  }

  template <class AT> 
    inline const Vector<Ref,AT> Vector<Ref,AT>::operator()(int i1, int i2) const {
    return operator()(Range<Var,Var>(i1,i2));
  }

  template <class AT>
    inline const Vector<Ref,AT> Vector<Ref,AT>::operator()(const Range<Var,Var> &I) const {

      assert(I.end()<m);

      return Vector<Ref,AT>(I.end()-I.start()+1,lda,tp,memory,elePtr(I.start()));
    }

  template <class AT>
    inline Vector<Ref,AT> Vector<Ref,AT>::operator()(const Range<Var,Var> &I) {

      assert(I.end()<m);

      return Vector<Ref,AT>(I.end()-I.start()+1,lda,tp,memory,elePtr(I.start()));
    }

  template <class AT>
    inline Vector<Ref,AT>::operator std::vector<AT>() const {
      std::vector<AT> ret(size());
      if(size()>0) memcpy(&ret[0], &operator()(0), sizeof(AT)*size());
      return ret;
    }

  template <class AT>
    inline Vector<Ref,AT>::Vector(std::vector<AT> v) : Matrix<General,Ref,Ref,AT>(v.size(),1) {
      if(size()>0) memcpy(&operator()(0), &v[0], sizeof(AT)*size());
    }

  /// @cond NO_SHOW

  template <class AT>
    inline Vector<Ref,AT>& Vector<Ref,AT>::copy(const Vector<Ref,AT> &x) {
      if(tp) {
        if(x.tp) 
          for(int i=0; i<size(); i++)
            et(i) = x.et(i); 
        else 
          for(int i=0; i<size(); i++)
            et(i) = x.er(i);
      }
      else {
        if(x.tp)
          for(int i=0; i<size(); i++)
            er(i) = x.et(i); 
        else 
          for(int i=0; i<size(); i++)
            er(i) = x.er(i);
      }
      return *this;
    }

  template <class AT> template <class Row>
    inline Vector<Ref,AT>& Vector<Ref,AT>::copy(const Vector<Row,AT> &x) {
      if(tp) 
	for(int i=0; i<size(); i++)
	  et(i) = x.e(i);
      else 
	for(int i=0; i<size(); i++)
	  er(i) = x.e(i);
      return *this;
    }

  /// @endcond

}

#endif
