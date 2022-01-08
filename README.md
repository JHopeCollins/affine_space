# affine_space
Small single-header C++20 utility providing CRTP base classes for strongly-typed values and differences. This is similar to a very simplified interpretation of an [affine space](https://en.wikipedia.org/wiki/Affine_space), hence the name.

There are many scenarios where it is useful to distinguish between a value of a particular type, and the difference between two values of a particular type.

There are already two significant examples of this in C++:
- [std::size_t](https://en.cppreference.com/w/cpp/types/size_t) and [std::ptrdiff_t](https://en.cppreference.com/w/cpp/types/ptrdiff_t) for describing memory locations
- [std::chrono::time_point](https://en.cppreference.com/w/cpp/chrono/time_point) and [std::chrono::duration](https://en.cppreference.com/w/cpp/chrono/duration) for describing time.

The header `affine_space.h` provides two base classes: `point_base` and `delta_base` (delta is a difference/displacement). The usual arithmetic operator overloads for an affine space are defined for these classes, and the Curiously Recurring Template Pattern ([CRTP](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/)) is used so that types deriving from `point_base` and `delta_base` can be used as strongly typed point/delta pairs.

Assuming `point` and `delta` are types deriving from `point_base` and `delta_base` respectively, `pN` and `dN` are instances of type `point` and `base` respectively, and `a` is a floating point value, the following arithmetic operators are defined:
```
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
The following operations are not defined because they make no sense in the context of an affine space
```
// p0*=a;      // will not compile
// p0/=a;      // will not compile
// p2 = p0+p1  // will not compile
```
