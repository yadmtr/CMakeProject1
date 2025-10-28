---
layout: page
title: sm::mat44
parent: Reference
nav_order: 7
permalink: /ref/mat44/
---
# sm::mat44
{: .no_toc }
## A 4x4 transformation matrix class
{: .no_toc }
```c++
#include <sm/mat44>
```

Header file: [<sm/mat44>](https://github.com/sebsjames/maths/blob/main/sm/mat44). Test and example code:  [tests/testTransformMatrix](https://github.com/sebsjames/maths/blob/main/tests/testTransformMatrix.cpp) [tests/testTranslatePretranslate](https://github.com/sebsjames/maths/blob/main/tests/testTranslatePretranslate.cpp) [tests/testTransMat_constexpr](https://github.com/sebsjames/maths/blob/main/tests/testTransMat_constexpr.cpp)

**Table of Contents**

- TOC
{:toc}

## Summary
A 4x4 matrix class with a templated element type. `constexpr` capable.

Defined as:
```c++
namespace sm {
    template <typename F> requires std::is_floating_point_v<F>
    struct mat44 {
        // ...
        std::array<F, 16> mat;
```
where `F` must be a floating point type. The data is stored in an `std::array` in column-major format; the left-most column of the matrix is stored in the first 4 elements of the array.

Note that this class template (along with `mat22` and `mat33`) is not designed with template parameters for rows and columns; it retains the simplicity of providing just a square transform matrix. The intention is to provide transformation operations without needing to bring in a great big matrix library like *Eigen* or *arma*. If you have more complex matrix manipulation needs, you can use one of those third party libraries (I use arma).

## Create a mat44

When you create a `mat44` with no constructor arguments, the matrix is initialized as the identity matrix

```c++
sm::mat44<double> m;
std::cout << "Initialized as the identity matrix:\n" << m << std::endl;
```

You can create and assign an initializer list
```c++
sm::mat44<double> m = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
std::cout << m << std::endl;
```
Gives:
```
[ 1, 5, 9, 13 ;
  2, 6, 10, 14 ;
  3, 7, 11, 15 ;
  4, 8, 12, 16 ]
```
See how the initializer list is placed into the matrix column-by-column.

The list may contain fewer than 16 elements:

```c++
sm::mat44<double> m = { 1, 2, 3, 4 };
std::cout << m << std::endl;
```
Gives:
```
[ 1, 0, 0, 0 ;
  2, 0, 0, 0 ;
  3, 0, 0, 0 ;
  4, 0, 0, 0 ]
```

The additional elements are all set to 0. This means you can create a null matrix with

```c++
sm::mat44<double> m = { 0 };
std::cout << m << std::endl;
```
Gives:
```
[ 0, 0, 0, 0 ;
  0, 0, 0, 0 ;
  0, 0, 0, 0 ;
  0, 0, 0, 0 ]
```

But **careful**: if you provide an empty brace list, you will cause the default constructor to be called and the matrix will be the identity matrix. If you want a null matrix, use `{ {} }` or `{0}`:

```c++
sm::mat44<double> m1 = {};      // Yields the identity matrix, NOT the null matrix
sm::mat44<double> m2 = { {} };  // Yields a null matrix
sm::mat44<double> m3 = { 0.0 }; // Yields a null matrix
```

## Set data in the mat44

### Raw access to the elements

You can set the data manually with an initializer list:
```c++
sm::mat44<int> m; // initially set up as identity matrix
m = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
std::cout << "Matrix contains:\n" << m << std::endl;
```
which outputs:
```
Matrix contains:
[ 0 , 4 , 8 , 12 ;
  1 , 5 , 9 , 13 ;
  2 , 6 , 10 , 14 ;
  3 , 7 , 11 , 15 ]
```

You can change individual elements of the matrix with the array access operator:
```c++
m[3] = 100;
std::cout << "Matrix updated:\n" << m << std::endl;
```

The updated matrix is:
```
Matrix updated:
[ 0 , 4 , 8 , 12 ;
  1 , 5 , 9 , 13 ;
  2 , 6 , 10 , 14 ;
  100 , 7 , 11 , 15 ]
```

You can reset a mat44 to the identity matrix:
```c++
m.setToIdentity();
```

### Setting elements by transforms

Often, you want to set the values in the matrix by defining translations and rotations.

#### Translation

```c++
sm::mat44<float> m;
sm::vec<float, 3> t = { 1, 2, 3 };
m.translate (t); // t could also be std::array<float, 3>
// or equivalently:
sm::mat44<float> m2;
m2.translate (1.0f, 2.0f, 3.0f);
```

`translate` applies the translation as a *post-multiplication* to the
existing matrix (`m` in the code above). `m.translate (t)` is
equivalent to the mathematical notation:

**M** = **M** * **T**.

**M** becomes a matrix that first applies the translation (because
**T** is the right-most matrix in the multiplication) and then applies
whatever transformation was originally in **M**.

`pretranslate` applies a translation as a *pre-multiplication*, making
`m.pretranslate (t)` equivalent to the following maths:

**M** = **T** * **M**.

With `pretranslate`, the requested translation is applied *following* any other
transformations that were specfied in **M**.

`translate` and `pretranslate` have the same effect as the functions of
the same names in [`Eigen::Transform`](https://libeigen.gitlab.io/eigen/docs-nightly/classEigen_1_1Transform.html).

#### Rotation

The `rotate` methods apply a rotation into the linear part of the matrix:

```c++
sm::mat44<float> m;
// Rotate by axis and angle
sm::vec<float> axis = { 1, 1, 0 }; // You can also use std::array<float, 3>
m.rotate (axis, sm::mathconst<float>::pi_over_2);
```

The `rotate` methods *post-multiply* the 'this' matrix by a pure
rotation matrix (again this is the same behaviour as Eigen), with the
equivalent mathematical notation for a rotation matrix **R** being:

**M** = **M** * **R**

You can also rotate by passing a quaternion to `rotate`:

```c++
// Rotate using a sm::quaternion
sm::mat44<float> m2;
sm::quaternion<double> qd (axis.as_double(), sm::mathconst<double>::pi_over_4);
m2.rotate (qd); // Note that the quaternion does not have to have the same
                // element type as the mat44
```

The axis in the quaternion constructor is always renormalized before
being used to define a rotation.

Finally, there are the `prerotate` methods, which apply the rotation
as a pre-multiplication.

`prerotate` is equivalent to

**M** = **R** * **M**

with the rotation pre-multiplying the existing matrix and therefore
*following* any transformations already encoded in *M*.

##### Rotation axis

Note that the `axis` passed to `rotate` (or `prerotate`) will be
automatically renormalized. If you *know* that your rotation axis is
already normalized and you want to save a few computations, or you
have another reason for rotating about an unnormalized axis vector,
you can use:

```c++
sm::vec<float> normalized_axis = { 0, 1, 0 };
constexpr bool renorm = false;
m.rotate<renorm> (normalized_axis, sm::mathconst<float>::pi_over_2);
// or
m.prerotate<renorm> (normalized_axis, sm::mathconst<float>::pi_over_2);
```

You just have to override the `renorm` template parameter whose
default is `true`.

#### Scale

In addition to rotate and translate functions, `mat44` provides
`scale` functions:

```c++
sm::mat44<float> m;
sm::vec<float> t = { 2, 0, 0 };
m.translate (t);
sm::vec<float> scaling = { 0.5, 1, 1.5 };
m.scale (scaling);
```
Here, the 3D scaling can be provided as a `sm::vec<float, 3>`,
`std::array<float, 3>` or as three floats.

It's also possible to specify an equal scaling in all elements:

```c++
sm::mat44<float> m;
sm::vec<float> t = { 2, 0, 0 };
m.translate (t);
float scaling = 1.2f;
m.scale (scaling);
```

### Special setter `frombasis`

```c++
static constexpr mat44<F> frombasis (const sm::vec<F> bx, const sm::vec<F> by, const sm::vec<F> bz);
constexpr void frombasis_inplace (const sm::vec<F> bx, const sm::vec<F> by, const sm::vec<F> bz);
```

The static function `frombasis` sets up a coordinate transformation, using a set of three basis vectors, which it returns.
`frombasis_inplace` is the non-static counterpart.

```c++
sm::vec<float> bx = { 0.707f, 0.707f, 0.0f };
sm::vec<float> by = { -0.707f, 0.707f, 0.0f };
sm::vec<float> bz = { 0, 0, 1 };

sm::mat44<float> mfb = sm::mat44<float>::frombasis (bx, by, bz);
```
The matrix now encodes a transformation of a vector from the right handed Cartesian coordinate frame into the frame specified by the vectors bx, by and bz.
```c++
    std::cout << "With matrix\n\n" << mfb << ",\n\n" << sm::vec<float>::ux() << " transforms to "
              << mfb * sm::vec<float>::ux() << std::endl << sm::vec<float>::uy() << " transforms to "
              << mfb * sm::vec<float>::uy() << std::endl << sm::vec<float>::uz() << " transforms to "
              << mfb * sm::vec<float>::uz() << std::endl << " and (1,2,3) transforms to "
              << mfb * sm::vec<>{1,2,3} << std::endl;
```
gives output:
```
With matrix

[ 0.707 , -0.707 , 0 , 0 ;
  0.707 , 0.707 , 0 , 0 ;
  0 , 0 , 1 , 0 ;
  0 , 0 , 0 , 1 ],

(1,0,0) transforms to (0.707000017,0.707000017,0,1)
(0,1,0) transforms to (-0.707000017,0.707000017,0,1)
(0,0,1) transforms to (0,0,1,1)
 and (1,2,3) transforms to (-0.707000017,2.12100005,3,1)
```

### Special setter  `perspective`

```c++
static constexpr sm::mat44<F> perspective (F fovDeg, F aspect, F zNear, F zFar) noexcept;
constexpr void perspective_inplace (F fovDeg, F aspect, F zNear, F zFar) noexcept;
```

`perspective` and `perspective_inplace` set up a perspective (or frustrum) projection, for use in computer graphics applications.

The field of view for the projection is given in degrees, measured from the top of the field to the bottom of the field (rather than from the left to the right).

The aspect ratio is "the number of multiples of the height that the width is". Greater than 1 for a wide-screen; less than 1 for a portrait screen.

The near and far z values specify near and far projection planes and should not be the same.

```c++
float field_of_view_degrees = 30.0f;
float aspect_ratio = 1.5f;
float z_near = 0.01f;
float z_far = 100.0f;
sm::mat44<float> mpers = sm::mat44<float>::perspective (field_of_view_degrees, aspect_ratio, z_near, z_far);
// Often, mpers is then pushed to the GPU as an 'OpenGL uniform' or similar.
```

### Special setter `orthographic`

```c++
static constexpr sm::mat44<F> orthographic (const sm::vec<F, 2>& lb, const sm::vec<F, 2>& rt,
                                            const F zNear, const F zFar) noexcept;
constexpr void orthographic_inplace (const sm::vec<F, 2>& lb, const sm::vec<F, 2>& rt,
                                     const F zNear, const F zFar) noexcept;
```

`orthographic` and `orthographic_inplace` set up an orthographic projection, for use in computer graphics applications.

An orthographic projection requires that you specify a *viewing volume*. This function takes a pair of 2D vectors to specify the left-bottom and right-top of the volume, along with two scalars representing near and far z values.

```c++
sm::vec<float, 2> left_bottom = { -1, -1 };
sm::vec<float, 2> right_top = { 1, 1 };
float z_near = 0.01f;
float z_far = 100.0f;
sm::mat44<float> mo;
mo.orthographic_inplace (left_bottom, right_top, z_near, z_far);
```

### Special setter `pure_rotation`

```c++
template <typename T> requires std::is_arithmetic_v<T>
static constexpr mat44<F> pure_rotation (const sm::quaternion<T>& q) noexcept
```

This static method returns a rotation matrix. It places the rotation q
into a mat44<F> and returns the matrix.

## Matrix operations

You can add, subtract and multiply `mat44` instances, and also add, subtract and multiply by scalars
```c++
sm::mat44<double> m1;
sm::mat44<double> m2;
sm::mat44<double> m3 = m1 + m2;
sm::mat44<double> m4 = m1 - m2;
sm::mat44<double> m5 = m1 * m2;
m5 += m2;
m4 -= m3;
m4 *= m1;
m4 *= 3;
sm::mat44<double> m6 = m4 - 7.45;
```

You can obtain the inverse and transposed matrices or carry out these operations in-place:
```c++
sm::mat44<float> m;
sm::mat44<float> mi = m.inverse(); // Returns the inverse.
sm::mat44<float> mt = m.transpose();        // Returns transposed matrix

m.inverse_inplace();   // Invert in-place
m.transpose_inplace(); // Transposes the matrix in place
```
### Matrix operations on vectors

You can, of course, multiply vectors by a `mat44`. Multiplication of a
vector by a `mat44` always yields a four dimensional vector. If you
are working in three dimensions, you simply ignore the last element of
the returned vector.

You should always use `sm::vec<>` as the vector type. The following will work fine:
```c++
// A perspective projection so that our matrix is not empty
sm::mat44<float> m = sm::mat44<float>::perspective (50, 1.4, 0.1, 100);

sm::vec<float, 3> v1 = { 1, 0, 0 };
std::cout << "\n" << m << " * " << v1 << " = " << m * v1 << std::endl;

sm::vec<float, 4> v2 = { 1, 1, 0, 0 };
std::cout << "\n" << m << " * " << v2 << " = " << m * v2 << std::endl;
```
If you want the output to be a three dimensional vector, use `vec<>::less_one_dim()`:
```c++
sm::vec<float, 3> v3d = (m * v1).less_one_dim();
```
There *is* a definition of vector multiplication for a 4 element `std::array`, though I'd recommend using `sm::vec`. Nevertheless, you can do:
```c++
std::array<float, 4> a2 = { 1, 1, 0, 0 };
std::array<float, 4> ares2 = (m * a2); // Note return object is also std::array
```

## Matrix properties

The determinant, trace, adjugate and cofactor of the matrix are available via these function calls:
```c++
sm::mat44<float> m;
float d = m.determinant();
float t = m.trace();
std::array<float, 16> a = m.adjugate();
std::array<float, 16> c = m.cofactor();
```
The adjugate and cofactor return `std::array` rather than `mat44` as they are usually used internally during a computation of the inverse.
