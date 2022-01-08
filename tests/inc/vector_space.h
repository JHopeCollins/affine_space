
# include <affine_space.h>

   template<std::size_t N> struct point;
   template<std::size_t N> struct delta;

   template<std::size_t N>
   struct point :
      affine::point_base<N,point<N>,delta<N>,double> {};

   template<std::size_t N>
   struct delta :
      affine::delta_base<N,point<N>,delta<N>,double> {};
