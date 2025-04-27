
#include "gdextension_component.h"

#include <godot_cpp/core/print_string.hpp>


void GDExtensionComponent::_bind_methods() {
    //
}

void GDExtensionComponent::enter_tree() {
    print_line("_enter_tree gdextension!");
}

void GDExtensionComponent::ready() {
    print_line("_ready gdextension!");
}
