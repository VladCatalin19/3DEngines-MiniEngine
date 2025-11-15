#include "Mesh.hpp"

#include <Constants/GraphicsConstants.hpp>
#include <Constants/JSONConstants.hpp>
#include <Math/Matrix4x4.hpp>

#include <Utils/ExceptionWithStacktrace.hpp>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/vector3.h>

#include <iostream>
#include <format>
#include <memory>
#include <vector>

static Assimp::Importer s_importer;

static const aiScene* ReadAssimpSceneFromFile(const std::string &path_to_file)
{
    const unsigned flags = aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_Triangulate;
    const aiScene* const scene = s_importer.ReadFile(path_to_file, flags);

    if (scene == nullptr)
    {
        const std::string error = std::format("Could not read mesh from \"{}\": {}", path_to_file, s_importer.GetErrorString());
        throw MG3TR::ExceptionWithStacktrace(error);
    }
    return scene;
}

static auto ConvertAssimpVerticesToMeshVertices(const aiMesh &mesh)
{
    const std::size_t vertices_count = mesh.mNumVertices;
    std::vector<MG3TR::Vector3> vertices;
    vertices.reserve(vertices_count);

    for (unsigned vertex_index = 0; vertex_index < vertices_count; ++vertex_index)
    {
        const aiVector3D &vertex_position = mesh.mVertices[vertex_index];
        const MG3TR::Vector3 vertex(vertex_position.x, vertex_position.y, vertex_position.z);

        vertices.push_back(vertex);
    }

    return vertices;
}

static auto ConvertAssimpNormalsToMeshNormals(const aiMesh &mesh)
{
    std::vector<MG3TR::Vector3> normals;
    const bool has_normals = mesh.HasNormals();

    if (has_normals)
    {
        const std::size_t vertices_count = mesh.mNumVertices;
        normals.reserve(vertices_count);

        for (unsigned vertex_index = 0; vertex_index < vertices_count; ++vertex_index)
        {
            const aiVector3D &vertex_normal = mesh.mNormals[vertex_index];
            const MG3TR::Vector3 normal(vertex_normal.x, vertex_normal.y, vertex_normal.z);

            normals.push_back(normal);
        }
    }

    return normals;
}

static auto ConvertAssimpUVCoordinatesToMeshUVCoordinates(const aiMesh &mesh)
{
    std::vector<MG3TR::Vector2> uvs;
    const bool has_texture_coordonates = mesh.HasTextureCoords(0);
    
    if (has_texture_coordonates)
    {
        const std::size_t vertices_count = mesh.mNumVertices;
        uvs.reserve(vertices_count);
    
        for (unsigned vertex_index = 0; vertex_index < vertices_count; ++vertex_index)
        {
            const aiVector3D &vertex_uv = mesh.mTextureCoords[0][vertex_index];
            const MG3TR::Vector2 uv(vertex_uv.x, vertex_uv.y);

            uvs.push_back(uv);
        }
    }

    return uvs;
}

static auto ConvertAssimpFacesToMeshTriangleIndices(const aiMesh &mesh)
{
    const std::size_t faces_number = mesh.mNumFaces;
    std::vector<unsigned> indices;

    indices.reserve(faces_number * 3);

    for (unsigned face_index = 0; face_index < faces_number; ++face_index)
    {
        const aiFace &face = mesh.mFaces[face_index];
        const std::size_t face_indices = face.mNumIndices;

        switch (face_indices)
        {
            case 3:
            case 4:
            {
                for (unsigned index = 0; index < face_indices; ++index)
                {
                    const unsigned vertex_index = face.mIndices[index];

                    indices.push_back(vertex_index);
                }
                break;
            }
            default:
            {
                std::cout << "Warning: Will not parse face with " << face.mNumIndices << " indices." << std::endl;
            }
        }
    }

    return indices;
}

