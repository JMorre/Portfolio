package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import server.JsonEncoder;
import server.request.EventRequest;
import server.result.EventResult;
import server.service.EventService;

public class EventHandler extends Handler implements HttpHandler {

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
			if (!uri.substring(0, 6).equals("/event")) {
				returnBadURIError(exchange);
				return;
			}
		} catch (IndexOutOfBoundsException e) {
			returnBadURIError(exchange);
			return;
		}
		
		String params;
		
		try {
			params = uri.substring(7, uri.length());
		} catch (IndexOutOfBoundsException e) {
			params = "";
		}
		
		String eventID = "";
		@SuppressWarnings("unused")
		String secondParam = "";
		
		for (int i = 0; i < params.length(); i++) {
			if (params.charAt(i) == '/') {
				eventID = params.substring(0, i);
				if (eventID.length() != params.length() - 1) {
					secondParam = params.substring(i + 1, params.length());
				}
				break;
			}
		}
		
		boolean idGiven = true;
		
		if (eventID.length() == 0) {
			try {
				eventID = params.substring(0, params.length());
				if (eventID.length() == 0) {
					idGiven = false;
				}
			}
			catch (IndexOutOfBoundsException e) {
				idGiven = false;
			}
		}
		
		EventRequest req = new EventRequest();
		req.authToken = auth;
		
		if (idGiven) {
			req.eventID = eventID;
		}
		else {
			req.eventID = null;
		}
		
		EventResult res = EventService.run(req);
		
		if (res.error == null) {
			if (idGiven) {
				res.event = res.events[0];
				res.events = null;
				res.setFields();
			}
			else {
				res.event = null;
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
