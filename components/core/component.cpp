
#include "component.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/script.hpp>
#include <godot_cpp/classes/main_loop.hpp>
#include <godot_cpp/classes/window.hpp>

Component::Component() {
    set_local_to_scene(true);
}

StringName Component::get_component_class() {
    Ref<Script> s = get_script();
    while (s.is_valid()) {
        if (!s->get_global_name().is_empty()) {
            return s->get_global_name();
        } else {
            s = s->get_base_script();
        }
    }

    return get_class();//FIXME:: gdextension doesn't expose get_class_name() yet, but I'm guessing this is less efficient
}

void Component::enter_tree(Node *p_parent) {
    _parent = p_parent;
    if (GDVIRTUAL_CALL(_enter_tree)) {
        //
    }
}

void Component::exit_tree() {
    if (GDVIRTUAL_CALL(_exit_tree)) {
        //
    }

    _parent = nullptr;
}

void Component::ready() {
    if (GDVIRTUAL_CALL(_ready)) {
        //
    }
}

void Component::process(double delta) {
    if (GDVIRTUAL_CALL(_process, delta)) {
        //
    }
}

void Component::physics_process(double delta) {
    if (GDVIRTUAL_CALL(_physics_process, delta)) {
        //
    }
}

bool Component::input(const Ref<InputEvent> &p_event) {
    bool result = false;
    if (GDVIRTUAL_CALL(_input, p_event, result)) {
        //
    }

    return result;
}

bool Component::shortcut_input(const Ref<InputEvent> &p_key_event) {
    bool result = false;
    if (GDVIRTUAL_CALL(_shortcut_input, p_key_event, result)) {
        //
    }

    return result;
}

bool Component::unhandled_input(const Ref<InputEvent> &p_event) {
    bool result = false;
    if (GDVIRTUAL_CALL(_unhandled_input, p_event, result)) {
        //
    }

    return result;
}

bool Component::unhandled_key_input(const Ref<InputEvent> &p_key_event) {
    bool result = false;
    if (GDVIRTUAL_CALL(_unhandled_key_input, p_key_event, result)) {
        //
    }

    return result;
}

bool Component::is_process_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_process);
}

bool Component::is_physics_process_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_physics_process);
}

bool Component::is_input_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_input);
}

bool Component::is_shortcut_input_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_shortcut_input);
}

bool Component::is_unhandled_input_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_unhandled_input);
}

bool Component::is_unhandled_key_input_overridden() const {
    return GDVIRTUAL_IS_OVERRIDDEN(_unhandled_key_input);
}

Node *Component::get_node_or_null(const NodePath &p_path_from_parent_node) const {
    Node *result = nullptr;

    if (_parent) {
        result = _parent->get_node_or_null(p_path_from_parent_node);
    }

    return result;
}

Node *Component::get_parent_node() const {
    return _parent;
}

void Component::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_component_class"), &Component::get_component_class);
    ClassDB::bind_method(D_METHOD("get_node_or_null", "path_from_parent_node"), &Component::get_node_or_null);
    ClassDB::bind_method(D_METHOD("get_parent_node"), &Component::get_parent_node);

    GDVIRTUAL_BIND(_enter_tree);
    GDVIRTUAL_BIND(_exit_tree);
    GDVIRTUAL_BIND(_ready);
    GDVIRTUAL_BIND(_process, "delta");
    GDVIRTUAL_BIND(_physics_process, "delta");

    GDVIRTUAL_BIND(_input, "event");
    GDVIRTUAL_BIND(_shortcut_input, "event");
    GDVIRTUAL_BIND(_unhandled_input, "event");
    GDVIRTUAL_BIND(_unhandled_key_input, "event");

    ADD_SIGNAL(MethodInfo("processing_changed", PropertyInfo(Variant::STRING_NAME, "emitter_class")));
}
