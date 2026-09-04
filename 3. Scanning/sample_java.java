
public class TestProgram {
    private static final int MAX_COUNT = 10;
    protected float value = 3.14;
    char grade = 'A';
    String message = "Hello, world!";

    public void runDemo() {
        if (MAX_COUNT > 0 && true != false) {
            for (int i = 0; i < MAX_COUNT; i++) {
                // This is a single-line comment
                /* This is a 
                   multi-line comment */
                value = value + 1.5;
            }
        }
        return null;
    }
}
