#ifndef RT_SHAPE_BASESHAPE
#define RT_SHAPE_BASESHAPE

#include <cstdint>

class BaseShape {

public:

    BaseShape();

    int32_t GetID() const;

protected:

    int32_t m_ID;

private:

    static int32_t NextFreeID;

};

#endif