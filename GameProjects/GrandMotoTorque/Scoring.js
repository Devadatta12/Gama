// HANDLES THE SCORING EVENT WHEN CHARACTER CRASHES WITH A MOVING PLATFORM.
COLLECTIBLE_ITEM = 8;
var uuid = getCalleeUUID();
var collidedUuid = getCollidedUUID();
var collidedType = getCollidedType();
var racecar = gethandle("character"+uuid.toString());
if (collidedUuid === 14){
    racecar.x = 35;
    racecar.y = 200;
}
else if (collidedUuid === 15){
    racecar.x = 575;
    racecar.y = 500;
}
else {
    if(collidedType === COLLECTIBLE_ITEM){
        racecar.score += 100;
        print('Reached Finish Line!!!');
    }
}
