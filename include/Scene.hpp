#ifndef RT_SCENE
#define RT_SCENE

#include "Camera.hpp"
#include "Shapes/ShapeTypes.hpp"

#include <memory>
#include <unordered_map>
#include <vector>


class BaseShape;
class Shader;


class Scene {

public:

    Scene(Camera SceneCamera);

    std::vector<std::unique_ptr<BaseShape>> &GetShapes(ShapeTypes Type);

    void LoadInShader(Shader &ShaderProgramm);

    Camera m_Camera;

protected:

    std::unordered_map<ShapeTypes, std::vector<std::unique_ptr<BaseShape>>> m_SceneObjects;

};

#endif // RT_SCENE
