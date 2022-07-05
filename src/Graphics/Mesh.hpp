#ifndef M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED
#define M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED

#include <Graphics/Material.hpp>
#include <Graphics/SubMesh.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Scene/IJsonSerializeable.hpp>

#include <string>               // std::string
#include <vector>               // std::vector

namespace MG3TR
{
    class Mesh : public IJsonSerializeable
    {
    private:
        std::vector<SubMesh> m_submeshes;
        std::vector<Material> m_materials;

        std::string m_path_to_file;

    public:
        Mesh(const std::vector<Vector3> &vertices = {},
             const std::vector<Vector3> &normals = {},
             const std::vector<Vector2> &uvs = {},
             const std::vector<std::uint32_t> &indices = {});

        Mesh(const std::string &path_to_file);

        virtual ~Mesh() noexcept = default;

        Mesh(const Mesh &);
        Mesh& operator=(const Mesh &);

        Mesh(Mesh &&) noexcept = default;
        Mesh& operator=(Mesh &&);

        const std::vector<SubMesh>& GetSubmeshes() const noexcept { return m_submeshes; }
        const std::vector<Material>& GetMaterials() const noexcept { return m_materials; }

        virtual nlohmann::json Serialize() const override;
        virtual void Deserialize(const nlohmann::json &json) override;
        virtual void LateBindAfterDeserialization(Scene &scene) override;

    private:
        void Construct(const std::vector<Vector3> &vertices,
                       const std::vector<Vector3> &normals,
                       const std::vector<Vector2> &uvs,
                       const std::vector<std::uint32_t> &indices);

        void Construct(const std::string &path_to_file);
    };
}

#endif // M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED
