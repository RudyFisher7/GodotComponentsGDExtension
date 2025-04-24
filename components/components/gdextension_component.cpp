
#include "gdextension_component.h"

#include <godot_cpp/core/print_string.hpp>


void GDExtensionComponent::_bind_methods() {
    //
}

void GDExtensionComponent::_enter_tree() {
    print_line("hello from gdextension!");
}
