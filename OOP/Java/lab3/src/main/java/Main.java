import scores.HighScores;
import scores.Score;
import view.gui.SweeperGUI;
import view.tui.SweeperTUI;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String gameMode = getGameMode().toUpperCase();
        switch (gameMode.toUpperCase()) {
            case "GUI": new SweeperGUI(); break;
            case "TUI": new SweeperTUI(); break;
            default: break;
        }
    }

    private static String getGameMode() {
        System.out.println("Please, choose game mode (GUI/TUI):");
        Scanner scanner = new Scanner(System.in);
        String gameMode = scanner.nextLine();
        return gameMode;
    }
}