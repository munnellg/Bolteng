#include "bolteng/graphics/mesh.h"
#include "sokoban.h"

int main() {
    bolt::graphics::Mesh mesh;
    return bolt::graphics::load_obj("assets/meshes/kenny/detail_treeLarge.obj", mesh);
//    return Sokoban().main();
}
