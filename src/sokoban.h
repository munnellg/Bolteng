#ifndef SOKOBAN_H
#define SOKOBAN_H

#define GAME_NAME "SOKOBAN"

class Sokoban {
public:
    Sokoban();

    bool init();
    bool play();
    void quit();

    void quit_main_loop();

private:
    bool m_quit;
};

#endif // SOKOBAN_H
