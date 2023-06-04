package network.protocol;

import network.protocol.json.JsonProtocol;
import network.protocol.serialize.SerializeProtocol;
import java.io.IOException;
import java.net.Socket;

public class ProtocolBuilder {

    public static Protocol create(ProtocolType type, Socket socket) throws IOException {
        switch (type) {
            case JSON       : return new JsonProtocol(socket);
            case SERIALIZE  : return new SerializeProtocol(socket);
            default         : return null;
        }
    }
}

