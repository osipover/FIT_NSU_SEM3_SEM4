package tests.commands;

import com.commands.Pop;
import com.commands.exceptions.ArgumentsNumberException;
import com.commands.exceptions.NotEnoughStackException;
import com.context.Context;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

class PopTest {
    Context context = new Context();
    Pop pop = new Pop();

    @Test
    void testPop(){
        context.push(1.0);
        context.push(2.0);
        assertDoesNotThrow(() -> pop.execute(new ArrayList<>(), context));
        assertEquals(1.0, context.getLastArgument());
    }

    @Test
    void testArgumentsNumberException(){
        ArrayList<String> args = new ArrayList<>(Arrays.asList("a"));
        assertThrows(ArgumentsNumberException.class, () -> {
            pop.execute(args, context);
        });
    }

    @Test
    void testEmptyStackException(){
        assertThrows(NotEnoughStackException.class, () -> {
            pop.execute(new ArrayList<>(), context);
        });
    }
}