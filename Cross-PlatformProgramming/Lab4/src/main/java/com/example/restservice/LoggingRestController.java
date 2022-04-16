package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that's responsible for application logging.
 *  <p>
 * logStartPage, logStartThread     -       Log the starting of pages and threads.<br>
 * logEnd                           -       Log the ending of pages and threads.<br>
 * logMethod, logDebug              -       Log different methods.<br>
 * logError                         -       Log errors (exceptions).<br>
 * </p>
 */
@RestController(value = "LoggingRestController")
public class LoggingRestController {
	private static final Logger logger = LoggerFactory.getLogger(LoggingRestController.class);
	public static void logStartPage(String name) {
		logger.info("");
		logger.info("Start: " + name);
	}
	public static void logStartThread(String name) {
		logger.info("Start: " + name);
	}
	public static void logEnd(String location) {
		logger.info("Successful end: " + location);
	}
	public static void logMethod(String alarm) {
		logger.warn(alarm + "()");
	}
	public static void logDebug(String debug) {
		logger.debug(debug + "()");
	}
	public static void logError(String error) {
		logger.error(error);
	}
}