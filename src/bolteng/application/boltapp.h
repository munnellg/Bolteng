#ifndef BOLTENG_APPLICATION_BOLTAPP_H
#define BOLTENG_APPLICATION_BOLTAPP_H

#include <cstdint>
#include <functional>

namespace bolt {
    class BoltApp {
    public:
        BoltApp();
        ~BoltApp() = default;

        virtual void update(uint64_t const deltaTime) = 0;
        int main();
        int const quit_main_loop();

    protected:
        bool m_quit;
        std::function<bool(void)> m_post_init;

    private:
        bool const init();
        void const quit();
    };
}

#endif // BOLTENG_APPLICATION_BOLTAPP_H
