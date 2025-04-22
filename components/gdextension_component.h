
#ifndef GODOT_COMPONENTS_EXTENSION_GDEXTENSION_COMPONENT_H
#define GODOT_COMPONENTS_EXTENSION_GDEXTENSION_COMPONENT_H


// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp\classes\component.hpp>

using namespace godot;


class GDExtensionComponent : public Component {
    GDCLASS(GDExtensionComponent, Component);

public:
    virtual void _enter_tree() override;

protected:
    static void _bind_methods();
};


#endif //GODOT_COMPONENTS_EXTENSION_GDEXTENSION_COMPONENT_H
