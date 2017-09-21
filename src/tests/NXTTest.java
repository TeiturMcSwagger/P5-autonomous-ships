package tests;

import lejos.nxt.Button;
import lejos.nxt.comm.RConsole;

/**
 * Created by Lau on 21/09/2017.
 */
public class NXTTest {
    public static void main(String[] args) {
        connectBluetooth();
        sleep_Test();
    }

    /**
     * Tests if Thread.sleep works on the NXT
     */
    private static void sleep_Test() {
        int i = 0;
        RConsole.println("Testing Thread.sleep");
        while(Button.readButtons() != Button.ID_ESCAPE || i != 5) {

            RConsole.println(Double.toString(i));

            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            i++;
        }
    }

    /**
     * Prints status messages while connecting RConsole to bluetooth
     */
    public static void connectBluetooth() {
        RConsole.println("Connecting to bluetooth");
        RConsole.openBluetooth(20000);
        RConsole.println("Connected to bluetooth");
    }
}
