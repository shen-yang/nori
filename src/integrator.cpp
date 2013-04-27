#include <nori/integrator.h>
#include <nori/sampler.h>
#include <nori/scene.h>
#include <nori/bsdf.h>
#include <nori/luminaire.h>
NORI_NAMESPACE_BEGIN

struct VisibilityTester {
	void SetSegment( const Point3f& p1, float eps1,
					 const Point3f& p2, float eps2 
					) {
		float dist = (p1 - p2).norm();
		ray = Ray3f(p1, (p2-p1)/dist, eps1, dist*(1-eps2) );
	}
	bool Unoccluded( const Scene* scene ) const {
		return !scene->rayIntersect(ray);
	}
	Ray3f ray;
};

inline float PowerHeuristic(int nf, float fPdf, int ng, float gPdf) {
    float f = nf * fPdf, g = ng * gPdf;
    return (f*f) / (f*f + g*g);
}



Color3f EstimateDirect( 
	const Scene* scene,
	const Luminaire* luminaire,
	const Ray3f& ray,
	const Intersection& its,
	const Point2f& lightSample, 
	const Point2f& bsdfSample ) {
	
	Point3f poslighted = its.p;
	Vector3f posNormal = its.shFrame.n;
	Color3f ld(0.0f);
	Point3f lightpos;
	Normal3f lightnormal;
	Vector3f wi;
	
	const BSDF* bsdf = its.mesh->getBSDF();
	// multiple importance sample light source
	luminaire->sample_L(poslighted, lightSample, &lightpos, &lightnormal, &wi );
	float lightpdf = luminaire->pdf(poslighted, wi, lightpos, lightnormal);
	if ( lightpdf > 0.0f ) {
		VisibilityTester vis;
		vis.SetSegment(poslighted, 1e-4f, lightpos, 1e-4f);
		if ( vis.Unoccluded(scene) ) {
			Color3f e = luminaire->le( lightpos, lightnormal, -wi );
			if ( !e.isZero() ) {
				Vector3f wolocal = its.toLocal(-ray.d).normalized();
				Vector3f wilocal = its.toLocal(wi).normalized();
				BSDFQueryRecord bRec(wilocal, wolocal, ESolidAngle);
				Color3f f = bsdf->eval(bRec);
				float bsdfpdf = bsdf->pdf( bRec );
				float weight = PowerHeuristic( 1, lightpdf, 1, bsdfpdf );
#ifdef NO_MIS
				ld = f * e * ( fabs(wi.dot(posNormal) )/lightpdf );
#else
				ld += f * e * ( fabs(wi.dot(posNormal) )*weight/lightpdf );
#endif
			}
		}
	}
#ifndef NO_MIS
	// multiple importance sample BSDF
	Vector3f wo = its.toLocal(-ray.d).normalized();
	BSDFQueryRecord bsdfRec(wo);
	Color3f w = bsdf->sample(bsdfRec, bsdfSample);
	Color3f li(0.0f);
	if ( !w.isZero() ) {
		Ray3f ray2( poslighted, its.toWorld(bsdfRec.wo) );
		Intersection lightIts;
		if ( scene->rayIntersect(ray2, lightIts) ){
			if (lightIts.mesh == luminaire->getMesh()) {
				li = luminaire->le( lightIts.p, lightIts.shFrame.n, (-ray2.d).normalized() );
				float bsdfpdf = bsdf->pdf(bsdfRec);
				float lightpdf = luminaire->pdf(
												poslighted, 
												ray2.d, 
												lightIts.p, 
												lightIts.shFrame.n
												);
				float weight = PowerHeuristic(1, bsdfpdf, 1, lightpdf);
				ld += w*li*weight;
			}
		}
	}
#endif
	return ld;
}

Color3f UniformSampleAllLights( 
		const Scene* scene,
		const Ray3f& ray,
		const Intersection& its, 
		Sampler* sampler ) {
	Color3f radiance(0.0f);
	const std::vector<const Luminaire*>& luminaires = scene->getLuminaires();
	for ( uint32_t i = 0; i < luminaires.size(); ++i ) {
		const Luminaire* luminaire = luminaires[i];
		int numSamples = luminaire->getSampleCount();
		Color3f ld(0.0f);
		for ( int j = 0; j < numSamples; ++j ) {
			Point2f lightSample = sampler->next2D();
			Point2f bsdfSample = sampler->next2D();
			ld += EstimateDirect( scene, luminaire, ray, its, lightSample, bsdfSample );
		}
		radiance += ld/numSamples;
	}
	return radiance;
}

NORI_NAMESPACE_END