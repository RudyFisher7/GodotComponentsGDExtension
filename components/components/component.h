
#pragma once


// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>

using namespace godot;

class Component : public Resource {
    GDCLASS(Component, Resource);

public:
    Object *owner = nullptr;

public:
    Component() = default;
    ~Component() override = default;

    StringName get_component_class();

    void enter_tree();
    void exit_tree();
    void ready();
    void process(double delta);
    void physics_process(double delta);

    bool input(const Ref<InputEvent> &p_event);
    bool shortcut_input(const Ref<InputEvent> &p_key_event);
    bool unhandled_input(const Ref<InputEvent> &p_event);
    bool unhandled_key_input(const Ref<InputEvent> &p_key_event);

    bool is_process_overridden() const;
    bool is_physics_process_overridden() const;

    bool is_input_overridden() const;
    bool is_shortcut_input_overridden() const;
    bool is_unhandled_input_overridden() const;
    bool is_unhandled_key_input_overridden() const;

protected:
    static void _bind_methods();

    GDVIRTUAL0(_enter_tree)
    GDVIRTUAL0(_exit_tree)
    GDVIRTUAL0(_ready)
    GDVIRTUAL1(_process, double)
    GDVIRTUAL1(_physics_process, double)

    GDVIRTUAL1R(bool, _input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _shortcut_input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _unhandled_input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _unhandled_key_input, Ref<InputEvent>)
};
