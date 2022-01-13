package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;

import server.JsonDecoder;
import server.JsonEncoder;
import server.request.RegisterRequest;
import server.result.RegisterResult;
import server.service.RegisterService;

public class RegisterHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		String ipAddress = exchange.getRequestHeaders().getFirst("X-FORWARDED-FOR");
		if (ipAddress == null) {
			ipAddress = exchange.getRemoteAddress().toString();
		}
		
		if (!exchange.getRequestURI().getPath().equals("/user/register")) {
			returnBadURIError(exchange);
			return;
		}
		
		if (!exchange.getRequestMethod().equals("POST")) {
			returnBadMethodError(exchange);
			return;
		}
		
		JsonObject body = JsonDecoder.getBodyValues(exchange);
		
		if (!verifyBody(body)) {
			returnBadPropertyError(exchange);
			return;
		}
		
		RegisterRequest sendReq = (RegisterRequest) createRequest(body, RegisterRequest.class);
		sendReq.agent = exchange.getRequestHeaders().getFirst("User-agent");
		sendReq.ipAddress = ipAddress;
		
		RegisterResult regResult = RegisterService.run(sendReq);
		
		if (regResult.error == null) {
			sendResponse(exchange, JsonEncoder.encodeToString(regResult), 200);
			return;
		}
		
		if (regResult.error.equals("exists")) {
			returnAlreadyExistsError(exchange);
			return;
		}
		
		if (regResult.error.equals("ISE")) {
			returnInternalServerError(exchange);
			return;
		}

	}

	private void returnAlreadyExistsError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Username already taken\"\n}";
		sendResponse(exchange, body, 400);
	}

	private static boolean verifyBody(JsonObject body) {
		try {
			String[] keys = {"userName", "password", "email", "firstName", "lastName", "gender"};
			for (int i = 0; i < keys.length; i++) {
				JsonElement j = body.get(keys[i]);
				String s = j.getAsString();
				if (!j.getAsJsonPrimitive().isString() || s.length() <= 0) throw new Exception();
			}
			
			String s = body.get("gender").getAsString();
			if (!s.equals("m") && !s.equals("f")) throw new Exception();
			
			return true;
		}
		catch (Exception e) {
			return false;
		}
	}
	
}
