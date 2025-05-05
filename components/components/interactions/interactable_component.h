//
// Created by rfish on 5/3/2025.
//

#pragma once

#include "core/component.h"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/variant.hpp>

class InteractableComponent : public Component {
    GDCLASS(InteractableComponent, Component);

public:
    bool get_is_repreatable() const;

protected:
    static void _bind_methods();
};
