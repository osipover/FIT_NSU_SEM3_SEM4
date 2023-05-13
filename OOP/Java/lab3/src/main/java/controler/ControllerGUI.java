package controler;

import model.coord.Coord;
import model.Game;


public class ControllerGUI {
    private Game game;

    public ControllerGUI(Game game) {
        this.game = game;
    }

    public void pressLeftButton(Coord coord) {
        game.openBox(coord);
        game.checkWinner();
    }

    public void pressRightButton(Coord coord) {
        game.applyFlag(coord);
    }

}
