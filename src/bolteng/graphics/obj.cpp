#include "mesh.h"
#include "../logging.h"

#include <algorithm>
#include <fstream>
#include <glm/glm.hpp>
#include <map>
#include <iostream>
#include <string_view>
#include <vector>

using namespace bolt::status;

// vertex data
static uint64_t const GEOMETRIC_VERTEX         = 0x0000000000000076; // v
static uint64_t const TEXTURE_VERTEX           = 0x0000000000007476; // vt
static uint64_t const VERTEX_NORMAL            = 0x0000000000006E76; // vn
static uint64_t const PARAMETER_SPACE_VERTEX   = 0x0000000000007076; // vp
static uint64_t const CURVE_OR_SURFACE         = 0x0000657079747363; // cstype
static uint64_t const DEGREE                   = 0x0000000000676564; // deg
static uint64_t const BASIS_MATRIX             = 0x0000000074616D62; // bmat
static uint64_t const STEP_SIZE                = 0x0000000070657473; // step
// elements
static uint64_t const POINT                    = 0x0000000000000070; // p
static uint64_t const LINE                     = 0x000000000000006C; // l 
static uint64_t const FACE                     = 0x0000000000000066; // f
static uint64_t const CURVE                    = 0x0000000076727563; // curv
static uint64_t const CURVE_2D                 = 0x0000003276727563; // curv2
static uint64_t const SURFACE                  = 0x0000000066727573; // surf
// free-form curve/surface body statements
static uint64_t const PARAMETER_VALUES         = 0x0000006D61726170; // param
static uint64_t const OUTER_TRIMMING_LOOP      = 0x000000006D697274; // trim
static uint64_t const INNER_TRIMMING_LOOP      = 0x00000000656C6F68; // hole
static uint64_t const SPECIAL_CURVE            = 0x0000000076726373; // scrv
static uint64_t const SPECIAL_POINT            = 0x0000000000007073; // sp
static uint64_t const END_STATEMENT            = 0x0000000000646E65; // end
// connectivity between free-form surfaces
static uint64_t const CONNECT                  = 0x00000000006E6F63; // con
// grouping
static uint64_t const GROUP_NAME               = 0x0000000000000067; // g
static uint64_t const SMOOTHING_GROUP          = 0x0000000000000073; // s
static uint64_t const MERGING_GROUP            = 0x000000000000676D; // mg
static uint64_t const OBJECT_NAME              = 0x000000000000006F; // o
// display/render attributes
static uint64_t const BEVEL_INTERPOLATION      = 0x0000006C65766562; // bevel
static uint64_t const COLOR_INTERPOLATION      = 0x707265746E695F63; // c_interp
static uint64_t const DISSOLVE_INTERPOLATION   = 0x707265746E695F64; // d_interp
static uint64_t const LEVEL_OF_DETAIL          = 0x0000000000646F6C; // lod
static uint64_t const MATERIAL_NAME            = 0x00006C746D657375; // usemtl
static uint64_t const MATERIAL_LIBRARY         = 0x000062696C6C746D; // mtllib
static uint64_t const SHADOW_CASTING           = 0x6F5F776F64616873; // shadow_obj
static uint64_t const RAY_TRACING              = 0x626F5F6563617274; // trace_obj
static uint64_t const CURVE_APPROX_TECHNIQUE   = 0x0000006863657463; // ctech
static uint64_t const SURFACE_APPROX_TECHNIQUE = 0x0000006863657473; // stech
// mtl file characteristics:
static uint64_t const NEW_MATERIAL   = 0x00006C746D77656E; // newmtl
static uint64_t const AMBIENT_COLOR  = 0x000000000000614B; // Ka
static uint64_t const DIFFUSE_COLOR  = 0x000000000000644B; // Kd
static uint64_t const SPECULAR_COLOR = 0x000000000000734B; // Ks
static uint64_t const ALPHA          = 0x0000000000000064; // d
static uint64_t const TRANSPARENCY   = 0x0000000000007254; // Tr
static uint64_t const SHININESS      = 0x0000000000000073; // s
static uint64_t const ILLUMINATION   = 0x000000000000006E; // n 
static uint64_t const MAP_KA         = 0x0000614B5F70616D; // map_Ka

