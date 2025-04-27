#pragma once

#include "component.h"
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/templates/hash_set.hpp>
#include <godot_cpp/templates/hash_map.hpp>

using namespace godot;

class ComponentCollection : public Resource {
    GDCLASS(ComponentCollection, Resource)

public:
    Object *owner = nullptr;

protected:
//    TypedDictionary<StringName, Component> _components;
    HashMap<StringName, Ref<Component>> _components;
    HashSet<Ref<Component>> _process_group;
    HashSet<Ref<Component>> _physics_process_group;
    HashSet<Ref<Component>> _input_group;
    HashSet<Ref<Component>> _shortcut_input_group;
    HashSet<Ref<Component>> _unhandled_input_group;
    HashSet<Ref<Component>> _unhandled_key_input_group;

public:
    static bool has_components(Object *obj);
    static void set_components(Object *obj, const Ref<ComponentCollection> &components);
    static void remove_components(Object *obj);
    static Ref<ComponentCollection> get_components(Object *obj);

    static bool object_has_component(Object *obj, const StringName &component_class);
    static void object_set_component(Object *obj, const Ref<Component> &component);
    static void object_remove_component(Object *obj, const StringName &component_class);
    static Ref<ComponentCollection> object_get_component(Object *obj, const StringName &component_class);

    ComponentCollection();
    virtual ~ComponentCollection();

//    TypedDictionary<StringName, Component> get_component_dictionary() const;
//    void set_component_dictionary(TypedDictionary<StringName, Component> value);

    bool is_runtime_managed() const;
    bool is_empty() const;
    bool has_component(const StringName& component_class) const;
    Ref<Component> get_component(const StringName& component_class) const;
    virtual void set_component(const Ref<Component> &value);
    virtual void remove_component(StringName component_class);
    void get_component_list(List<Ref<Component>> *out) const;
    void get_component_class_list(List<StringName> *out) const;

    bool is_processing() const;
    bool is_processing_physics() const;
    bool is_processing_input() const;
    bool is_processing_shortcut_input() const;
    bool is_processing_unhandled_input() const;
    bool is_processing_unhandled_key_input() const;

    void call_components_enter_tree();
    void call_components_exit_tree();
    void call_components_ready();
    void call_components_process(double delta);
    void call_components_physics_process(double delta);

    bool call_components_input(const Ref<InputEvent> &p_event);
    bool call_components_shortcut_input(const Ref<InputEvent> &p_key_event);
    bool call_components_unhandled_input(const Ref<InputEvent> &p_event);
    bool call_components_unhandled_key_input(const Ref<InputEvent> &p_key_event);

protected:
    static void _bind_methods();
    void _get_property_list(List<PropertyInfo> *out) const;
    bool _get(const StringName &p_property, Variant &r_value) const;
    bool _set(const StringName &p_property, const Variant &p_value);

    bool _remove_component(StringName component_class);
};
