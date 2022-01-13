package server.handler;

import java.io.IOException;
import java.io.OutputStream;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.sun.net.httpserver.HttpExchange;

import server.request.IRequest;

public class Handler {
	
	protected static Set<String> getHeaderKeys(HttpExchange exchange) {
		return exchange.getRequestHeaders().keySet();
	}
	
	protected static Collection<List<String>> getHeaderValues(HttpExchange exchange) {
		return exchange.getRequestHeaders().values();
	}
	
	protected static Path getURIPath(HttpExchange exchange) {
		return Paths.get(exchange.getRequestURI().toString());
	}
	
	protected static String getRequestBodyString(HttpExchange exchange) {
		return exchange.getRequestBody().toString();
	}
	
	protected static String getMethodString(HttpExchange exchange) {
		return exchange.getRequestMethod().toString();
	}
	
	protected void returnBadPropertyError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Missing/invalid property\"\n}";
		sendResponse(exchange, body, 400);
	}
	
	protected void returnBadMethodError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Bad method request\"\n}";
		sendResponse(exchange, body, 400);
	}
	
	protected void returnBadURIError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Bad URI request\"\n}";
		sendResponse(exchange, body, 400);
	}
	
	protected void sendResponse(HttpExchange exchange, String body, int header) throws IOException {
		byte[] bs = body.getBytes();
		OutputStream os = exchange.getResponseBody();
		exchange.sendResponseHeaders(header, bs.length);
		os.write(bs);
		os.close();
	}
	
	protected static IRequest createRequest(JsonObject body, Class<?> cls) {
		GsonBuilder builder = new GsonBuilder();
		builder.setPrettyPrinting();
		Gson gson = builder.create();
		IRequest req = (IRequest) gson.fromJson(body, cls);
		return req;
	}
	
	protected static String headersToString(HttpExchange exchange) {
		Set<String> s = Handler.getHeaderKeys(exchange);
		Collection<List<String>> c = Handler.getHeaderValues(exchange);
		
		StringBuilder sb = new StringBuilder();
		
			Iterator<String> sit = s.iterator();
			Iterator<List<String>> cit = c.iterator();
			while (sit.hasNext()) {
				sb.append(sit.next());
				sb.append(": ");
				List<String> l = cit.next();
				for (int j = 0; j < l.size(); j++) {
					if (l.size() == 1) {
						sb.append("\"");
						sb.append(l.get(0));
						sb.append("\"");
					}
					else {
						if (j == 0) {
							sb.append("{\n");
						}
						sb.append("\t\"");
						sb.append(l.get(j));
						sb.append("\"\n");
						if (j == l.size() - 1) {
							sb.append("}");
						}
					}
				}
				sb.append("\n");
			}
		
		return sb.toString();
	}
	

	protected void returnInternalServerError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Internal server error\"\n}";
		sendResponse(exchange, body, 400);
	}
	

	protected void returnBadParamError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Invalid parameters\"\n}";
		sendResponse(exchange, body, 400);
	}
	
	protected void returnBadAuthError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Invalid authentication token\"\n}";
		sendResponse(exchange, body, 400);
	}
	
	protected void returnBadBelongError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Request does not belong to user\"\n}";
		sendResponse(exchange, body, 400);
	}

	protected void returnBadIDError(HttpExchange exchange) throws IOException {
		String body = "{\n\t\"message\": \"Invalid ID\"\n}";
		sendResponse(exchange, body, 400);
	}
	
}
