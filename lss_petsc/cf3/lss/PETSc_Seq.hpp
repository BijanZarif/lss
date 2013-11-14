// Copyright (C) 2013 Vrije Universiteit Brussel, Belgium
//
// This software is distributed under the terms of the
// GNU Lesser General Public License version 3 (LGPLv3).
// See doc/lgpl.txt and doc/gpl.txt for the license text.


#ifndef cf3_lss_PETSc_Seq_hpp
#define cf3_lss_PETSc_Seq_hpp


#include "LibLSS_PETSC.hpp"
#include "../../../lss/cf3/lss/linearsystem.hpp"


namespace cf3 {
namespace lss {


namespace detail {


/// @brief PETSc matrix wrapper (consistent with cf3::lss::detail::matrix<...>)
struct petsc_matrix_wrapper  :
  matrix< double, petsc_matrix_wrapper >
{
  petsc_matrix_wrapper() : v(double()) {}

  petsc_matrix_wrapper& initialize(const size_t& i, const size_t& j, const double& _value=double()) { return *this; }
  petsc_matrix_wrapper& initialize(const std::vector< double >& _vector) { return *this; }
  petsc_matrix_wrapper& initialize(const std::string& _fname)            { return *this; }

  petsc_matrix_wrapper& clear()                  { return *this; }
  petsc_matrix_wrapper& zerorow(const size_t& i) { return *this; }

  petsc_matrix_wrapper& operator=(const petsc_matrix_wrapper& _other) { return *this; }
  petsc_matrix_wrapper& operator=(const double& _value)               { return *this; }

  const double& operator()(const size_t& i, const size_t& j=0) const { return v; }
        double& operator()(const size_t& i, const size_t& j=0)       { return v; }

  double v;
};


/// @brief PETSc vector wrapper (consistent with cf3::lss::detail::matrix<...>)
struct petsc_vector_wrapper  :
  matrix< double, petsc_vector_wrapper >
{
  petsc_vector_wrapper() : v(double()) {}

  petsc_vector_wrapper& initialize(const size_t& i, const size_t& j, const double& _value=double()) { return *this; }
  petsc_vector_wrapper& initialize(const std::vector< double >& _vector) { return *this; }
  petsc_vector_wrapper& initialize(const std::string& _fname)            { return *this; }

  petsc_vector_wrapper& clear()                  { return *this; }
  petsc_vector_wrapper& zerorow(const size_t& i) { return *this; }

  petsc_vector_wrapper& operator=(const petsc_vector_wrapper& _other) { return *this; }
  petsc_vector_wrapper& operator=(const double& _value)               { return *this; }

  const double& operator()(const size_t& i, const size_t& j=0) const { return v; }
        double& operator()(const size_t& i, const size_t& j=0)       { return v; }

  double v;
};


}  // namespace detail


/**
 * @brief Interface to PETSc linear system solver, sequential (serial) version
 * @author Pedro Maciel
 */
class lss_API PETSc_Seq : public linearsystem< double >
{
  // utility definitions
  typedef detail::petsc_matrix_wrapper matrix_t;


 public:
  // framework interfacing
  static std::string type_name() { return "petsc"; }


  /// Construction
  PETSc_Seq(const std::string& name,
    const size_t& _size_i=size_t(),
    const size_t& _size_j=size_t(),
    const size_t& _size_k=1,
    const double& _value=double() );

  /// Solve
  PETSc_Seq& solve();


 protected:
  // linear system matrix interfacing

  const double& A(const size_t& i, const size_t& j) const { return m_A(i,j); }
        double& A(const size_t& i, const size_t& j)       { return m_A(i,j); }

  void A___initialize(const size_t& i, const size_t& j, const double& _value=double()) { m_A.initialize(i,j,_value); }
  void A___initialize(const std::vector< double >& _vector) { m_A.initialize(_vector); }
  void A___initialize(const std::string& _fname)            { m_A.initialize(_fname);  }
  void A___clear()                    { m_A.clear();    }
  void A___zerorow(const size_t& i)   { m_A.zerorow(i); }
  void A___print_level(const int& _l) { m_A.m_print = detail::print_level(_l); }

  void          A___print(std::string& _fname) const { m_A.print(_fname);   }
  std::ostream& A___print(std::ostream& o)     const { return m_A.print(o); }
  size_t        A___size(const size_t& d)      const { return m_A.size(d);  }


 protected:
  // storage
  matrix_t m_A;
};


}  // namespace lss
}  // namespace cf3


#endif
