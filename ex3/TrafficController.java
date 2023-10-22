/*
 * Trabalho 2 PCD - Ex 3 - Seção Crítica em Java
 * Nome: Rodrigo Peixe Oliveira
 * RA: 147873
 */

public class TrafficController {

    private enum Side {LEFT, RIGHT, NONE};
    private Side currentSide = Side.NONE;
    private int numCars = 0;

    public void enterLeft() {
        enterBridge(Side.LEFT);
    }
    public void enterRight() {
        enterBridge(Side.RIGHT);
    }
    public void leaveLeft() {
        leaveBridge(Side.LEFT);
    }
    public void leaveRight() {
        leaveBridge(Side.RIGHT);
    }

    private synchronized void enterBridge(Side side) {
        if (numCars > 0 && currentSide != side) {
            try {
                wait();
            } catch (InterruptedException e) {}
        }
        numCars++;
        currentSide = side;
    }

    private synchronized void leaveBridge(Side side) {
        numCars--;
        if (numCars == 0) {
            currentSide = Side.NONE;
            notifyAll();
        }
    }
}