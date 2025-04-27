extends Node


@export var spawn_scene: PackedScene = null
@export var spawner: MultiplayerSpawner = null
@export var spawn_root: Node = null
@export var label: Label = null


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	assert(spawn_scene != null)
	assert(spawner != null)
	assert(spawn_root != null)
	assert(label != null)
	
	multiplayer.peer_connected.connect(_on_peer_connected)
	multiplayer.peer_disconnected.connect(_on_peer_disconnected)
	
	spawner.add_spawnable_scene(spawn_scene.resource_path)
	
	var args: PackedStringArray = OS.get_cmdline_args()
	if OS.is_debug_build() and args.size() >= 2:
		get_window().title = args[1]
		push_warning("**THIS SESSION IS: %s**" % args[1])
	if OS.is_debug_build() and args.size() >= 6:
		get_window().position = Vector2i(args[2].to_int(), args[3].to_int())
		get_window().size = Vector2i(args[4].to_int(), args[5].to_int())


func _on_peer_connected(id: int) -> void:
	label.text = "peer connected: %s" % id
	if multiplayer.is_server():
		_add_object(id)


func _on_peer_disconnected(id: int) -> void:
	label.text = "peer disconnected: %s" % id


func _on_host_button_pressed() -> void:
	var peer := ENetMultiplayerPeer.new()
	var error: Error = peer.create_server(2020)
	assert(error == OK)
	multiplayer.multiplayer_peer = peer
	_add_object(1)


func _on_join_button_pressed() -> void:
	var peer := ENetMultiplayerPeer.new()
	var error: Error = peer.create_client("localhost", 2020)
	assert(error == OK)
	multiplayer.multiplayer_peer = peer


func _on_erase_button_pressed() -> void:
	if spawn_root.get_child_count() > 0:
		var child: Node = spawn_root.get_child(0)
		spawn_root.remove_child(child)
		child.queue_free()


func _add_object(id: int) -> void:
	var node: Node = spawn_scene.instantiate()
	node.name = str(id)
	spawn_root.add_child(node)
