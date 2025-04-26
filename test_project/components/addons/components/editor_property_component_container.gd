extends EditorProperty


var _root_vbox: VBoxContainer = null
var _container_picker: EditorResourcePicker = null
var _component_picker: EditorResourcePicker = null
var _component_manager_root: VBoxContainer = null
var _current_value

var _is_updating: bool = false


func _init() -> void:
	_root_vbox = VBoxContainer.new()
	_root_vbox.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_root_vbox.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	add_child(_root_vbox)
	
	property_changed.connect(_on_property_changed)


func _ready() -> void:
	var new_value = get_edited_object()[get_edited_property()]
	
	_build_component_container_editor()
	
	if new_value != null:
		_build_component_manager_editor()
	
	_current_value = new_value


func _update_property() -> void:
	_is_updating = true
	var new_value = get_edited_object()[get_edited_property()]
	print("current: ", _current_value)
	print("new: ", new_value)
	
	_change_editor(_current_value, new_value)
	
	_current_value = new_value
	_is_updating = false


func _on_property_changed(property: StringName, value, field: StringName, changing: bool) -> void:
	print("property changed: %s %s %s %s" % [
			property,
			value,
			field,
			changing,
	])


func _on_component_container_changed(resource: Resource) -> void:
	print("current: ", str(_current_value))
	print("resource: ", str(resource))
	print("_is_updating: ", str(_is_updating))
	
	if _is_updating:
		return
	
	emit_changed(get_edited_property(), resource)


func _on_component_container_selected(resource: Resource, inspect: bool) -> void:
	print("selected: resource: ", str(resource))


func _on_add_button_pressed() -> void:
	print("component to add: ", str(_component_picker.edited_resource))


func _change_editor(previous_value, current_value) -> void:
	if previous_value == null and current_value != null:
		_build_component_manager_editor()
	elif previous_value != null and current_value == null:
		_component_manager_root.queue_free()
		_component_manager_root = null
		_component_picker = null
		_container_picker.edited_resource = current_value


func _build_component_container_editor() -> void:
	_container_picker = EditorResourcePicker.new()
	_container_picker.base_type = "ComponentCollection"
	add_focusable(_container_picker)
	_container_picker.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_container_picker.custom_minimum_size = Vector2(180.0 , 32.0)
	_container_picker.resource_changed.connect(_on_component_container_changed)
	_container_picker.resource_selected.connect(_on_component_container_selected)
	
	var value = get_edited_object()[get_edited_property()]
	if value != null:
		_container_picker.edited_resource = value as ComponentCollection
	
	_root_vbox.add_child(_container_picker)


func _build_component_manager_editor() -> void:
	_component_manager_root = VBoxContainer.new()
	_component_manager_root.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_component_manager_root.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	
	var hbox := HBoxContainer.new()
	hbox.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	
	var add_button := Button.new()
	add_button.icon = preload("res://icon.svg")
	add_button.expand_icon = true
	add_button.custom_minimum_size = Vector2(32.0, 32.0)
	add_button.pressed.connect(_on_add_button_pressed)
	
	_component_picker = EditorResourcePicker.new()
	_component_picker.base_type = "Component"
	add_focusable(_component_picker)
	_component_picker.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	_component_picker.custom_minimum_size = Vector2(180.0 , 32.0)
	
	var error_message_label := Label.new()
	error_message_label.text = "Cannot add Component. Component of this type already exists."
	
	hbox.add_child(add_button)
	hbox.add_child(_component_picker)
	_component_manager_root.add_child(hbox)
	_component_manager_root.add_child(error_message_label)
	_root_vbox.add_child(_component_manager_root)
