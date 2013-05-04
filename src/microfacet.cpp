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
#undef NDEBUG
#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/random.h>

NORI_NAMESPACE_BEGIN

float Fresnel(float cosThetai, float extIOR, float intIOR) {
    // Compute indices of refraction for dielectric
    bool entering = cosThetai > 0.0f;
    float ei = extIOR, et = intIOR;
    if (!entering)
        std::swap(ei, et);
    // Compute _sint_ using Snell's law
    float sint = ei/et * sqrtf(std::max(0.f, 1.f - cosThetai*cosThetai));
    if (sint >= 1.0f) {
        // Handle total internal reflection
        return 1.0f;
    } else {
		// Compute Fresnel reflectance for dielectric
		float a = extIOR - intIOR;
		float b = extIOR + intIOR;
		float r0 = a/b;
		r0 *= r0;
		float c = 1.0f - std::abs(cosThetai);
		float result = r0 + (1.0f-r0)*c*c*c*c*c;
		return result;
    }
}
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

		m_random.seed(FloatAsInt(m_alpha+m_kd.maxCoeff()));
	}

	/// Evaluate the BRDF for the given pair of directions
	inline Color3f eval(const BSDFQueryRecord &bRec) const {
		Vector3f m = (bRec.wi + bRec.wo).normalized();
		float d = evalNormal(m);
		float idotm = bRec.wi.dot(m);
		float f = Fresnel(idotm, m_extIOR, m_intIOR);
		float g = G(bRec, m);
		float cosThetai = Frame::cosTheta(bRec.wi);
		float cosThetao = Frame::cosTheta(bRec.wo);
		Color3f result = m_kd*INV_PI + 
			m_ks*(0.25f*d*f*g/(cosThetai*cosThetao));
		return result;
	}

	/// Evaluate the sampling density of \ref sample() wrt. solid angles
	inline float pdf(const BSDFQueryRecord &bRec) const {
		if (bRec.wi.z()<=0.0f || bRec.wo.z()<= 0.0f) {
			return 0.0f;
		}
		Vector3f m = (bRec.wi + bRec.wo).normalized();
		float pdfs = evalNormal(m);
		//float pdfd = Frame::cosTheta(bRec.wo)*INV_PI;
		//return 0.5f*(pdfs+pdfd);
		return pdfs;
	}

	/// Sample the BRDF
	Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample) const {
		if(bRec.wi.z() <= 0.0f){
			return Color3f(0.0f);
		}
		bRec.measure = ESolidAngle;

		float tanThetaMSqr = -m_alpha*m_alpha*std::log(1.0f-sample.x());
		//assert(tanThetaMSqr >= 0.0f);
		float cosThetaM = 1.0f/std::sqrt(1.0f+tanThetaMSqr);
		float sinThetaM = std::sqrt(1.0f-cosThetaM*cosThetaM);
		float phiM = TWOPI*sample.y();
		Vector3f m(sinThetaM*std::cos(phiM),
					sinThetaM*std::sin(phiM),
					cosThetaM);//half vector, or microsurface normal
		if (m.z()*bRec.wi.z() < 0.0f) {//not on the same sphere
			m = -m;
		}
		float idotm = bRec.wi.dot(m);
		bRec.wo = 2.0f*idotm*m - bRec.wi;
		if (bRec.wo.z()<= 0.0f) {
			return Color3f(0.0f);//m_kd?
		}

		Color3f brdf = eval(bRec);
		float p = pdf(bRec);
		Color3f weight = brdf*Frame::cosTheta(bRec.wo)/p;
#if 0		
		float cosThetaI = Frame::cosTheta(bRec.wi);
		float reflectance = Fresnel(idotm, m_extIOR, m_intIOR);
		float g = G(bRec,m);
		float weightSpecular = reflectance*idotm*g/(cosThetaI*cosThetaM);
		Color3f weight = m_kd + m_ks*weightSpecular;
		if(weight.minCoeff()<=0.0f) {
			throw NoriException(QString("microfacet: m: %1, i: %2, idotm: %3, g: %4, r: %5")
				.arg(m.toString())
				.arg(bRec.wi.toString())
				.arg(idotm)
				.arg(g)
				.arg(reflectance));
		}
#endif
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
	mutable Random m_random;
	// eval Beckman distribution
	float evalNormal( const Vector3f& m) const{
		float cosThetaM = Frame::cosTheta(m);
		float alphaSqr = m_alpha*m_alpha;
		float exponent = -Frame::tanTheta2(m)/alphaSqr;
		float cosThetaM2 = cosThetaM*cosThetaM;
		float result = INV_PI*std::exp(exponent)/
			(alphaSqr*cosThetaM2*cosThetaM);
		return result;
	}

	float G( const BSDFQueryRecord& bRec, const Vector3f& m) const{
		const Vector3f& v = bRec.wo;
		float tanTheta = Frame::tanTheta(v);
		if ( tanTheta == 0.0f ) {
			return 1.0f;
		}
		if (v.dot(m)*Frame::cosTheta(v) <= 0.0f) {
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
#define NDEBUG
NORI_REGISTER_CLASS(Microfacet, "microfacet");
NORI_NAMESPACE_END
