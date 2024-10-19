package gameoflife.organisms.animals;

import gameoflife.structs.Vector;
import gameoflife.structs.RandomGenerator;
import gameoflife.organisms.Organism;

public class Animal extends Organism {

    public Animal(String icon, int strength, int initiative, Vector position) {
        super(icon, strength, initiative, position);
    }

    public void Action() {

        RandomGenerator r = new RandomGenerator();
        AddAge();

        Vector[] allowedMoves = world.GetPossibleMoves();
        int move = r.random(0,allowedMoves.length-1);

        while(!SetPos(GetPos().Add(allowedMoves[move]))){
            move++;
            move%=allowedMoves.length;
        }
    }

    public void Collision(Organism other) {

        if(this.getClass().equals(other.getClass())){
            if(this.GetAge()<10||other.GetAge()<10){
                return;
            }
            try {
                Vector[] allowedMoves = world.GetPossibleMoves();
                int move = 0;
                while(!world.OnBoard(GetPos().Add(allowedMoves[move]))||world.GetOrganism(GetPos().Add(allowedMoves[move]))!=null){
                    move++;
                    if(move==allowedMoves.length) {
                        world.Log("No place for baby " + this.getClass().getSimpleName());
                        return;
                    }
                }
                RevertMove();
                world.AddOrganism(this.getClass().getCanonicalName(), GetPos().Add(allowedMoves[move]));
            } catch (Exception e) {
                System.err.println(e.getMessage());
            }
            world.Log(this.getClass().getSimpleName()+" baby has been born");
            return;
        }
        if(this.Escaped()||other.Escaped()) {
            return;
        }
        if(this.GetStrength()>=other.GetStrength()){
            world.Log(this.getClass().getSimpleName()+" killed "+other.getClass().getSimpleName()+"!");
            other.Kill();
        } else {
            world.Log(this.getClass().getSimpleName()+" has been killed by "+other.getClass().getSimpleName()+"!");
            this.Kill();
        }
    }
    
}
