
# include <vector_space.h>

# include <catch.hpp>

# include <concepts>

   using point2 = point<2>;
   using delta2 = delta<2>;

   static_assert( std::same_as<point2::value_type,delta2::value_type> );
   using value_type = point2::value_type;

   constexpr static auto eps = std::numeric_limits<value_type>::epsilon();

   TEST_CASE( "vector size", "[vector][point][delta]" )
  {
      REQUIRE( point2::size() == 2 );
      REQUIRE( delta2::size() == 2 );
  }

   TEST_CASE( "vector accessors", "[vector][point][delta]" )
  {
      constexpr value_type val0{1};
      constexpr value_type val1{2};

      SECTION( "vector point accessors", "[vector][point]" )
     {
         const point2 p{{val0,val1}};

         REQUIRE( p[0] == Approx( val0 ).epsilon( eps ) );
         REQUIRE( p[1] == Approx( val1 ).epsilon( eps ) );
     }

      SECTION( "vector delta accessors", "[vector][point]" )
     {
         const delta2 d{{val0,val1}};

         REQUIRE( d[0] == Approx( val0 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( val1 ).epsilon( eps ) );
     }
  }

   TEST_CASE( "vector in-place arithmetic", "[vector][point][delta]" )
  {
      constexpr value_type pval0{3};
      constexpr value_type pval1{4};

      constexpr value_type dval0{5};
      constexpr value_type dval1{6};

      constexpr value_type dval2{7};
      constexpr value_type dval3{8};

      constexpr value_type coeff{9};

      SECTION( "vector point in-place addition", "[vector][point]" )
     {
         point2 p{{pval0,pval1}};

         p+=delta2{{dval0,dval1}};

         REQUIRE( p[0] == Approx( pval0+dval0 ).epsilon( eps ) );
         REQUIRE( p[1] == Approx( pval1+dval1 ).epsilon( eps ) );
     }

      SECTION( "vector point in-place subtraction", "[vector][point]" )
     {
         point2 p{{pval0,pval1}};

         p-=delta2{{dval0,dval1}};

         REQUIRE( p[0] == Approx( pval0-dval0 ).epsilon( eps ) );
         REQUIRE( p[1] == Approx( pval1-dval1 ).epsilon( eps ) );
     }

      SECTION( "vector delta in-place addition", "[vector][delta]" )
     {
         delta2 d{{dval0,dval1}};

         d+=delta2{{dval2,dval3}};

         REQUIRE( d[0] == Approx( dval0+dval2 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1+dval3 ).epsilon( eps ) );
     }

      SECTION( "vector delta in-place subtraction", "[vector][delta]" )
     {
         delta2 d{{dval0,dval1}};

         d-=delta2{{dval2,dval3}};

         REQUIRE( d[0] == Approx( dval0-dval2 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1-dval3 ).epsilon( eps ) );
     }

      SECTION( "vector delta in-place multiplication", "[vector][delta]" )
     {
         delta2 d{{dval0,dval1}};

         d*=coeff;

         REQUIRE( d[0] == Approx( dval0*coeff ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1*coeff ).epsilon( eps ) );
     }

      SECTION( "vector delta in-place division", "[vector][delta]" )
     {
         delta2 d{{dval0,dval1}};

         d/=coeff;

         REQUIRE( d[0] == Approx( dval0/coeff ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1/coeff ).epsilon( eps ) );
     }

      SECTION( "vector delta in-place negation", "[vector][delta]" )
     {
         delta2 d{{dval0,dval1}};

         d=-d;

         REQUIRE( d[0] == Approx( -dval0 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( -dval1 ).epsilon( eps ) );
     }
  }

   TEST_CASE( "vector arithmetic", "[vector][point][delta]" )
  {
      constexpr value_type pval0{10};
      constexpr value_type pval1{11};

      constexpr value_type pval2{12};
      constexpr value_type pval3{13};

      constexpr value_type dval0{14};
      constexpr value_type dval1{15};

      constexpr value_type dval2{16};
      constexpr value_type dval3{17};

      constexpr value_type coeff{18};

      SECTION( "vector point-point subtraction", "[vector][point][delta]" )
     {
         const delta2 d = point2{{pval0,pval1}}-point2{{pval2,pval3}};

         REQUIRE( d[0] == Approx( pval0-pval2 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( pval1-pval3 ).epsilon( eps ) );
     }

      SECTION( "vector point+delta addition", "[vector][point][delta]" )
     {
         const point2 p = point2{{pval0,pval1}}+delta2{{dval0,dval1}};

         REQUIRE( p[0] == Approx( pval0+dval0 ).epsilon( eps ) );
         REQUIRE( p[1] == Approx( pval1+dval1 ).epsilon( eps ) );
     }

      SECTION( "vector point-delta subtraction", "[vector][point][delta]" )
     {
         const point2 p = point2{{pval0,pval1}}-delta2{{dval0,dval1}};

         REQUIRE( p[0] == Approx( pval0-dval0 ).epsilon( eps ) );
         REQUIRE( p[1] == Approx( pval1-dval1 ).epsilon( eps ) );
     }

      SECTION( "vector delta+delta addition", "[vector][delta]" )
     {
         const delta2 d = delta2{{dval0,dval1}}+delta2{{dval2,dval3}};

         REQUIRE( d[0] == Approx( dval0+dval2 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1+dval3 ).epsilon( eps ) );
     }

      SECTION( "vector delta-delta subtraction", "[vector][delta]" )
     {
         const delta2 d = delta2{{dval0,dval1}}-delta2{{dval2,dval3}};

         REQUIRE( d[0] == Approx( dval0-dval2 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1-dval3 ).epsilon( eps ) );
     }

      SECTION( "vector num*delta multiplication", "[vector][delta]" )
     {
         const delta2 d = coeff*delta2{{dval0,dval1}};

         REQUIRE( d[0] == Approx( coeff*dval0 ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( coeff*dval1 ).epsilon( eps ) );
     }

      SECTION( "vector delta*num multiplication", "[vector][delta]" )
     {
         const delta2 d = delta2{{dval0,dval1}}*coeff;

         REQUIRE( d[0] == Approx( dval0*coeff ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1*coeff ).epsilon( eps ) );
     }

      SECTION( "vector delta/num division", "[vector][delta]" )
     {
         const delta2 d = delta2{{dval0,dval1}}/coeff;

         REQUIRE( d[0] == Approx( dval0/coeff ).epsilon( eps ) );
         REQUIRE( d[1] == Approx( dval1/coeff ).epsilon( eps ) );
     }
  }

