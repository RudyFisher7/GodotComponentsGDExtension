//
// Created by rfish on 5/3/2025.
//

#pragma once

#include "core/component.h"
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/builtin_types.hpp>
#include <godot_cpp/variant/variant.hpp>

class InteractableComponent : public Component {
    GDCLASS(InteractableComponent, Component);

public:
    Ref<Texture2D> icon;

public:
    InteractableComponent();
    Ref<Texture2D> get_icon() const;
    void set_icon(const Ref<Texture2D> &value);

    virtual bool get_is_repreatable() const;
    virtual bool get_is_approachable() const;
    virtual bool get_is_busy() const;
    virtual bool get_has_notice() const;
    virtual void set_has_notice(bool value);
    virtual bool start();

protected:
    static void _bind_methods();
};
