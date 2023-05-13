package controler;

import model.coord.Coord;
import model.Game;

import java.util.ArrayList;

public class ControllerTUI {
    private Game game;

    public ControllerTUI(Game game) {
        this.game = game;
    }

    public void execute(String commandName, ArrayList<String> args) {
        if (args.size() != 2) return;
        int x = Integer.parseInt(args.get(0));
        int y = Integer.parseInt(args.get(1));
        if (commandName.equalsIgnoreCase("OPEN")) {
            game.openBox(new Coord(x, y));
            game.checkWinner();
        } else if (commandName.equalsIgnoreCase("FLAG")) {
            game.applyFlag(new Coord(x, y));
        }
    }
}
