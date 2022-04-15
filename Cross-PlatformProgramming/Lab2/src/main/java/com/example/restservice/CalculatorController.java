package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController
public class CalculatorController {
	/**
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		LoggingController.infoLog(LoggingController.DefaultLogs.IndexLog);
		return "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.";
	}
	/**
	 * From meter to inch converter.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculatorMeters(@RequestParam(value = "value", required = false) String value) {
		double meters = Calculator.String2double("/meters", value);
		LoggingController.infoLog(LoggingController.DefaultLogs.Meter2inch);
		return "" + meters + " meter(s) is " + Calculator.meter2inch(meters) + " inch(es).";
	}
	/**
	 * From inch to meter converter.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculatorInches(@RequestParam(value = "value", required = false) String value) {
		double inches = Calculator.String2double("/inches", value);
		LoggingController.infoLog(LoggingController.DefaultLogs.Inch2meter);
		return "" + inches + " inch(s) is " + Calculator.inch2meter(inches) + " meter(s).";
	}
}