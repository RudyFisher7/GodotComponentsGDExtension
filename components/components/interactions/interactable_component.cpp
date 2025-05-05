//
// Created by rfish on 5/3/2025.
//

#include "interactable_component.h"

bool InteractableComponent::get_is_repreatable() const {
    return false;
}

void InteractableComponent::_bind_methods() {
    ADD_SIGNAL(MethodInfo("finished", PropertyInfo(Variant::OBJECT, "emitter")));
}
