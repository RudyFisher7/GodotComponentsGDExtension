//
// Created by rfish on 5/1/2025.
//

#include "interactable.h"

Interactable::Interactable() :
        interactable_name(),
        _components() {

}

String Interactable::get_interactable_name() const {
    return interactable_name;
}

void Interactable::set_interactable_name(const String &value) {
    interactable_name = value;
}

void Interactable::ready() {
    for (int64_t i = 0; i < _components.size(); ++i) {
        Ref<InteractableComponent> component = _components[i];
        if (!component->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
            component->connect("finished", callable_mp(this, &Interactable::_on_component_finished));
        }
    }
}

TypedArray<InteractableComponent> Interactable::get_components() const {
    return _components;
}

void Interactable::set_components(const TypedArray<InteractableComponent> &value) {
    if (!_components.is_empty()) {
        for (int64_t i = 0; i < _components.size(); ++i) {
            Ref<InteractableComponent> component = _components[i];
            if (component->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
                component->disconnect("finished", callable_mp(this, &Interactable::_on_component_finished));
            }
        }
    }

    _components = value;

    if (!_components.is_empty()) {
        for (int64_t i = 0; i < _components.size(); ++i) {
            Ref<InteractableComponent> component = _components[i];
            if (!component->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
                component->connect("finished", callable_mp(this, &Interactable::_on_component_finished));
            }
        }
    }
}

void Interactable::add_component(const Ref<InteractableComponent> &value) {
    _components.push_back(value);

    if (!value->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
        value->connect("finished", callable_mp(this, &Interactable::_on_component_finished));
    }
}

void Interactable::erase_component(const Ref<InteractableComponent> &value) {
    int64_t index = _components.find(value);

    if (index > -1) {
        _components.remove_at(index);
        if (value->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
            value->disconnect("finished", callable_mp(this, &Interactable::_on_component_finished));
        }
    }
}

void Interactable::erase_component_at(int64_t index) {
    Ref<InteractableComponent> component = _components[index];
    _components.remove_at(index);

    if (component->is_connected("finished", callable_mp(this, &Interactable::_on_component_finished))) {
        component->disconnect("finished", callable_mp(this, &Interactable::_on_component_finished));
    }
}

void Interactable::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_interactable_name"), &Interactable::get_interactable_name);
    ClassDB::bind_method(D_METHOD("set_interactable_name", "value"), &Interactable::set_interactable_name);
    ClassDB::bind_method(D_METHOD("add_component", "value"), &Interactable::add_component);
    ClassDB::bind_method(D_METHOD("erase_component", "value"), &Interactable::erase_component);
    ClassDB::bind_method(D_METHOD("erase_component_at", "index"), &Interactable::erase_component_at);
    ClassDB::bind_method(D_METHOD("_on_component_finished", "emitter"), &Interactable::_on_component_finished);

    ADD_PROPERTY(PropertyInfo(Variant::STRING, "interactable_name", PropertyHint::PROPERTY_HINT_TYPE_STRING), "set_interactable_name", "get_interactable_name");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "_components", PropertyHint::PROPERTY_HINT_ARRAY_TYPE), "set_components", "get_components");

    ADD_SIGNAL(MethodInfo("component_erased", PropertyInfo(Variant::OBJECT, "emitter")));
}

void Interactable::_on_component_finished(const Ref<InteractableComponent> &emitter) {
    if (!emitter->get_is_repreatable()) {
        _components.erase(emitter);
        emit_signal("component_erased", emitter);
    }
}
