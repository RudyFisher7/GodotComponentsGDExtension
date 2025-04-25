//
// Created by rfish on 4/24/2025.
//

#include "component_container.h"
#include <godot_cpp/core/print_string.hpp>

Ref<ComponentContainer> ComponentContainer::get_components(Object *obj) {
    if (!obj->has_meta(StringName("components"))) {
        return nullptr;
    }

    Variant variant = obj->get_meta(StringName("components"));
    return (Ref<ComponentContainer>) Object::cast_to<ComponentContainer>(variant); // use c-cast to disambiguate
}

bool ComponentContainer::has_component(StringName component_class) const {
    return _components.has(component_class);
}

Ref<Component> ComponentContainer::get_component(StringName component_class) const {
    if (!has_component(component_class)) {
        return nullptr;
    }

    Ref<Component> result;

    result = _components.get(component_class);

    return result;
}

void ComponentContainer::set_component(Ref<Component> value) {
    ERR_FAIL_COND_MSG(value->owner != nullptr, vformat("This component already has an owner. Remove it first."));
    ERR_FAIL_COND_MSG(!value.is_valid(), vformat("Can't add a null component."));

    (void)_remove_component(value->get_component_class());

    _components[value->get_component_class()] = value;
    value->owner = Object::cast_to<Object>(this);

    if (value->is_process_overridden()) {
        (void)_process_group.insert(value);
    }

    if (value->is_physics_process_overridden()) {
        (void)_physics_process_group.insert(value);
    }

    if (value->is_input_overridden()) {
        (void)_input_group.insert(value);
    }

    if (value->is_shortcut_input_overridden()) {
        (void)_shortcut_input_group.insert(value);
    }

    if (value->is_unhandled_input_overridden()) {
        (void)_unhandled_input_group.insert(value);
    }

    if (value->is_unhandled_key_input_overridden()) {
        (void)_unhandled_key_input_group.insert(value);
    }

    print_line("Added ", value->get_component_class());

    emit_changed();
}

void ComponentContainer::remove_component(StringName component_class) {
    if (_remove_component(component_class)) {
        emit_changed();
    }
}

void ComponentContainer::get_component_list(List<Ref<Component>> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        out->push_back(K.value);
    }
}

void ComponentContainer::get_component_class_list(List<StringName> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        out->push_back(K.key);
    }
}

bool ComponentContainer::is_processing() const {
    return !_process_group.is_empty();
}

bool ComponentContainer::is_processing_physics() const {
    return !_physics_process_group.is_empty();
}

bool ComponentContainer::is_processing_input() const {
    return !_input_group.is_empty();
}

bool ComponentContainer::is_processing_shortcut_input() const {
    return !_shortcut_input_group.is_empty();
}

bool ComponentContainer::is_processing_unhandled_input() const {
    return !_unhandled_input_group.is_empty();
}

bool ComponentContainer::is_processing_unhandled_key_input() const {
    return !_unhandled_key_input_group.is_empty();
}

void ComponentContainer::call_components_enter_tree() {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->enter_tree();
    }
}

void ComponentContainer::call_components_exit_tree() {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->exit_tree();
    }
}

void ComponentContainer::call_components_ready() {
    print_line("call_components_ready");
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->ready();
    }
}

void ComponentContainer::call_components_process(double delta) {
    for (const Ref<Component> &K : _process_group) {
        K->process(delta); //NOTE:: this ideally should call Node::get_process_delta_time()
    }
}

void ComponentContainer::call_components_physics_process(double delta) {
    for (const Ref<Component> &K : _physics_process_group) {
        K->physics_process(delta); //NOTE:: this ideally should call Node::get_physics_process_delta_time()
    }
}

bool ComponentContainer::call_components_input(const Ref<InputEvent> &p_event) {
    for (const Ref<Component> &K : _input_group) {
        if (K->input(p_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentContainer::call_components_shortcut_input(const Ref<InputEvent> &p_key_event) {
    for (const Ref<Component> &K : _shortcut_input_group) {
        if (K->shortcut_input(p_key_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentContainer::call_components_unhandled_input(const Ref<InputEvent> &p_event) {
    for (const Ref<Component> &K : _unhandled_input_group) {
        if (K->unhandled_input(p_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentContainer::call_components_unhandled_key_input(const Ref<InputEvent> &p_key_event) {
    for (const Ref<Component> &K : _unhandled_key_input_group) {
        if (K->unhandled_key_input(p_key_event)) {
            return true;
        }
    }

    return false;
}

void ComponentContainer::_bind_methods() {
    ClassDB::bind_method(D_METHOD("has_component", "component_class"), &ComponentContainer::has_component);
    ClassDB::bind_method(D_METHOD("get_component", "component_class"), &ComponentContainer::get_component);
    ClassDB::bind_method(D_METHOD("set_component", "value"), &ComponentContainer::set_component);
    ClassDB::bind_method(D_METHOD("remove_component", "component_class"), &ComponentContainer::remove_component);
}

void ComponentContainer::_get_property_list(List<PropertyInfo> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &k_v : _components) {
        PropertyInfo property_info = PropertyInfo(Variant::OBJECT, "components/" + String(k_v.key), PROPERTY_HINT_RESOURCE_TYPE, "Component", PropertyUsageFlags::PROPERTY_USAGE_DEFAULT | PropertyUsageFlags::PROPERTY_USAGE_READ_ONLY);
        out->push_back(property_info);
    }
}

bool ComponentContainer::_get(const StringName &p_property, Variant &r_value) const {
    bool result = false;

    const String COMPONENTS = "components/";
    String p_string = p_property;
    if (p_string.begins_with(COMPONENTS)) {
        String key = p_string.trim_prefix(COMPONENTS);

        result = has_component(key);

        if (result) {
            r_value = get_component(key);
        }
    }

    return result;
}

bool ComponentContainer::_set(const StringName &p_property, const Variant &p_value) {
    bool result = false;

    const String COMPONENTS = "components/";
    String p_string = p_property;
    if (p_string.begins_with(COMPONENTS)) {
        set_component(p_value);
        result = true;
    }

    return result;
}

bool ComponentContainer::_remove_component(StringName component_class) {
    if (!_components.has(component_class)) {
        return false;
    }

    bool result = false;
    Ref<Component> value = _components.get(component_class);
    if (value.is_valid()) {
        result = true;
        _components.erase(component_class);
        value->owner = nullptr;

        (void)_process_group.erase(value);
        (void)_physics_process_group.erase(value);
        (void)_input_group.erase(value);
        (void)_shortcut_input_group.erase(value);
        (void)_unhandled_input_group.erase(value);
        (void)_unhandled_key_input_group.erase(value);
    }

    return result;
}