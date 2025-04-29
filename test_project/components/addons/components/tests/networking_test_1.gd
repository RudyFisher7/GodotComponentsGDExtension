extends HBoxContainer


@export var tmp_resource := TestGDScriptComponent.new()


func _on_timer_timeout() -> void:
	if is_multiplayer_authority():
		$Label.text = str(get_meta("tmp_meta"))
	var c := ComponentCollection.object_get_component(self, &"TestGDScriptComponent") as TestGDScriptComponent
	if not c:
		printerr("No TestGDScriptComponent")
		return
	
	push_warning("c.tmp_0: ", str(c.tmp_0))
	$Label2.text = str(c.tmp_0)


func _on_line_edit_text_changed(new_text: String) -> void:
	if is_multiplayer_authority():
		set_meta("tmp_meta", new_text)


func _on_spin_box_value_changed(value: float) -> void:
	if is_multiplayer_authority():
		var c := ComponentCollection.object_get_component(self, &"TestGDScriptComponent") as TestGDScriptComponent
		if not c:
			printerr("No TestGDScriptComponent")
			return
		c.tmp_0 = value
		print("assigned to: ", str(c.tmp_0))
