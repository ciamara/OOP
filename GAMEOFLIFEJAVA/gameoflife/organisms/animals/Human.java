package gameoflife.organisms.animals;

import gameoflife.structs.Vector;

public class Human extends Animal {
    
    Vector nextMove;
    public int ability = -5;

    public Human(Vector position) {
        super("|",5, 4, position);
        nextMove = new Vector(0,0);
    }

    public void SetMove(int x, int y) {
        if(!world.OnBoard(this.GetPos()))
            return;
        nextMove = new Vector(x,y);
    }

    public void Action(){

        AddAge();

        if(ability>=0){

            Vector[] burnables = {
                new Vector(0, 1),
                new Vector(1, 1),
                new Vector(1, 0),
                new Vector(1, -1),
                new Vector(0, -1),
                new Vector(-1, -1),
                new Vector(-1, 0),
                new Vector(-1, 1)
            };

            for (Vector burnable : burnables) {

                Vector position = GetPos().Add(burnable);

                if (world.OnBoard(position)) {

                    if (world.GetOrganism(position) != null) {

                        world.Log(this.getClass().getSimpleName() + " burned a " + world.GetOrganism(position).getClass().getSimpleName() + "...");
                        world.GetOrganism(position).Kill();
                    }
                }
            }
        }

        if(ability> -5){
            ability--;
        }

        if(nextMove.GetX() == 0 && nextMove.GetY() == 0){
            return;
        }
        SetPos(GetPos().Add(nextMove));
        SetMove(0,0);
    }

    public void ActivateAbility() {
        if(ability != -5){
            return;
        }
        ability = 5;
    }

    public void SetAbility(int amount) {
        ability = amount;
    }
}
