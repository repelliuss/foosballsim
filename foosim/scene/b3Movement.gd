extends KinematicBody

var current_station
var is_done

const SPEED = 2
const ARRIVED_EPSILON = 0.025
const STATIONS = [4.131, -3.993, 2.295]

# Called when the node enters the scene tree for the first time.
func _ready():
	current_station = 0
	is_done = false

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	
	if (current_station >= len(STATIONS)):
		is_done = true
		
	if (!is_done):
		var deltax = STATIONS[current_station] - self.transform.origin.x

		self.transform.origin.x += delta*deltax*SPEED
		
		if (abs(deltax) < ARRIVED_EPSILON):
			current_station += 1
