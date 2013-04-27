#if !defined(__LUMINAIRE_H)
#define __LUMINAIRE_H

#include <nori/object.h>

NORI_NAMESPACE_BEGIN
class Luminaire : public NoriObject {
public:
	virtual void setMesh( const Mesh* mesh){m_mesh = mesh;}
	virtual const Mesh* getMesh() const {return m_mesh;}
	virtual void sample_L(
				const Point3f& poslighted, 
				const Point2f &sample, 
				Point3f* lightpos, 
				Normal3f* normal, 
				Vector3f* wi) const = 0;

	virtual Color3f le(
		const Point3f& lightpos, 
		const Vector3f& normal, 
		const Vector3f& wo
		) const = 0;

	virtual float pdf(
			const Point3f& poslighted, 
			const Vector3f& wi, 
			const Point3f& lightpos, 
			const Normal3f& normal) const = 0;
	/// delta distribution, for specular reflection and refraction
	virtual bool isDelta() const {return false;}
	EClassType getClassType() const { return ELuminaire; }
	
	int getSampleCount() const {return m_sampleCount;}
protected:
	const Mesh* m_mesh;
	int m_sampleCount;
};
NORI_NAMESPACE_END
#endif