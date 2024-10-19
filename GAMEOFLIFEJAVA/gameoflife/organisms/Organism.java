package gameoflife.organisms;

import gameoflife.structs.Vector;
import gameoflife.World;

import java.io.Serializable;
import java.lang.reflect.InvocationTargetException;

public abstract class Organism implements Serializable {

    protected World world;
    private int strength;
    private final int initiative;
    private int age;
    private final String icon;
    public Vector position;
    public Vector previousPosition;

    static public String[] AddableOrganisms = {
        "animals.Wolf",
        "animals.Sheep",
        "animals.Fox",
        "animals.Turtle",
        "animals.Antelope",
        "plants.Grass",
        "plants.Guarana",
        "plants.DeadlyNightshade",
        "plants.Dandelion",
        "plants.SosnowskyHogweed",
    };

    protected Organism(String icon, int strength, int initiative, Vector position) {
        world = World.GetInstance();
        this.strength = strength;
        this.initiative = initiative;
        this.age = 0;
        this.icon = icon;
        this.position = position;
    }

    public static Organism Spawn(World world, String name, Vector position) {
        try{
            if(!name.contains("gameoflife.organisms"))
                name = "gameoflife.organisms." + name;
            return (Organism) Class.forName(name).getConstructor(Vector.class).newInstance(position);
        } catch (ClassNotFoundException | NoSuchMethodException | InstantiationException | IllegalAccessException | InvocationTargetException e) {
            e.printStackTrace();
        }
        return null;
    }

    public abstract void Action();

    public abstract void Collision(Organism other);

    public void Kill() {
        position = new Vector(-1,-1);
        strength = -1;
    }

    public int GetStrength() {
        return strength;
    }

    public void AddStrength(int strength) {
        this.strength += strength;
    }

    public void SetStrength(int amount) {
        this.strength = amount;
    }

    public int GetInitiative() {
        return initiative;
    }

    public int GetAge() {
        return age;
    }

    public void AddAge() {
        this.age++;
    }

    public void SetAge(int amount) {
        this.age = amount;
    }

    public Vector GetPos() {
        return position;
    }

    public boolean Escaped(){
        return false;
    }

    public boolean SetPos(Vector position) {

        if (!world.OnBoard(position)){
            return false;
        }
        world.Log(getClass().getSimpleName() + " moved to " + position.ToString());
        previousPosition = this.position;
        Organism other = world.GetOrganism(position);
        if (other!=null&&other!=this) {
            other.Collision(this);
        }
        this.position = position;
        return true;
    }

    public void RevertMove() {
        SetPos(previousPosition);
    }

    public String GetIcon() {
        return icon;
    }

    public int Compare(Organism organism) {
        if (this.initiative < organism.initiative){
            return 1;
        }
        else if (this.initiative > organism.initiative){
            return -1;
        }
        else {
            return Integer.compare(this.age, organism.age);
        }
    }
}
