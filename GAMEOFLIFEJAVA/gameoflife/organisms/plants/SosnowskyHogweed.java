package gameoflife.organisms.plants;

import gameoflife.structs.Vector;
import gameoflife.organisms.Organism;
import gameoflife.organisms.animals.Animal;

public class SosnowskyHogweed extends Plant {

    public SosnowskyHogweed(Vector position){
        super("$", 10, position);
    }

    @Override
    public void Action(){

        Vector[] poisonables = {
            new Vector(0, 1),
            new Vector(1, 1),
            new Vector(1, 0),
            new Vector(1, -1),
            new Vector(0, -1),
            new Vector(-1, -1),
            new Vector(-1, 0),
            new Vector(-1, 1)
        };

        for(Vector poisonable : poisonables){

            Vector position = GetPos().Add(poisonable);

            if(world.OnBoard(position)) {

                if (world.GetOrganism(position) != null) {

                    if (world.GetOrganism(position) instanceof Animal){

                        world.Log(this.getClass().getSimpleName() + " poisoned a " + world.GetOrganism(position).getClass().getSimpleName() + "...");
                        world.GetOrganism(position).Kill();
                    }
                }
            }
        }
        super.Action();
    }

    @Override
    public void Collision(Organism other){

        other.Kill();
        this.Kill();
    }
}
