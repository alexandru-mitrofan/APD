package synchronizedSortedList;

import java.util.Collections;
import java.util.List;
import java.util.concurrent.Semaphore;

public class Sort extends Thread {
    private final List<Integer> list;
    Semaphore sem;

    public Sort(List<Integer> list, Semaphore sem) {
        super();
        this.sem = sem;
        this.list = list;
    }

    @Override
    public void run() {
        try {
            sem.acquire();
            Collections.sort(list);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}