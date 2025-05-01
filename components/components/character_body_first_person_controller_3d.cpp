//
// Created by rfish on 4/27/2025.
//

#include "character_body_first_person_controller_3d.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

CharacterBodyFirstPersonController3D::CharacterBodyFirstPersonController3D() :
        character_body_path(),
        camera_path(),
        move_speed(2.5),
        mouse_sensitivity(0.1, 0.1),
        _character_body(nullptr),
        _camera(nullptr),
        _current_rotation_velocity(0.0, 0.0),
        move_left(),
        move_right(),
        move_forward(),
        move_backward(),
        toggle_mouse_captured()
{

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
    if (!_camera || !_character_body) {
        return;
    }

    _handle_rotation(p_delta);

    if (!_character_body->is_on_floor()) {
        _character_body->set_velocity(_character_body->get_velocity() + (_character_body->get_gravity() * float(p_delta)));
    }

    Input *input = Input::get_singleton();

    Vector2 input_vector = input->get_vector(move_left, move_right, move_forward, move_backward);
    Vector3 direction = _character_body->get_transform().basis.xform(Vector3(input_vector.x, 0.0, input_vector.y));
    direction.normalize();

    if (! direction.is_zero_approx()) {
        Vector3 velocity = direction * move_speed;
        _character_body->set_velocity(velocity);
    } else {
        Vector3 velocity = _character_body->get_velocity().move_toward(Vector3(), move_speed);
        _character_body->set_velocity(velocity);
    }

    _character_body->move_and_slide();
}

bool CharacterBodyFirstPersonController3D::input(const Ref<InputEvent> &p_event) {
    bool result = false;

    Ref<InputEventMouseMotion> event = Object::cast_to<InputEventMouseMotion>(*p_event);
    if (event.is_valid()) {
        _current_rotation_velocity = -event->get_relative();
    } else if (p_event->is_action_released(toggle_mouse_captured)) {
        Input *input = Input::get_singleton();
        if (input->get_mouse_mode() == Input::MOUSE_MODE_CAPTURED) {
            input->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
        } else if (input->get_mouse_mode() == Input::MOUSE_MODE_VISIBLE) {
            input->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
        }
    }

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

NodePath CharacterBodyFirstPersonController3D::get_camera_path() const {
    return camera_path;
}

void CharacterBodyFirstPersonController3D::set_camera_path(const NodePath &p_value) {
    camera_path = p_value;
    _try_set_camera();
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

const StringName &CharacterBodyFirstPersonController3D::get_move_left() const {
    return move_left;
}

void CharacterBodyFirstPersonController3D::set_move_left(const StringName &p_value) {
    move_left = p_value;
}

const StringName &CharacterBodyFirstPersonController3D::get_move_right() const {
    return move_right;
}

void CharacterBodyFirstPersonController3D::set_move_right(const StringName &p_value) {
    move_right = p_value;
}

const StringName &CharacterBodyFirstPersonController3D::get_move_forward() const {
    return move_forward;
}

void CharacterBodyFirstPersonController3D::set_move_forward(const StringName &p_value) {
    move_forward = p_value;
}

const StringName &CharacterBodyFirstPersonController3D::get_move_backward() const {
    return move_backward;
}

void CharacterBodyFirstPersonController3D::set_move_backward(const StringName &p_value) {
    move_backward = p_value;
}

const StringName &CharacterBodyFirstPersonController3D::get_toggle_mouse_captured() const {
    return toggle_mouse_captured;
}

void CharacterBodyFirstPersonController3D::set_toggle_mouse_captured(const StringName &p_value) {
    toggle_mouse_captured = p_value;
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

    ClassDB::bind_method(D_METHOD("set_move_speed", "value"), &CharacterBodyFirstPersonController3D::set_move_speed);
    ClassDB::bind_method(D_METHOD("get_move_speed"), &CharacterBodyFirstPersonController3D::get_move_speed);
    ClassDB::bind_method(D_METHOD("set_mouse_sensitivity", "value"), &CharacterBodyFirstPersonController3D::set_mouse_sensitivity);
    ClassDB::bind_method(D_METHOD("get_mouse_sensitivity"), &CharacterBodyFirstPersonController3D::get_mouse_sensitivity);

    ClassDB::bind_method(D_METHOD("set_move_left", "value"), &CharacterBodyFirstPersonController3D::set_move_left);
    ClassDB::bind_method(D_METHOD("get_move_left"), &CharacterBodyFirstPersonController3D::get_move_left);
    ClassDB::bind_method(D_METHOD("set_move_right", "value"), &CharacterBodyFirstPersonController3D::set_move_right);
    ClassDB::bind_method(D_METHOD("get_move_right"), &CharacterBodyFirstPersonController3D::get_move_right);
    ClassDB::bind_method(D_METHOD("set_move_forward", "value"), &CharacterBodyFirstPersonController3D::set_move_forward);
    ClassDB::bind_method(D_METHOD("get_move_forward"), &CharacterBodyFirstPersonController3D::get_move_forward);
    ClassDB::bind_method(D_METHOD("set_move_backward", "value"), &CharacterBodyFirstPersonController3D::set_move_backward);
    ClassDB::bind_method(D_METHOD("get_move_backward"), &CharacterBodyFirstPersonController3D::get_move_backward);
    ClassDB::bind_method(D_METHOD("set_toggle_mouse_captured", "value"), &CharacterBodyFirstPersonController3D::set_toggle_mouse_captured);
    ClassDB::bind_method(D_METHOD("get_toggle_mouse_captured"), &CharacterBodyFirstPersonController3D::get_toggle_mouse_captured);

    ClassDB::bind_method(D_METHOD("get_character_body"), &CharacterBodyFirstPersonController3D::get_character_body);
    ClassDB::bind_method(D_METHOD("get_camera"), &CharacterBodyFirstPersonController3D::get_camera);

    ADD_GROUP("Required Nodes", "");
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "character_body_path", PropertyHint::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "CharacterBody3D"), "set_character_body_path", "get_character_body_path");
    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "camera_path", PropertyHint::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Camera3D"), "set_camera_path", "get_camera_path");

    ADD_GROUP("Properties", "");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "move_speed"), "set_move_speed", "get_move_speed");
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "mouse_sensitivity"), "set_mouse_sensitivity", "get_mouse_sensitivity");

    ADD_GROUP("Input Actions", "");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "move_left"), "set_move_left", "get_move_left");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "move_right"), "set_move_right", "get_move_right");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "move_forward"), "set_move_forward", "get_move_forward");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "move_backward"), "set_move_backward", "get_move_backward");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "toggle_mouse_captured"), "set_toggle_mouse_captured", "get_toggle_mouse_captured");
}

void CharacterBodyFirstPersonController3D::_handle_rotation(float p_delta) {
    Input *input = Input::get_singleton();
    if (input->get_mouse_mode() != Input::MOUSE_MODE_CAPTURED) {
        return;
    }

    if (!_current_rotation_velocity.is_zero_approx()) {
        _camera->rotate_x(_current_rotation_velocity.y * mouse_sensitivity.x * p_delta);
        _character_body->rotate_y(_current_rotation_velocity.x * mouse_sensitivity.y * p_delta);
        _current_rotation_velocity = Vector2();
    }
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
