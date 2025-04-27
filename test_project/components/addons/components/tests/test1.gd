extends Node


# Test ComponentCollection's emit_changed()
func _enter_tree() -> void:
	var c := get_meta("components") as ComponentCollection
	
	c.set_component(GDExtensionComponent.new())
	await get_tree().create_timer(1.0).timeout
	c.set_component(GDScriptComponent.new())
	await get_tree().create_timer(1.0).timeout
	c.remove_component(&"GDScriptComponent")
