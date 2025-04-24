#pragma once

#include "component_container/component_container.h"
#include "components/component.h"
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node.hpp>

class ComponentManager : public Node {
    GDCLASS(ComponentManager, Node);

protected:
    Node *_parent = nullptr;
    Ref<ComponentContainer> _manager;

public:
    ComponentManager() = default;

    void _enter_tree() override;

protected:
    static void _bind_methods();
};
