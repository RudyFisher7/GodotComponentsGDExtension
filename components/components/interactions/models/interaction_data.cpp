//
// Created by rfish on 5/3/2025.
//

#include "interaction_data.h"

InteractionData::InteractionData(
        Ref<InteractorComponent> interactor_component,
        Ref<InteractableComponent> interactable_component
) : interactor_component(interactor_component), interactable_component(interactable_component) {}