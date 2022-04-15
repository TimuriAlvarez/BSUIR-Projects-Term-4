package com.example.restservice;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class RestServiceApplication {
	/**
	 * The method that uses Spring Boot’s SpringApplication.run() to launch an application.
	 * @param args Arguments for RestServiceApplication's run() method.
	 */
	public static void main(String[] args) {
		SpringApplication.run(RestServiceApplication.class, args);
	}
}
