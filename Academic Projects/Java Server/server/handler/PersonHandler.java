package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import server.JsonEncoder;
import server.request.PersonRequest;
import server.result.PersonResult;
import server.service.PersonService;

public class PersonHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		String uri = exchange.getRequestURI().getPath();
		
		String auth = exchange.getRequestHeaders().getFirst("Authorization");
		
		if (auth == null || auth.length() == 0) {
			returnBadAuthError(exchange);
			return;
		}

		if (!exchange.getRequestMethod().equals("GET")) {
			returnBadMethodError(exchange);
			return;
		}		
		
		try {
			if (!uri.substring(0, 7).equals("/person")) {
				returnBadURIError(exchange);
				return;
			}
		} catch (IndexOutOfBoundsException e) {
			returnBadURIError(exchange);
			return;
		}
		
		String params;
		
		try {
			params = uri.substring(8, uri.length());
		} catch (IndexOutOfBoundsException e) {
			params = "";
		}
		
		String personID = "";
		@SuppressWarnings("unused")
		String secondParam = "";
		
		for (int i = 0; i < params.length(); i++) {
			if (params.charAt(i) == '/') {
				personID = params.substring(0, i);
				if (personID.length() != params.length() - 1) {
					secondParam = params.substring(i + 1, params.length());
				}
				break;
			}
		}
		
		boolean idGiven = true;
		
		if (personID.length() == 0) {
			try {
				personID = params.substring(0, params.length());
				if (personID.length() == 0) {
					idGiven = false;
				}
			}
			catch (IndexOutOfBoundsException e) {
				idGiven = false;
			}
		}
		
		PersonRequest req = new PersonRequest();
		req.authToken = auth;
		
		if (idGiven) {
			req.personID = personID;
		}
		else {
			req.personID = null;
		}
		
		PersonResult res = PersonService.run(req);
		
		if (res.error == null) {
			if (idGiven) {
				res.person = res.persons[0];
				res.persons = null;
				res.setFields();
			}
			else {
				res.person = null;
				res.setArray();
			}
			sendResponse(exchange, JsonEncoder.encodeToString(res), 200);
			return;
		}
		
		if (res.error.equals("invalidauth")) {
			returnBadAuthError(exchange);
			return;
		}
		
		if (res.error.equals("notfound")) {
			returnBadIDError(exchange);
			return;
		}
		
		if (res.error.equals("doesnotbelong")) {
			returnBadBelongError(exchange);
			return;
		}
		
		if (res.error.equals("ISE")) {
			returnInternalServerError(exchange);
			return;
		}
				
	}

}
