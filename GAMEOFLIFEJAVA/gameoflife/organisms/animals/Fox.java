package gameoflife.organisms.animals;

import gameoflife.structs.Vector;
import gameoflife.structs.RandomGenerator;

public class Fox extends Animal {
    
    public Fox(Vector position) {
        super("^", 3, 7, position);
    }

    @Override
    public void Action() {

        RandomGenerator r = new RandomGenerator();

        AddAge();

        Vector[] allowedMoves = world.GetPossibleMoves();
        for(int move = r.random(0,allowedMoves.length-1); move<=world.GetPossibleMoves().length*2; move++){
            if(!world.OnBoard(GetPos().Add(allowedMoves[move%world.GetPossibleMoves().length])))
                continue;
            if(world.GetOrganism(GetPos().Add(allowedMoves[move%world.GetPossibleMoves().length]))==null){
                SetPos(GetPos().Add(allowedMoves[move%world.GetPossibleMoves().length]));
                return;
            }
            if(world.GetOrganism(GetPos().Add(allowedMoves[move%world.GetPossibleMoves().length])).GetStrength()<=GetStrength()){
                SetPos(GetPos().Add(allowedMoves[move%world.GetPossibleMoves().length]));
                return;
            }
            else{
                world.Log("Fox avoided a stronger enemy");
            }
        }
    }
}
