#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/luminaire.h>

NORI_NAMESPACE_BEGIN

enum ELightStrategy { ESAMPLE_ALL, ESAMPLE_ONE };

/**
 * \brief Direct Lighting integrator.
 */
class DirectLight : public Integrator {
public:
	DirectLight(const PropertyList &propList) {
		QString strategy = propList.getString("sampleStrategy", "sampleAll");
		if ( strategy == "sampleOne" ) {
			m_strategy = ESAMPLE_ONE;
		} else {
			m_strategy = ESAMPLE_ALL;
		}
	}

	Color3f Li(const Scene *scene, Sampler *sampler, const Ray3f &ray) const {
		/* Find the surface that is visible in the requested direction */
		Intersection its;
		if (!scene->rayIntersect(ray, its))
			return Color3f(0.0f);
		Color3f radiance(0.0f);
		const Luminaire* luminaire = its.mesh->getLuminaire();
		// intersect light, count emission
		if (luminaire != NULL) {
			Vector3f wo = (-ray.d).normalized();
			radiance += luminaire->le(its.p, its.shFrame.n, wo);
		}
		const std::vector<const Luminaire*>& luminaires = scene->getLuminaires();
		if ( luminaires.size() > 0 ) {
			// apply direct light
			switch ( m_strategy ) {
			case ESAMPLE_ALL:
				radiance += UniformSampleAllLights(scene, ray, its, sampler);
				break;
			case ESAMPLE_ONE:
				throw NoriException("sample_one strategy is not implemented");
				break;
			default:
				throw NoriException("unknown light sampling strategy" );
			}
		}
		
		return radiance;
	}

	QString toString() const {
		return QString(
			"DirectLighting[\n"
			"  strategy = %1\n"
			"]").arg(m_strategy == ESAMPLE_ALL? "sampleAll":"sampleOne");
	}
private:
	const static int m_maxDepth = 10;
	ELightStrategy m_strategy;
};

NORI_REGISTER_CLASS(DirectLight, "directlight");
NORI_NAMESPACE_END
