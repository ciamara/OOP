package gameoflife;

import java.util.Scanner;

import gameoflife.organisms.Organism;
import gameoflife.structs.Vector;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class GameOfLife {

    static World world;
    private JButton[][] fields;
    private JTextArea textArea;
    
    public static void main(String[] args) {

        SwingUtilities.invokeLater(() -> {
            GameOfLife game = new GameOfLife();
            game.start();
        });
    }

    public void start() {

        Scanner scanner = new Scanner(System.in);
        int height;
        int width;

        System.out.print("Enter board height: ");
        height = scanner.nextInt();
        System.out.print("Enter board width: ");
        width = scanner.nextInt();

        scanner.close();

        world = World.GetInstance(width, height);
        world.SpawnOrganisms();

        JFrame frame = new JFrame("Game Of Life 2024, Tamara Mruk 197584");

        frame.getContentPane().setBackground(Color.BLACK);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);

        createBoard(frame, height, width);

        SwingUtilities.invokeLater(() -> {
            createLog();
            createMenu(frame);
            drawOrganisms();
        });
    }

    private void createBoard(JFrame frame, int height, int width) {

        frame.getContentPane().removeAll();

        JPanel boardPanel = new JPanel();
        boardPanel.setLayout(new GridLayout(height, width));
        boardPanel.setBackground(Color.BLACK);

        fields = new JButton[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                JButton field = new JButton();
                field.setForeground(Color.WHITE);
                field.setBackground(Color.BLACK);
                field.addActionListener(new FieldClickListener());
                field.addMouseListener(new FieldMouseListener());
                boardPanel.add(field);
                fields[i][j] = field;
            }
        }

        frame.getContentPane().add(boardPanel, BorderLayout.CENTER);
        createMenu(frame);
        frame.revalidate();
        frame.repaint();
    }

    private void createLog() {

        JFrame frame = new JFrame("Logs");

        frame.getContentPane().setBackground(Color.BLACK);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        textArea = new JTextArea();
        textArea.setEditable(false);
        textArea.setBackground(Color.BLACK);
        textArea.setForeground(Color.WHITE);

        JScrollPane scrollPane = new JScrollPane(textArea);
        frame.getContentPane().add(scrollPane);

        updateLog();

        frame.setSize(300, 500);
        frame.setVisible(true);
    }

    private class FieldClickListener implements ActionListener {

        @Override
        public void actionPerformed(ActionEvent e) {

            JButton clickedField = (JButton) e.getSource();
            final int[] coordinates = {-1, -1};

            for (int i = 0; i < fields.length; i++) {

                for (int j = 0; j < fields[i].length; j++) {

                    if (fields[i][j] == clickedField) {
                        coordinates[0] = j;
                        coordinates[1] = i;
                        break;
                    }
                }
                
            }

            JPopupMenu popupMenu = new JPopupMenu();
            String[] organisms = {
                "Grass", "Dandelion", "Guarana", "DeadlyNightshade", 
                "SosnowskyHogweed", "Sheep", "Wolf", "Fox", "Turtle", "Antelope"
            };

            for (String organism : organisms) {

                JMenuItem menuItem = new JMenuItem(organism);
                menuItem.setBackground(Color.BLACK);
                menuItem.setForeground(Color.WHITE); 
                menuItem.addActionListener(new ActionListener() {
                    @Override
                    public void actionPerformed(ActionEvent e) {

                        switch (organism) {
                            case "Grass":
                                world.AddOrganism("plants.Grass",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Dandelion":
                                world.AddOrganism("plants.Dandelion",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Guarana":
                                world.AddOrganism("plants.Guarana",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "DeadlyNightshade":
                                world.AddOrganism("plants.DeadlyNightshade",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "SosnowskyHogweed":
                                world.AddOrganism("plants.SosnowskyHogweed",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Sheep":
                                world.AddOrganism("animals.Sheep",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Wolf":
                                world.AddOrganism("animals.Wolf",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Fox":
                                world.AddOrganism("animals.Fox",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Turtle":
                                world.AddOrganism("animals.Turtle",new Vector(coordinates[0], coordinates[1]));
                                break;
                            case "Antelope":
                                world.AddOrganism("animals.Antelope",new Vector(coordinates[0], coordinates[1]));
                                break;
                            default:
                                break;
                        }
                        drawOrganisms();
                    }
                });
                popupMenu.add(menuItem);
            }
            popupMenu.show(clickedField, 0, 0);
        }
    }

    private static class FieldMouseListener implements MouseListener {

        @Override
        public void mouseClicked(MouseEvent e) {}

        @Override
        public void mousePressed(MouseEvent e) {}

        @Override
        public void mouseReleased(MouseEvent e) {}

        @Override
        public void mouseEntered(MouseEvent e) {
            JButton field = (JButton) e.getSource();
            field.setBackground(Color.DARK_GRAY); 
        }

        @Override
        public void mouseExited(MouseEvent e) {
            JButton field = (JButton) e.getSource();
            field.setBackground(Color.BLACK); 
        }
    }

    private void createMenu(JFrame frame) {

        JPanel menuPanel = new JPanel();
        menuPanel.setLayout(new GridLayout(0, 1));
        menuPanel.setBackground(Color.BLACK);

        JButton[] buttons = new JButton[]{
            new JButton("Move Up"),
            new JButton("Move Left"),
            new JButton("Move Down"),
            new JButton("Move Right"),
            new JButton("Next Round"),
            new JButton("Ability"),
            new JButton("Save Game"),
            new JButton("Load Game")
        };

        for (JButton button : buttons) {
            button.setBackground(Color.BLACK);
            button.setForeground(Color.WHITE);
            menuPanel.add(button);
        }

        for (JButton button : buttons) {

            button.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    String action = button.getText();
                    switch (action) {
                        case "Move Up":
                            world.human.SetMove(0,-1);
                            break;
                        case "Move Left":
                            world.human.SetMove(-1,0);
                            break;
                        case "Move Down":
                            world.human.SetMove(0,1);
                            break;
                        case "Move Right":
                            world.human.SetMove(1,0);
                            break;
                        case "Next Round":
                            world.DoRound();
                            updateLog();
                            drawOrganisms();
                            break;
                        case "Ability":
                            if((world.human.ability>-5)&&(world.human.ability<0)){
                                world.Log("Ability on cooldown!");
                            }
                            else if(world.human.ability>=0){
                                world.Log("Ability is currently being used");
                            }
                            world.human.ActivateAbility();
                            updateLog();
                            break;
                        case "Save Game":
                            world.SaveGame();
                            break;
                        case "Load Game":
                            try {
                                String[] data;
                                String filePath = "save.txt";
                                int height, width, round;

                                BufferedReader reader = new BufferedReader(new FileReader(filePath));
                    
                                String line = reader.readLine();

                                reader.close();
                                
                                data = line.split("\\|");
                    
                                if (data != null) {
                    
                                    height = Integer.parseInt(data[0]);
                                    width = Integer.parseInt(data[1]);
                                    round = Integer.parseInt(data[2]);
                        
                                    world = World.GetInstance(width, height);
                                    world.SetRound(round);

                                    world.LoadGame();
                                    createBoard(frame, height, width);
                                    updateLog();
                                    drawOrganisms();
                                    
                                } else {
                                System.out.println("Failed to load game data.");
                                }
                            } catch (IOException ex) {
                                System.out.println("An error occurred while loading the game data: " + ex.getMessage());
                                ex.printStackTrace();
                            }
                            break;
                        default:
                            break;
                    }
                }
            });
        }
        frame.add(menuPanel, BorderLayout.WEST);
    }

    private void drawOrganisms() {

        for (JButton[] row : fields) {

            for (JButton button : row) {

                button.setText("");
            }
        }

        for (Organism organism : world.organisms) {

            int x = organism.position.GetX();
            int y = organism.position.GetY();

            if ((x >= 0 && x < fields.length && y >= 0 && y < fields[0].length)&&(organism.GetStrength()>=0)) {
                JButton button = fields[y][x];
                String o = organism.getClass().getCanonicalName();

                switch(o){
                    case "gameoflife.organisms.plants.Grass":
                        button.setForeground(Color.GREEN);
                        button.setText("🌱");
                        break;
                    case "gameoflife.organisms.plants.Dandelion":
                        button.setForeground(Color.YELLOW);
                        button.setText("🌼");
                        break;
                    case "gameoflife.organisms.plants.Guarana":
                        button.setForeground(Color.RED);
                        button.setText("🌹");
                        break;
                    case "gameoflife.organisms.plants.DeadlyNightshade":
                        button.setForeground(Color.BLUE);
                        button.setText("🍇");
                        break;
                    case "gameoflife.organisms.plants.SosnowskyHogweed":
                        button.setForeground(Color.WHITE);
                        button.setText("💀");
                        break;
                    case "gameoflife.organisms.animals.Sheep":
                        button.setForeground(Color.WHITE);
                        button.setText("🐑");
                        break;
                    case "gameoflife.organisms.animals.Wolf":
                        button.setForeground(Color.LIGHT_GRAY);
                        button.setText("🐺");
                        break;
                    case "gameoflife.organisms.animals.Fox":
                        button.setForeground(Color.ORANGE);
                        button.setText("🦊");
                        break;
                    case "gameoflife.organisms.animals.Turtle":
                        button.setForeground(Color.GREEN);
                        button.setText("🐢");
                        break;
                    case "gameoflife.organisms.animals.Antelope":
                        button.setForeground(Color.YELLOW);
                        button.setText("🦌");
                        break;
                    case "gameoflife.organisms.animals.Human":
                        button.setForeground(Color.PINK);
                        button.setText("👤");
                        break;
                    
                }
            }
        }
        SwingUtilities.getWindowAncestor(fields[0][0]).revalidate();
        SwingUtilities.getWindowAncestor(fields[0][0]).repaint();
    }

    private void updateLog() {

        if (textArea != null) {

            textArea.setText(""); 

            textArea.append("ROUND: " + world.round + "\n");
            textArea.append("ABILITY: " + world.human.ability + "\n\n");

            textArea.append(world.logs);
        }
    }
}