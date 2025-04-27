extends Node


# Test ComponentCollection's emit_changed()
func _enter_tree() -> void:
	return#FIXME::
	ComponentCollection.object_set_component(self, TestGDExtensionComponent.new())
	await get_tree().create_timer(1.0).timeout
	ComponentCollection.object_set_component(self, TestGDScriptComponent.new())
	await get_tree().create_timer(1.0).timeout
	ComponentCollection.object_remove_component(self, &"TestGDScriptComponent")
