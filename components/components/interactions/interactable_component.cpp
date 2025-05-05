//
// Created by rfish on 5/3/2025.
//

#include "interactable_component.h"

InteractableComponent::InteractableComponent() : icon(nullptr) {}

Ref<Texture2D> InteractableComponent::get_icon() const {
    return icon;
}

void InteractableComponent::set_icon(const Ref<Texture2D> &value) {
    icon = value;
}

bool InteractableComponent::get_is_repreatable() const {
    return false;
}

bool InteractableComponent::get_is_approachable() const {
    return false;
}

bool InteractableComponent::get_is_busy() const {
    return false;
}

bool InteractableComponent::get_has_notice() const {
    return false;
}

void InteractableComponent::set_has_notice(bool value) {

}

bool InteractableComponent::start() {
    return false;
}

void InteractableComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_icon"), &InteractableComponent::get_icon);
    ClassDB::bind_method(D_METHOD("set_icon", "value"), &InteractableComponent::set_icon);
    ClassDB::bind_method(D_METHOD("get_is_repreatable"), &InteractableComponent::get_is_repreatable);
    ClassDB::bind_method(D_METHOD("get_is_approachable"), &InteractableComponent::get_is_approachable);
    ClassDB::bind_method(D_METHOD("get_is_busy"), &InteractableComponent::get_is_busy);
    ClassDB::bind_method(D_METHOD("get_has_notice"), &InteractableComponent::get_has_notice);
    ClassDB::bind_method(D_METHOD("set_has_notice", "value"), &InteractableComponent::set_has_notice);
    ClassDB::bind_method(D_METHOD("start"), &InteractableComponent::start);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "icon", PropertyHint::PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_icon", "get_icon");

    ADD_SIGNAL(MethodInfo("noticed", PropertyInfo(Variant::BOOL, "value"), PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("approachable_changed", PropertyInfo(Variant::BOOL, "value"), PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("started", PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("finished", PropertyInfo(Variant::OBJECT, "emitter")));
}
