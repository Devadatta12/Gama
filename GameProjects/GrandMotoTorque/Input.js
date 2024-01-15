// Raising event based which game is being played.
CLOCKWISE = 1;
ANTICLOCKWISE = 2;
var inputType = getInputType();
var uuid = getCalleeUUID();
var racecar = gethandle("character"+uuid.toString());
if (inputType === 0){
    INCREASE_HEALTH_EVENT = 33
    Raise(INCREASE_HEALTH_EVENT)
}
if(inputType === CLOCKWISE){
    racecar.angle = 1;
    // OR CHANGE TEXTURE.
// CHANGE ANGLE.
}
if(inputType === ANTICLOCKWISE){
    racecar.angle = -1;
// CHANGE ANGLE.
}