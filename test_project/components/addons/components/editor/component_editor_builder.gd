class_name ComponentEditorBuilder
extends Control


static func build() -> Dictionary[StringName, Control]:
	var result: Dictionary[StringName, Control] = {}
	
	var root := PanelContainer.new()
	root.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	root.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	
	var skeleton := VBoxContainer.new()
	skeleton.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	skeleton.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	
	# header
	
	#var header := VBoxContainer.new()
	#skeleton.add_child(header)
	#
	#var header_text := Label.new()
	#header_text.text = "Components"
	#header_text.size_flags_horizontal = Control.SIZE_SHRINK_CENTER
	#header.add_child(header_text)
	
	# body
	
	var row0 := HBoxContainer.new()
	row0.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row0.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	
	var add_label := Label.new()
	add_label.text = "Add Component:"
	add_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_RIGHT
	add_label.custom_minimum_size = Vector2(160.0, 0.0)
	#add_label.disabled = true
	row0.add_child(add_label)
	
	var add_picker := EditorResourcePicker.new()
	add_picker.base_type = "Component"
	add_picker.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row0.add_child(add_picker)
	
	skeleton.add_child(row0)
	
	var row1 := HBoxContainer.new()
	row1.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row1.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	
	var remove_label := Label.new()
	remove_label.text = "Remove Component:"
	remove_label.horizontal_alignment = HORIZONTAL_ALIGNMENT_RIGHT
	remove_label.custom_minimum_size = Vector2(160.0, 0.0)
	#remove_label.disabled = true
	row1.add_child(remove_label)
	
	var remove_picker := EditorResourcePicker.new()
	remove_picker.base_type = "Component"
	remove_picker.size_flags_horizontal = Control.SIZE_EXPAND_FILL
	row1.add_child(remove_picker)
	
	skeleton.add_child(row1)
	
	var row2 := Button.new()
	row2.size_flags_horizontal = Control.SIZE_SHRINK_CENTER
	row2.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	row2.text = "Add/Remove Runtime Manager"
	skeleton.add_child(row2)
	
	var row3 := Button.new()
	row3.size_flags_horizontal = Control.SIZE_SHRINK_CENTER
	row3.size_flags_vertical = Control.SIZE_SHRINK_BEGIN
	row3.text = "Copy Components Property Path To Clipboard"
	skeleton.add_child(row3)
	
	root.add_child(skeleton)
	
	result[&"root"] = root
	result[&"add_picker"] = add_picker
	result[&"remove_picker"] = remove_picker
	result[&"add_remove_runtime_button"] = row2
	result[&"copy_property_path_button"] = row3
	
	return result
