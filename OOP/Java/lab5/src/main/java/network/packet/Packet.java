package network.packet;

import java.io.Serializable;

public class Packet implements Serializable {
    public static final String USERS_LIST = "users_list";
    public static final String REG = "reg";
    public static final String MSG = "msg";
    public static final String PING = "ping";

    private String title;
    private String username;
    private Object content;

    public Packet(String title, String username, Object content) {
        this.title = title;
        this.username = username;
        this.content = content;
    }

    public String getTitle() {
        return this.title;
    }

    public String getUsername() {
        return this.username;
    }

    public Object getContent() {
        return this.content;
    }
}
