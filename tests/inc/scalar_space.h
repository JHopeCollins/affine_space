
# include <affine_space.h>

   struct point;
   struct delta;

   struct point :
      affine::scalar_point_base<point,delta,double> {};

   struct delta :
      affine::scalar_delta_base<point,delta,double> {};
