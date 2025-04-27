class_name TestGDScriptComponent
extends Component


@export var tmp_0: int = 0
@export var tmp_name: String = "temp"


func _enter_tree() -> void:
	print("GDScript entered the tree")


func _exit_tree() -> void:
	print("GDScript exited the tree")


func _ready() -> void:
	print("gdscript ready")


func _process(_delta: float) -> void:
	print("process")
#
#
#func _physics_process(_delta: float) -> void:
	#print("physics process")
#
#
#func _input(event: InputEvent) -> bool:
	#print("input: ", event.as_text())
	#return false
#
#
#func _shortcut_input(event: InputEvent) -> bool:
	#print("shortcut: ", event.as_text())
	#return false
#
#
#func _unhandled_input(event: InputEvent) -> bool:
	#print("unhandled input: ", event.as_text())
	#return false
#
#
#func _unhandled_key_input(event: InputEvent) -> bool:
	#print("unhandled key: ", event.as_text())
	#return false
