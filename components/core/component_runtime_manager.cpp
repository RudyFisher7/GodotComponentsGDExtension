//
// Created by rfish on 4/24/2025.
//

#include "component_runtime_manager.h"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/error_macros.hpp>


void ComponentRuntimeManager::_enter_tree() {
    _parent = get_parent();
    ERR_FAIL_COND_MSG(_parent == nullptr, vformat("%s needs a parent Node in the scene tree.", get_path()));
    if (!_parent->has_meta(StringName("components"))) {
        WARN_PRINT(vformat("%s's parent Node has no components to manage.", get_path()));

        // just add a dummy to avoid crashes if user decides to call any set_process_*() methods.
        // I'd rather do this than have another check inside _process(), etc.
        _components = (Ref<ComponentContainer>)memnew(ComponentContainer);
    } else {
        Variant variant = _parent->get_meta(StringName("components"));
        _components = (Ref<ComponentContainer>) Object::cast_to<ComponentContainer>(variant); // use c-cast to disambiguate

        _components->connect("changed", callable_mp(this, &ComponentRuntimeManager::_update_processing));
        _components->call_components_enter_tree();
    }
}

void ComponentRuntimeManager::_exit_tree() {
    if (_components.is_valid()) {
        _components->disconnect("changed", callable_mp(this, &ComponentRuntimeManager::_update_processing));
        _components->call_components_exit_tree();
    }
}

void ComponentRuntimeManager::_ready() {
    if (_components.is_valid()) {
        _update_processing();
        _components->call_components_ready();
    } else {
        _set_processing(false);
    }
}

void ComponentRuntimeManager::_process(double p_delta) {
    _components->call_components_process(p_delta);
}

void ComponentRuntimeManager::_physics_process(double p_delta) {
    _components->call_components_physics_process(p_delta);
}

void ComponentRuntimeManager::_input(const Ref<InputEvent> &p_event) {
    if (_components->call_components_input(p_event)) {
        get_viewport()->set_input_as_handled();
    }
}

void ComponentRuntimeManager::_shortcut_input(const Ref<InputEvent> &p_event) {
    if (_components->call_components_shortcut_input(p_event)) {
        get_viewport()->set_input_as_handled();
    }
}

void ComponentRuntimeManager::_unhandled_input(const Ref<InputEvent> &p_event) {
    if (_components->call_components_unhandled_input(p_event)) {
        get_viewport()->set_input_as_handled();
    }
}

void ComponentRuntimeManager::_unhandled_key_input(const Ref<InputEvent> &p_event) {
    if (_components->call_components_unhandled_key_input(p_event)) {
        get_viewport()->set_input_as_handled();
    }
}

void ComponentRuntimeManager::_bind_methods() {}

void ComponentRuntimeManager::_update_processing() {
    set_process(_components->is_processing());
    set_physics_process(_components->is_processing_physics());
    set_process_input(_components->is_processing_input());
    set_process_shortcut_input(_components->is_processing_shortcut_input());
    set_process_unhandled_input(_components->is_processing_unhandled_input());
    set_process_unhandled_key_input(_components->is_processing_unhandled_key_input());
}

void ComponentRuntimeManager::_set_processing(bool value) {
    set_process(value);
    set_physics_process(value);
    set_process_input(value);
    set_process_shortcut_input(value);
    set_process_unhandled_input(value);
    set_process_unhandled_key_input(value);
}