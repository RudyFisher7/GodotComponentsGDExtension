#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

class ComponentContainer : public Resource {
    GDCLASS(ComponentContainer, Resource)

public:
    static Ref<ComponentContainer> get_container(Object obj);

protected:
    static void _bind_methods();
};
