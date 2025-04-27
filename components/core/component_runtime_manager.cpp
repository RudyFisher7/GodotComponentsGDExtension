//
// Created by rfish on 4/24/2025.
//

#include "component_runtime_manager.h"

#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/error_macros.hpp>

ComponentRuntimeManager::~ComponentRuntimeManager() {
    if (_components.is_valid()) {
        _components->owner = nullptr;
    }
}

void ComponentRuntimeManager::_enter_tree() {
    _parent = get_parent();
    if(_parent == nullptr) {
        _components = (Ref<ComponentCollection>)memnew(ComponentCollection);
    }

    ERR_FAIL_COND_MSG(_parent == nullptr, vformat("%s needs a parent Node in the scene tree.", get_name()));

    _components = ComponentCollection::get_components(_parent);
    if (_components.is_valid() && _components->owner != nullptr) {
        ERR_PRINT(vformat("%s's components are already being managed by another ComponentRuntimeManager.", _parent->get_name()));
        _components = (Ref<ComponentCollection>)nullptr;
    }

    if (_components.is_valid()) {
        _components->owner = this;
        _components->connect("changed", callable_mp(this, &ComponentRuntimeManager::_update_processing));
        _components->call_components_enter_tree();
    } else {
        WARN_PRINT(vformat("%s's parent Node has no components to manage.", get_name()));

        // just add a dummy to avoid crashes if user decides to call any set_process_*() methods.
        // I'd rather do this than have another check inside _process(), etc.
        _components = (Ref<ComponentCollection>)memnew(ComponentCollection);
    }
}

void ComponentRuntimeManager::_exit_tree() {
    _parent = nullptr;
    _components->owner = nullptr;
    _components->disconnect("changed", callable_mp(this, &ComponentRuntimeManager::_update_processing));
    _components->call_components_exit_tree();
    _components = (Ref<ComponentCollection>)nullptr;
}

void ComponentRuntimeManager::_ready() {
    _update_processing();
    _components->call_components_ready();
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

void ComponentRuntimeManager::_bind_methods() {

}

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
