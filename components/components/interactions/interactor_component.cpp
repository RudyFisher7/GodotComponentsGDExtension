//
// Created by rfish on 5/1/2025.
//

#include "interactor_component.h"

InteractorComponent::InteractorComponent() {

}

StringName InteractorComponent::get_understood_interactable_component_class() const {
    return {};
}

bool InteractorComponent::get_is_available() const {
    return false;
}

bool InteractorComponent::get_can_interact_with(const Ref<InteractableComponent> &target) const {
    return false;
}

bool InteractorComponent::get_is_cooling_down() const {
    return false;
}

bool InteractorComponent::start(const Ref<InteractableComponent> &target) {
    return false;
}

void InteractorComponent::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_understood_interactable_component_class"), &InteractorComponent::get_understood_interactable_component_class);
    ClassDB::bind_method(D_METHOD("get_is_available"), &InteractorComponent::get_is_available);
    ClassDB::bind_method(D_METHOD("get_can_interact_with", "target"), &InteractorComponent::get_can_interact_with);
    ClassDB::bind_method(D_METHOD("get_is_cooling_down"), &InteractorComponent::get_is_cooling_down);
    ClassDB::bind_method(D_METHOD("start", "target"), &InteractorComponent::start);

    ADD_SIGNAL(MethodInfo("availability_changed", PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("cool_down_finished", PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("started", PropertyInfo(Variant::OBJECT, "emitter")));
    ADD_SIGNAL(MethodInfo("finished", PropertyInfo(Variant::OBJECT, "emitter")));
}
