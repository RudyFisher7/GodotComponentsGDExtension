
#pragma once


// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/core/gdvirtual.gen.inc>
#include <godot_cpp/classes/scene_tree.hpp>

using namespace godot;

class Component : public Resource {
    GDCLASS(Component, Resource);

public:
    Object *owner = nullptr;

protected:
    Node *_parent = nullptr;

public:
    Component();
    ~Component() override = default;

    StringName get_component_class();

    // note:: gdextension's GDVIRTUAL_BIND macro doesn't allow native classes to
    // override them, only GDScript. if this is changed to mirror Godot's behavior, then
    // replace these overridden virtuals with the GDVIRTUAL_BIND functions.
    virtual void enter_tree(Node *p_parent);
    virtual void exit_tree();
    virtual void ready();
    virtual void process(double delta);
    virtual void physics_process(double delta);

    virtual bool input(const Ref<InputEvent> &p_event);
    virtual bool shortcut_input(const Ref<InputEvent> &p_key_event);
    virtual bool unhandled_input(const Ref<InputEvent> &p_event);
    virtual bool unhandled_key_input(const Ref<InputEvent> &p_key_event);

    virtual bool is_process_overridden() const;
    virtual bool is_physics_process_overridden() const;

    virtual bool is_input_overridden() const;
    virtual bool is_shortcut_input_overridden() const;
    virtual bool is_unhandled_input_overridden() const;
    virtual bool is_unhandled_key_input_overridden() const;

    Node *get_node_or_null(const NodePath &p_path_from_parent_node) const;
    Node *get_parent_node() const;

protected:
    static void _bind_methods();

    GDVIRTUAL1(_enter_tree, Node*)
    GDVIRTUAL0(_exit_tree)
    GDVIRTUAL0(_ready)
    GDVIRTUAL1(_process, double)
    GDVIRTUAL1(_physics_process, double)

    GDVIRTUAL1R(bool, _input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _shortcut_input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _unhandled_input, Ref<InputEvent>)
    GDVIRTUAL1R(bool, _unhandled_key_input, Ref<InputEvent>)
};
