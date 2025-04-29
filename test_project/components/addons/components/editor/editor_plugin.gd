@tool
extends EditorPlugin


var plugin


func _enter_tree():
	plugin = preload("uid://ckaegtesi67y8").new()
	var undo_redo := get_undo_redo() as EditorUndoRedoManager # TODO:: integrate with undo/redo commands
	add_inspector_plugin(plugin)


func _exit_tree():
	remove_inspector_plugin(plugin)
