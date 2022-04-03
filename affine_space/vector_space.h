
# pragma once

/*
 * MIT License
 * 
 * Copyright (c) 2022 Joshua T. Hope-Collins
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


/*
 * https://github.com/JHopeCollins/affine_space
 *
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

# include <array>
# include <concepts>
# include <type_traits>

/*
 * type acceptable as underlying precision
 *    currently alias for floating_point
 *    could be extended to include types with appropriate arithmetic operator overloads
 *       e.g. complex, rational or fixed precision numbers, or simd wrapper types
 */
   template<typename T>
   concept numeric =
      std::floating_point<T>;

// --------------- vector space element ---------------

/*
 * base CRTP type for an element of a vector space
 */
   template<std::size_t         ndim,
            typename       derived_t,
            numeric num_t>
   struct vector_space_base
  {
      constexpr static bool vector_valued = (ndim>0);

      using element_type =
         std::conditional_t<
            vector_valued,
            std::array<num_t,ndim>,
            num_t>;

      using value_type = num_t;
      element_type element;

      [[nodiscard]]
      constexpr static std::size_t size() requires vector_valued { return ndim; }

   // accessors
      [[nodiscard]] constexpr       value_type& operator[]( const std::size_t i )       requires vector_valued { return element[i]; }
      [[nodiscard]] constexpr const value_type& operator[]( const std::size_t i ) const requires vector_valued { return element[i]; }

   // in-place arithmetic
      derived_t& operator+=( const derived_t& other )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<ndim; ++i ){ elems[i]+=other[i]; }
        }
         else
        {
            element+=other.element;
        }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator-=( const derived_t& other )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<N; ++i ){ elems[i]-=other[i]; }
        }
         else
        {
            element-=other.element;
        }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator*=( const std::convertible_to<num_t> auto a )
     {
         if constexpr( vector_valued )
        {
            for( auto& w : elems ){ w*=a; }
        }
         else
        {
            element*=a;
        }
         return static_cast<derived_t&>(*this);
     }

      derived_t& operator/=( const std::convertible_to<num_t> auto a )
     {
         return static_cast<derived_t&>(*this)*=(num_t(1)/a);
     }

      [[nodiscard]]
      constexpr derived_t operator-()
     {
         if constexpr( vector_valued )
        {
            derived_t result(static_cast<const derived_t&>(*this));
            for( auto& x : result.element ){ x=-x; }
            return result;
        }
         else
        {
            return {{-element}};
        }
     }
  };

/*
 * type aliases for scalar (0D) vector spaces
 */
   template<typename derived_t
            numeric      num_t>
   using scalar_vector_base =
      vector_space_base<0,
                        derived_t,
                        num_t>;

// --------------- Vector arithmetic ---------------

   // v = v+v
   template<size_t        ndim,
            typename derived_t,
            numeric      num_t>
   derived_t operator+( const vector_space_base<ndim,derived_t,num_t>& lhs,
                        const vector_space_base<ndim,derived_t,num_t>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result+=static_cast<const derived_t&>(rhs);
      return result;
  }

   // v = v-v
   template<size_t       ndim,
            typename derived_t,
            numeric      num_t>
   derived_t operator-( const vector_space_base<ndim,derived_t,num_t>& lhs,
                        const vector_space_base<ndim,derived_t,num_t>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result-=static_cast<const derived_t&>(rhs);
      return result;
  }

   // v = a*v
   template<size_t       ndim,
            typename derived_t,
            numeric      num_t>
   derived_t operator*( const std::convertible_to<num_t> auto a,
                        const vector_space_base<ndim,derived_t,num_t>& rhs )
  {
      derived_t result(static_cast<const derived_t&>(rhs));
      result*=a;
      return result;
  }

   // v = v*a
   template<size_t       ndim,
            typename derived_t,
            numeric      num_t>
   derived_t operator*( const vector_space_base<ndim,derived_t,num_t>& lhs,
                        const std::convertible_to<num_t> auto a )
  {
      return a*lhs;
  }

   // v = v/a
   template<size_t       ndim,
            typename derived_t,
            numeric      num_t>
   derived_t operator/( const vector_space_base<ndim,derived_t,num_t>& lhs,
                        const std::convertible_to<num_t> auto a )
  {
      derived_t result(static_cast<const derived_t&>(lhs));
      result/=a;
      return result;
  }

