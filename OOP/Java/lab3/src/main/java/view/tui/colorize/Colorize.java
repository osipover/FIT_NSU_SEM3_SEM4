package view.tui.colorize;

public class Colorize {
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";

    public static String black(String symbol) {
        return ANSI_BLACK + symbol + ANSI_RESET;
    }

    public static String red(String symbol) {
        return ANSI_RED + symbol + ANSI_RESET;
    }

    public static String green(String symbol) {
        return ANSI_GREEN + symbol + ANSI_RESET;
    }

    public static String yellow(String symbol) {
        return ANSI_YELLOW + symbol + ANSI_RESET;
    }

    public static String cyan(String symbol) {
        return ANSI_CYAN + symbol + ANSI_RESET;
    }

    public static String white(String symbol) {
        return ANSI_WHITE + symbol + ANSI_RESET;
    }

    public static String blue(String symbol) {
        return ANSI_BLUE + symbol + ANSI_RESET;
    }

    public static String purple(String symbol) {
        return ANSI_PURPLE + symbol + ANSI_RESET;
    }
}
