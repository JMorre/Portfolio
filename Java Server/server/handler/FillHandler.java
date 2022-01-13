package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import server.JsonEncoder;
import server.request.FillRequest;
import server.result.FillResult;
import server.service.FillService;

public class FillHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		String uri = exchange.getRequestURI().getPath();

		if (!exchange.getRequestMethod().equals("POST")) {
			returnBadMethodError(exchange);
			return;
		}		
		
		try {
			if (!uri.substring(0, 6).equals("/fill/")) {
				returnBadURIError(exchange);
				return;
			}
		} catch (IndexOutOfBoundsException e) {
			returnBadURIError(exchange);
			return;
		}
		
		String params;
		
		try {
			params = uri.substring(6, uri.length());
		} catch (IndexOutOfBoundsException e) {
			returnBadParamError(exchange);
			return;
		}
		
		String username = "";
		String secondParam = "";
		for (int i = 0; i < params.length(); i++) {
			if (params.charAt(i) == '/') {
				username = params.substring(0, i);
				if (username.length() != params.length() - 1) {
					secondParam = params.substring(i + 1, params.length());
				}
				break;
			}
		}
		
		if (username.length() == 0) {
			try {
				username = params.substring(0, params.length());
				if (username.length() == 0) {
					returnBadParamError(exchange);
					return;
				}
			}
			catch (IndexOutOfBoundsException e) {
				returnBadParamError(exchange);
				return;
			}
		}
		
		int gen;
		if (secondParam.length() == 0) {
			gen = 4;
		}
		else {
			try {
				gen = Integer.parseUnsignedInt(secondParam);
			}
			catch (NumberFormatException e) {
				returnBadParamError(exchange);
				return;
			}
		}
		
		FillRequest req = new FillRequest();
		
		req.username = username;
		req.gen = gen;
		
		FillResult res = FillService.run(req);
		
		if (res.error == null) {
			sendResponse(exchange, JsonEncoder.encodeToString(res), 200);
			return;
		}
		
		if (res.error.equals("notfound")) {
			returnBadParamError(exchange);
			return;
		}
		
		if (res.error.equals("ISE")) {
			returnInternalServerError(exchange);
			return;
		}
				
	}

}
