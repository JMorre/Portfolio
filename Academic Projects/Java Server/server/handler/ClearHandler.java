package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;

import server.JsonEncoder;
import server.request.ClearRequest;
import server.result.ClearResult;
import server.service.ClearService;

public class ClearHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		if (!exchange.getRequestURI().getPath().equals("/clear")) {
			returnBadURIError(exchange);
			return;
		}
		
		if (!exchange.getRequestMethod().equals("POST")) {
			returnBadMethodError(exchange);
			return;
		}
		
		ClearRequest sendReq = new ClearRequest();

		ClearResult clearResult = ClearService.run(sendReq);
		
		if (clearResult.error == null) {
			clearResult.message = "Clear succeeded.";
			sendResponse(exchange, JsonEncoder.encodeToString(clearResult), 200);
			return;
		}
		
		if (clearResult.error.equals("ISE")) {
			returnInternalServerError(exchange);
			return;
		}

	}

}
