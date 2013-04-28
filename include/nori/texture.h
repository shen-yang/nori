#ifndef __TEXTURE_H
#define __TEXTURE_H
#include <nori/object.h>


NORI_NAMESPACE_BEGIN

class Texture: public NoriObject {
public:
	Color3f lookUp(float u, float v) const;
	EClassType getClassType() const { return ETEXTURE; }
};
NORI_NAMESPACE_END

#endif