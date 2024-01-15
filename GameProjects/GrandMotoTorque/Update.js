// HANDLES THE SCORING EVENT WHEN CHARACTER CRASHES WITH A MOVING PLATFORM.
var uuid = getCalleeUUID();
var car = gethandle("character"+uuid.toString());
if (car.score === 100){
    print('YOU WIN!');
}