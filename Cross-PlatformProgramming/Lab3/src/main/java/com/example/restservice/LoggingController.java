package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that's responsible for application logging.
 */
@RestController
public class LoggingController {
	/**
	 * Controller logger.
	 */
	private static final Logger logger = LoggerFactory.getLogger(LoggingController.class);

	/**
	 * Common (default) log messages.
	 */
	public static final class DefaultLogs {
		public static final String IndexLog = "IndexPage";
		public static final String Meter2inch = "Meters to inches conversion";
		public static final String Inch2meter = "Inches to meters conversion";
		public static final String String2doubleConversion = "String to double conversion";
	}

	/**
	 * Logging method for trace log.
	 * @param traceMessage Message for logging.
	 */
	public static void traceLog (final String traceMessage) {
		logger.trace(traceMessage);
	}
	/**
	 * Logging method for trace debug.
	 * @param debugMessage Message for logging.
	 */
	public static void debugLog (final String debugMessage) {
		logger.debug(debugMessage);
	}
	/**
	 * Logging method for information log.
	 * @param informationMessage Message for logging.
	 */
	public static void infoLog (final String informationMessage) {
		traceLog(informationMessage);
		logger.info(informationMessage);
	}
	/**
	 * Logging method for warning log.
	 * @param warningMessage Message for logging.
	 */
	public static void warnLog (final String warningMessage) {
		debugLog(warningMessage);
		logger.warn(warningMessage);
	}
	/**
	 * Logging method for error log.
	 * @param errorMessage Message for logging.
	 */
	public static void errorLog (final String errorMessage) {
		debugLog(errorMessage);
		logger.error(errorMessage);
	}
}