#include "boltapp.h"
#include "../input/input.h"
#include "../logging.h"
#include "../subsystems/subsystems.h"
#include <cstdlib>

namespace bolt {
    
    std::string const BoltApp::DEFAULT_APP_NAME = "BoltApp";

    BoltApp::BoltApp() : 
        m_appName(DEFAULT_APP_NAME),
        m_quit(false)
    {}

    BoltApp::BoltApp(std::string const &appName) : 
        m_appName(appName),
        m_quit(false)
    {}

    int BoltApp::main() {
        uint64_t curr = 0, last = 0;

        if (!preInit())  { return EXIT_FAILURE; }
        if (!init())     { return EXIT_FAILURE; }
        if (!postInit()) { return EXIT_FAILURE; }

        while (!m_quit) {
            last = curr;
            curr = subsystems::time::get_ticks();
            subsystems::events::process();
            m_currentScene->update(curr - last);
        } 
        
        preQuit();

        quit();

        postQuit();

        return EXIT_SUCCESS;
    }

    bool BoltApp::init() {
        logging::set_level(logging::Level::debug);

        if(!subsystems::init()) {
            return false;
        }

        // always make sure we can quit the app
        bolt::input::platform.bind(bolt::input::PLATFORM_QUIT, std::bind(&BoltApp::quitMainLoop, this));

        return true;
    }

    int BoltApp::quitMainLoop() {
        m_quit = true;
        return 0;
    }

    void BoltApp::quit() {
        preQuit();

        // release all memory
        subsystems::quit();
    }
}
