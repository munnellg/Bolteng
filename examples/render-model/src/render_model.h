#ifndef LOAD_3D_MODEL_H
#define LOAD_3D_MODEL_H

#include <bolteng/application/boltapp.h>

class RenderModel : public bolt::BoltApp {
public:
    RenderModel();

protected:
    bool postInit() override;
    bool preQuit() override;
};

#endif // LOAD_3D_MODEL_H
