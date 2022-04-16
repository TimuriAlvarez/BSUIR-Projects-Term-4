package com.example.restservice;

import org.jetbrains.annotations.NotNull;
import org.springframework.stereotype.Service;

@Service(value = "CounterService")
public class CounterService {
	private static long counter = 0;
	synchronized public static void incrementCounter() {
		LoggingController.debug("CounterService.incrementCounter");
		++counter;
	}
	public static @NotNull String getMessage() {
		LoggingController.warn("CounterService.getMessage");
		return counter + " request(s) has already been registered.";
	}
}
