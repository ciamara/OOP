package gameoflife;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.stream.Collectors;

import gameoflife.organisms.Organism;
import gameoflife.organisms.animals.Human;
import gameoflife.structs.Vector;
import gameoflife.structs.RandomGenerator;

public abstract class World {

    int height;
    int width;
    int round;
    Human human;
    String logs;
    ArrayList<Organism> organisms;
    Vector initialPosition;
    static World currentInstance = null;

    static public World GetInstance(int width, int height) {
        currentInstance = new RecWorld(width, height);
        return currentInstance;
    }

    static public World GetInstance() {
        return currentInstance;
    }

    public void DoRound(){
        logs = "";
        ++round;
        organisms = new ArrayList<>(organisms.stream().filter(o -> o.GetStrength() >= 0).collect(Collectors.toList()));
        organisms.sort(Organism::Compare);
        int size = organisms.size();
        for (int i = 0; i < size; i++) {
            if(organisms.get(i).GetStrength()>=0)
                organisms.get(i).Action();
        }
    }

    public void Log(String message){
        logs+=message+"\n";
    }

    public void SetRound(int amount) {
        round = amount;
    }

    public Boolean OnBoard(Vector position){
        return position.GetX()>=0 && position.GetX()<width && position.GetY()>=0 && position.GetY()<height;
    }
    public void AddOrganism(String name, Vector position){
        Organism o = Organism.Spawn(this, name, position);
        organisms.add(o);
        o.previousPosition = o.position;
        Log(o.getClass().getSimpleName() + " appeared at " + position.ToString());
    }

    public Organism GetOrganism(Vector position) {
        return organisms.stream().filter(o -> o.GetPos().IsEqual(position)).findFirst().orElse(null);
    }

    public abstract Vector[] GetPossibleMoves();

    void SpawnOrganisms(){
        RandomGenerator r = new RandomGenerator();
        AddOrganism("animals.Human", new Vector(r.random(0,width-1), r.random(0,height-1)));
        human = (Human) organisms.get(0);
        AddOrganism("animals.Sheep", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("animals.Sheep", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("animals.Wolf", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("animals.Fox", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("animals.Turtle", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("animals.Antelope", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("plants.Grass", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("plants.Dandelion", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("plants.DeadlyNightshade", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("plants.Guarana", new Vector(r.random(0,width-1), r.random(0,height-1)));
        AddOrganism("plants.SosnowskyHogweed", new Vector(r.random(0,width-1), r.random(0,height-1)));
    }

    public Human GetHuman(){
        return human;
    }

    public void SaveGame(){

        String filePath = "save.txt";

        try {
            FileWriter writer = new FileWriter(filePath);
            
            writer.write(height + "|" + width + "|" + round + "\n");

            for (Organism organism : organisms) {
                String name = organism.getClass().getCanonicalName();
                if(name=="gameoflife.organisms.animals.Human"){
                    writer.write(name + "|" + organism.position.GetX() + "|" + organism.position.GetY() + "|" + organism.GetStrength() + "|" + organism.GetAge() + "|" + human.ability + "\n");
                }
                else {
                    writer.write(name + "|" + organism.position.GetX() + "|" + organism.position.GetY() + "|" + organism.GetStrength() + "|" + organism.GetAge() + "\n");
                }
            }
            Log("Game saved successfully!");
            writer.close();
        } catch (IOException e) {
            Log("An error occurred while saving the game data: " + e.getMessage());
            e.printStackTrace();
        }
    }

    public void LoadGame() {

        String[] data;
        String filePath = "save.txt";
        int x, y, strength, age, ability;
        Vector vector;
        String line;

        try {
            BufferedReader reader = new BufferedReader(new FileReader(filePath));

            line = reader.readLine();
           
            while ((line = reader.readLine()) != null) {

                data = line.split("\\|");

                String fullname = data[0];
                String[] parts = fullname.split("\\.");
                String name;

                name = parts[parts.length - 2] + "." + parts[parts.length - 1];

                x = Integer.parseInt(data[1]);
                y = Integer.parseInt(data[2]);
                vector = new Vector(x, y);
                strength = Integer.parseInt(data[3]);
                age = Integer.parseInt(data[4]);

                AddOrganism(name, vector);
                Organism organism = GetOrganism(vector);

                if (organism instanceof Human) {

                    human = (Human) organism;
                    human.SetStrength(strength);
                    human.SetAge(age);
                    ability = Integer.parseInt(data[5]);
                    human.SetAbility(ability);
                }
            }
            reader.close();
        } catch (IOException e) {
            System.out.println("An error occurred while loading the game data: " + e.getMessage());
            e.printStackTrace();
        }
        Log("Game loaded successfully!");
    }
}
