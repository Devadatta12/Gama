// HANDLES THE SCORING EVENT WHEN CHARACTER CRASHES WITH A MOVING PLATFORM.
var uuid = getCalleeUUID()
var astronaut = gethandle("character"+uuid.toString());
astronaut.score -= 1
print('Score decreased')