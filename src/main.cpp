#include "sokoban.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Sokoban sokoban;

    if (!sokoban.init()) {
        return EXIT_FAILURE;
    }

    sokoban.play();

    return EXIT_SUCCESS;
}
