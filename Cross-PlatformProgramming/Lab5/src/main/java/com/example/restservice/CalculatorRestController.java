package com.example.restservice;

import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.LinkedList;
import java.util.List;

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
	 * Greetings page. Implemented just for fun.
	 * @return Greetings message.
	 */
	@GetMapping("/")
	public String calculatorGreetings() {
		LoggingRestController.logStartPage("Greetings");
		new CounterServiceThread();
		String result = "Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches, /calculator. Good luck there.";
		LoggingRestController.logEnd("Greetings");
		return result;
	}
	/**
	 * From meter to inch converter page.
	 * @param value real, not negative value of meters.
	 * @return String that contains meters and their value in inches.
	 */
	@GetMapping("/meters")
	public String calculator2inches(@RequestParam(value = "value", required = false) String value) {
		LoggingRestController.logStartPage("/meters");
		new CounterServiceThread();
		String result = cache.requestCache("meters", value);
		LoggingRestController.logEnd("/meters");
		return result;
	}
	/**
	 * From inch to meter converter page.
	 * @param value real, not negative value of inches.
	 * @return String that contains inches and their value in meters.
	 */
	@GetMapping("/inches")
	public String calculator2meters(@RequestParam(value = "value", required = false) String value) {
		LoggingRestController.logStartPage("/inches");
		new CounterServiceThread();
		String result = cache.requestCache("inches", value);
		LoggingRestController.logEnd("/inches");
		return result;
	}
	/**
	 * Counter display page.
	 * Visiting this page doesn't affect counter value.
	 * @return String that contains message about counter state.
	 */
	@GetMapping("/counter")
	public String calculatorCounter() {
		LoggingRestController.logStartPage("/counter");
		String result = CounterService.getMessage();
		LoggingRestController.logEnd("/counter");
		return result;
	}
	/**
	 * Post mapping for JSON POST-requests.
	 * @param list JSON-request representation.
	 * @return String with all responses including exceptions.
	 */
	@PostMapping("/calculator")
	public List<String> calculatorPost(@RequestBody @NotNull List<PostParameterClass> list) {
		LoggingRestController.logStartPage("/calculator");
		new CounterServiceThread();
		List<String> result = new LinkedList<>();
		list.forEach((element) -> {
			try { result.add(cache.requestCache(element)); }
			catch (RuntimeException exception) { result.add(exception.getMessage()); }
		});
		LoggingRestController.logEnd("/calculator");
		return result;
	}
}