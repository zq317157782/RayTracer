/*
 * light.cpp
 *
 *  Created on: 2016年7月11日
 *      Author: Administrator
 */
#include "point.h"
#include "montecarlo.h"
RGB PointLight::Sample_L(const Point &p, Float pEpsilon, const LightSample &ls,
		Vector3f *wi, Float *pdf, VisibilityTester *vis) const {
	*wi = Normalize(mPos - p); //标准化的点到光源的向量
	*pdf = 1.0f;
	vis->SetSegment(p, pEpsilon, mPos, 0.0f);
	return mIntensity / DistanceSqr(mPos, p);
}

bool PointLight::IsDeltaLight() const {
	return true;
}

RGB PointLight::Power(const Scene* scene) const {
	return 4 * Pi * mIntensity; //对点光源在整个球体立体角内求积分
}

RGB PointLight::Sample_L(const Scene *scene, const LightSample &ls, Float u1,
		Float u2, Ray *ray, Normal *Ns, Float *pdf) const {
	*ray = Ray(mPos, UniformSampleSphere(ls.uPos[0], ls.uPos[1]), 0.f,
			INFINITY);
	*Ns = (Normal)ray->d;
	*pdf = UniformSpherePdf();
	return mIntensity;
}
