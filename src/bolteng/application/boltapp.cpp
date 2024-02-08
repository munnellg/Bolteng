#include "boltapp.h"
#include "../input/input.h"
#include "../logging.h"
#include "../subsystems/subsystems.h"

namespace bolt {
    BoltApp::BoltApp() : m_quit(false) {
    }

    int BoltApp::main() {
        uint64_t curr = 0, last = 0;

        if (!init()) {
            return EXIT_FAILURE;
        }

        while (!m_quit) {
            last = curr;
            curr = subsystems::time::get_ticks();
            subsystems::events::process();
            update(curr - last);
        } 

        quit();

        return EXIT_SUCCESS;
    }

    bool const BoltApp::init() {
        logging::set_level(logging::Level::debug);

        if(!subsystems::init()) {
            return false;
        }

        bolt::input::platform.bind(bolt::input::PLATFORM_QUIT, std::bind(&BoltApp::quit_main_loop, this));

        return (m_post_init)? m_post_init() : true;
    }

    int const BoltApp::quit_main_loop() {
        m_quit = true;
        return 0;
    }

    void const BoltApp::quit() {
        // release all memory
        subsystems::quit();
    }
}
