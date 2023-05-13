package view.tui.commands.menu;

import scores.Score;
import view.tui.commands.Command;
import view.tui.commands.Console;

import java.io.FileInputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;
import java.util.Scanner;

public class HighScores implements Command {
    private final String PATH_TO_HIGH_SCORES = "C:\\Users\\osipo\\IdeaProjects\\sweeper\\src\\main\\resources\\highscores";
    private scores.HighScores highScores;

    @Override
    public void execute(ArrayList<String> args) {
        Console.clear();
        loadHighScores();
        for (Score score : highScores.getTable()) {
            System.out.println(score.toString());
        }

        System.out.println("Press \"4\" to chose EXIT");
        Scanner scanner = new Scanner(System.in);
        String line;
        while (!(line = scanner.nextLine()).equals("4")) {}
        Console.clear();
    }

    private void loadHighScores() {
        try {
            FileInputStream fileInputStream = new FileInputStream(PATH_TO_HIGH_SCORES);
            ObjectInputStream objectInputStream = new ObjectInputStream(fileInputStream);
            this.highScores = (scores.HighScores) objectInputStream.readObject();
            objectInputStream.close();
        } catch (IOException | ClassNotFoundException ex) {

        }
    }
}
