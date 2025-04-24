//
// Created by rfish on 4/24/2025.
//

#include "component_manager.h"

#include <godot_cpp/core/error_macros.hpp>


void ComponentManager::_enter_tree() {
    _parent = get_parent();
    ERR_FAIL_COND_MSG(_parent != nullptr, "ComponentManager needs a parent node in the scene tree.");
}

void ComponentManager::_bind_methods() {}
