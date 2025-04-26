class_name GDComponentContainer
extends Resource


@export var _components: Dictionary[StringName, GDComponent] = {}


static func get_component_container_from(obj: Object) -> GDComponentContainer:
	return obj.get_meta(&"GDComponentContainer") as GDComponentContainer


static func get_component_from(obj: Object, type: StringName) -> GDComponent:
	var result: GDComponent = null
	var container := obj.get_meta(&"GDComponentContainer") as GDComponentContainer
	
	if container:
		result = container.get_component(type)
	
	return result


func get_component(type: StringName) -> GDComponent:
	var result: GDComponent = null
	
	if _components.has(type):
		result = _components[type]
	
	return result


func enter_tree() -> void:
	for c: GDComponent in _components.values():
		c._enter_tree()


func exit_tree() -> void:
	for c: GDComponent in _components.values():
		c._exit_tree()


func ready() -> void:
	for c: GDComponent in _components.values():
		c._ready()


func process(delta: float) -> void:
	for c: GDComponent in _components.values():
		c._process(delta)


func physics_process(delta: float) -> void:
	for c: GDComponent in _components.values():
		c._physics_process(delta)


func input(event: InputEvent, viewport: Viewport) -> void:
	for c: GDComponent in _components.values():
		c._input(event, viewport)
		if viewport.is_input_handled():
			return


func unhandled_input(event: InputEvent, viewport: Viewport) -> void:
	for c: GDComponent in _components.values():
		c._unhandled_input(event, viewport)
		if viewport.is_input_handled():
			return


func unhandled_key_input(event: InputEvent, viewport: Viewport) -> void:
	for c: GDComponent in _components.values():
		c._unhandled_key_input(event, viewport)
		if viewport.is_input_handled():
			return


func shortcut_input(event: InputEvent, viewport: Viewport) -> void:
	for c: GDComponent in _components.values():
		c._shortcut_input(event, viewport)
		if viewport.is_input_handled():
			return
