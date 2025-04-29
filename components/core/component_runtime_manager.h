#pragma once

#include "component_collection.h"
#include "component.h"
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

class ComponentRuntimeManager : public Node {
    GDCLASS(ComponentRuntimeManager, Node);

protected:
    Node *_parent = nullptr;
    Ref<ComponentCollection> _components;

public:
    ComponentRuntimeManager() = default;
    virtual ~ComponentRuntimeManager() override;

    void _enter_tree() override;
    void _exit_tree() override;
    void _ready() override;
    void _process(double p_delta) override;
    void _physics_process(double p_delta) override;
    void _input(const Ref<InputEvent> &p_event) override;
    void _shortcut_input(const Ref<InputEvent> &p_event) override;
    void _unhandled_input(const Ref<InputEvent> &p_event) override;
    void _unhandled_key_input(const Ref<InputEvent> &p_event) override;

protected:
    static void _bind_methods();

    void _update_processing();
    void _set_processing(bool value);
};
