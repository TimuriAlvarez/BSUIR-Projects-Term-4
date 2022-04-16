package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that's responsible for application logging.
 */
@RestController(value = "LoggingController")
public class LoggingController {
	/**
	 * Controller logger.
	 */
	private static final Logger logger = LoggerFactory.getLogger(LoggingController.class);

	/**
	 * Public logging methods.
	 */
	public static void start(String location) {
		logger.info("Start: " + location);
	}
	public static void end(String location) {
		logger.info("Successful end: " + location);
	}
	public static void warn(String alarm) {
		logger.warn(alarm + "()");
	}
	public static void error(String error) {
		logger.error(error);
	}
	public static void debug(String debug) {
		logger.debug(debug + "()");
	}
}