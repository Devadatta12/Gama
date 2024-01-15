// HANDLES THE SCORING EVENT WHEN CHARACTER CRASHES WITH A MOVING PLATFORM.
var uuid = getCalleeUUID()
var astronaut = gethandle("character"+uuid.toString());
pos = astronaut.x;
if (astronaut.resultant == 0){
    astronaut.score -= 1;
    print('Score = '+astronaut.score);
}