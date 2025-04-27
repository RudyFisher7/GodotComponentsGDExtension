extends HBoxContainer


@export var node_tmp_0: int = 0


func _on_timer_timeout() -> void:
	if is_multiplayer_authority():
		$Label.text = str(get_meta("tmp_meta"))


func _on_line_edit_text_changed(new_text: String) -> void:
	if is_multiplayer_authority():
		set_meta("tmp_meta", new_text)
