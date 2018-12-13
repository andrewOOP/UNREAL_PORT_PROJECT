# UNREAL_PORT_PROJECT

# Unity / Unreal Differences

Sprites
--------------
* Unity - Sprite is 2D by default
* Unreal - Paper2D is 3D by default

Collision
--------------
* Unity - You have to set up a 3D capsule collider to the 2D sprite
* Unreal - Collision is built in and automatic in Paper2D

Objects
--------------
* Unity - GameObject is everything
* Unreal - UObject is everything, but the main things build out of that are Actors (like GameObjects), Pawns (which can be controlled by AI or a player), and Controller (which is how an AI or player controls a Pawn)

Scripts
--------------
* Unity - Scripts are components put on a GameObject to give functionality
* Unreal - UObjects ARE the scripts. Components are then put on top of that like Meshes

Prefabs
--------------
* Unity - Prefabs are prefabs
* Unreal - It's kinda like Blueprints, but blueprints should be thought of more like extending a C++ object with more functionality and options.

External Libraries
--------------
* Unity - Not really anything. Only a few things have to be imported to extend a script
* Unreal - Almost nothing is included. It's best practice to use forward declaration in the header file using "class someclass". In the cpp file, that's where you should include the headers of external classes like Paper2D.
