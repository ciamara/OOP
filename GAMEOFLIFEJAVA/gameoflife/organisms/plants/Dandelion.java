package gameoflife.organisms.plants;

import gameoflife.structs.Vector;

public class Dandelion extends Plant {

    public Dandelion(Vector position){
        super("*", 0, position);
    }

    @Override
    public void Action(){
        
        super.Action();
        super.Action();
        super.Action();
    }
    
}
