
#pragma once


// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include "core/component.h"

#include <godot_cpp/classes/object.hpp>

class TestGDExtensionComponent : public Component {
    GDCLASS(TestGDExtensionComponent, Component);

public:
    void enter_tree() override;
    void ready() override;

protected:
    static void _bind_methods();
};
