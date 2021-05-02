extends KinematicBody

var current_station
var is_done

const SPEED = 3
const ARRIVED_EPSILON = 0.2
const STATIONS = [[3.4, 4], [-4.985, -16.543], [13.54, 0], [-13.496, 10.402], [-6.861, 16.122], [-0.699, -27.976]]

# Called when the node enters the scene tree for the first time.
func _ready():
	current_station = 0
	is_done = false

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	if (current_station >= len(STATIONS)):
		is_done = true
		
	if (!is_done):
		var deltax = STATIONS[current_station][0] - self.transform.origin.x
		var deltaz = STATIONS[current_station][1] - self.transform.origin.z

		self.transform.origin.x += delta*deltax*SPEED
		self.transform.origin.z += delta*deltaz*SPEED
		
		if (abs(deltax) < ARRIVED_EPSILON && abs(deltaz) < ARRIVED_EPSILON):
			current_station += 1

#func _physics_process(delta):
#	var dir = Vector3()
#
#	if (Input.is_action_pressed("move_fw")):
#		dir += -camera.basis[2]
#	if (Input.is_action_pressed("move_bw")):
#		dir += camera.basis[2]
#	if (Input.is_action_pressed("move_lw")):
#		dir += -camera.basis[0]
#	if (Input.is_action_pressed("move_rw")):
#		dir += camera.basis[0]
#
#
#	dir.y = 0
#	dir = dir.normalized()
#
#	velocity.y += delta * gravity
#
#	var hv = velocity
#	hv.y = 0
#
#	var new_pos = dir * SPEED
#	var accel = DE_ACCELERATION
#
#	if (dir.dot(hv) > 0):
#		accel = ACCELERATION
#
#	hv = hv.linear_interpolate(new_pos, accel*delta)
#
#	velocity.x = hv.x
#	velocity.z = hv.z
#
#	velocity = move_and_slide(velocity, Vector3(0,0,0))
