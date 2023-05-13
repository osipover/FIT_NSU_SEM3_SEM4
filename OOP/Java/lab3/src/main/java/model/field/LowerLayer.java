package model.field;

import model.cell.Cell;
import model.coord.Coord;
import model.ranges.Ranges;

import java.util.ArrayList;

public class LowerLayer {
    private Matrix field;
    private int totalBombs;

    public LowerLayer(int totalBombs) {
        this.totalBombs = totalBombs;
        field = new Matrix(Cell.ZERO);
    }

    public void init(Coord firstCoord) {
        for (int i = 0; i < totalBombs; ++i) {
            placeBomb(firstCoord);
        }
    }

    private void placeBomb(Coord firstCoord) {
        Coord coord = Ranges.getRandomCoord();
        while(field.get(coord) == Cell.BOMB && coord.equals(firstCoord)) {
            coord = Ranges.getRandomCoord();
        }
        field.set(coord, Cell.BOMB);
        setNumbersAroundBomb(coord);
    }

    public void init() {
        for (int i = 0; i < totalBombs; ++i) {
            placeBomb();
        }
    }

    public Cell get(Coord coord) {
        return field.get(coord);
    }

    private void placeBomb() {
        Coord coord = Ranges.getRandomCoord();
        while(field.get(coord) == Cell.BOMB) {
            coord = Ranges.getRandomCoord();
        }
        field.set(coord, Cell.BOMB);
        setNumbersAroundBomb(coord);
    }

    private void setNumbersAroundBomb(Coord coord) {
        ArrayList<Coord> arounds = Ranges.getCoordsAround(coord);
        for (Coord around : arounds) {
            if (field.get(around) != Cell.BOMB) {
                field.set(around, field.get(around).getNextNumber());
            }
        }
    }

    public int getCountOfBombs() {
        return totalBombs;
    }

}
