public class ProducerThread extends Thread {
    public  final Tank tank;
    private final MultiLockFacility.FacilityController controller;

    public ProducerThread(Tank tank, MultiLockFacility.FacilityController controller) {
        this.tank = tank;
        this.controller = controller;
    }

    @Override
    public void run() {
        try {
            Actions.start_element_generator(tank.getId());
            while (true) {
                controller.produce(tank);
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}