struct FaceVertex {
    int32_t v, vt, vn;
    FaceVertex() : v(0), vt(0), vn(0) {}
    friend std::ostream& operator<<(std::ostream &os, FaceVertex const &fv);
};

struct Face {
    std::vector<FaceVertex> vertices;
    friend std::ostream& operator<<(std::ostream &os, Face const &f);
};

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float alpha;
    float shininess;
    int illum;
    void clear() {
        ambient.r = ambient.g = ambient.b = 0.0;
        diffuse.r = diffuse.g = diffuse.b = 0.0;
        specular.r = specular.g = specular.b = 0.0;
        alpha     = 0.0;
        shininess = 0.0;
        illum     = 0.0;
    }
};

struct Group {
    std::vector<glm::vec4> vertices;
    std::vector<glm::vec3> textures;
    std::vector<glm::vec3> normals;
    std::vector<Face> faces;

    void clear() {
        vertices.clear();
        textures.clear();
        normals.clear();
        faces.clear();
    }
};

struct ObjLoader {
    std::map<std::string, Group> groups;
    std::map<std::string, Material> materials;

    [[nodiscard]] Status load_material(std::filesystem::path const &path) {
        std::string material_name;
        Material material;

        std::ifstream in(path);

        if (!in.is_open()) {
            LOG_ERROR("Failed to open file '%s'", path);
            return FILE_NOT_FOUND;
        }

        for (std::string line; std::getline(in, line); /* update in check */) {
            // clear out any characters that are parts of comment or windows line feed
            size_t comment_pos = line.find_first_of("#\r");
            if (comment_pos != std::string::npos) {
                line.resize(comment_pos);
            }
            
            // check if the line is blank
            if (line.size() > 0) {
                char typebuf[8] = {0};
                std::stringstream ss(line);
                std::string typestr;
                ss >> typestr;
                
                typestr.copy(typebuf, std::min(typestr.size(), 8ul));
                uint64_t typeint = *((uint64_t *) typebuf);
                switch (typeint) {
                    case NEW_MATERIAL:
                        if (!material_name.empty()) {
                            materials.insert({material_name, material});
                            material.clear();
                            material_name.clear();
                        }
                        ss >> material_name;
                        break;
                    case AMBIENT_COLOR: 
                        ss >> material.ambient.r >> material.ambient.g >> material.ambient.b;
                        break;
                    case DIFFUSE_COLOR:
                        ss >> material.diffuse.r >> material.diffuse.g >> material.diffuse.b;
                        break;
                    case SPECULAR_COLOR:
                        ss >> material.specular.r >> material.specular.g >> material.specular.b;
                        break;
                    case ALPHA:
                        ss >> material.alpha;
                        break;
                    case TRANSPARENCY:
                        ss >> material.alpha;
                        material.alpha = 1.0 - material.alpha;
                        break;
                    case SHININESS:
                        ss >> material.shininess;
                        break;
                    case ILLUMINATION:
                        ss >> material.illum;
                        break;
                    case MAP_KA:
                        LOG_WARN("MAP_KA unsupported");
                        break;
                }
            }
        }

        in.close();

        return SUCCESS;
    }

