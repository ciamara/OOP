package gameoflife.organisms.animals;

import gameoflife.structs.Vector;
import gameoflife.structs.RandomGenerator;

public class Antelope extends Animal {

    public Antelope(Vector position) {
        super("&", 4, 4, position);
    }

    @Override
    public void Action() {
        super.Action();
        super.Action();
    }

    @Override
    public boolean Escaped(){

        RandomGenerator r = new RandomGenerator();
        if(r.random(0,1)==0){
            return false;
        }
        Vector[] allowedMoves = world.GetPossibleMoves();
        int move = 0;
        while(!world.OnBoard(GetPos().Add(allowedMoves[move]))||world.GetOrganism(GetPos().Add(allowedMoves[move]))!=null){
            move++;
            if(move==allowedMoves.length) {
                world.Log(this.getClass().getSimpleName() + "failed to escape!");
                return false;
            }
        }
        this.RevertMove();
        world.Log(this.getClass().getSimpleName()+" has escaped!");
        return true;
    }
}
