#include "sokoban.h"

int main(int argc, char *argv[]) {
    Sokoban sokoban;

    if (sokoban.init()) {
        sokoban.play();
    }

    sokoban.quit();

    return EXIT_SUCCESS;
}
