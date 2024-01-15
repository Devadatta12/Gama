DEFAULT_VELOCITY = 3;
var uuid = getCalleeUUID();
var asteroid = gethandle("movingPlatform"+uuid.toString());
time = asteroid.delta_time;
displacement = DEFAULT_VELOCITY*time;

locationX = 0;
locationY = 0;
//print("Displacement "+displacement.toString());
if (asteroid.animation === 1){
    if (asteroid.y >= 350 && !asteroid.direction){
        asteroid.x += 0;
        asteroid.y += displacement;
        asteroid.direction = 1;
    }
    else if (asteroid.y <= 180 && asteroid.direction){
        asteroid.x += 0;
        asteroid.y -= displacement;
        asteroid.direction = 0;
    }
    else if (asteroid.direction){
        asteroid.x += 0;
        asteroid.y -= displacement;
    }
    else{
        asteroid.x += 0;
        asteroid.y += displacement;
    }
} else {

    if (asteroid.x >= 600 &&  !asteroid.direction){
        asteroid.y += 0;
        asteroid.x -= displacement;
        asteroid.direction = 1;
    }
    else if (asteroid.x <= 200 && asteroid.direction){
        asteroid.y += 0;
        asteroid.x += displacement;
        asteroid.direction = 0;
    }
    else if (asteroid.direction){
        asteroid.y += 0;
        asteroid.x -= displacement;
    }
    else{
        asteroid.y += 0;
        asteroid.x += displacement;
    }
}
