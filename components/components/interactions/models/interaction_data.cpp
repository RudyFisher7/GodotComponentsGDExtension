//
// Created by rfish on 5/3/2025.
//

#include "interaction_data.h"

InteractionData::InteractionData(
        InteractorComponent *interactor_component,
        InteractableComponent *interactable_component
) : interactor_component(interactor_component), interactable_component(interactable_component) {}