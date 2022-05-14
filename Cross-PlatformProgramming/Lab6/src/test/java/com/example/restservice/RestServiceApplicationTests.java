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
    public void greetingShouldReturnGreetingsMessage() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/",
                String.class)).contains("Greetings");
    }

    @Test
    public void testInches0() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testInches1() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testInches2() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=a",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testInches3() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=-1",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testInches4() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/inches?value=1",
                String.class)).doesNotContain("Run-time exception: ");
    }

    @Test
    public void testMeters0() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testMeters1() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testMeters2() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=a",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testMeters3() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=-1",
                String.class)).contains("Run-time exception: ");
    }
    @Test
    public void testMeters4() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/meters?value=1",
                String.class)).doesNotContain("Run-time exception: ");
    }
    @Test
    public void testCounter() {
        assertThat(this.restTemplate.getForObject("http://localhost:" + port + "/counter",
                String.class)).contains("registered");
    }
}