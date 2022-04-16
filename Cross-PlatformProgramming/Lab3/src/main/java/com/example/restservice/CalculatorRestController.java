package com.example.restservice;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController(value = "CalculatorRestController")
public class CalculatorRestController {
	/**
	 * Common application cache.
	 */
	private CalculatorCacheService cache;
	/**
	 * Create new application cache (@Autowired).
	 */
	@Autowired
	void setCalculatorCache() {
		LoggingRestController.logMethod("CalculatorRestController.setCalculatorCache");
		this.cache = new CalculatorCacheService();
	}
	/**
	 * Message that stores the output result before returning it  as  a  response.
	 */
	private String message;
	/**
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		LoggingRestController.logStart("Greetings");
		message = "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.";
		LoggingRestController.logEnd("Greetings");
		return message;
	}
	/**
	 * From meter to inch converter page.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculator2inches(@RequestParam(value = "value", required = false) String value) {
		LoggingRestController.logStart("/meters");
		message = value + " meter(s) is " + cache.meters2inches(value) + " inch(es).";
		LoggingRestController.logEnd("/meters");
		return message;
	}
	/**
	 * From inch to meter converter page.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculator2meters(@RequestParam(value = "value", required = false) String value) {
		LoggingRestController.logStart("/inches");
		message = value + " inch(s) is " + cache.inches2meters(value) + " meter(s).";
		LoggingRestController.logEnd("/inches");
		return message;
	}
}