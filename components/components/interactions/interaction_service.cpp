//
// Created by rfish on 5/5/2025.
//

#include "interaction_service.h"

TypedArray<InteractableComponent> InteractionService::get_approachable_and_understood_interaction_datas(
        Ref<Interactor> interactor,
        Ref<Interactable> interactable
) {
    TypedArray<InteractableComponent> result;

    TypedArray<InteractorComponent> interactor_components = interactor->get_components();

    for (int64_t i = 0; i < interactor_components.size(); ++i) {
        Ref<InteractorComponent> current = interactor_components[i];
        if (current->get_is_available()) {
//            Ref<InteractableComponent> interactable_current = inter//todo:: pickup here
        }
    }

    return result;
}
