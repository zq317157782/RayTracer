//
// Created by 诸谦 on 15/12/28.
//

#include "Shape.h"
#include "transform.h"

Shape::Shape(Transform *o2w,Transform *w2o,bool ro, bool mShadow)
        : localToWorld(o2w),worldToLocal(w2o),ReverseOrientation(ro),TransformSwapsHandedness(o2w->SwapsHandedness()), mShadow(mShadow),shapeID(nextShapeID++) { }


bool Shape::castShadow() const{
    return mShadow;
}

void Shape::setCastShadow(bool s) {
    mShadow=s;
}

unsigned int Shape::nextShapeID=0;
