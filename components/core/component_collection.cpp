//
// Created by rfish on 4/24/2025.
//

#include "component_collection.h"
#include <godot_cpp/core/print_string.hpp>
#include <godot_cpp/classes/engine.hpp>

bool ComponentCollection::has_components(Object *obj) {
    ERR_FAIL_COND_V_MSG(obj == nullptr, false, "Object is null. Failed to check for components.");
    return obj->has_meta(StringName("components"));
}

void ComponentCollection::set_components(Object *obj, const Ref<ComponentCollection> &components) {
    ERR_FAIL_COND_MSG(obj == nullptr, "Object is null. Failed to set components.");
    obj->set_meta(StringName("components"), components);

    Engine *engine = Engine::get_singleton();

    ERR_FAIL_COND_MSG(engine == nullptr, "Engine singleton is null!?");

    if (!engine->is_editor_hint() && components->is_runtime_managed()) {
        components->call_components_enter_tree();
        components->call_components_ready();
    }
}

void ComponentCollection::remove_components(Object *obj) {
    ERR_FAIL_COND_MSG(obj == nullptr, "Object is null. Failed to check for components.");
    obj->remove_meta(StringName("components"));
}

Ref<ComponentCollection> ComponentCollection::get_components(Object *obj) {
    ERR_FAIL_COND_V_MSG(obj == nullptr, nullptr, "Object is null. Failed to get components.");

    if (!obj->has_meta(StringName("components"))) {
        return nullptr;
    }

    Variant variant = obj->get_meta(StringName("components"));
    return (Ref<ComponentCollection>) Object::cast_to<ComponentCollection>(variant); // use c-cast to disambiguate
}

ComponentCollection::ComponentCollection() {
    set_local_to_scene(true);
}

ComponentCollection::~ComponentCollection() {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->owner = nullptr;
    }
}

//TypedDictionary<StringName, Component> ComponentCollection::get_component_dictionary() const {
//    return _components;
//}
//
//void ComponentCollection::set_component_dictionary(TypedDictionary<StringName, Component> value) {
//    _components = value;
//}

bool ComponentCollection::is_runtime_managed() const {
    return owner != nullptr;
}

bool ComponentCollection::is_empty() const {
    return _components.is_empty();
}

bool ComponentCollection::has_component(const StringName& component_class) const {
    return _components.has(component_class);
}

Ref<Component> ComponentCollection::get_component(const StringName& component_class) const {
    if (!has_component(component_class)) {
        return nullptr;
    }

    Ref<Component> result;

    result = _components[component_class];

    return result;
}

void ComponentCollection::set_component(const Ref<Component> &value) {
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

    Engine *engine = Engine::get_singleton();

    ERR_FAIL_COND_MSG(engine == nullptr, "Engine singleton is null!?");

    if (!engine->is_editor_hint() && is_runtime_managed()) {
        value->enter_tree();
        value->ready();
    }

    emit_changed();
}

void ComponentCollection::remove_component(StringName component_class) {
    if (_remove_component(std::move(component_class))) {
        emit_changed();
    }
}

void ComponentCollection::get_component_list(List<Ref<Component>> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        out->push_back(K.value);
    }
}

void ComponentCollection::get_component_class_list(List<StringName> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        out->push_back(K.key);
    }
}

bool ComponentCollection::is_processing() const {
    return !_process_group.is_empty();
}

bool ComponentCollection::is_processing_physics() const {
    return !_physics_process_group.is_empty();
}

bool ComponentCollection::is_processing_input() const {
    return !_input_group.is_empty();
}

bool ComponentCollection::is_processing_shortcut_input() const {
    return !_shortcut_input_group.is_empty();
}

bool ComponentCollection::is_processing_unhandled_input() const {
    return !_unhandled_input_group.is_empty();
}

bool ComponentCollection::is_processing_unhandled_key_input() const {
    return !_unhandled_key_input_group.is_empty();
}

void ComponentCollection::call_components_enter_tree() {
//    Array array = _components.values();
//    for (int i = 0; i < array.size(); ++i) {
//        Ref<Component> c = Object::cast_to<Component>(array[i]);
//        c->enter_tree();
//    }

    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->enter_tree();
    }
}

void ComponentCollection::call_components_exit_tree() {
//    Array array = _components.values();
//    for (int i = 0; i < array.size(); ++i) {
//        Ref<Component> c = Object::cast_to<Component>(array[i]);
//        c->exit_tree();
//    }

    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->exit_tree();
    }
}

