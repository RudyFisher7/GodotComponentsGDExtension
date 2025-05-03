//
// Created by rfish on 5/1/2025.
//

#include "interactable.h"

void Interactable::_bind_methods() {
    ADD_SIGNAL(MethodInfo("component_erased", PropertyInfo(Variant::OBJECT, "emitter")));
}
