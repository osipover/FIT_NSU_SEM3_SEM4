package tests;

import com.command_factory.CommandFactory;
import com.command_factory.exception.CommandFactoryException;
import com.command_factory.exception.FindCommandException;
import com.commands.Command;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvSource;

import static org.junit.jupiter.api.Assertions.*;

class CommandFactoryTest {
    static CommandFactory commandFactory;
    @BeforeAll
    static void createCommandFactory(){
        try {
            commandFactory = new CommandFactory();
        } catch (CommandFactoryException ex){
            System.err.println(ex.getMessage());
        }
    }

    @ParameterizedTest
    @CsvSource(value = {
            "PUSH, com.commands.Push",
            "POP, com.commands.Pop",
            "PRINT, com.commands.Print",
            "DEFINE, com.commands.Define",
            "SQRT, com.commands.Square",
            "+, com.commands.Addition",
            "-, com.commands.Subtraction",
            "*, com.commands.Multiplication",
            "/, com.commands.Division"
    })
    void testCommandCreation(String commandName, String commandClassName) {
        try {
            Command command = commandFactory.create(commandName);
            assertEquals(commandClassName, command.getClass().getName());
        } catch (CommandFactoryException ex) {
            System.err.println(ex.getMessage());
        }
    }

    @Test
    void testCommandFactoryException(){
        assertThrows(FindCommandException.class, () -> {
            Command command = commandFactory.create("LIMIT");
        });
    }
}