package model;

import model.cell.Cell;
import model.coord.Coord;
import model.field.LowerLayer;
import model.field.UpperLayer;
import model.ranges.Ranges;
import model.state.GameState;

public class Game {
    private GameState state;
    private LowerLayer lowerLayer;
    private UpperLayer upperLayer;

    public Game(int cols, int rows, int totalBombs) {
        Ranges.setSize(new Coord(cols, rows));
        this.lowerLayer = new LowerLayer(totalBombs);
        this.upperLayer = new UpperLayer();
    }

    public void start() {
        upperLayer.init();
        state = GameState.WAIT;
    }

    public boolean isOver() {
        return (state != GameState.RUN && state != GameState.WAIT);
    }

    public void checkWinner() {
        if (state == GameState.RUN) {
            if (lowerLayer.getCountOfBombs() == upperLayer.getCountOfClosedCell()) {
                state = GameState.WON;
            }
        }
    }

    public final GameState getState() {
        return this.state;
    }

    public Cell getCell(Coord coord) {
        if (upperLayer.get(coord) == Cell.OPENED)
            return lowerLayer.get(coord);
        else
            return upperLayer.get(coord);
    }

    public void openBox(Coord coord) {
        if (state == GameState.WAIT) {
            lowerLayer.init(coord);
            state = GameState.RUN;
        }
        if (state != GameState.RUN) return;

        Cell cell = upperLayer.get(coord);
        if (cell == Cell.OPENED) return;
        if (cell == Cell.FLAGED) return;
        if (cell == Cell.CLOSED) {
            cell = lowerLayer.get(coord);
            if (cell == Cell.BOMB) {
                openBomb(coord);
                openAllBombs(coord);
                state = GameState.LOSE;
                return;
            }
            if (cell == Cell.ZERO) { openCellsAround(coord); return; }
            upperLayer.setOpenedToCell(coord);
        }
    }

    private void openAllBombs(Coord coordBomb) {
        for (Coord coord : Ranges.getAllCoords()) {
            if (lowerLayer.get(coord) == Cell.BOMB && !coord.equals(coordBomb)){
                if (upperLayer.get(coord) == Cell.FLAGED) {
                    upperLayer.setBombedUnderFlagToCell(coord);
                } else {
                    upperLayer.setOpenedToCell(coord);
                }

            }
        }
    }

    public void openCellsAround(Coord coord) {
        upperLayer.setOpenedToCell(coord);
        for (Coord around : Ranges.getCoordsAround(coord)) {
            openBox(around);
        }
    }

    public void openBomb(Coord coord) {
        upperLayer.setBombedToCell(coord);
    }

    public void applyFlag(Coord coord) {
        if (state != GameState.RUN) return;
        upperLayer.setFlagToCell(coord);
    }
}
