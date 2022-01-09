
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
 * This header defines two base types corresponding to a point and a displacement (delta) in an affine space.
 *
 *    These types must both be inherited from using CRTP. Instances of the two derived types will act as members of an affine space, with only the expected arithmetic operations allowed,
 *    i.e. displacements can be added/subtracted to give other displacements,
 *         displacements can be added/subtracted to/from points to give other points,
 *         points can be subtracted to give displacements,
 *         displacements can be multiplied by scalars to give other displacements,
 *         points cannot be added, nor multiplied by scalars
 *         in-place versions of these operations are also defined
 *    No assumption is made on whether the space is linear or nonlinear.
 *    All instances are assumed to be represented in the standard basis. Transformations between bases must be implemented by the deriving classes.
 *
 *    If ndim=0, then the space is scalar, and a single element is stored
 *    If ndim>0, then the space is multidimensional, and an array of elements is stored which can be accessed using the array accessor []
 *       note that ndim=1 acts as if multidimensional (has [] operator), so that algorithms can be implemented generically for 1,2,3,... dimensional spaces.
 *
 *    Code example:
 *
 *    // declarations are required before definitions
 *       template<std::size_t N> struct cartesian_point_t
 *       template<std::size_t N> struct cartesian_delta_t
 *
 *       template<std::size_t N>
 *       struct cartesian_point_t :
 *          point_base<N,
 *                     cartesian_point_t<N>,
 *                     cartesian_delta_t<N>,
 *                     double> {};
 *
 *       template<std::size_t N>
 *       struct cartesian_delta_t :
 *          delta_base<N,
 *                     cartesian_point_t<N>,
 *                     cartesian_delta_t<N>,
 *                     double> {};
 *
 *       cartesian_point_t<3> x0,x1;
 *       cartesian_delta_t<3> d0,d1;
 *       const double a = ...
 *
 *       // ... initialise ... x0[0]= ...
 *
 *       d1 = d0+d1;
 *       d1 = d0-d1;
 *
 *       x1 = x0+d0;
 *       x1 = x0-d0;
 *
 *       d1 = x1-x0:
 *
 *       d1 = a*d0:
 *       d1 = d0*a:
 *       d1 = d0/a:
 *
 *       // x0 = x0+x1;    // will not compile!
 *       // x0 =  a*x1;    // will not compile!
 *
 */

# include <array>
# include <concepts>
# include <type_traits>

namespace affine
{

/*
 * type acceptable as underlying precision
 *    currently alias for floating_point
 *    could be extended to include types with appropriate arithmetic operator overloads
 *       e.g. complex, rational or fixed precision numbers, or simd wrapper types
 */
   template<typename T>
   concept numeric =
      std::floating_point<T>;

// --------------- forward declarations ---------------

   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   struct point_base;

   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   struct delta_base;


// --------------- affine space point/displacement ---------------

/*
 * base CRTP type for a point_t in an affine space
 */
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   struct point_base
  {
      constexpr static bool vector_valued = (ndim>0);

      using element_type =
         std::conditional_t<
            vector_valued,
            std::array<num_t,ndim>,
            num_t>;

      using value_type = num_t;
      using point_type = point_t;
      using delta_type = delta_t;
      element_type element;

      [[nodiscard]]
      constexpr static std::size_t size() requires vector_valued { return ndim; }

   // accessors
      [[nodiscard]] constexpr       value_type& operator[]( const std::size_t i )       requires vector_valued { return element[i]; }
      [[nodiscard]] constexpr const value_type& operator[]( const std::size_t i ) const requires vector_valued { return element[i]; }

   // in-place arithmetic
      constexpr point_type& operator+=( const delta_type& d )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<ndim; ++i ){ element[i]+=d[i]; }
        }
         else
        {
            element+=d.element;
        }
         return static_cast<point_type&>(*this);
     }

      constexpr point_type& operator-=( const delta_type& d )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<ndim; ++i ){ element[i]-=d[i]; }
        }
         else
        {
            element-=d.element;
        }
         return static_cast<point_type&>(*this);
     }
  };


