//
// Created by rfish on 4/27/2025.
//

#include "character_body_first_person_controller_3d.h"

#include <godot_cpp/classes/engine.hpp>

CharacterBodyFirstPersonController3D::CharacterBodyFirstPersonController3D() :
        character_body_path(),
        camera_path(),
        move_speed(2.5),
        mouse_sensitivity(0.1, 0.1),
        _character_body(nullptr),
        _camera(nullptr),
        _current_rotation_velocity(0.0, 0.0) {

}

void CharacterBodyFirstPersonController3D::enter_tree() {
    //
}

void CharacterBodyFirstPersonController3D::physics_process(double p_delta) {

}

bool CharacterBodyFirstPersonController3D::input(const Ref<InputEvent> &p_event) {
    bool result = false;
    return result;
}

bool CharacterBodyFirstPersonController3D::is_physics_process_overridden() const {
    return true;
}

bool CharacterBodyFirstPersonController3D::is_input_overridden() const {
    return true;
}

NodePath CharacterBodyFirstPersonController3D::get_character_body_path() const {
    return character_body_path;
}

void CharacterBodyFirstPersonController3D::set_character_body_path(const NodePath &p_character_body_path) {
    character_body_path = p_character_body_path;

    if (_scene_tree) {
        Node *node = get_node_or_null(character_body_path);
        _character_body = Object::cast_to<CharacterBody3D>(node);
    }
}

float CharacterBodyFirstPersonController3D::get_move_speed() const {
    return move_speed;
}

void CharacterBodyFirstPersonController3D::set_move_speed(float p_move_speed) {
    move_speed = p_move_speed;
}

Vector2 CharacterBodyFirstPersonController3D::get_mouse_sensitivity() const {
    return mouse_sensitivity;
}

void CharacterBodyFirstPersonController3D::set_mouse_sensitivity(const Vector2 &p_mouse_sensitivity) {
    mouse_sensitivity = p_mouse_sensitivity;
}

NodePath CharacterBodyFirstPersonController3D::get_camera_path() const {
    return camera_path;
}

void CharacterBodyFirstPersonController3D::set_camera_path(const NodePath &p_value) {
    camera_path = p_value;

    if (_scene_tree) {
        Node *node = get_node_or_null(camera_path);
        _camera = Object::cast_to<Camera3D>(node);
    }
}

void CharacterBodyFirstPersonController3D::_bind_methods() {
    //
}

void CharacterBodyFirstPersonController3D::_handle_rotation(float p_delta) {
    //
}
