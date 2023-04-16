package model;

import javax.swing.*;
import java.awt.*;

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

    public ImageIcon icon;
    public String symbol;
    public Cell getNextNumberBox() {
        return Cell.values()[this.ordinal() + 1];
    }
}