/*
 * base CRTP type for a displacement in an affine space
 */
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   struct delta_base
  {
      constexpr static bool vector_valued = (ndim>0);

      using element_type =
         std::conditional_t<
            vector_valued,
            std::array<num_t,ndim>,
            num_t>;

      using value_type = num_t;
      using point_type = point_t;
      using delta_type = delta_t;
      element_type element;

      [[nodiscard]]
      constexpr static std::size_t size() requires vector_valued { return ndim; }

   // accessors
      [[nodiscard]] constexpr       value_type& operator[]( const std::size_t i )       requires vector_valued { return element[i]; }
      [[nodiscard]] constexpr const value_type& operator[]( const std::size_t i ) const requires vector_valued { return element[i]; }

   // in-place arithmetic
      constexpr delta_type& operator+=( const delta_type& d )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<ndim; ++i ){ element[i]+=d[i]; }
        }
         else
        {
            element+=d.element;
        }
         return static_cast<delta_type&>(*this);
     }

      constexpr delta_type& operator-=( const delta_type& d )
     {
         if constexpr( vector_valued )
        {
            for( std::size_t i=0; i<ndim; ++i ){ element[i]-=d[i]; }
        }
         else
        {
            element-=d.element;
        }
         return static_cast<delta_type&>(*this);
     }

      constexpr delta_type& operator*=( const std::floating_point auto a )
     {
         if constexpr( vector_valued )
        {
            for( num_t& w : element ){ w*=a; }
        }
         else
        {
            element*=a;
        }
         return static_cast<delta_type&>(*this);
     }

      constexpr delta_type& operator/=( const std::floating_point auto a )
     {
         return static_cast<delta_type&>(*this)*=1/a;
     }

      [[nodiscard]]
      constexpr delta_type operator-()
     {
         if constexpr( vector_valued )
        {
            delta_t result(static_cast<const delta_t&>(*this));
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
 * type aliases for scalar (0D) affine spaces
 */
   template<typename point_t,
            typename delta_t,
            numeric    num_t>
   using scalar_point_base =
      point_base<0,
                 point_t,
                 delta_t,
                 num_t>;

   template<typename point_t,
            typename delta_t,
            numeric    num_t>
   using scalar_delta_base =
      delta_base<0,
                 point_t,
                 delta_t,
                 num_t>;

// --------------- point_t arithmetic ---------------


   // d = p-p
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator-( const point_base<ndim,point_t,delta_t,num_t>& lhs,
                                const point_base<ndim,point_t,delta_t,num_t>& rhs )
  {
      if constexpr( std::remove_reference_t<decltype(lhs)>::vector_valued )
     {
         delta_t del{};
         for( std::size_t i=0; i<ndim; ++i ){ del[i]=lhs[i]-rhs[i]; }
         return del;
     }
      else
     {
         return {{lhs.element-rhs.element}};
     }
  }

   // p = p+d
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr point_t operator+( const point_base<ndim,point_t,delta_t,num_t>& p,
                                const delta_base<ndim,point_t,delta_t,num_t>& d )
  {
      point_t result(static_cast<const point_t&>(p));
      result+=static_cast<const delta_t&>(d);
      return result;
  }

   // p = p-d
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr point_t operator-( const point_base<ndim,point_t,delta_t,num_t>& p,
                                const delta_base<ndim,point_t,delta_t,num_t>& d )
  {
      point_t result(static_cast<const point_t&>(p));
      result-=static_cast<const delta_t&>(d);
      return result;
  }


// --------------- delta_t arithmetic ---------------

   // d = d+d
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator+( const delta_base<ndim,point_t,delta_t,num_t>& lhs,
                                const delta_base<ndim,point_t,delta_t,num_t>& rhs )
  {
      delta_t result(static_cast<const delta_t&>(lhs));
      result+=static_cast<const delta_t&>(rhs);
      return result;
  }

   // d = d-d
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator-( const delta_base<ndim,point_t,delta_t,num_t>& lhs,
                                const delta_base<ndim,point_t,delta_t,num_t>& rhs )
  {
      delta_t result(static_cast<const delta_t&>(lhs));
      result-=static_cast<const delta_t&>(rhs);
      return result;
  }

   // d = a*d
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator*( const std::floating_point auto a,
                                const delta_base<ndim,point_t,delta_t,num_t>& d )
  {
      delta_t result(static_cast<const delta_t&>(d));
      result*=a;
      return result;
  }

   // d = d*a
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator*( const delta_base<ndim,point_t,delta_t,num_t>& d,
                                const std::floating_point auto a )
  {
      return a*d;
  }

   // d = d/a
   template<std::size_t ndim,
            typename point_t,
            typename delta_t,
            numeric    num_t>
   [[nodiscard]]
   constexpr delta_t operator/( const delta_base<ndim,point_t,delta_t,num_t>& d,
                                const std::floating_point auto a )
  {
      delta_t result(static_cast<const delta_t&>(d));
      result/=a;
      return result;
  }

}

