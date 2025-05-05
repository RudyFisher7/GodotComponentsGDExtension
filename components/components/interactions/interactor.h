//
// Created by rfish on 5/1/2025.
//

#pragma once

#include "core/component.h"
#include "core/component_collection.h"
#include "components/interactions/interactable.h"
#include "components/interactions/interactable_component.h"
#include "components/interactions/interactor_component.h"
#include "components/interactions/models/interaction_data.h"

#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/collision_object3d.hpp>
#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/ray_cast3d.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/variant.hpp>

class Interactor : public Component {
    GDCLASS(Interactor, Component);

protected:
    NodePath _ray_cast3d_path;
    NodePath _area3d_path;
    TypedArray<NodePath> _collision_exception3d_paths;
    TypedArray<InteractorComponent> _components;

    TypedArray<Interactable> _interactables;

    RayCast3D *_ray_cast3d;
    Area3D *_area3d;
    TypedArray<CollisionObject3D> _exceptions3d;

    Object *_raycasted_object;

public:
    Interactor();

    void ready() override;
    void physics_process(double p_delta) override;
    bool is_physics_process_overridden() const override;
    const NodePath &get_ray_cast3d_path() const;
    void set_ray_cast3d_path(const NodePath &value);
    const NodePath &get_area3d_path() const;
    void set_area3d_path(const NodePath &value);
    TypedArray<NodePath> get_collision_exception3d_paths() const;
    void set_collision_exception3d_paths(const TypedArray<NodePath> &value);
    TypedArray<InteractorComponent> get_components() const;
    void set_components(const TypedArray<InteractorComponent> &value);

    bool start(const Ref<InteractionData> &data);

protected:
    static void _bind_methods();

    void _on_area_entered(Area3D *area);
    void _on_area_exited(Area3D *area);

    void _on_body_entered(Node3D *body);
    void _on_body_exited(Node3D *body);
    void _on_interactable_component_erased(Ref<Interactable> interactable);

    void _add_interactable(Node *node);
    void _erase_interactable(Node *node);
    void _add_overlapping_interactables();

    void _try_set_ray_cast3d();
    void _try_set_area3d();
    void _try_set_exceptions3d();

};
