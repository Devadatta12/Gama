// HANDLES THE SCORING EVENT WHEN CHARACTER CRASHES WITH A MOVING PLATFORM.
COLLECTIBLE_ITEM = 8;
DEATH_EVENT = 13;
var uuid = getCalleeUUID();
var collidedUuid = getCollidedUUID();
var collidedType = getCollidedType();
var adventurer = gethandle("character"+uuid.toString());
if (collidedUuid === 20){
    adventurer.score -= 100;
    Raise(DEATH_EVENT);
}
else if(collidedType === COLLECTIBLE_ITEM){
    adventurer.score += 10;
    print('Coin Collected!!!');
}
else {
    adventurer.score -= 2;
    print('Health decreased!!!');
}
