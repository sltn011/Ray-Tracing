#ifndef RT_WINDOWMANAGER
#define RT_WINDOWMANAGER

#include <cstdint>
#include <string>

struct GLFWwindow;
class Shader;

class WindowManager {

public:

    WindowManager(int32_t Width, int32_t Height, int32_t Samples = 1);

    ~WindowManager();

    bool IsWindowOpen();

    GLFWwindow *GetWindow() const;

    void Render(Shader &ShaderProgramm);

    void SaveImagePNG(std::string const &FilePath);

private:

    void CleanUp();

    void ResizeCallback(int32_t NewWidth, int32_t NewHeight);

    GLFWwindow *m_Window;

    int32_t m_NumSamples;

};

#endif // RT_WINDOWMANAGER
