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
        _exceptions3d(),
        _raycasted_object()
{
    //
}

void Interactor::ready() {
    _try_set_exceptions3d();

    if (!ray_cast3d_path.is_empty()) {
        _try_set_ray_cast3d();
    }

    if (!_ray_cast3d && !area3d_path.is_empty()) {
        _try_set_area3d();
    }

    if (_area3d) {
        _add_overlapping_interactables();
    }
}

void Interactor::physics_process(double p_delta) {
    if (!_ray_cast3d) {
        return;
    }

    Object *previous_object = _raycasted_object;
    _raycasted_object = _ray_cast3d->get_collider();
    if (previous_object != _raycasted_object) {
        if (previous_object) {
            Node *node = Object::cast_to<Node>(previous_object);
            _erase_interactable(node);
        }

        if (_raycasted_object) {
            Node *node = Object::cast_to<Node>(_raycasted_object);
            _erase_interactable(node);
        }
    }
}

bool Interactor::is_physics_process_overridden() const {
    return _ray_cast3d != nullptr;
}

bool Interactor::start(const Ref<InteractionData> &data) {
    if (data.is_null() || data->interactable_component.is_null() || data->interactor_component.is_null()) {
        return false;
    }

    bool result = data->interactor_component->start(data->interactable_component);

    return result;
}

void Interactor::_bind_methods() {
    ADD_SIGNAL(MethodInfo("interactable_entered", PropertyInfo(Variant::OBJECT, "interactable")));
    ADD_SIGNAL(MethodInfo("interactable_exited", PropertyInfo(Variant::OBJECT, "interactable")));
}

void Interactor::_on_area_entered(Area3D *area) {
    _add_interactable(area);
}

void Interactor::_on_area_exited(Area3D *area) {
    _erase_interactable(area);
}

void Interactor::_on_body_entered(Node3D *body) {
    _add_interactable(body);
}

void Interactor::_on_body_exited(Node3D *body) {
    _erase_interactable(body);
}

void Interactor::_on_interactable_component_erased(Ref<Interactable> interactable) {
    if (interactable->get_components().is_empty()) {
        int64_t index = _interactables.find(interactable);
        if (index > -1) {
            _interactables.remove_at(index);
            interactable->disconnect("component_erased", callable_mp(this, &Interactor::_on_interactable_component_erased));
            emit_signal("interactable_exited", interactable);
        }
    }
}

void Interactor::_add_interactable(Node *node) {
    Ref<Component> component = ComponentCollection::object_get_component(node, "Interactable");
    if (component.is_valid()) {
        Ref<Interactable> interactable = Object::cast_to<Interactable>(*component);
        if (interactable.is_valid() && !_exceptions3d.has(node) && !_interactables.has(interactable)) {
            _interactables.push_back(interactable);
            interactable->connect("component_erased", callable_mp(this, &Interactor::_on_interactable_component_erased));
            emit_signal("interactable_entered", interactable);
        }
    }
}

void Interactor::_erase_interactable(Node *node) {
    Ref<Component> component = ComponentCollection::object_get_component(node, "Interactable");

    if (component.is_valid()) {
        Ref<Interactable> interactable = Object::cast_to<Interactable>(*component);
        if (interactable.is_valid()) {
            int64_t index = _interactables.find(interactable);
            if (index > -1) {
                _interactables.remove_at(index);
                interactable->disconnect("component_erased", callable_mp(this, &Interactor::_on_interactable_component_erased));
                emit_signal("interactable_exited", interactable);
            }
        }
    }
}

void Interactor::_add_overlapping_interactables() {
    TypedArray<Area3D> areas = _area3d->get_overlapping_areas();
    TypedArray<Node3D> bodies = _area3d->get_overlapping_bodies();

    for (int64_t i = 0; i < areas.size(); ++i) {
        _add_interactable(Object::cast_to<Node>(areas[i]));
    }

    for (int64_t i = 0; i < bodies.size(); ++i) {
        _add_interactable(Object::cast_to<Node>(bodies[i]));
    }
}

void Interactor::_try_set_ray_cast3d() {
    _ray_cast3d = nullptr;
    Node *node = get_node_or_null(ray_cast3d_path);
    if (node) {
        _ray_cast3d = Object::cast_to<RayCast3D>(node);
    }
}

void Interactor::_try_set_area3d() {
    if (_area3d) {
        _area3d->disconnect("area_entered", callable_mp(this, &Interactor::_on_area_entered));
        _area3d->disconnect("area_exited", callable_mp(this, &Interactor::_on_area_exited));

        _area3d->disconnect("body_entered", callable_mp(this, &Interactor::_on_body_entered));
        _area3d->disconnect("body_exited", callable_mp(this, &Interactor::_on_body_exited));
    }

    _area3d = nullptr;

    Node *node = get_node_or_null(area3d_path);
    if (node) {
        _area3d = Object::cast_to<Area3D>(node);
    }

    if (_area3d) {
        _area3d->connect("area_entered", callable_mp(this, &Interactor::_on_area_entered));
        _area3d->connect("area_exited", callable_mp(this, &Interactor::_on_area_exited));

        _area3d->connect("body_entered", callable_mp(this, &Interactor::_on_body_entered));
        _area3d->connect("body_exited", callable_mp(this, &Interactor::_on_body_exited));

        if (!_area3d->is_monitoring()) {
            WARN_PRINT("Area3D in Interactor is not monitoring. Set monitoring to true to get interactions.");
        }
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
