package model;

import java.util.ArrayList;

public class LowerLayer {
    private Matrix field;
    private int totalBombs;

    public LowerLayer(int totalBombs) {
        this.totalBombs = totalBombs;
        field = new Matrix(Cell.ZERO);
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
                field.set(around, field.get(around).getNextNumberBox());
            }
        }
    }

    public int getCountOfBombs() {
        return totalBombs;
    }

}
