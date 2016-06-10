//
// Created by 诸谦 on 15/12/28.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H



#include "../scene/Scene.h"
#include "../sampler/Sampler.h"
#include "../common/Film.h"
#include <memory>
class Camera {
protected:
    Point mEye;
    Point mLookAt;
    Vector mUp;

    Vector u,v,w;//本地坐标系
    float mExposureTime;

    //计算本地坐标
    void computeUVW();

    Sampler* mSampler;
public:
    Camera(const Point & eye= Point(0, 0, 0), const Point & lookAt= Point(0, 0, -1), const Vector & up= Vector(0, 1, 0), const float exposureTime=1);
    /*渲染场景*/
    virtual void renderScene(const Scene&, Film &)=0;

    void setSampler(Sampler* sampler);
};


#endif //RAYTRACER_CAMERA_H