static auto ConvertAssimpMaterialsToMeshMaterials(const aiScene &scene)
{
    const bool has_materials = scene.HasMaterials();
    std::vector<MG3TR::Material> materials;

    if (has_materials)
    {
        const std::size_t material_count = scene.mNumMaterials;

        materials.reserve(material_count);
    
        for (unsigned material_index = 0; material_index < material_count; ++material_index)
        {
            const aiMaterial * const assimp_material = scene.mMaterials[material_index];
            const unsigned texture_count = assimp_material->GetTextureCount(aiTextureType_DIFFUSE);

            if (texture_count > 0)
            {
                MG3TR::Material material;
    
                aiString path;
                aiReturn return_code = assimp_material->GetTexture(aiTextureType_DIFFUSE, 0, &path);
                if (return_code != AI_SUCCESS)
                {
                    throw MG3TR::ExceptionWithStacktrace("Could not get difuse texture.");
                }
    
                std::string absolute_path = std::format("{}{}", MG3TR_ROOT_DIR, path.C_Str());
                material.m_diffuse_texture = std::make_shared<MG3TR::Texture>(absolute_path);
    
                materials.push_back(material);
            }
        }

    }

    return materials;
}

namespace MG3TR
{
    Mesh::Mesh(const std::vector<Vector3> &vertices,
               const std::vector<Vector3> &normals,
               const std::vector<Vector2> &uvs,
               const std::vector<unsigned> &indices)
    {
        Construct(vertices, normals, uvs, indices);
    }
    
    Mesh::Mesh(const std::string &path_to_file)
    {
        Construct(path_to_file);
    }

    Mesh::Mesh(const Mesh &other)
        : m_submeshes(other.m_submeshes),
          m_materials(other.m_materials),
          m_path_to_file(other.m_path_to_file)
    {

    }

    Mesh& Mesh::operator=(const Mesh &other)
    {
        m_submeshes = other.m_submeshes;
        m_path_to_file = other.m_path_to_file;
        m_materials = other.m_materials;

        return *this;
    }

    Mesh& Mesh::operator=(Mesh &&other)
    {
        m_submeshes = std::move(other.m_submeshes);
        m_path_to_file = std::move(other.m_path_to_file);
        m_materials = std::move(other.m_materials);

        return *this;
    }

    const std::vector<SubMesh>& Mesh::GetSubmeshes() const
    {
        return m_submeshes;
    }

    const std::vector<Material>& Mesh::GetMaterials() const
    {
        return m_materials;
    }
    
    nlohmann::json Mesh::Serialize() const
    {
        namespace Constants = MeshJSONConstants;

        nlohmann::json json;

        if (!m_path_to_file.empty())
        {
            json[Constants::k_parent_node][Constants::k_path_to_file_attribute] = m_path_to_file;
        }
        else
        {
            throw ExceptionWithStacktrace("Cannot serialize mesh not read from file.");
        }

        return json;
    }
    
    void Mesh::Deserialize(const nlohmann::json &json)
    {
        namespace Constants = MeshJSONConstants;

        if (json.at(Constants::k_parent_node).contains(Constants::k_path_to_file_attribute))
        {
            std::string path = json[Constants::k_parent_node][Constants::k_path_to_file_attribute];
            Construct(path);
        }
    }
    
    void Mesh::LateBindAfterDeserialization([[maybe_unused]] Scene &scene) 
    {
        
    }
    
    void Mesh::Construct(const std::vector<Vector3> &vertices,
                         const std::vector<Vector3> &normals,
                         const std::vector<Vector2> &uvs,
                         const std::vector<std::uint32_t> &indices)
    {
        m_path_to_file = "";

        const bool has_vertices = !vertices.empty();
        const bool has_indices = !indices.empty();

        if (has_vertices && has_indices)
        {
            SubMesh submesh(vertices, normals, uvs, indices);

            m_submeshes.push_back(std::move(submesh));
        }
    }
    
    void Mesh::Construct(const std::string &path_to_file)
    {
        m_path_to_file = path_to_file;

        const aiScene* const scene = ReadAssimpSceneFromFile(path_to_file);
        const unsigned meshes_count = scene->mNumMeshes;

        m_submeshes.reserve(meshes_count);

        for (unsigned mesh_index = 0; mesh_index < meshes_count; ++mesh_index)
        {
            const aiMesh * const mesh = scene->mMeshes[mesh_index];

            auto vertices = ConvertAssimpVerticesToMeshVertices(*mesh);
            auto normals = ConvertAssimpNormalsToMeshNormals(*mesh);
            auto uvs = ConvertAssimpUVCoordinatesToMeshUVCoordinates(*mesh);
            auto indices = ConvertAssimpFacesToMeshTriangleIndices(*mesh);
            SubMesh submesh(std::move(vertices), std::move(normals), std::move(uvs), std::move(indices));

            m_submeshes.push_back(std::move(submesh));
        }

        m_materials = ConvertAssimpMaterialsToMeshMaterials(*scene);
    }
}
