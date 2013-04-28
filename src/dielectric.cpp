#include <nori/bsdf.h>
#include <nori/frame.h>
#include <nori/random.h>

NORI_NAMESPACE_BEGIN
float FrDiel(float cosi, float cost, const float &etai,
                const float &etat) {
    float Rparl = ((etat * cosi) - (etai * cost)) /
                     ((etat * cosi) + (etai * cost));
    float Rperp = ((etai * cosi) - (etat * cost)) /
                     ((etai * cosi) + (etat * cost));
    return (Rparl*Rparl + Rperp*Rperp) / 2.f;
}

float Evaluate(float cosi, float intIOR, float extIOR) {
    // Compute Fresnel reflectance for dielectric
    cosi = clamp(cosi, -1.f, 1.f);

    // Compute indices of refraction for dielectric
    bool entering = cosi > 0.;
    float ei = intIOR, et = extIOR;
    if (!entering)
        std::swap(ei, et);

    // Compute _sint_ using Snell's law
    float sint = ei/et * sqrtf(std::max(0.f, 1.f - cosi*cosi));
    if (sint >= 1.0f) {
        // Handle total internal reflection
        return 1.0f;
    }
    else {
        float cost = std::sqrt(std::max(0.f, 1.f - sint*sint));
        return FrDiel(fabsf(cosi), cost, ei, et);
    }
}
/**
 * \brief Specular reflection and transmission for dielectric material
 */
class Dielectric : public BSDF {
public:
	Dielectric(const PropertyList &propList) {
		/* Interior IOR (default: BK7 borosilicate optical glass) */
		m_intIOR = propList.getFloat("intIOR", 1.5046f);

		/* Exterior IOR (default: air) */
		m_extIOR = propList.getFloat("extIOR", 1.000277f);
	}

	/// Evaluate the BRDF model
	Color3f eval(const BSDFQueryRecord &bRec) const {
		return Color3f(0.0f);
	}

	/// Compute the density of \ref sample() wrt. solid angles
	float pdf(const BSDFQueryRecord &bRec) const {
		return 0.0f;
	}

	/// Draw a a sample from the BRDF model
	float sampleReflection(BSDFQueryRecord &bRec, const float f) const {
		// compute perfect specular reflection direction
		bRec.wo = Vector3f(-bRec.wi.x(), -bRec.wi.y(), bRec.wi.z());
		return f;
	}

	/// Draw a a sample from the BRDF model
	float sampleRefraction(BSDFQueryRecord &bRec, float f) const {
		bool entering = Frame::cosTheta(bRec.wi) > 0.0f;
		float ei = m_extIOR, et = m_intIOR;
		if (!entering) {
			std::swap(ei, et);
		}

		// compute transmitted ray direction using snell's law
		float sini2 = Frame::sinTheta2(bRec.wi);
		float eta = ei/et;
		float sint2 = eta*eta*sini2;
		
		// handle total internal reflection for transmission
		if ( sint2 >= 1.0f ) {
			return 0.0f;
		}
		float cost = std::sqrt(std::max(0.0f, 1.0f - sint2));
		if (entering) {
			cost = -cost;
		}
		float sintOverSini = eta;
		bRec.wo = Vector3f(
			sintOverSini*-bRec.wi.x(), 
			sintOverSini*-bRec.wi.y(), 
			cost);
		float inveta = et/ei;
		return (1.0f-f)*inveta*inveta;
	}
	Color3f sample(BSDFQueryRecord &bRec, const Point2f &sample)const{
		float reflectance = Evaluate(Frame::cosTheta(bRec.wi), m_extIOR, m_intIOR);
		float rp = 0.25f + 0.5f*reflectance;
		float result;
		if (sample.x() < rp) {
			result = sampleReflection(bRec, reflectance);
			result/=rp;
		} else {
			result = sampleRefraction(bRec, reflectance);
			result/=(1-rp);
		}
		return Color3f(result);
	}
	/// Return a human-readable summary
	QString toString() const {
		return QString(
			"Diffuse[\n"
			"  intIOR = %1\n"
			"  extIOR = %2\n"
			"]")
			.arg(m_intIOR)
			.arg(m_extIOR);
	}

	float isSpecular() const { return true; }
	EClassType getClassType() const { return EBSDF; }
private:
	float m_intIOR, m_extIOR;
};

NORI_REGISTER_CLASS(Dielectric, "dielectric");
NORI_NAMESPACE_END
