package server.handler;

import java.io.IOException;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import server.JsonDecoder;
import server.JsonEncoder;
import server.request.LoginRequest;
import server.result.LoginResult;
import server.service.LoginService;

public class LoginHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		String ipAddress = exchange.getRequestHeaders().getFirst("X-FORWARDED-FOR");
		if (ipAddress == null) {
			ipAddress = exchange.getRemoteAddress().toString();
		}
		
		if (!exchange.getRequestURI().getPath().equals("/user/login")) {
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
		
		LoginRequest sendReq = (LoginRequest) createRequest(body, LoginRequest.class);
		sendReq.agent = exchange.getRequestHeaders().getFirst("User-agent");
		sendReq.ipAddress = ipAddress;
		
		LoginResult logResult = LoginService.run(sendReq);
		
		if (logResult.error == null) {
			sendResponse(exchange, JsonEncoder.encodeToString(logResult), 200);
			return;
		}
		 
		if (logResult.error.equals("invalid")) {
			returnInvalidPasswordError(exchange);
			return;
		}
		
		if (logResult.error.equals("notfound")) {
			returnNotFoundUsernameError(exchange);
			return;
		}
		
		if (logResult.error.equals("ISE")) {
			returnInternalServerError(exchange);
			return;
		}
		
	}
	
	private void returnNotFoundUsernameError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Username not found\"\n}";
		sendResponse(exchange, body, 400);
	}

	private void returnInvalidPasswordError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Invalid password\"\n}";
		sendResponse(exchange, body, 400);
	}

	private static boolean verifyBody(JsonObject body) {
		try {
			String[] keys = {"userName", "password"};
			for (int i = 0; i < keys.length; i++) {
				JsonElement j = body.get(keys[i]);
				String s = j.getAsString();
				if (!j.getAsJsonPrimitive().isString() || s.length() <= 0) throw new Exception();
			}

			return true;
		}
		catch (Exception e) {
			return false;
		}
	}

}
