
#pragma once

#include "kyo/entity/composite.h"


class ControllableEntity: public CompositeEntity {
private:

public:

    // default definitions are given so controlled entities don't need to
    // override all of them

    virtual void on_key_press(Key key) {};

    virtual void on_key_hold(Key key) {};

    virtual void on_key_release(Key key) {};
};