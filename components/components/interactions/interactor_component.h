//
// Created by rfish on 5/1/2025.
//

#pragma once

#include "core/component.h"
#include "components/interactions/interactable_component.h"

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/collision_object3d.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/variant.hpp>

class InteractorComponent : public Component {
    GDCLASS(InteractorComponent, Component);

public:
    InteractorComponent();
    virtual StringName get_understood_interactable_component_class() const;
    virtual bool get_is_available() const;
    virtual bool get_can_interact_with(const Ref<InteractableComponent> &target) const;
    virtual bool get_is_cooling_down() const;
    virtual bool start(const Ref<InteractableComponent> &target);

protected:
    static void _bind_methods();
};
