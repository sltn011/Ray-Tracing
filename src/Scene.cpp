#include "Scene.hpp"

#include "Shader.hpp"
#include "Shapes/BaseShape.hpp"

Scene::Scene(Camera SceneCamera) {
    m_Camera = SceneCamera;
}

std::vector<std::unique_ptr<BaseShape>> &Scene::GetShapes(ShapeTypes Type) {
    return m_SceneObjects[Type];
}

void Scene::LoadInShader(Shader &ShaderProgramm) {

    ShaderProgramm.use();

    m_Camera.LoadInShader(ShaderProgramm);

    for (auto &p : m_SceneObjects) {
        std::string UValueName = std::string{ "U" } + ShapeTypesUtils::GetShapeTypeName(p.first) + std::string{ "Num" };
        ShaderProgramm.setUniformInt(UValueName, static_cast<int32_t>(p.second.size()));
        for (size_t i = 0; i < p.second.size(); ++i) {
            p.second[i]->LoadInShader(ShaderProgramm, i);
        }
    }
}
