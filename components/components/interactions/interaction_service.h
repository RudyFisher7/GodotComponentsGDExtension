//
// Created by rfish on 5/5/2025.
//

#pragma once

#include "components/interactions/interactor.h"
#include "components/interactions/interactable.h"
#include "components/interactions/components/interactor_component.h"
#include "components/interactions/components/interactable_component.h"

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

using namespace godot;

class InteractionService : public Object {
    GDCLASS(InteractionService, Object);

public:
    static TypedArray<InteractableComponent> get_approachable_and_understood_interaction_datas(Ref<Interactor> interactor, Ref<Interactable> interactable);

};
