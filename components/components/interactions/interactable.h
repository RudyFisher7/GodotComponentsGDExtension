//
// Created by rfish on 5/1/2025.
//

#pragma once

#include "core/component.h"
#include "components/interactions/interactable_component.h"
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/collision_object3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/variant.hpp>

class Interactable : public Component {
    GDCLASS(Interactable, Component);

public:
    String interactable_name;

protected:
    TypedArray<InteractableComponent> _components;

public:
    Interactable();

    void ready() override;

    String get_interactable_name() const;
    void set_interactable_name(const String &value);
    TypedArray<InteractableComponent> get_components() const;
    void set_components(const TypedArray<InteractableComponent> &value);
    void add_component(const Ref<InteractableComponent> &value);
    void erase_component(const Ref<InteractableComponent> &value);
    void erase_component_at(int64_t index);

protected:
    static void _bind_methods();

    void _on_component_finished(const Ref<InteractableComponent> &emitter);
};
