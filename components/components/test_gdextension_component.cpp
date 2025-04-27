
#include "test_gdextension_component.h"

#include <godot_cpp/core/print_string.hpp>


void TestGDExtensionComponent::_bind_methods() {
    //
}

void TestGDExtensionComponent::enter_tree() {
    print_line("_enter_tree gdextension!");
}

void TestGDExtensionComponent::ready() {
    print_line("_ready gdextension!");
}
