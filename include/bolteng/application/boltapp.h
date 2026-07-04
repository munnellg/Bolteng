#ifndef BOLTENG_APPLICATION_BOLTAPP_H
#define BOLTENG_APPLICATION_BOLTAPP_H

#include "scene.h"

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace bolt {
    class BoltApp {
    public:
        static std::string const DEFAULT_APP_NAME;

        BoltApp();
        BoltApp(std::string const &appName);

        int main();
        int quitMainLoop();

    protected:
        virtual bool preInit()  { return true; }
        virtual bool postInit() { return true; }
        virtual bool preQuit()  { return true; }
        virtual bool postQuit() { return true; }

        std::string const m_appName;

        bool m_quit;
        std::shared_ptr<Scene> m_currentScene;

    private:
        bool init();
        void quit();
    };
}

#endif // BOLTENG_APPLICATION_BOLTAPP_H
