package model.field;

import model.cell.Cell;
import model.coord.Coord;
import model.ranges.Ranges;

public class UpperLayer {
    private Matrix field;
    private int countOfClosedCells;

    public void init() {
        countOfClosedCells = Ranges.getSize().x * Ranges.getSize().y;
        field = new Matrix(Cell.CLOSED);
    }

    public Cell get (Coord coord) {
        return field.get(coord);
    }

    public void setOpenedToCell(Coord coord) {
        field.set(coord, Cell.OPENED);
        --countOfClosedCells;
    }

    public void setBombedToCell(Coord coord) {
        field.set(coord, Cell.BOMBED);
    }

    public void setBombedUnderFlagToCell(Coord coord) {
        field.set(coord, Cell.NOBOMB);
    }

    public void setFlagToCell(Coord coord) {
        switch(field.get(coord)) {
            case CLOSED -> field.set(coord, Cell.FLAGED);
            case FLAGED -> field.set(coord, Cell.CLOSED);
        }
    }

    public int getCountOfClosedCell() {
        return countOfClosedCells;
    }
}
