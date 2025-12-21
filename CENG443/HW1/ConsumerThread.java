public class ConsumerThread extends Thread {
    private final MultiLockFacility.FacilityController controller;

    public ConsumerThread(MultiLockFacility.FacilityController controller) {
        this.controller = controller;
    }

    @Override
    public void run() {
        try {
            consume();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private boolean hasEnough() {
        for (Tank t : controller.getTanks())
            if (t.getStock() < t.getBatch())
                return false;
        return true;
    }

    private void switchToProducing() {
        controller.getBarrierLock().lock();
        try {
            controller.setFullTanks(0);
            controller.setProducingPhase(true);
            for (int i = 1; i <= controller.getTotalProducers(); i++) {
                controller.getIsFull()[i] = 0;
            }
            controller.getProducersCond().signalAll();
        } finally {
            controller.getBarrierLock().unlock();
        }
    }

    private void consume() throws InterruptedException{
        while (true) {
            controller.getBarrierLock().lock();
            try {
                while (controller.isProducingPhase()) {
                    controller.getConsumerCond().await();
                    Actions.start_compound_generator();
                }
            } finally {
                controller.getBarrierLock().unlock();
            }

            for (Tank t : controller.getTanks()) t.getLock().lock();

            try {
                while (hasEnough()){
                    //System.out.print("Consuming batch: ");
                    for (Tank t : controller.getTanks()) {
                        t.setStock(t.getStock() - t.getBatch());
                        //System.out.print(t.getStock() + " ");
                    }
                    //System.out.println();
                    Actions.generate_compound();
                }
            } finally {
                for (Tank t : controller.getTanks()) {
                    t.getLock().unlock();
                }
                Actions.stop_compound_generator();
                switchToProducing();
            }
        }
    }
}
