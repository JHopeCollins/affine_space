
# pragma once


# include <array>
# include <iostream>
# include <concepts>

/*
 * This header defines a base type corresponding to a member of a vector space
 *
 *    This type must both be inherited from using CRTP. Instances of the derived type will act as members of a vector space, with only the expected arithmetic operations allowed,
 *    i.e. vectors can be added/subtracted to give other vectors,
 *         vectors can be multiplied by scalars to give other vectors,
 *         in-place versions of these operations are also defined
 *    No assumption is made on whether the space is linear or nonlinear.
 *    All instances are assumed to be represented in the standard basis. Transformations between bases must be implemented by the deriving classes.
 *    Individual elements of Vectors can be accessed using the array accessor []
 *
 *    Code example:
 *
 *       template<size_t N>
 *       struct CartesianVector : vector_space_base<N,CartesianVector<N>> {};
 *
 *       CartesianVector<3> v0,v1;
 *       const double a = ...
 *
 *       // ... initialise ... v0[0]= ...
 *
 *       v1 = v0+v1;
 *       v1 = v0-v1;
 *
 *       v1 = a*v0:
 *       v1 = v0*a:
 *       v1 = v0/a:
 *
 *    Brace initialisation is also possible
 *       CartesianVector<3> p{0.,1.,2.};
 *
 *    Sending Vector to stream sends each element in turn separated by a space
 *    ostream << v0  // -> // ostream << v0[0] << " " << v0[1] ... << v0[n];
 */

// --------------- vector space element ---------------

/*
 * base CRTP type for an element of a vector space
 */
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   struct vector_space_base
  {
      using value_type = real;
      constexpr static size_t N=ndim;
      std::array<real,N> elems;

   // accessors
            real& operator[]( const size_t i )       { return elems[i]; }
      const real& operator[]( const size_t i ) const { return elems[i]; }

   // in-place arithmetic
      derived_t& operator+=( const derived_t& other )
     {
         for( size_t i=0; i<N; ++i ){ elems[i]+=other[i]; }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator-=( const derived_t& other )
     {
         for( size_t i=0; i<N; ++i ){ elems[i]-=other[i]; }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator*=( const std::convertible_to<real> auto a )
     {
         for( real& w : elems ){ w*=a; }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator/=( const std::convertible_to<real> auto a )
     {
         const auto a1=1./a;
         for( real& w : elems ){ w*=a1; }
         return static_cast<derived_t&>(*this);
     }
  };

// --------------- Vector arithmetic ---------------

   // v = v+v
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   derived_t operator+( const vector_space_base<ndim,derived_t,real>& lhs,
                      const vector_space_base<ndim,derived_t,real>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result+=static_cast<const derived_t&>(rhs);
      return result;
  }

   // v = v-v
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   derived_t operator-( const vector_space_base<ndim,derived_t,real>& lhs,
                      const vector_space_base<ndim,derived_t,real>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result-=static_cast<const derived_t&>(rhs);
      return result;
  }

   // v = a*v
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   derived_t operator*( const std::convertible_to<real> auto a,
                      const vector_space_base<ndim,derived_t,real>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(rhs));
      result*=a;
      return result;
  }

   // v = v*a
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   derived_t operator*( const vector_space_base<ndim,derived_t,real>& lhs,
                      const std::convertible_to<real> auto a )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result*=a;
      return result;
  }

   // v = v/a
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   derived_t operator/( const vector_space_base<ndim,derived_t,real>& lhs,
                      const std::convertible_to<real> auto a )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result*=1./a;
      return result;
  }


// --------------- Printing to stream ---------------

/*
 * send each element of Vector to stream, seperated by a single space
 */
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   std::ostream& operator<<(       std::ostream& os,
                             const vector_space_base<ndim,derived_t,real>& v )
  {
      for( size_t i=0; i<ndim-1; i++ )
     {
         os << v[i] << " ";
     }
      os << v[ndim-1];
      return os;
  }

/*
 * read each element of Vector from stream
 */
   template<size_t              ndim,
            typename         derived_t,
            std::floating_point real>
   std::istream& operator>>( std::istream& is,
                             vector_space_base<ndim,derived_t,real>& v )
  {
      for( auto& elem : v.elems ){ is >> elem; }
      return is;
  }

