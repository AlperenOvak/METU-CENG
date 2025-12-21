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
            produce();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    private void produce() throws InterruptedException {
        Actions.start_element_generator(tank.getId());
        while (true) {
            // Wait at barrier until phase is PRODUCING
            controller.getBarrierLock().lock();
            try {
                while (!controller.isProducingPhase() || controller.getIsFull()[tank.getId()] == 1) {
                    controller.getProducersCond().await();
                    Actions.start_element_generator(tank.getId());
                }
            } finally {
                controller.getBarrierLock().unlock();
            }

            // Produce into tank
            try {
                tank.getLock().lock();
                if (tank.getStock() >= tank.getCapacity()){
                    
                    // increase full Tank count at barrier
                    controller.getBarrierLock().lock();
                    controller.getIsFull()[tank.getId()] = 1;
                    boolean allFull = false;
                    try {
                        controller.setFullTanks(controller.getFullTanks() + 1);
                        if (controller.getFullTanks() == controller.getTotalProducers()) {
                            controller.setProducingPhase(false);
                            allFull = true;
                        }
                        Actions.stop_element_generator(tank.getId());
                        // Signal consumer after action
                        if (allFull) {
                            controller.getConsumerCond().signal();
                        }
                    } finally {
                        controller.getBarrierLock().unlock();
                    }
                    
                    
                    // return and wait for next phase
                    //tank.getLock().unlock();
                    continue; // instead of return, since in loop
                }

                Actions.generate_element(tank.getId());
                tank.setStock(tank.getStock() + 1);
                //System.out.println("Tank " + tank.getId() + " stock: " + tank.getStock());

            } finally {
                tank.getLock().unlock();
            }
        }
    }
}