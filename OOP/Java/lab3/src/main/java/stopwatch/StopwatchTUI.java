package stopwatch;

public class StopwatchTUI {
    private long begin;
    private long end;

    public StopwatchTUI() {

    }

    public void start() {
        begin = System.currentTimeMillis();
    }

    public void stop() {
        end = System.currentTimeMillis();
    }

    @Override
    public String toString() {
        long totalSeconds = (end - begin) / 1000;
        int hours = (int)(totalSeconds / 3600);
        int minutes = (int)((totalSeconds % 3600) / 60);
        int seconds = (int)(totalSeconds % 60);

        String timeString = String.format("%02d:%02d:%02d", hours, minutes, seconds);
        return timeString;
    }

}
