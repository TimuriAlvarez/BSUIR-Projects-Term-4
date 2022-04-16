package com.example.restservice;

import org.jetbrains.annotations.NotNull;

class CounterService {
	private static long counter = 0;

	synchronized public static void increment() {
		++counter;
	}
	synchronized public static @NotNull String getMessage() {
		return counter + " request(s) has already been registered.";
	}
}

public class CounterServiceThread extends Thread {
	public CounterServiceThread() {
		super();
		LoggingRestController.logDebug(getName() + ".CounterServiceThread");
		start();
	}
	@Override
	synchronized public void run() {
		LoggingRestController.logStartThread(getName());
		CounterService.increment();
		LoggingRestController.logEnd(getName());
	}
}