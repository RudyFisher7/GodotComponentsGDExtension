#class_name ComponentCollection
extends Resource
##TODO:: implement this gdscript version of this class

@export var _components: Dictionary[StringName, Component] = {}


static func get_components(obj: Object) -> ComponentCollection:
	return obj.get_meta(&"components") as ComponentCollection


static func has_components(obj: Object) -> bool:
	return obj.has_meta(&"components")


static func set_components(obj: Object, components: ComponentCollection) -> void:
	obj.set_meta(&"components", components)


static func remove_components(obj: Object) -> void:
	obj.remove_meta(&"components")


func get_component(type: StringName) -> Component:
	var result: Component = null
	
	if _components.has(type):
		result = _components[type]
	
	return result


func call_components_enter_tree() -> void:
	for c: Component in _components.values():
		c._enter_tree()


func call_components_exit_tree() -> void:
	for c: Component in _components.values():
		c._exit_tree()


func call_components_ready() -> void:
	for c: Component in _components.values():
		c._ready()


func call_components_process(delta: float) -> void:
	for c: Component in _components.values():
		c._process(delta)


func call_components_physics_process(delta: float) -> void:
	for c: Component in _components.values():
		c._physics_process(delta)


func call_components_input(event: InputEvent) -> bool:
	for c: Component in _components.values():
		if c._input(event):
			return true
	
	return false


func call_components_unhandled_input(event: InputEvent) -> bool:
	for c: Component in _components.values():
		if c._unhandled_input(event):
			return true
	
	return false


func call_components_unhandled_key_input(event: InputEvent) -> bool:
	for c: Component in _components.values():
		if c._unhandled_key_input(event):
			return true
	
	return false


func call_components_shortcut_input(event: InputEvent) -> bool:
	for c: Component in _components.values():
		if c._shortcut_input(event):
			return true
	
	return false
