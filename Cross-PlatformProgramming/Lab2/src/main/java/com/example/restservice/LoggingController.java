package com.example.restservice;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class LoggingController {
	private static final Logger logger = LoggerFactory.getLogger(LoggingController.class);
	public static final class DefaultLogs {
		public static final String IndexLog = "IndexPage";
		public static final String Meter2inch = "Meters to inches conversion";
		public static final String Inch2meter = "Inches to meters conversion";
		public static final String String2doubleConversion = "String to double conversion";
	}
	public static void traceLog (final String logMessage) {
		logger.trace(logMessage);
	}
	public static void debugLog (final String logMessage) {
		logger.debug(logMessage);
	}
	public static void infoLog (final String logMessage) {
		traceLog(logMessage);
		logger.info(logMessage);
	}
	public static void warnLog (final String logMessage) {
		debugLog(logMessage);
		logger.warn(logMessage);
	}
	public static void errorLog (final String logMessage) {
		debugLog(logMessage);
		logger.error(logMessage);
	}
}