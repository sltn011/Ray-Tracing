#ifndef RT_SCREENQUAD
#define RT_SCREENQUAD

#include <cstdint>

class ScreenQuad {

    uint32_t m_VAO;
    uint32_t m_VBO;

public:

    ScreenQuad();

    ~ScreenQuad();

    void Render();

};

#endif // RT_SCREENQUAD
