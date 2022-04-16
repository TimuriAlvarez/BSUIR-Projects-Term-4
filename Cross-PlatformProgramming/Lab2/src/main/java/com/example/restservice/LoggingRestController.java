package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that's responsible for application logging.
 */
@RestController(value = "LoggingRestController")
public class LoggingRestController {
	/**
	 * Actual logger used to log everything.
	 */
	private static final Logger logger = LoggerFactory.getLogger(LoggingRestController.class);
	/**
	 * Log the starting of pages.
	 * @param name Page's name
	 */
	public static void logStart(String name) {
		logger.info("");
		logger.info("Start: " + name);
	}
	/**
	 * Log the ending of pages.
	 * @param name  Page's name
	 */
	public static void logEnd(String name) {
		logger.info("Successful end: " + name);
	}
	/**
	 * Log an important method.
	 * @param name  Method's name
	 */
	public static void logMethod(String name) {
		logger.warn(name + "()");
	}
	/**
	 * Log an unimportant method.
	 * @param name  Method's name
	 */
	public static void logDebug(String name) {
		logger.debug(name + "()");
	}
	/**
	 * Log an error or an exception.
	 * @param error  Error's or exception's name
	 */
	public static void logError(String error) {
		logger.error(error);
	}
}