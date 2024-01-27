#include "sokoban.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Sokoban sokoban;

    if (!sokoban.init()) {
        return EXIT_FAILURE;
    }

    sokoban.play();

    sokoban.quit();

    return EXIT_SUCCESS;
}
