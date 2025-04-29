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

void CharacterBodyFirstPersonController3D::enter_tree(Node *p_parent) {
    _parent = p_parent;
}

void CharacterBodyFirstPersonController3D::ready() {
    if (!_character_body) {
        _try_set_character_body();
    }

    if (!_camera) {
        _try_set_camera();
    }
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
    _try_set_character_body();
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
    _try_set_camera();
}

CharacterBody3D *CharacterBodyFirstPersonController3D::get_character_body() const {
    return _character_body;
}

Camera3D *CharacterBodyFirstPersonController3D::get_camera() const {
    return _camera;
}

void CharacterBodyFirstPersonController3D::_bind_methods() {
    ClassDB::bind_method(D_METHOD("set_character_body_path", "value"), &CharacterBodyFirstPersonController3D::set_character_body_path);
    ClassDB::bind_method(D_METHOD("get_character_body_path"), &CharacterBodyFirstPersonController3D::get_character_body_path);
    ClassDB::bind_method(D_METHOD("set_camera_path", "value"), &CharacterBodyFirstPersonController3D::set_camera_path);
    ClassDB::bind_method(D_METHOD("get_camera_path"), &CharacterBodyFirstPersonController3D::get_camera_path);

    ClassDB::bind_method(D_METHOD("get_character_body"), &CharacterBodyFirstPersonController3D::get_character_body);
    ClassDB::bind_method(D_METHOD("get_camera"), &CharacterBodyFirstPersonController3D::get_camera);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "character_body_path", PropertyHint::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "CharacterBody3D"), "set_character_body_path", "get_character_body_path");
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "camera_path", PropertyHint::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Camera3D"), "set_camera_path", "get_camera_path");
}

void CharacterBodyFirstPersonController3D::_handle_rotation(float p_delta) {
    //
}

void CharacterBodyFirstPersonController3D::_try_set_character_body() {
    if (_parent) {
        Node *node = get_node_or_null(character_body_path);
        _character_body = Object::cast_to<CharacterBody3D>(node);
    }
}

void CharacterBodyFirstPersonController3D::_try_set_camera() {
    if (_parent) {
        Node *node = get_node_or_null(camera_path);
        _camera = Object::cast_to<Camera3D>(node);
    }
}
