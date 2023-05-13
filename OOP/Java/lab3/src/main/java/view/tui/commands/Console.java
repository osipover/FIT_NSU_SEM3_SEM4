package view.tui.commands;

public class Console {
    public static void clear(){
        try {
            ProcessBuilder pb = new ProcessBuilder("cmd", "/c", "cls");
            Process startProcess = pb.inheritIO().start();
            startProcess.waitFor();
        } catch (Exception ex) {}
    }
}
