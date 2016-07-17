/*
 * metal.cpp
 *
 *  Created on: 2016年7月15日
 *      Author: Administrator
 */

#include "metal.h"
#include <Scene.h>
#include "reflection.h"

Metal::Metal(const RGB& reflectance,const RGB& e, const RGB& kk,MicrofacetDistribution* dis){
	mFresnel=new FresnelConductor(e,kk);
	mBrdf=new Microfacet(reflectance,mFresnel,dis);
}


RGB Metal::shade(const Intersection &sr){
	Vector wo=-sr.ray.d;
    Point hitPoint=sr.ray(sr.distance);
    Vector wi;
    float pdf;
    VisibilityTester vt;
    RGB L(0,0,0);
    LightSample ls;
    unsigned long lignt_num=sr.scene.getLightNum();
    for(unsigned long i=0;i<lignt_num;++i){
        RGB l=sr.scene.getLight(i)->Sample_L(hitPoint,0,ls,&wi,&pdf,&vt);
        if(!vt.Unoccluded(&sr.scene)) continue;
        double ndotl=Dot(sr.normal,wi);
        if(ndotl>0){
        	//cout<<"brdf:"<<mBrdf->f(wi,wo).r<<"brdf:"<<mBrdf->f(wi,wo).g<<"brdf:"<<mBrdf->f(wi,wo).b<<endl;
            L=L+l*mBrdf->f(wi,wo)*ndotl;  //mDiffuseBrdf.f(sr,wi,wo)
        }
    }
    return L;
}

RGB Metal::areaLightShade(Intersection &sr) {
    return RGB(0,0,0);
}