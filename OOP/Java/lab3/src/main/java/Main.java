
import view.gui.SweeperGUI;
import view.tui.SweeperTUI;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        GameInterface gameInterface = getGameInterface();
        switch (gameInterface) {
            case TUI -> new SweeperTUI();
            case GUI -> new SweeperGUI();
        }
    }

    private static GameInterface getGameInterface() {
        System.out.println("Press \"1\" to choose TEXT INTERFACE");
        System.out.println("Press \"2\" to choose GRAPHIC INTERFACE");

        String input = null;

        while (true) {
            Scanner scanner = new Scanner(System.in);
            input = scanner.nextLine();
            if (input.equals("1")) return GameInterface.TUI;
            if (input.equals("2")) return GameInterface.GUI;
        }
    }

    enum GameInterface {
        TUI,
        GUI
    }
}