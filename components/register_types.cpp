

#include "register_types.h"

#include "core/component.h"
#include "core/component_collection.h"
#include "core/component_runtime_manager.h"
#include "components/test_gdextension_component.h"
#include "components/character_body_first_person_controller_3d.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_components_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }

    GDREGISTER_RUNTIME_CLASS(ComponentRuntimeManager);
    ClassDB::register_class<ComponentCollection>();
    ClassDB::register_class<Component>();
    ClassDB::register_class<TestGDExtensionComponent>();
    ClassDB::register_class<CharacterBodyFirstPersonController3D>();
}

void uninitialize_components_types(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
}

extern "C" {

GDExtensionBool GDE_EXPORT components_library_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization
) {
    GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_components_types);
    init_obj.register_terminator(uninitialize_components_types);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_obj.init();
}
}
