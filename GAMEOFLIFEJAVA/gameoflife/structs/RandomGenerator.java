package gameoflife.structs;

import java.util.Random;

public class RandomGenerator {

    public int random(int min, int max) {
        Random rand = new Random();
        return rand.nextInt((max - min) + 1) + min;
    }
}
