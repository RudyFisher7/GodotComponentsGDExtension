//
// Created by rfish on 5/1/2025.
//

#pragma once

#include "core/component.h"
#include "components/interactions/interactable.h"
#include "components/interactions/interactor_component.h"
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

public:
    NodePath ray_cast3d_path;
    NodePath area3d_path;
    TypedArray<NodePath> collision_exception3d_paths;

protected:
    TypedArray<InteractorComponent> _components;
    TypedArray<Interactable> _interactables;

    RayCast3D *_ray_cast3d;
    Area3D *_area3d;
    TypedArray<CollisionObject3D> _exceptions3d;

public:
    Interactor();

    void ready() override;
    void physics_process(double p_delta) override;
    bool is_physics_process_overridden() const override;

protected:
    static void _bind_methods();

    void _on_area_entered(Area3D *area);
    void _on_area_exited(Area3D *area);

    void _on_body_entered(Node3D *body);
    void _on_body_exited(Node3D *body);

    void _try_set_ray_cast3d();
    void _try_set_area3d();
    void _try_set_exceptions3d();

};
