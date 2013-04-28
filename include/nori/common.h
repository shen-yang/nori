/*
    This file is part of Nori, a simple educational ray tracer

    Copyright (c) 2012 by Wenzel Jakob and Steve Marschner.

    Nori is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License Version 3
    as published by the Free Software Foundation.

    Nori is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#if !defined(__COMMON_H)
#define __COMMON_H

#define EIGEN_NO_DEBUG 

#if defined(_MSC_VER)
/* Disable some warnings on MSVC++ */
#pragma warning(disable : 4307) /*  "integral constant overflow" in Eigen */
#define WIN32_LEAN_AND_MEAN     /* Don't ever include MFC on Windows */
#define NOMINMAX                /* Don't override min/max */
#endif

/* Include the basics needed by any Nori file */
#include <iostream>
#include <algorithm>
#include <vector>
#include <Eigen/Core>
#include <QString>
#include <stdint.h>
#include <ImathPlatform.h>

/* Convenience definitions */
#define NORI_NAMESPACE_BEGIN namespace nori {
#define NORI_NAMESPACE_END }

#if defined(__APPLE__)
#define PLATFORM_MACOS
#elif defined(__linux__)
#define PLATFORM_LINUX
#elif defined(WIN32)
#define PLATFORM_WINDOWS
#endif

/* "Ray epsilon": relative error threshold for ray intersection computations */
#define Epsilon 1e-4f

/* A few useful constants */
#define INV_PI       0.31830988618379067154f
#define INV_TWOPI    0.15915494309189533577f
#define INV_FOURPI   0.07957747154594766788f
#define SQRT_TWO     1.41421356237309504880f
#define INV_SQRT_TWO 0.70710678118654752440f

#define TWOPI 6.28318530717958647692f

/* Optimization-related macros */
#if defined(__GNUC__)
#define EXPECT_TAKEN(a)        __builtin_expect(a, true)
#define EXPECT_NOT_TAKEN(a)    __builtin_expect(a, false)
#if defined(__linux) 
#define __restrict             __restrict__
#endif
#else
#define EXPECT_TAKEN(a)        a
#define EXPECT_NOT_TAKEN(a)    a
#endif

/* MSVC is missing a few C99 functions */
#if defined(_MSC_VER)
	/// No nextafterf()! -- an implementation is provided in support_win32.cpp
	extern float nextafterf(float x, float y);
#endif

#if !defined(_GNU_SOURCE)
	/// Emulate sincosf using sinf() and cosf()
	inline void sincosf(float theta, float *_sin, float *_cos) {
		*_sin = sinf(theta);
		*_cos = cosf(theta);
	}
#endif

NORI_NAMESPACE_BEGIN

/* Forward declarations */
template <typename Scalar, int Dimension>  struct TVector;
template <typename Scalar, int Dimension>  struct TPoint;
template <typename Point, typename Vector> struct TRay;
template <typename Point>                  struct TBoundingBox;

/* Basic Nori data structures (vectors, points, rays, bounding boxes,
   kd-trees) are oblivious to the underlying data type and dimension.
   The following list of typedefs establishes some convenient aliases
   for specific types. */
