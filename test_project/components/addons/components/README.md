# Godot Components GDExtension

## Description
This GDExtention adds components to Godot.

## Basic Usage
### Inspector
1. Inspect any Node in the SceneTree
2. You'll find controls in the inspector for managing this Node's components.
	a. Use the "Add Component" OptionButton to choose a component to add to the Node.
	b. Use the "Remove Component" OptionButton to remove a component from the Node.
	c. The new Component class supports Node's SceneTree-related notification functions (e.g., _physics_process(), _input(), etc.). Use the "Add/Remove Runtime Manager" Button to add/remove a child Node that will manage these notifications for the components during runtime.
	d. The "Copy Components Property Path To Clipboard" button allows for convenient pasting for use in get(), set(), and MultiplayerSynchronizer's SceneReplicationConfig.

### Code
1. Use ComponentCollection's static functions to manage a Node's components (get_components(), set_components(), remove_components(), has_components()).
2. Use ComponentCollection's other functions to manage any specific component within the collection.

## Details
- Components inherit Resource to take advantage of its property serialization API.
- Unlike Resource, Components are "made local to scene" by default. This allows inheriting scenes to add/remove any components and override their exported properties without affecting the base scene. There is no need to use "editable children" to expose the child Nodes' details in the inheriting scene.
- GDScripts can extend Component just like any other engine class.
	a. GDScripts must have a class_name specified for them to show up in the inspector and to avoid collisions with other component types.
	b. IMPORTANT: If you rename a GDScript Component's class_name, it is recommended to reload the project and re-save your scenes.


## Current Known Issues
- The editor plugin causes the ComponentRuntimeManager to process in editor instead of just in runtime (like tool annotation).
- The inheriting scene's components don't get their exported properties updated from the base scene's like regular Resources should. You will need to delete the inheriting scene and re-instantiate it after editing the base scene.
