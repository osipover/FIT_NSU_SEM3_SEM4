package model.cell;

public enum Cell {
    ZERO,
    NUM1,
    NUM2,
    NUM3,
    NUM4,
    NUM5,
    NUM6,
    NUM7,
    NUM8,
    BOMB,

    OPENED,
    CLOSED,
    FLAGED,
    BOMBED,
    NOBOMB;

    public Cell getNextNumber() {
        return Cell.values()[this.ordinal() + 1];
    }
}
