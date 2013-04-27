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

#if !defined(__FRAME_H)
#define __FRAME_H

#include <nori/vector.h>

NORI_NAMESPACE_BEGIN

/**
 * \brief Stores a three-dimensional orthonormal coordinate frame
 *
 * This class is mostly used to quickly convert between different
 * cartesian coordinate systems and to efficiently compute certain
 * quantities (e.g. \ref cosTheta(), \ref tanTheta, ..).
 */
struct Frame {
	Vector3f s, t;
	Normal3f n;

	/// Default constructor -- performs no initialization!
	inline Frame() { }

	/// Given a normal and tangent vectors, construct a new coordinate frame
	inline Frame(const Vector3f &s, const Vector3f &t, const Normal3f &n)
	 : s(s), t(t), n(n) { }

	/// Construct a frame from the given orthonormal vectors
	inline Frame(const Vector3f &x, const Vector3f &y, const Vector3f &z)
	 : s(x), t(y), n(z) { }

	/// Construct a new coordinate frame from a single vector
	inline Frame(const Vector3f &n) : n(n) {
		coordinateSystem(n, s, t);
	}

	/// Convert from world coordinates to local coordinates
	inline Vector3f toLocal(const Vector3f &v) const {
		return Vector3f(
			v.dot(s), v.dot(t), v.dot(n)
		);
	}

	/// Convert from local coordinates to world coordinates
	inline Vector3f toWorld(const Vector3f &v) const {
		return s * v.x() + t * v.y() + n * v.z();
	}

	/** \brief Assuming that the given direction is in the local coordinate 
	 * system, return the cosine of the angle between the normal and v */
	inline static float cosTheta(const Vector3f &v) {
		return v.z();
	}

	inline static float cosTheta2(const Vector3f& v) {
		return v.z()*v.z();
	}
	/** \brief Assuming that the given direction is in the local coordinate
	 * system, return the sine of the angle between the normal and v */
	inline static float sinTheta(const Vector3f &v) {
		float temp = sinTheta2(v);
		if (temp <= 0.0f)
			return 0.0f;
		return std::sqrt(temp);
	}

	/** \brief Assuming that the given direction is in the local coordinate
	 * system, return the tangent of the angle between the normal and v */
	inline static float tanTheta(const Vector3f &v) {
		float temp = 1 - v.z()*v.z();
		if (temp <= 0.0f)
			return 0.0f;
		return std::sqrt(temp) / v.z();
	}
	
	inline static float tanTheta2(const Vector3f& v) {
		float zsqr = v.z()*v.z();
		float temp = 1.0f - zsqr;
		return temp/zsqr;
	}
	/** \brief Assuming that the given direction is in the local coordinate
	 * system, return the squared sine of the angle between the normal and v */
	inline static float sinTheta2(const Vector3f &v) {
		return 1.0f - v.z() * v.z();
	}

	/** \brief Assuming that the given direction is in the local coordinate 
	 * system, return the sine of the phi parameter in spherical coordinates */
	inline static float sinPhi(const Vector3f &v) {
		float sinTheta = Frame::sinTheta(v);
		if (sinTheta == 0.0f)
			return 1.0f;
		return clamp(v.y() / sinTheta, -1.0f, 1.0f);
	}

	/** \brief Assuming that the given direction is in the local coordinate 
	 * system, return the cosine of the phi parameter in spherical coordinates */
	inline static float cosPhi(const Vector3f &v) {
		float sinTheta = Frame::sinTheta(v);
		if (sinTheta == 0.0f)
			return 1.0f;
		return clamp(v.x() / sinTheta, -1.0f, 1.0f);
	}

	/** \brief Assuming that the given direction is in the local coordinate
	 * system, return the squared sine of the phi parameter in  spherical
	 * coordinates */
	inline static float sinPhi2(const Vector3f &v) {
		return clamp(v.y() * v.y() / sinTheta2(v), 0.0f, 1.0f);
	}

	/** \brief Assuming that the given direction is in the local coordinate
	 * system, return the squared cosine of the phi parameter in  spherical
	 * coordinates */
	inline static float cosPhi2(const Vector3f &v) {
		return clamp(v.x() * v.x() / sinTheta2(v), 0.0f, 1.0f);
	}

	/// Equality test
	inline bool operator==(const Frame &frame) const {
		return frame.s == s && frame.t == t && frame.n == n;
	}

	/// Inequality test
	inline bool operator!=(const Frame &frame) const {
		return !operator==(frame);
	}

	/// Return a human-readable string summary of this frame
	inline QString toString() const {
		return QString(
				"Frame[\n"
				"  s = %1,\n"
				"  t = %2,\n"
				"  n = %3\n"
				"]")
			.arg(s.toString()).arg(t.toString()).arg(n.toString());
	}
};

NORI_NAMESPACE_END

#endif /* __FRAME_H */
