#include "mesh.h"

#include "../logging.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <optional>

namespace bolt {
    [[nodiscard]] std::optional<Mesh> assimp_load(std::filesystem::path const &path) {
        Assimp::Importer importer;

        const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

        if (!scene) {
            LOG_ERROR("Error parsing '%s': '%s'\n", path.c_str(), importer.GetErrorString());
            return std::nullopt;
        }

        LOG_INFO("Found %lu meshes", scene->mNumMeshes);

        if (scene->mNumMeshes <= 0) {
            return std::nullopt;
        }

        Mesh mesh;
        aiVector3D const Zero3D(0.0f, 0.0f, 0.0f);
        size_t offset = 0; 
        for (unsigned int j = 0; j < scene->mNumMeshes; j++) {

            aiMesh const *paiMesh = scene->mMeshes[j];

            for (unsigned int i = 0 ; i < paiMesh->mNumVertices ; i++) {
                Vertex v;

                aiVector3D const *pPos      = &(paiMesh->mVertices[i]);
                aiVector3D const *pNormal   = &(paiMesh->mNormals[i]);
                aiVector3D const *pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;

                v.m_position = glm::vec3(pPos->x, pPos->y, pPos->z);
                v.m_normal   = glm::vec3(pNormal->x, pNormal->y, pNormal->z);
                v.m_texture  = glm::vec2(pTexCoord->x, pTexCoord->y);

                mesh.m_vertices.push_back(v);
            }

            for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++) {
                aiFace const &face = paiMesh->mFaces[i];

                mesh.m_indices.push_back(offset + face.mIndices[0]);
                mesh.m_indices.push_back(offset + face.mIndices[1]);
                mesh.m_indices.push_back(offset + face.mIndices[2]);
            }

            offset = mesh.m_vertices.size();
        }

        LOG_INFO("Found %lu vertices", mesh.m_vertices.size());

        return std::make_optional(std::move(mesh));
    }
}
