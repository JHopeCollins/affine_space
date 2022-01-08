
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

   TEST_CASE( "vector point accessor", "[vector][point]" )
  {
      constexpr value_type pval0{1};
      constexpr value_type pval1{2};

      point2 p0{{pval0,pval1}};
      const point2 p1{{pval0,pval1}};

      REQUIRE( p0[0] == Approx( pval0 ).epsilon( eps ) );
      REQUIRE( p0[1] == Approx( pval1 ).epsilon( eps ) );

      REQUIRE( p1[0] == Approx( pval0 ).epsilon( eps ) );
      REQUIRE( p1[1] == Approx( pval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta accessor", "[vector][delta]" )
  {
      constexpr value_type dval0{2};
      constexpr value_type dval1{3};

      delta2 d0{{dval0,dval1}};
      const delta2 d1{{dval0,dval1}};

      REQUIRE( d0[0] == Approx( dval0 ).epsilon( eps ) );
      REQUIRE( d0[1] == Approx( dval1 ).epsilon( eps ) );

      REQUIRE( d1[0] == Approx( dval0 ).epsilon( eps ) );
      REQUIRE( d1[1] == Approx( dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector point in-place addition", "[vector][point]" )
  {
      constexpr value_type pval0{3};
      constexpr value_type pval1{4};

      constexpr value_type dval0{5};
      constexpr value_type dval1{6};

      point2 p{{pval0,pval1}};

      p+=delta2{{dval0,dval1}};

      REQUIRE( p[0] == Approx( pval0+dval0 ).epsilon( eps ) );
      REQUIRE( p[1] == Approx( pval1+dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector point in-place subtraction", "[vector][point]" )
  {
      constexpr value_type pval0{7};
      constexpr value_type pval1{8};

      constexpr value_type dval0{9};
      constexpr value_type dval1{10};

      point2 p{{pval0,pval1}};

      p-=delta2{{dval0,dval1}};

      REQUIRE( p[0] == Approx( pval0-dval0 ).epsilon( eps ) );
      REQUIRE( p[1] == Approx( pval1-dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta in-place addition", "[vector][delta]" )
  {
      constexpr value_type dval00{11};
      constexpr value_type dval01{12};

      constexpr value_type dval10{13};
      constexpr value_type dval11{14};

      delta2 d0{{dval00,dval01}};

      d0+=delta2{{dval10,dval11}};

      REQUIRE( d0[0] == Approx( dval00+dval10 ).epsilon( eps ) );
      REQUIRE( d0[1] == Approx( dval01+dval11 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta in-place subtraction", "[vector][delta]" )
  {
      constexpr value_type dval00{15};
      constexpr value_type dval01{16};

      constexpr value_type dval10{17};
      constexpr value_type dval11{18};

      delta2 d0{{dval00,dval01}};

      d0-=delta2{{dval10,dval11}};

      REQUIRE( d0[0] == Approx( dval00-dval10 ).epsilon( eps ) );
      REQUIRE( d0[1] == Approx( dval01-dval11 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta in-place multiplication", "[vector][delta]" )
  {
      constexpr value_type dval0{19};
      constexpr value_type dval1{20};
      constexpr value_type coeff{21};

      delta2 d{{dval0,dval1}};

      d*=coeff;

      REQUIRE( d[0] == Approx( dval0*coeff ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval1*coeff ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta in-place division", "[vector][delta]" )
  {
      constexpr value_type dval0{22};
      constexpr value_type dval1{23};
      constexpr value_type coeff{24};

      delta2 d{{dval0,dval1}};

      d/=coeff;

      REQUIRE( d[0] == Approx( dval0/coeff ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval1/coeff ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta in-place negation", "[vector][delta]" )
  {
      constexpr value_type dval0{25};
      constexpr value_type dval1{26};
      delta2 d{{dval0,dval1}};

      d=-d;

      REQUIRE( d[0] == Approx( -dval0 ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( -dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector point-point subtraction", "[vector][arithmetic]" )
  {
      constexpr value_type pval00{25};
      constexpr value_type pval01{26};

      constexpr value_type pval10{27};
      constexpr value_type pval11{28};

      const point2 p0{{pval00,pval01}};
      const point2 p1{{pval10,pval11}};

      const delta2 d = p1-p0;

      REQUIRE( d[0] == Approx( pval10-pval00 ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( pval11-pval01 ).epsilon( eps ) );
  }

   TEST_CASE( "vector point+delta addition", "[vector][arithmetic]" )
  {
      constexpr value_type pval0{29};
      constexpr value_type pval1{30};

      constexpr value_type dval0{31};
      constexpr value_type dval1{32};

      const point2 p =  point2{{pval0,pval1}}+delta2{{dval0,dval1}};

      REQUIRE( p[0] == Approx( pval0+dval0 ).epsilon( eps ) );
      REQUIRE( p[1] == Approx( pval1+dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector point-delta subtraction", "[vector][arithmetic]" )
  {
      constexpr value_type pval0{29};
      constexpr value_type pval1{30};

      constexpr value_type dval0{31};
      constexpr value_type dval1{32};

      const point2 p =  point2{{pval0,pval1}}-delta2{{dval0,dval1}};

      REQUIRE( p[0] == Approx( pval0-dval0 ).epsilon( eps ) );
      REQUIRE( p[1] == Approx( pval1-dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta+delta addition", "[vector][arithmetic]" )
  {
      constexpr value_type dval00{33};
      constexpr value_type dval01{34};

      constexpr value_type dval10{35};
      constexpr value_type dval11{36};

      const delta2 d =  delta2{{dval00,dval01}}+delta2{{dval10,dval11}};

      REQUIRE( d[0] == Approx( dval00+dval10 ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval01+dval11 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta-delta subtraction", "[vector][arithmetic]" )
  {
      constexpr value_type dval00{37};
      constexpr value_type dval01{38};

      constexpr value_type dval10{39};
      constexpr value_type dval11{40};

      const delta2 d =  delta2{{dval00,dval01}}-delta2{{dval10,dval11}};

      REQUIRE( d[0] == Approx( dval00-dval10 ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval01-dval11 ).epsilon( eps ) );
  }

   TEST_CASE( "vector num*delta multiplication", "[vector][arithmetic]" )
  {
      constexpr value_type dval0{41};
      constexpr value_type dval1{42};
      constexpr value_type coeff{43};

      const delta2 d = coeff*delta2{{dval0,dval1}};

      REQUIRE( d[0] == Approx( coeff*dval0 ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( coeff*dval1 ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta*num multiplication", "[vector][arithmetic]" )
  {
      constexpr value_type dval0{44};
      constexpr value_type dval1{45};
      constexpr value_type coeff{46};

      const delta2 d = delta2{{dval0,dval1}}*coeff;

      REQUIRE( d[0] == Approx( dval0*coeff ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval1*coeff ).epsilon( eps ) );
  }

   TEST_CASE( "vector delta/num division", "[vector][arithmetic]" )
  {
      constexpr value_type dval0{47};
      constexpr value_type dval1{48};
      constexpr value_type coeff{49};

      const delta2 d = delta2{{dval0,dval1}}/coeff;

      REQUIRE( d[0] == Approx( dval0/coeff ).epsilon( eps ) );
      REQUIRE( d[1] == Approx( dval1/coeff ).epsilon( eps ) );
  }

