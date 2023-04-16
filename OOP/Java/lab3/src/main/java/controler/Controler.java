package controler;

import model.Coord;
import model.Game;

import java.util.ArrayList;

public class Controler {
    private Game game;

    public Controler(Game game) {
        this.game = game;
    }

    public void pressLeftButton(Coord coord) {
        game.openBox(coord);
        game.checkWinner();
    }

    public void pressRightButton(Coord coord) {
        game.applyFlag(coord);
    }

    public void execute(String commandName, ArrayList<String> args) {
        if (args.size() != 2) return;
        int x = Integer.parseInt(args.get(0));
        int y = Integer.parseInt(args.get(1));
        if (commandName.equalsIgnoreCase("OPEN")) {
            pressLeftButton(new Coord(x, y));
        } else if (commandName.equalsIgnoreCase("FLAG")) {
            pressRightButton(new Coord(x, y));
        }
    }

}
