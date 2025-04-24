//
// Created by rfish on 4/24/2025.
//

#include "component_manager.h"

#include <godot_cpp/core/error_macros.hpp>


void ComponentManager::_enter_tree() {
    _parent = get_parent();
    ERR_FAIL_COND_MSG(_parent == nullptr, vformat("%s needs a parent Node in the scene tree.", get_path()));
    if (!_parent->has_meta(StringName("components"))) {
        WARN_PRINT(vformat("%s's parent Node has no components to manage.", get_path()));
    } else {
        Variant variant = _parent->get_meta(StringName("components"));
        _components = (Ref<ComponentContainer>) Object::cast_to<ComponentContainer>(variant); // use c-cast to disambiguate
    }
}

void ComponentManager::_bind_methods() {}
