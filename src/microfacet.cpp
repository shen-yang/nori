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

#include <nori/bsdf.h>
#include <nori/frame.h>

NORI_NAMESPACE_BEGIN

class Microfacet : public BSDF {
public:
	Microfacet(const PropertyList &propList) {
		/* RMS surface roughness */
		m_alpha = propList.getFloat("alpha", 0.1f);

		/* Interior IOR (default: BK7 borosilicate optical glass) */
		m_intIOR = propList.getFloat("intIOR", 1.5046f);

		/* Exterior IOR (default: air) */
		m_extIOR = propList.getFloat("extIOR", 1.000277f);

		/* Albedo of the diffuse base material (a.k.a "kd") */
		m_kd = propList.getColor("kd", Color3f(0.5f));

		/* To ensure energy conservation, we must scale the 
		   specular component by 1-kd. 

		   While that is not a particularly realistic model of what 
		   happens in reality, this will greatly simplify the 
		   implementation. Please see the course staff if you're 
		   interested in implementing a more realistic version 
		   of this BRDF. */
		m_ks = 1 - m_kd.maxCoeff();
	}

	/// Evaluate the BRDF for the given pair of directions
	inline Color3f eval(const BSDFQueryRecord &bRec) const {
		Vector3f m = (bRec.wi + bRec.wo).normalized();
		float d = evalNormal(m);
		float f = fresnel(bRec.wi, m, m_extIOR, m_intIOR);
		float g = smithG1(bRec.wi, m);
		float cosThetai = Frame::cosTheta(bRec.wi);
		float cosThetao = Frame::cosTheta(bRec.wo);
		Color3f result = m_kd*INV_PI + 
			Color3f(0.25f*m_ks*d*f*g/(cosThetai*cosThetao));
		return result;
	}

	/// Evaluate the sampling density of \ref sample() wrt. solid angles
	inline float pdf(const BSDFQueryRecord &bRec) const {
		Vector3f m = (bRec.wi + bRec.wo).normalized();
		return evalNormal(m) * Frame::cosTheta(m);
	}

	/// Sample the BRDF
	Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const {
		float tanThetaMSqr = -m_alpha*m_alpha*std::log(std::max(1e-8f, 1.0f-sample.x()));
		float cosThetaM = 1.0f/std::sqrt(1.0f+tanThetaMSqr);
		float sinThetaM = std::sqrt(std::max(0.0f, 1.0f-cosThetaM*cosThetaM));
		float phiM = TWOPI*sample.y();
		Vector3f m(sinThetaM*std::cos(phiM),
				   sinThetaM*std::sin(phiM),
				   cosThetaM);//half vector, or microsurface normal
		float idotm = bRec.wi.dot(m);
		bRec.wo = 2.0f*idotm*m - bRec.wi;
		Color3f weight = eval(bRec)*Frame::cosTheta(bRec.wo)/pdf(bRec);
		return weight;
	}
	
	
	QString toString() const {
		return QString(
			"Microfacet[\n"
			"  alpha = %1,\n"
			"  intIOR = %2,\n"
			"  extIOR = %3,\n"
			"  kd = %4\n"
			"  ks = %5,\n"
			"]")
		.arg(m_alpha)
		.arg(m_intIOR)
		.arg(m_extIOR)
		.arg(m_kd.toString())
		.arg(m_ks);
	}
private:
	float m_alpha;
	float m_intIOR, m_extIOR;
	float m_ks;
	Color3f m_kd;
	// eval Beckman distribution
	float evalNormal( const Vector3f& m) const{
		if ( Frame::cosTheta(m) <= 0.0f ){
			return 0.0f;
		}
		float alphaSqr = m_alpha*m_alpha;
		float exponent = Frame::tanTheta2(m)/alphaSqr;
		float cosTheta2 = Frame::cosTheta2(m);
		float result = std::exp(-exponent)/
			(M_PI*alphaSqr*cosTheta2*cosTheta2);
		if (result < 1e-20f) {
			result = 0.0f;
		}
		return result;
	}

	/// SmithG1 shadow masking
	float smithG1( const Vector3f& v, const Vector3f& m) const{
		float tanTheta = std::abs(Frame::tanTheta(v));
		if ( tanTheta == 0.0f ) {
			return 1.0f;
		}
		if (v.dot(m)*Frame::cosTheta(v) <= 0) {
			return 0.0f;
		}
		float a =  1.0f/(m_alpha*tanTheta);
		if ( a>=1.6f) {
			return 1.0f;
		}
		float asqr = a*a;
		return (3.535f * a + 2.181f * asqr)
				/ (1.0f + 2.276f * a + 2.577f * asqr);
	}
};

NORI_REGISTER_CLASS(Microfacet, "microfacet");
NORI_NAMESPACE_END
