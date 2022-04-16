package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that's responsible for application logging.
 *
 * Page logs:                   start() & end().
 * Unimportant methods logs:    debug();
 * Important methods logs:      warn();
 * Error (exception) logs:      error();
 *
 * All of them accept String with message as input parameter.
 */
@RestController(value = "LoggingRestController")
public class LoggingRestController {
	private static final Logger logger = LoggerFactory.getLogger(LoggingRestController.class);

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