extends EditorInspectorPlugin


var EditorPropertyComponentContainer: GDScript = preload("res://addons/components/editor_property_component_container.gd")
var _object: Node = null


#func _init() -> void:
	#EditorInterface.get_inspector().resource_selected.connect(_on_resource_selected)


func _can_handle(object: Object) -> bool:
	return not object is Component and not object is ComponentCollection


#func _parse_property(
		#object: Object,
		#type: Variant.Type,
		#name: String,
		#hint_type: PropertyHint,
		#hint_string: String,
		#usage_flags: int,
		#wide: bool,
#) -> bool:
	#var result: bool = false
	#
	#if hint_string == "ComponentCollection" or name.begins_with("metadata/components"):
		#return false
		#add_property_editor(name, EditorPropertyComponentContainer.new())
		#result = true
		#
		#print("%s %s %s %s %s %s %s" % [
				#object.get_class(),
				#type,
				#name,
				#hint_type,
				#hint_string,
				#usage_flags,
				#wide,
		#])
	#
	#return result


func _parse_end(object: Object) -> void:
	_object = object as Node
	var spacer := Control.new()
	spacer.custom_minimum_size = Vector2(0.0, 32.0)
	add_custom_control(spacer)
	
	var dict := ComponentEditor.build()
	dict[&"add_button"].pressed.connect(_on_add_button_pressed.bind(dict[&"add_picker"]))
	dict[&"remove_button"].pressed.connect(_on_remove_button_pressed.bind(dict[&"remove_picker"]))
	dict[&"add_picker"].resource_changed.connect(_on_add_resource_changed.bind(dict[&"add_picker"]))
	dict[&"remove_picker"].resource_changed.connect(_on_remove_resource_changed.bind(dict[&"remove_picker"]))
	dict[&"add_remove_runtime_button"].pressed.connect(_on_add_remove_runtime_button_pressed)
	
	add_custom_control(dict[&"root"])


func _on_resource_selected(resource: Resource, path: String) -> void:
	print(resource)
	print(path)


func _on_add_resource_changed(resource: Resource, picker: EditorResourcePicker) -> void:
	picker.edited_resource = null
	if not _object or not resource:
		return
	
	var component := resource as Component
	
	if not ComponentCollection.has_components(_object):
		ComponentCollection.set_components(_object, ComponentCollection.new())
	
	var container := ComponentCollection.get_components(_object)
	
	if container.has_component(component.get_component_class()):
		var toaster := EditorInterface.get_editor_toaster() as EditorToaster
		var warning_message: String = "%s already has a component of type %s. If you intended to overwrite it, remove it first." % [_object.name, component.get_component_class()]
		toaster.push_toast(warning_message, EditorToaster.SEVERITY_ERROR)
		printerr(warning_message)
		return
	
	container.set_component(component.duplicate(true) as Component)
	_object.notify_property_list_changed()


func _on_remove_resource_changed(resource: Resource, picker: EditorResourcePicker) -> void:
	picker.edited_resource = null
	if not _object or not ComponentCollection.has_components(_object):
		return
	
	var container := ComponentCollection.get_components(_object)
	container.remove_component((resource as Component).get_component_class())
	if container.is_empty():
		ComponentCollection.remove_components(_object)
	_object.notify_property_list_changed()


func _on_add_button_pressed(picker: EditorResourcePicker) -> void:
	if not _object:
		return
	
	var component := picker.edited_resource as Component
	
	if not ComponentCollection.has_components(_object):
		ComponentCollection.set_components(_object, ComponentCollection.new())
	
	var container := ComponentCollection.get_components(_object)
	
	if container.has_component(component.get_component_class()):
		var toaster := EditorInterface.get_editor_toaster() as EditorToaster
		var warning_message: String = "%s already has a component of type %s. If you intended to overwrite it, remove it first." % [_object.name, component.get_component_class()]
		toaster.push_toast(warning_message, EditorToaster.SEVERITY_ERROR)
		printerr(warning_message)
		return
	
	container.set_component(component.duplicate(true) as Component)
	_object.notify_property_list_changed()


func _on_remove_button_pressed(picker: EditorResourcePicker) -> void:
	if not _object or not ComponentCollection.has_components(_object):
		return
	
	var container := ComponentCollection.get_components(_object)
	container.remove_component((picker.edited_resource as Component).get_component_class())
	if container.is_empty():
		ComponentCollection.remove_components(_object)
	_object.notify_property_list_changed()


func _on_add_remove_runtime_button_pressed() -> void:
	if not _object:
		return
	
	if not ComponentCollection.has_components(_object):
		var toaster := EditorInterface.get_editor_toaster() as EditorToaster
		var warning_message: String = "%s has no components. Add one first." % _object.name
		toaster.push_toast(warning_message, EditorToaster.SEVERITY_ERROR)
		printerr(warning_message)
		return
	
	if _object.has_node(^"./ComponentRuntimeManager"):
		print("remove ComponentRuntimeManager")
		_object.remove_child(_object.get_node(^"./ComponentRuntimeManager"))
	else:
		print("add ComponentRuntimeManager")
		var child := ComponentRuntimeManager.new()
		_object.add_child(child, true, Node.INTERNAL_MODE_DISABLED)
		child.owner = EditorInterface.get_edited_scene_root()
