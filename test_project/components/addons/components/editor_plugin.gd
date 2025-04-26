@tool
extends EditorPlugin


var plugin
var section: Control


func _enter_tree():
	plugin = preload("res://addons/components/editor_inspector_plugin.gd").new()
	section = preload("res://addons/components/inspector_components_section.tscn").instantiate() as Control
	add_inspector_plugin(plugin)
	add_control_to_dock(EditorPlugin.DOCK_SLOT_RIGHT_UL, section)
	add_custom_type("GDComponent", "Resource", preload("res://addons/components/component.gd"), preload("res://icon.svg"))


func _exit_tree():
	remove_custom_type("GDComponent")
	remove_control_from_docks(section)
	remove_inspector_plugin(plugin)
	
	section.free()
