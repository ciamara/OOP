package gameoflife.organisms.plants;

import gameoflife.structs.Vector;
import gameoflife.organisms.Organism;
import gameoflife.structs.RandomGenerator;

public class Plant extends Organism {

    public Plant(String icon, int strength, Vector position) {
        super(icon, strength, 0, position);
    }

    @Override
    public void Action() {

        RandomGenerator r = new RandomGenerator();
        AddAge();

        if(r.random(0,50)==50){

            Vector[] spreadables = {
                new Vector(0, 1),
                new Vector(1, 1),
                new Vector(1, 0),
                new Vector(1, -1),
                new Vector(0, -1),
                new Vector(-1, -1),
                new Vector(-1, 0),
                new Vector(-1, 1)
            };
    
            for (Vector spreadable : spreadables) {

                Vector newPos = GetPos().Add(spreadable);

                if (world.OnBoard(newPos) && world.GetOrganism(newPos) == null) {
                    try {
                        world.Log(this.getClass().getSimpleName() + " spreads");
                        world.AddOrganism(this.getClass().getCanonicalName(), newPos);
                        return;
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            }
        }
    }

    @Override
    public void Collision(Organism other) {

        if(this.getClass().equals(other.getClass())){
            return;
        }
        if(GetStrength()>=other.GetStrength()){
            world.Log(this.getClass().getSimpleName()+" has poisoned "+other.getClass().getSimpleName()+"!");
            other.Kill();
        } else {
            world.Log(this.getClass().getSimpleName()+" has been eaten by "+other.getClass().getSimpleName()+"!");
            this.Kill();
        }
    }
}
