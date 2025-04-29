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

class CharacterBodyFirstPersonController3D : public Component {
    GDCLASS(CharacterBodyFirstPersonController3D, Component);

public:
    NodePath character_body_path;
    NodePath camera_path;

    float move_speed;
    Vector2 mouse_sensitivity;

protected:
    CharacterBody3D *_character_body;
    Camera3D *_camera;
    Vector2 _current_rotation_velocity;

public:
    CharacterBodyFirstPersonController3D();
    void enter_tree(Node *p_parent) override;
    void ready() override;
    void physics_process(double p_delta) override;
    bool input(const Ref<InputEvent> &p_event) override;
    bool is_physics_process_overridden() const override;
    bool is_input_overridden() const override;

    NodePath get_character_body_path() const;
    void set_character_body_path(const NodePath &p_character_body_path);
    float get_move_speed() const;
    void set_move_speed(float p_move_speed);
    Vector2 get_mouse_sensitivity() const;
    void set_mouse_sensitivity(const Vector2 &p_mouse_sensitivity);
    NodePath get_camera_path() const;
    void set_camera_path(const NodePath &p_value);

    CharacterBody3D *get_character_body() const;
    Camera3D *get_camera() const;

protected:
    static void _bind_methods();
    virtual void _handle_rotation(float p_delta);
    void _try_set_character_body();
    void _try_set_camera();
};
