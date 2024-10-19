package gameoflife.organisms.plants;

import gameoflife.structs.Vector;
import gameoflife.organisms.Organism;

public class DeadlyNightshade extends Plant {

    public DeadlyNightshade(Vector position){
        super("%", 99, position);
    }

    @Override
    public void Collision(Organism other){

        world.Log(this.getClass().getSimpleName() +" poisoned a " + other.getClass().getSimpleName() + " and died...");
        other.Kill();
        this.Kill();
    }
    
}
