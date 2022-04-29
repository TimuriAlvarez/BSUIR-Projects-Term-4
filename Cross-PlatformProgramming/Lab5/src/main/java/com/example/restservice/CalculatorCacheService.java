package com.example.restservice;

import org.jetbrains.annotations.Contract;
import org.jetbrains.annotations.NotNull;
import org.springframework.stereotype.Service;
import java.util.HashMap;


@Service(value = "CalculatorCacheService")
public final class CalculatorCacheService {
	/**
	 * HashMap that contains cache.
	 */
	HashMap<Double, Double> hashMap;
	/**
	 * Calculator Cache Service constructor.
	 * Initializes HashMap with a new HashMap() value.
	 */
	CalculatorCacheService() {
		this.hashMap = new HashMap<>();
	}
	/**
	 * Cache checker for meters.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Meters.
	 * @return Inches.
	 */
	private double meters2inches(String value) {
		LoggingRestController.logDebug("CalculatorCacheMap.meters2inches");
		double meters = CalculatorLogicService.String2double("/meters", value);
		if (!hashMap.containsKey(meters))
			hashMap.put(meters, CalculatorLogicService.meters2inches(meters));
		return hashMap.get(meters);
	}
	/**
	 * Cache checker for inches.
	 * Calls a conversion from CalculatorService class and puts the result as a record in HashMap.
	 * @param value Inches.
	 * @return Meters.
	 */
	private double inches2meters(String value) {
		LoggingRestController.logDebug("CalculatorCacheMap.inches2meters");
		double inches = CalculatorLogicService.String2double("/inches", value);
		if (!hashMap.containsValue(inches))
			hashMap.put(CalculatorLogicService.inches2meters(inches), inches);
		return getHashMapKey(inches);
	}
	/**
	 * Getter for key from HashMap.
	 * @param value Actual HashMap value that must already be in the HashMap.
	 * @return Key value.
	 */
	private double getHashMapKey(double value) {
		LoggingRestController.logMethod("CalculatorCacheMap.getHashMapKey");
		for (double key:
			hashMap.keySet()) {
			if (hashMap.get(key).equals(value)) return key;
		}
		throw new HashMapKeyAbsenceException(value);
	}
	/**
	 * Service class interface for cache management.
	 * @param units String that contains measurement units.
	 * @param value Value of these units.
	 * @return Value of these units in the opposite measurement system.
	 */
	@Contract(pure = true)
	public @NotNull String requestCache(@NotNull String units, double value) {
		return requestCache(units, String.valueOf(value));
	}
	/**
	 * Service class interface for cache management.
	 * @param units String that contains measurement units.
	 * @param value Value of these units.
	 * @return Value of these units in the opposite measurement system.
	 */
	@Contract(pure = true)
	public @NotNull String requestCache(@NotNull String units, String value) {
		LoggingRestController.logDebug("CalculatorCacheMap.requestCache");
		switch (units) {
			case "meters":
				return value + " meter(s) is " + meters2inches(value) + " inch(es).";
			case "inches":
				return value + " inch(es) is " + inches2meters(value) + " meter(s).";
			default:
				throw new UnitsRecognitionException(units);
		}
	}
}
