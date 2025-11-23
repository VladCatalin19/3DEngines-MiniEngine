#ifndef M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED
#define M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED

#include <Graphics/Material.hpp>
#include <Graphics/SubMesh.hpp>
#include <Math/Vector2.hpp>
#include <Math/Vector3.hpp>
#include <Serialisation/ISerialisable.hpp>

#include <string>
#include <vector>

namespace MG3TR
{
    class Mesh : public ISerialisable
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

        virtual ~Mesh() = default;

        Mesh(const Mesh &);
        Mesh(Mesh &&) = default;
        
        Mesh& operator=(const Mesh &);
        Mesh& operator=(Mesh &&);

        const std::vector<SubMesh>& GetSubmeshes() const;
        const std::vector<Material>& GetMaterials() const;

        virtual void Serialise(ISerialiser &serialiser) override;
        virtual void Deserialise(IDeserialiser &deserialiser) override;

    private:
        void Construct(const std::vector<Vector3> &vertices,
                       const std::vector<Vector3> &normals,
                       const std::vector<Vector2> &uvs,
                       const std::vector<std::uint32_t> &indices);

        void Construct(const std::string &path_to_file);
    };
}

#endif // M3GTR_SRC_GRAPHICS_MESH_HPP_INCLUDED
