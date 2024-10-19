package gameoflife.organisms.plants;

import gameoflife.organisms.Organism;
import gameoflife.structs.Vector;

public class Guarana extends Plant {

    public Guarana(Vector position){
        super("+", 0, position);
    }

    @Override
    public void Collision(Organism other){

        other.AddStrength(3);
        world.Log(other.getClass().getSimpleName()+" got strength from eating a guarana");
        this.Kill();
    }
    
}
