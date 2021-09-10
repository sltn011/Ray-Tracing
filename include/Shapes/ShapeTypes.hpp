#ifndef RT_SHAPETYPES
#define RT_SHAPETYPES

#include <string>

enum class ShapeTypes {
    ST_Sphere,
    ST_MAX
};

class ShapeTypesUtils {
public:

    static std::string GetShapeTypeName(ShapeTypes Type);

};

#endif // RT_SHAPETYPES
