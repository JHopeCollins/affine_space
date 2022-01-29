
# include <scalar_space.h>

# include <catch.hpp>

# include <concepts>

   static_assert( std::same_as<point::value_type,delta::value_type> );
   using value_type = point::value_type;

   constexpr static auto eps = std::numeric_limits<value_type>::epsilon();

   TEST_CASE( "scalar in-place arithmetic", "[scalar][point][delta]" )
  {
      constexpr value_type pval{2};
      constexpr value_type dval0{3};
      constexpr value_type dval1{4};
      constexpr value_type coeff{5};

      SECTION( "scalar point in-place addition", "[scalar][point]" )
     {

         point p{{pval}};

         p+=delta{{dval0}};

         REQUIRE( p.element == Approx( pval+dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar point in-place subtraction", "[scalar][point]" )
     {

         point p{{pval}};

         p-=delta{{dval0}};

         REQUIRE( p.element == Approx( pval-dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar delta in-place addition", "[scalar][delta]" )
     {
         delta d{{dval0}};

         d+=delta{{dval1}};

         REQUIRE( d.element == Approx( dval0+dval1 ).epsilon( eps ) );
     }

      SECTION( "scalar delta in-place subtraction", "[scalar][delta]" )
     {
         delta d{{dval0}};

         d-=delta{{dval1}};

         REQUIRE( d.element == Approx( dval0-dval1 ).epsilon( eps ) );
     }

      SECTION( "scalar delta in-place multiplication", "[scalar][delta]" )
     {
         delta d{{dval0}};

         d*=coeff;

         REQUIRE( d.element == Approx( dval0*coeff ).epsilon( eps ) );
     }

      SECTION( "scalar delta in-place division", "[scalar][delta]" )
     {
         delta d{{dval0}};

         d/=coeff;

         REQUIRE( d.element == Approx( dval0/coeff ).epsilon( eps ) );
     }

      SECTION( "scalar delta in-place negation", "[scalar][delta]" )
     {
         delta d{{dval0}};

         d=-d;

         REQUIRE( d.element == Approx( -dval0 ).epsilon( eps ) );
     }
  }

   TEST_CASE( "scalar arithmetic", "[scalar][point][delta]" )
  {
      constexpr value_type pval0{6};
      constexpr value_type pval1{7};
      constexpr value_type dval0{8};
      constexpr value_type dval1{9};
      constexpr value_type coeff{10};

      SECTION( "scalar point-point subtraction", "[scalar][point][delta]" )
     {
         const delta d = point{{pval1}}-point{{pval0}};

         REQUIRE( d.element == Approx( pval1-pval0 ).epsilon( eps ) );
     }

      SECTION( "scalar point+delta addition", "[scalar][point][delta]" )
     {
         const point p = point{{pval0}}+delta{{dval0}};

         REQUIRE( p.element == Approx( pval0+dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar point-delta subtraction", "[scalar][point][delta]" )
     {
         const point p = point{{pval0}}-delta{{dval0}};

         REQUIRE( p.element == Approx( pval0-dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar delta+delta addition", "[scalar][delta]" )
     {
         const delta d = delta{{dval0}}+delta{{dval1}};

         REQUIRE( d.element == Approx( dval0+dval1 ).epsilon( eps ) );
     }

      SECTION( "scalar delta+delta addition", "[scalar][delta]" )
     {
         const delta d = delta{{dval0}}-delta{{dval1}};

         REQUIRE( d.element == Approx( dval0-dval1 ).epsilon( eps ) );
     }

      SECTION( "scalar num*delta multiplication", "[scalar][delta]" )
     {
         const delta d = coeff*delta{{dval0}};

         REQUIRE( d.element == Approx( coeff*dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar delta*num multiplication", "[scalar][delta]" )
     {
         const delta d = delta{{dval0}}*coeff;

         REQUIRE( d.element == Approx( coeff*dval0 ).epsilon( eps ) );
     }

      SECTION( "scalar delta/num division", "[scalar][delta]" )
     {
         const delta d = delta{{dval0}}/coeff;

         REQUIRE( d.element == Approx( dval0/coeff ).epsilon( eps ) );
     }
  }

