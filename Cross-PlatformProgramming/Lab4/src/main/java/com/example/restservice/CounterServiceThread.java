package com.example.restservice;

import org.jetbrains.annotations.NotNull;

/**
 * Service class that provides counting of url-requests for application and thread safe access for the counter value.
 */
class CounterService {
	/**
	 * Actual counter.
	 */
	private static long counter = 0;
	/**
	 * Method for incrementing counter.
	 */
	synchronized public static void increment() {
		++counter;
	}
	/**
	 * Method for getting counter message.
	 * @return String contains counter message.
	 */
	synchronized public static @NotNull String getMessage() {
		return counter + " request(s) has already been registered.";
	}
}

/**
 * Service class that provides thread-based interface for thread safe counter incrementation.
 */
public class CounterServiceThread extends Thread {
	/**
	 * Constructor that calls method start() which calls overridden method run().
	 */
	public CounterServiceThread() {
		super();
		LoggingRestController.logDebug(getName() + ".CounterServiceThread");
		start();
	}
	/**
	 * Overridden method that calls counter incrementation.
	 */
	@Override
	synchronized public void run() {
		LoggingRestController.logStartThread(getName());
		CounterService.increment();
		LoggingRestController.logEnd(getName());
	}
}