package tests.commands;

import com.commands.Push;
import com.commands.exceptions.ArgumentsNumberException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.Arguments;
import org.junit.jupiter.params.provider.MethodSource;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.stream.Stream;

import static org.junit.jupiter.api.Assertions.*;

class PushTest {
    Context context = new Context();
    Push push = new Push();

    static Stream<Arguments> prepareArgs(){
        return Stream.of(
                Arguments.of(new ArrayList<String>(Arrays.asList("0"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("1.0"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("-1.0"))),
                Arguments.of(new ArrayList<String>(Arrays.asList("25.25")))
        );
    }
    @ParameterizedTest
    @MethodSource("prepareArgs")
    void testPush(ArrayList<String> args){
        assertDoesNotThrow(() -> push.execute(args, context));
        assertEquals(Double.parseDouble(args.get(0)), context.getLastArgument());
    }

    @Test
    void testArgumentsNumberException() {
        assertThrows(ArgumentsNumberException.class, () -> {
            push.execute(new ArrayList<>(), context);
        });
    }

}