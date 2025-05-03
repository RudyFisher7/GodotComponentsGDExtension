//
// Created by rfish on 5/3/2025.
//

#pragma once

#include "core/component.h"
#include "components/interactions/interactable_component.h"
#include "components/interactions/interactor_component.h"

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

class InteractionData : public RefCounted {
    GDCLASS(InteractionData, RefCounted);

public:
    InteractorComponent *interactor_component;
    InteractableComponent * interactable_component;

    InteractionData(InteractorComponent *interactor_component, InteractableComponent *interactable_component);
};
