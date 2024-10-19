package gameoflife;

import gameoflife.structs.Vector;

import java.awt.*;

import java.io.Serializable;
import java.util.ArrayList;


public class RecWorld extends World implements Serializable {

    transient Rectangle[][] board;
    final Vector[] directions = {new Vector(0, 1), new Vector(1, 0), new Vector(0, -1), new Vector(-1, 0)};

    public RecWorld(int width, int height) {
        this.width = width;
        this.height = height;
        round = 0;
        organisms = new ArrayList<>();
        logs = "World\n";
    }

    @Override
    public Vector[] GetPossibleMoves() {
        return directions;
    }
    
}