typedef TVector<float, 1>       Vector1f;
typedef TVector<float, 2>       Vector2f;
typedef TVector<float, 3>       Vector3f;
typedef TVector<float, 4>       Vector4f;
typedef TVector<double, 1>      Vector1d;
typedef TVector<double, 2>      Vector2d;
typedef TVector<double, 3>      Vector3d;
typedef TVector<double, 4>      Vector4d;
typedef TVector<int, 1>         Vector1i;
typedef TVector<int, 2>         Vector2i;
typedef TVector<int, 3>         Vector3i;
typedef TVector<int, 4>         Vector4i;
typedef TPoint<float, 1>        Point1f;
typedef TPoint<float, 2>        Point2f;
typedef TPoint<float, 3>        Point3f;
typedef TPoint<float, 4>        Point4f;
typedef TPoint<double, 1>       Point1d;
typedef TPoint<double, 2>       Point2d;
typedef TPoint<double, 3>       Point3d;
typedef TPoint<double, 4>       Point4d;
typedef TPoint<int, 1>          Point1i;
typedef TPoint<int, 2>          Point2i;
typedef TPoint<int, 3>          Point3i;
typedef TPoint<int, 4>          Point4i;
typedef TBoundingBox<Point1f>   BoundingBox1f;
typedef TBoundingBox<Point2f>   BoundingBox2f;
typedef TBoundingBox<Point3f>   BoundingBox3f;
typedef TBoundingBox<Point4f>   BoundingBox4f;
typedef TBoundingBox<Point1d>   BoundingBox1d;
typedef TBoundingBox<Point2d>   BoundingBox2d;
typedef TBoundingBox<Point3d>   BoundingBox3d;
typedef TBoundingBox<Point4d>   BoundingBox4d;
typedef TBoundingBox<Point1i>   BoundingBox1i;
typedef TBoundingBox<Point2i>   BoundingBox2i;
typedef TBoundingBox<Point3i>   BoundingBox3i;
typedef TBoundingBox<Point4i>   BoundingBox4i;
typedef TRay<Point2f, Vector2f> Ray2f;
typedef TRay<Point3f, Vector3f> Ray3f;

/// Some more forward declarations
class NoriObject;
class NoriObjectFactory;
class Mesh;
class BSDF;
class Texture;
class Luminaire;
class Bitmap;
class BlockGenerator;
class ImageBlock;
class Camera;
class Integrator;
class Sampler;
class KDTree;
class Scene;
class ReconstructionFilter;
class PhaseFunction;
class Medium;

/// Import cout, cerr, endl for debugging purposes
using std::cout;
using std::cerr;
using std::endl;

/// Simple exception class, which stores a human-readable error description
class NoriException {
public:
	NoriException(const QString &reason) : m_reason(reason) { }
	inline const QString &getReason() const { return m_reason; }
private:
	QString m_reason;
};

/// Measures associated with probability distributions
enum EMeasure {
	EUnknownMeasure = 0,
	ESolidAngle,
	EDiscrete
};

//// Convert radians to degrees
inline float radToDeg(float value) { return value * (180.0f / M_PI); }

/// Convert degrees to radians
inline float degToRad(float value) { return value * (M_PI / 180.0f); }

/// Simple floating point clamping function
inline float clamp(float value, float min, float max) {
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else return value;
}

/// Simple integer clamping function
inline int clamp(int value, int min, int max) {
	if (value < min)
		return min;
	else if (value > max)
		return max;
	else return value;
}

/// Linearly interpolate between two values
inline float lerp(float t, float v1, float v2) {
    return ((float) 1 - t) * v1 + t * v2;
}



/// Uniformly sample a vector on the unit sphere with respect to solid angles
extern Vector3f squareToUniformSphere(const Point2f &sample);

/// Uniformly sample a vector on the unit hemisphere with respect to solid angles
extern Vector3f squareToUniformHemisphere(const Point2f &sample);

/// Uniformly sample a vector on the unit hemisphere with respect to projected solid angles
extern Vector3f squareToCosineHemisphere(const Point2f &sample);

/// Uniformly sample a vector on a 2D disk
extern Point2f squareToUniformDisk(const Point2f &sample);

/// Low-distortion concentric square to disk mapping by Peter Shirley (PDF: 1/PI)
extern Point2f squareToUniformDiskConcentric(const Point2f &sample);

/// Convert an uniformly distributed square sample into barycentric coordinates
extern Point2f squareToUniformTriangle(const Point2f &sample);

/// Compute a direction for the given coordinates in spherical coordinates
extern Vector3f sphericalDirection(float theta, float phi);

/// Compute a direction for the given coordinates in spherical coordinates
extern Point2f sphericalCoordinates(const Vector3f &dir);

/// Indent a complete string (except for the first line) by the requested number of spaces
extern QString indent(const QString &string, int amount = 2);

/// Allocate an aligned region of memory
extern void *allocAligned(size_t size);

/// Free an aligned region of memory
extern void freeAligned(void *ptr);

/// Return the number of cores (real and virtual)
extern int getCoreCount();

NORI_NAMESPACE_END

#endif /* __COMMON_H */
