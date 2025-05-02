//
// Created by rfish on 5/1/2025.
//

#include "interactor.h"

Interactor::Interactor() :
        ray_cast3d_path(),
        area3d_path(),
        collision_exception3d_paths(),
        _components(),
        _interactables(),
        _area3d(nullptr),
        _ray_cast3d(nullptr),
        _exceptions3d()
{
    //
}

void Interactor::ready() {
    if (!ray_cast3d_path.is_empty()) {
        _try_set_ray_cast3d();
    }

    if (!_ray_cast3d && !area3d_path.is_empty()) {
        _try_set_area3d();
    }

    _try_set_exceptions3d();
}

void Interactor::physics_process(double p_delta) {
    //
}

bool Interactor::is_physics_process_overridden() const {
    return _ray_cast3d != nullptr;
}

void Interactor::_bind_methods() {

    ADD_SIGNAL(MethodInfo("interactable_entered", PropertyInfo(Variant::OBJECT, "interactable")));
    ADD_SIGNAL(MethodInfo("interactable_exited", PropertyInfo(Variant::OBJECT, "interactable")));
}

void Interactor::_on_area_entered(Area3D *area) {
    //
}

void Interactor::_on_area_exited(Area3D *area) {
    //
}

void Interactor::_on_body_entered(Node3D *body) {
    //
}

void Interactor::_on_body_exited(Node3D *body) {
    //
}

void Interactor::_try_set_ray_cast3d() {
    Node *node = get_node_or_null(ray_cast3d_path);
    if (node) {
        _ray_cast3d = Object::cast_to<RayCast3D>(node);
    }
}

void Interactor::_try_set_area3d() {
    Node *node = get_node_or_null(area3d_path);
    if (node) {
        _area3d = Object::cast_to<Area3D>(node);
    }
}

void Interactor::_try_set_exceptions3d() {
    _exceptions3d.resize(collision_exception3d_paths.size());
    for (int64_t i = 0; i < collision_exception3d_paths.size(); ++i) {
        Node *node = get_node_or_null(area3d_path);
        if (node) {
            collision_exception3d_paths.insert(i, Object::cast_to<CollisionObject3D>(node));
        }
    }
}
