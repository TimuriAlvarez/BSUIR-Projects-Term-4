package com.example.restservice;

import org.springframework.boot.autoconfigure.SpringBootApplication;

import static org.springframework.boot.SpringApplication.*;

/**
 * Rest Service Application class that is used to run the application.
 */
@SpringBootApplication
public class RestServiceApplication {
	/**
	 * The main method that uses Spring Boot’s SpringApplication.run() to launch an application.
	 * @param args Arguments for RestServiceApplication's run() method.
	 */
	public static void main(String[] args) {
		run(RestServiceApplication.class, args);
	}
}
