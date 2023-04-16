package model;

import model.Cell;
import model.Coord;

public class Matrix {
    private Cell[][] matrix;

    public Matrix(Cell defaultCell) {
        matrix = new Cell[Ranges.getSize().x][Ranges.getSize().y];
        for (Coord coord : Ranges.getAllCoords()) {
            matrix[coord.x][coord.y] = defaultCell;
        }
    }

    public Cell get(Coord coord) {
        if (Ranges.inRange(coord))
            return matrix[coord.x][coord.y];
        return null;
    }

    public void set(Coord coord, Cell cell) {
        if (Ranges.inRange(coord))
            matrix[coord.x][coord.y] = cell;
    }

}
