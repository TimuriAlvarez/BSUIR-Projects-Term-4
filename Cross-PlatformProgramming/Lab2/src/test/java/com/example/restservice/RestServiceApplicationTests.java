package com.example.restservice;

import org.junit.jupiter.api.Test;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.context.SpringBootTest.WebEnvironment;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.boot.test.web.server.LocalServerPort;

import static org.assertj.core.api.Assertions.assertThat;

@SpringBootTest(webEnvironment = WebEnvironment.RANDOM_PORT)
public class RestServiceApplicationTests {

	@LocalServerPort
	private int port;

	@Autowired
	private TestRestTemplate restTemplate;

	@Test
		public void greetingShouldReturnGreetingsMessage() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/",
			String.class)).contains("Greetings, traveller. Here you can convert meters to inches and vice versa: all you, need is a right page and the value. Available pages: /, /meters, /inches. Good luck there.");
	}

	@Test
	public void testInches0() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testInches1() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testInches2() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=a",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testInches3() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=-1",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testInches4() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=1",
			String.class)).doesNotContain("EXCEPTION: ");
	}

	@Test
	public void testMeters0() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testMeters1() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testMeters2() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=a",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testMeters3() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=-1",
			String.class)).contains("EXCEPTION: ");
	}
	@Test
	public void testMeters4() throws Exception {
		assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=1",
			String.class)).doesNotContain("EXCEPTION: ");
	}
}