    [[nodiscard]] Status load_mesh(std::filesystem::path const &path) {
        std::string group_name;
        Group group;

        std::ifstream in(path);

        if (!in.is_open()) {
            LOG_ERROR("Failed to open file '%s'", path);
            return FILE_NOT_FOUND;
        }

        for (std::string line; std::getline(in, line); /* update in check */) {
            // clear out any characters that are parts of comment or windows line feed
            size_t comment_pos = line.find_first_of("#\r");
            if (comment_pos != std::string::npos) {
                line.resize(comment_pos);
            }

            // check if the line is blank
            if (line.size() > 0) {
                char typebuf[8] = {0};
                std::stringstream ss(line);
                std::string typestr;
                ss >> typestr;
                
                typestr.copy(typebuf, std::min(typestr.size(), 8ul));
                uint64_t typeint = *((uint64_t *) typebuf);
                switch (typeint) {
                    // vertex data
                    case GEOMETRIC_VERTEX: {
                        glm::vec4 vertex;
                        ss >> vertex.x >> vertex.y >> vertex.z;

                        if (!ss.eof()) { 
                            ss >> vertex.w; 
                        } else {
                            vertex.w = 1.0f;
                        }

                        group.vertices.emplace_back(vertex);

                        break;
                    }
                    case TEXTURE_VERTEX: {
                        glm::vec3 vertex;
                        ss >> vertex.s;

                        if (!ss.eof()) {
                            ss >> vertex.t; 
                        } else {
                            vertex.t = 0.0;
                        }

                        if (!ss.eof()) { 
                            ss >> vertex.p; 
                        } else {
                            vertex.p = 0.0f;
                        }

                        group.textures.emplace_back(vertex);

                        break;
                    }
                    case VERTEX_NORMAL: {
                        glm::vec3 vertex;
                        ss >> vertex.x >> vertex.y >> vertex.z;
                        group.normals.emplace_back(vertex);
                        break;
                    }
                    case PARAMETER_SPACE_VERTEX:
                        LOG_WARN("PARAMETER_SPACE_VERTEX not supported");
                        break;
                    case CURVE_OR_SURFACE:
                        LOG_WARN("CURVE_OR_SURFACE not supported");
                        break;
                    case DEGREE:
                        LOG_WARN("DEGREE not supported");
                        break;
                    case BASIS_MATRIX:
                        LOG_WARN("BASIS_MATRIX not supported");
                        break;
                    case STEP_SIZE:
                        LOG_WARN("STEP_SIZE not supported");
                        break;

                    // elements
                    case POINT:
                        LOG_WARN("POINT not supported");
                        break;
                    case LINE:
                        LOG_WARN("LINE not supported");
                        break;
                    case FACE: {
                        Face face;
                        std::string vertex_str; 

                        while (!ss.eof()) {
                            FaceVertex vertex;
                            ss >> vertex_str;

                            size_t n_indexes = std::count(vertex_str.begin(), vertex_str.end(), '/');

                            switch (n_indexes) {
                                case 2: {
                                    size_t i_normal = vertex_str.find_last_of('/');
                                    vertex.vn = atoi(&vertex_str[i_normal + 1]);
                                    vertex_str.resize(i_normal);
                                }
                                case 1: {
                                    size_t i_texture = vertex_str.find_last_of('/');
                                    vertex.vt = atoi(&vertex_str[i_texture + 1]);
                                    vertex_str.resize(i_texture);
                                }
                                case 0: {
                                    vertex.v = atoi(&vertex_str[0]);
                                }
                            }

                            // correct relative indexes
                            if (vertex.v < 0)  { vertex.v  = group.vertices.size() - vertex.v; }
                            if (vertex.vt < 0) { vertex.vt = group.textures.size() - vertex.vt; }
                            if (vertex.vn < 0) { vertex.vn = group.normals.size() - vertex.vn; }

                            face.vertices.emplace_back(vertex);
                        }

                        group.faces.emplace_back(face);
                        break;
                    }
                    case CURVE:
                        LOG_WARN("CURVE not supported");
                        break;
                    case CURVE_2D:
                        LOG_WARN("CURVE_2D not supported");
                        break;
                    case SURFACE:
                        LOG_WARN("SURFACE not supported");
                        break;

                    // free-form curve/surface body statements
                    case PARAMETER_VALUES:
                        LOG_WARN("PARAMETER_VALUES not supported");
                        break;
                    case OUTER_TRIMMING_LOOP:
                        LOG_WARN("OUTER_TRIMMING_LOOP not supported");
                        break;
                    case INNER_TRIMMING_LOOP:
                        LOG_WARN("INNER_TRIMMING_LOOP not supported");
                        break;
                    case SPECIAL_CURVE:
                        LOG_WARN("SPECIAL_CURVE not supported");
                        break;
                    case SPECIAL_POINT:
                        LOG_WARN("SPECIAL_POINT not supported");
                        break;
                    case END_STATEMENT:
                        LOG_WARN("END_STATEMENT not supported");
                        break;

                    // connectivity between free-form surfaces
                    case CONNECT:
                        LOG_WARN("CONNECT not supported");
                        break;

                    // grouping
                    case GROUP_NAME: {
                        if (!group_name.empty()) {
                            groups.emplace(group_name, std::move(group));
                            group.clear();
                            group_name.clear();
                        }
                        break;
                    }
                    case SMOOTHING_GROUP:
                        LOG_WARN("SMOOTHING_GROUP not supported");
                        break;
                    case MERGING_GROUP:
                        LOG_WARN("MERGING_GROUP not supported");
                        break;
                    case OBJECT_NAME:
                        LOG_WARN("OBJECT_NAME not supported");
                        break;

                    // display/render attributes
                    case BEVEL_INTERPOLATION:
                        LOG_WARN("BEVEL_INTERPOLATION not supported");
                        break;
                    case COLOR_INTERPOLATION:
                        LOG_WARN("COLOR_INTERPOLATION not supported");
                        break;
                    case DISSOLVE_INTERPOLATION:
                        LOG_WARN("DISSOLVE_INTERPOLATION not supported");
                        break;
                    case LEVEL_OF_DETAIL:
                        LOG_WARN("LEVEL_OF_DETAIL not supported");
                        break;
                    case MATERIAL_NAME: {
                        std::string name;
                        ss >> name;
                        if (materials.contains(name)) {
                            std::cout << "Assigning material " << name << std::endl;
                        } else {
                            std::cout << "Unknown material " << name << std::endl;
                        }
                        break;
                    }
                    case MATERIAL_LIBRARY: {
                        std::string libname;
                        ss >> libname;
                        std::filesystem::path lib = path.parent_path() / libname;
                        if (load_material(lib)) {
                            LOG_WARN("failed to load materials at '%s'", lib.c_str());
                        }
                        break;
                    }
                    case SHADOW_CASTING:
                        LOG_WARN("SHADOW_CASTING not supported");
                        break;
                    case RAY_TRACING:
                        LOG_WARN("RAY_TRACING not supported");
                        break;
                    case CURVE_APPROX_TECHNIQUE:
                        LOG_WARN("CURVE_APPROX_TECHNIQUE not supported");
                        break;
                    case SURFACE_APPROX_TECHNIQUE:
                        LOG_WARN("SURFACE_APPROX_TECHNIQUE not supported");
                        break;
                    default:
                        LOG_WARN("UNKNOWN not supported");
                        break;
                }
            }
        }

        in.close();

        return SUCCESS;
    }
};

std::ostream& operator<<(std::ostream &os, FaceVertex const &fv) {
    os << fv.v << "/" << fv.vt << "/" << fv.vn;
    return os;
}

std::ostream& operator<<(std::ostream &os, Face const &f) {
    os << "f";
    std::for_each(f.vertices.begin(), f.vertices.end(), [&](auto fv) { os << " " << fv; });
    return os;
}

namespace bolt {
    [[nodiscard]] Status load_obj(std::filesystem::path const &path, Mesh &mesh) {
        return ObjLoader().load_mesh(path);
    }
}
