package com.example.restservice;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import static com.example.restservice.LoggingController.*;

/**
 * Controller that gets user's url-request and sends appropriate response.
 */
@RestController(value = "CalculatorController")
public class CalculatorController {
	static final CalculatorCache cache = new CalculatorCache();
	String message = CounterService.getMessage();
	/**
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		start("Greeting");
		CounterService.incrementCounter();
		message = "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.";
		end("Greeting");
		return message;
	}
	/**
	 * From meter to inch converter page.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculator2inches(@RequestParam(value = "value", required = false) String value) {
		start("/meters");
		CounterService.incrementCounter();
		message = value + " meter(s) is " + cache.meters2inches(value) + " inch(es).";
		end("/meters");
		return message;
	}
	/**
	 * From inch to meter converter page.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculator2meters(@RequestParam(value = "value", required = false) String value) {
		start("/inches");
		CounterService.incrementCounter();
		message = value + " inch(s) is " + cache.inches2meters(value) + " meter(s).";
		end("/inches");
		return message;
	}

	/**
	 * Counter display page.
	 * Visiting this page doesn't affect counter value.
	 * @return String that contains message about counter state.
	 */
	@GetMapping("/counter")
	public String calculatorCounter() {
		start("/counter");
		message = CounterService.getMessage();
		end("/counter");
		return message;
	}
}