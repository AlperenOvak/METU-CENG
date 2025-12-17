public class ConsumerThread extends Thread {
    private final MultiLockFacility.FacilityController controller;

    public ConsumerThread(MultiLockFacility.FacilityController controller) {
        this.controller = controller;
    }

    @Override
    public void run() {
        try {
            while (true) {
                controller.consumeBatch();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}
