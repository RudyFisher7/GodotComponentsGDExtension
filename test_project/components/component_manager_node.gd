extends Node


@onready var _parent: Node = $".." as Node
@onready var _component_container: GDComponentContainer = GDComponentContainer.get_component_container_from(_parent)

func _exit_tree() -> void:
	_component_container.exit_tree()

func _ready() -> void:
	assert(_parent != null)
	assert(_component_container != null)
	_component_container.ready()

func _process(delta: float) -> void:
	_component_container.process(delta)

func _physics_process(delta: float) -> void:
	_component_container.physics_process(delta)

func _input(event: InputEvent) -> void:
	_component_container.input(event, get_viewport())

func _unhandled_input(event: InputEvent) -> void:
	_component_container.unhandled_input(event, get_viewport())

func _unhandled_key_input(event: InputEvent) -> void:
	_component_container.unhandled_key_input(event, get_viewport())

func _shortcut_input(event: InputEvent) -> void:
	_component_container.shortcut_input(event, get_viewport())
