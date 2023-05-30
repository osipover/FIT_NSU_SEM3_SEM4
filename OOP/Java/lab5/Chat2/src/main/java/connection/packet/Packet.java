package connection.packet;

import java.io.Serializable;

public class Packet implements Serializable {
    public static final String USERS_LIST = "users_list";
    public static final String REG = "reg";
    public static final String MSG = "msg";

    private String title;
    private String username;
    private String message;

    public Packet(String title, String username, String text) {
        this.title = title;
        this.username = username;
        this.message = text;
    }

    public String getTitle() {
        return this.title;
    }

    public String getUsername() {
        return this.username;
    }

    public String getMessage() {
        return this.message;
    }
}
