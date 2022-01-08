
# include <scalar_space.h>

# include <catch.hpp>

# include <concepts>

   static_assert( std::same_as<point::value_type,delta::value_type> );
   using value_type = point::value_type;

   constexpr static auto eps = std::numeric_limits<value_type>::epsilon();

   TEST_CASE( "scalar point in-place addition", "[scalar][point]" )
  {
      constexpr value_type pval{1};
      constexpr value_type dval{2};
      point p{{pval}};

      p+=delta{{dval}};

      REQUIRE( p.element == Approx( pval+dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar point in-place subtraction", "[scalar][point]" )
  {
      constexpr value_type pval{3};
      constexpr value_type dval{4};
      point p{{pval}};

      p-=delta{{dval}};

      REQUIRE( p.element == Approx( pval-dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta in-place addition", "[scalar][delta]" )
  {
      constexpr value_type dval0{1};
      constexpr value_type dval1{2};
      delta d{{dval0}};

      d+=delta{{dval1}};

      REQUIRE( d.element == Approx( dval0+dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta in-place subtraction", "[scalar][delta]" )
  {
      constexpr value_type dval0{3};
      constexpr value_type dval1{4};
      point d{{dval0}};

      d-=delta{{dval1}};

      REQUIRE( d.element == Approx( dval0-dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta in-place multiplication", "[scalar][delta]" )
  {
      constexpr value_type dval{5};
      constexpr value_type coeff{2};
      delta d{{dval}};

      d*=coeff;

      REQUIRE( d.element == Approx( dval*coeff ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta in-place division", "[scalar][delta]" )
  {
      constexpr value_type dval{6};
      constexpr value_type coeff{2};
      delta d{{dval}};

      d/=coeff;

      REQUIRE( d.element == Approx( dval/coeff ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta in-place negation", "[scalar][delta]" )
  {
      constexpr value_type dval{7};
      delta d{{dval}};

      d=-d;

      REQUIRE( d.element == Approx( -dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar point-point subtraction", "[scalar][arithmetic]" )
  {
      constexpr value_type pval0{5};
      constexpr value_type pval1{6};

      const point p0{{pval0}};
      const point p1{{pval1}};

      const delta d = p1-p0;

      REQUIRE( d.element == Approx( pval1-pval0 ).epsilon( eps ) );
  }

   TEST_CASE( "scalar point+delta addition", "[scalar][arithmetic]" )
  {
      constexpr value_type pval{7};
      constexpr value_type dval{8};

      const point p = point{{pval}}+delta{{dval}};

      REQUIRE( p.element == Approx( pval+dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar point-delta subtraction", "[scalar][arithmetic]" )
  {
      constexpr value_type pval{9};
      constexpr value_type dval{10};

      const point p = point{{pval}}-delta{{dval}};

      REQUIRE( p.element == Approx( pval-dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta+delta addition", "[scalar][arithmetic]" )
  {
      constexpr value_type dval0{11};
      constexpr value_type dval1{12};

      const delta d = delta{{dval0}}+delta{{dval1}};

      REQUIRE( d.element == Approx( dval0+dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta-delta subtraction", "[scalar][arithmetic]" )
  {
      constexpr value_type dval0{13};
      constexpr value_type dval1{14};

      const delta d = delta{{dval0}}-delta{{dval1}};

      REQUIRE( d.element == Approx( dval0-dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "scalar num*delta multiplication", "[scalar][arithmetic]" )
  {
      constexpr value_type dval{15};
      constexpr value_type coeff{16};

      const delta d = coeff*delta{{dval}};

      REQUIRE( d.element == Approx( coeff*dval ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta*num multiplication", "[scalar][arithmetic]" )
  {
      constexpr value_type dval{17};
      constexpr value_type coeff{18};

      const delta d = delta{{dval}}*coeff;

      REQUIRE( d.element == Approx( dval*coeff ).epsilon( eps ) );
  }

   TEST_CASE( "scalar delta/num division", "[scalar][arithmetic]" )
  {
      constexpr value_type dval{19};
      constexpr value_type coeff{20};

      const delta d = delta{{dval}}/coeff;

      REQUIRE( d.element == Approx( dval/coeff ).epsilon( eps ) );
  }

