#include <nori/luminaire.h>
#include <nori/mesh.h>
NORI_NAMESPACE_BEGIN
class DiffuseAreaLight: public Luminaire {
public:
	DiffuseAreaLight(const PropertyList &propList) {
		m_radiance = propList.getColor("radiance", Color3f(1.0f));
		m_sampleCount = propList.getInteger("sampleCount", 1 );
	}
	void sample_L(
				const Point3f& poslighted, 
				const Point2f &sample, 
				Point3f* lightpos, 
				Normal3f* normal, 
				Vector3f* wi) const;
	Color3f le(
			const Point3f& lightpos, 
			const Vector3f& normal, 
			const Vector3f& wo) const;
	float pdf(
			const Point3f& poslighted, 
			const Vector3f& wi, 
			const Point3f& lightpos, 
			const Normal3f& normal) const;
	QString toString() const {
		return QString(
			"area[\n"
			"  radiance = %1\n"
			"]").arg(m_radiance.toString());
	}
private:
	Color3f m_radiance;
};

void DiffuseAreaLight::sample_L(
			const Point3f& poslighted,
			const Point2f& sample, 
			Point3f* lightpos,
			Normal3f* normal,
			Vector3f* wi
			) const {
	m_mesh->samplePosition( sample, *lightpos, *normal );
	*wi = (*lightpos - poslighted).normalized();
}
// called after ray intersection test
float DiffuseAreaLight::pdf(
			const Point3f& poslighted, 
			const Vector3f& wi, 
			const Point3f& lightpos, 
			const Normal3f& normal) const {
	// convert to solid angle measure
	Vector3f dir = poslighted - lightpos;
	float pdf = dir.squaredNorm()/(normal.dot(-wi)*m_mesh->surfaceArea() );
	return fabs(pdf);
}

Color3f DiffuseAreaLight::le(
			const Point3f& lightpos, 
			const Vector3f& normal, 
			const Vector3f& wo
			) const {
	return normal.dot(wo) > 0.0f? m_radiance: Color3f(0.0f);
}

NORI_REGISTER_CLASS(DiffuseAreaLight, "area");

NORI_NAMESPACE_END