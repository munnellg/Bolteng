#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "../core/component.h"

class RenderComponent : public Component {
public:
    static ComponentId const ID;

    RenderComponent();
    virtual bool init(void *pDescription) override final;
};

#endif // RENDERABLE_H
