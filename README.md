# affine_space
Small single-header C++20 utility providing CRTP base classes for strongly-typed values and differences. This is similar to a very simplified interpretation of an [affine space](https://en.wikipedia.org/wiki/Affine_space), hence the name.

### What is an affine space?

There are many scenarios where it is useful to distinguish between a value of a particular type, and the difference between two values of a particular type.

As an example, locations and distances. Leeds and Manchester are two cities in the UK. We could think of the result of "Leeds minus Manchester" as being the direction and distance to travel from Manchester to Leeds (approximately 36 miles North-East). We could repeat with "Hull minus Leeds" to get the direction/distance from Leeds to Hull (approximately 50 miles East). Adding  these two directions/distances should give the direction and distance you would need to travel to get from Manchester to Hull. In pseudo-code:
```
position_t Manchester = /* ... */
position_t Leeds = /* ... */
position_t Hull = /* ... */

displacement_t Manchester_to_Leeds = Leeds - Manchester;
displacement_t Leeds_to_Hull = Hull - Leeds;
displacement_t Manchester_to_Hull = Hull - Manchester;

assert( Manchester_to_Leeds + Leeds_to_Hull == Manchester_to_Hull );
```
Note that `position_t` and `displacement_t` are distinct types. It is intuitive that `position_t + displacement_t -> position_t` and `displacement_t + displacement_t -> displacement_t`, however it makes no sense to add two positions - what would the result of Leeds + Manchester be? Strongly typing `position_t` and `displacement_t` encodes these rules in the type system.

Similarly, it makes sense to be able to multiply displacements. If I tell you to walk one mile East, then do the same thing another four times, I am telling you to walk five miles East. In pseudo-code:
```
displacement_t one_mile{1};
displacement_t five_miles{5};
assert( 5*one_mile == five_miles );
```
On the other hand, multiplication of positions has no meaning - what would five times Leeds be? A bigger Leeds?

Affine spaces are useful in a range of applications, most often in the context of physical quantities. There are a number of other properties and operations needed for a full mathematical description of an affine space, but this small library is restricted to only the arithmetic operations.

There are already two significant examples of types which represent affine spaces in C++:
- [std::size_t](https://en.cppreference.com/w/cpp/types/size_t) and [std::ptrdiff_t](https://en.cppreference.com/w/cpp/types/ptrdiff_t) for describing memory locations.
- [std::chrono::time_point](https://en.cppreference.com/w/cpp/chrono/time_point) and [std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration) for describing time.

### How do I use affine_space?

#### Defining new affine space types

The header `affine_space.h` provides two base classes: `point_base` and `delta_base` (delta is a difference/displacement). The usual arithmetic operator overloads for an affine space are defined for these classes, and the Curiously Recurring Template Pattern ([CRTP](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/)) is used so that types deriving from `point_base` and `delta_base` can be used as strongly typed point/delta pairs.

The declarations of `point_base` and `delta_base` are:
```
template<std::size_t ndim,
         typename point_t,
         typename delta_t,
         numeric    num_t>
struct point_base;

template<std::size_t ndim,
         typename point_t,
         typename delta_t,
         numeric    num_t>
struct point_base;
```
The first template parameter `ndim` is the dimension of the affine space - in the example above, the space is the surface of the Earth, so `ndim=2`. The next two parameters are the derived CRTP types - `point_t` is the type deriving from `point_base` and `delta_t` is the type deriving from `delta_t`. Finally, `num_t` is the type used to store the underlying values. `numeric` is a C++20 concept used to ensure that`num_t` satisfies all the required arithmetic operations. For now, `numeric` is identical to `std::floating_point` but this could be extended in the future, for example to include complex numbers or SIMD wrapper types.

To define a new affine space with the `point_t` and `displacement_t` types:
```
# include <affine_space.h>

template<std::size_t N> struct point_t;
template<std::size_t N> struct displacement_t;

template<std::size_t N>
struct point_t
   affine::point_base<N,
                      point_t<N>,
                      displacement_t<N>,
                      double> {};

template<std::size_t N>
struct displacement
   affine::delta_base<N,
                      point_t<N>,
                      displacement_t<N>,
                      double> {};
```
Note that both types must be declared before they are defined, so that both types can be used as template parameters in the `point_t` definition.

#### Using affine space types

The `point_base` and `delta_base` base classes define the following arithmetic operations:
```
point_t<N> p0 = /* ... */
point_t<N> p1 = /* ... */

displacement_t<N> d0 = /* ... */
displacement_t<N> d1 = /* ... */
displacement_t<N> d2 = /* ... */

p0+=d0;
p0-=d0;

p1 = p0+d0;
p1 = p0-d0;

d0+=d1;
d0-=d1;

d2 = d0+d1;
d2 = d0-d1;

d1 = p1-p0;

d0*=a;
d0/=a;

d1 = a*d0;
d1 = d0*a;
d1 = d0/a;
```
The underlying values can be accessed using the bracket operator, and both types have a static `size()` member function which returns `ndim`.

There is a distinction made between the cases of `ndim == 1`, and `ndim == 0`. In the `ndim == 1` case, the `point` and `displacement` types still act like vectors, with the bracket operator and `size()` member function. This is useful for writing algorithms for spaces of arbitrary dimension. However, if `ndim == 0` then the space is assumed to be scalar, and bracket operator and `size()` member function are disabled using C++20 `requires` clauses. In this case, the underlying value can be accessed directly as the `element` member variable. Two template type aliases, `scalar_point_base` and `scalar_delta_base` are provided for this case:
```
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
              num_t>
```
