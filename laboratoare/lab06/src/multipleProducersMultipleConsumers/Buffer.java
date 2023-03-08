package multipleProducersMultipleConsumers;
import java.util.concurrent.ArrayBlockingQueue;

public class Buffer {
	ArrayBlockingQueue<Integer> values = new ArrayBlockingQueue<>(100);
	void put(int value) {
		try {
			values.put(value);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	int get() {
		try {
			return values.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return 0;
	}
}
