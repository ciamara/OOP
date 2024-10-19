package gameoflife.organisms.animals;

import gameoflife.structs.Vector;
import gameoflife.organisms.Organism;
import gameoflife.structs.RandomGenerator;

public class Turtle extends Animal {

    public Turtle(Vector position) {
        super("@", 2, 1, position);
    }

    @Override
    public void Action() {

        RandomGenerator r = new RandomGenerator();

        int move = r.random(0,1);
        if(move==0)
            return;
        super.Action();
    }

    @Override
    public void Collision(Organism other) {
        
        if(other.GetStrength()<5 && this.getClass()!=other.getClass()){
            world.Log("Turtle blocked the attack!");
            other.RevertMove();
            return;
        }
        super.Collision(other);
    }
    
}