void ComponentCollection::call_components_ready() {
//    Array array = _components.values();
//    for (int i = 0; i < array.size(); ++i) {
//        Ref<Component> c = Object::cast_to<Component>(array[i]);
//        c->ready();
//    }

    for (const KeyValue<StringName, Ref<Component>> &K : _components) {
        K.value->ready();
    }
}

void ComponentCollection::call_components_process(double delta) {
    for (const Ref<Component> &K : _process_group) {
        K->process(delta); //NOTE:: this ideally should call Node::get_process_delta_time()
    }
}

void ComponentCollection::call_components_physics_process(double delta) {
    for (const Ref<Component> &K : _physics_process_group) {
        K->physics_process(delta); //NOTE:: this ideally should call Node::get_physics_process_delta_time()
    }
}

bool ComponentCollection::call_components_input(const Ref<InputEvent> &p_event) {
    for (const Ref<Component> &K : _input_group) {
        if (K->input(p_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentCollection::call_components_shortcut_input(const Ref<InputEvent> &p_key_event) {
    for (const Ref<Component> &K : _shortcut_input_group) {
        if (K->shortcut_input(p_key_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentCollection::call_components_unhandled_input(const Ref<InputEvent> &p_event) {
    for (const Ref<Component> &K : _unhandled_input_group) {
        if (K->unhandled_input(p_event)) {
            return true;
        }
    }

    return false;
}

bool ComponentCollection::call_components_unhandled_key_input(const Ref<InputEvent> &p_key_event) {
    for (const Ref<Component> &K : _unhandled_key_input_group) {
        if (K->unhandled_key_input(p_key_event)) {
            return true;
        }
    }

    return false;
}

void ComponentCollection::_bind_methods() {
    ClassDB::bind_static_method("ComponentCollection", D_METHOD("has_components", "obj"), &ComponentCollection::has_components);
    ClassDB::bind_static_method("ComponentCollection", D_METHOD("set_components", "obj", "components"), &ComponentCollection::set_components);
    ClassDB::bind_static_method("ComponentCollection", D_METHOD("remove_components", "obj"), &ComponentCollection::remove_components);
    ClassDB::bind_static_method("ComponentCollection", D_METHOD("get_components", "obj"), &ComponentCollection::get_components);
//    ClassDB::bind_method(D_METHOD("get_component_dictionary"), &ComponentCollection::get_component_dictionary);
//    ClassDB::bind_method(D_METHOD("set_component_dictionary", "value"), &ComponentCollection::set_component_dictionary);
    ClassDB::bind_method(D_METHOD("is_runtime_managed"), &ComponentCollection::is_runtime_managed);
    ClassDB::bind_method(D_METHOD("is_empty"), &ComponentCollection::is_empty);
    ClassDB::bind_method(D_METHOD("has_component", "component_class"), &ComponentCollection::has_component);
    ClassDB::bind_method(D_METHOD("get_component", "component_class"), &ComponentCollection::get_component);
    ClassDB::bind_method(D_METHOD("set_component", "value"), &ComponentCollection::set_component);
    ClassDB::bind_method(D_METHOD("remove_component", "component_class"), &ComponentCollection::remove_component);

//    ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "_components"), "set_component_dictionary", "get_component_dictionary");
}

void ComponentCollection::_get_property_list(List<PropertyInfo> *out) const {
    for (const KeyValue<StringName, Ref<Component>> &k_v : _components) {
        PropertyInfo property_info = PropertyInfo(Variant::OBJECT, "components/" + String(k_v.key), PROPERTY_HINT_RESOURCE_TYPE, "Component", PropertyUsageFlags::PROPERTY_USAGE_DEFAULT);
        out->push_back(property_info);
    }
}

bool ComponentCollection::_get(const StringName &p_property, Variant &r_value) const {
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

bool ComponentCollection::_set(const StringName &p_property, const Variant &p_value) {
    bool result = false;

    const String COMPONENTS = "components/";
    String p_string = p_property;
    if (p_string.begins_with(COMPONENTS)) {
        set_component(p_value);
        result = true;
    }

    return result;
}

bool ComponentCollection::_remove_component(StringName component_class) {
    if (!_components.has(component_class)) {
        return false;
    }

    bool result = false;
    Ref<Component> value = _components[component_class];
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

        Engine *engine = Engine::get_singleton();

        ERR_FAIL_COND_V_MSG(engine == nullptr, result, "Engine singleton is null!?");

        if (!engine->is_editor_hint() && is_runtime_managed()) {
            value->exit_tree();
        }
    }

    return result;
}