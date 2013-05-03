#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/texture.h>
#include <nori/luminaire.h>
#include <nori/random.h>

NORI_NAMESPACE_BEGIN


const int kSampleDepth = 3;
/**
 * \brief Path Tracing.
 */
class Path : public Integrator {
public:
	Path(const PropertyList &propList) {
		m_maxDepth = propList.getInteger("maxDepth", 13);
	}

	Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &r) const {
		/* Find the surface that is visible in the requested direction */
		Intersection its;
		Ray3f ray(r);
		if (!scene->rayIntersect(ray, its))
			return Color3f(0.0f);
		Color3f radiance(0.0f);
		
		bool specularBounce = false;
		Color3f pathThroughput(1.0f);
		for ( int bounces = 0; ; ++bounces ) {
			const Luminaire* luminaire = its.mesh->getLuminaire();
			if ((bounces == 0 || specularBounce) && luminaire != NULL) {
				Vector3f wo = (-ray.d).normalized();
				Color3f emission = luminaire->le(its.p, its.shFrame.n, wo);
				radiance += pathThroughput*emission;
			}
			const Texture* texture = its.mesh->getTexture();
			Color3f texel(1.0f);
			if ( texture ) {
				texel = texture->lookUp(its.uv.x(), its.uv.y());
			}
			const BSDF* bsdf = its.mesh->getBSDF();
			// sample illumination from lights, add to path contribution
			if (!bsdf->isSpecular()){
				radiance += pathThroughput*UniformSampleAllLights(scene, ray, its, sampler)*texel;
			}
			// sample bsdf to get new path direction
			BSDFQueryRecord bRec(its.toLocal((-ray.d)).normalized());
			Color3f f = bsdf->sample(bRec, sampler->next2D() );	
			if (f.isZero() ) { // farther path no contribution
				break;
			}
			specularBounce = bsdf->isSpecular();
			Vector3f d = its.toWorld(bRec.wo);
			f *= texel;
			pathThroughput *= f;
			ray = Ray3f(its.p, d );
			// possibly termination
			if (bounces > kSampleDepth) {
#if 0
				float continueProbability = std::min( 0.5f, pathThroughput.y() );
				if ( sampler->next1D() > continueProbability ) {
					break;
				}
#else
				float continueProbability = std::max(f.x(), 
					std::max(f.y(), f.z()));
				if ( sampler->next1D() > continueProbability ) {
					break;
				}
#endif
				pathThroughput /= continueProbability;
			}
			if (bounces == m_maxDepth) {
				break;
			}
			// find next vertex of path
			if ( !scene->rayIntersect(ray, its) ) {
				break;
			}
		}

		return radiance;
	}

	QString toString() const {
		return QString(
			"path[maxDepth=%1]").arg(m_maxDepth);
	}
private:
	int m_maxDepth;
};

NORI_REGISTER_CLASS(Path, "path");
typedef Path MiPath;
NORI_REGISTER_CLASS(MiPath, "mipath");
NORI_NAMESPACE_END
