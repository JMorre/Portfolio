package server;

import java.io.IOException;
import java.io.InputStream;

import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.sun.net.httpserver.HttpExchange;

public class JsonDecoder {
	
	public static JsonObject getBodyValues(HttpExchange exchange) throws IOException {
		String request = requestToString(exchange);
		
		JsonParser parser = new JsonParser();
		JsonElement rootNode = parser.parse(request);
		JsonObject details = rootNode.getAsJsonObject();
		return details;
	}
	
	private static String requestToString(HttpExchange exchange) throws IOException {
		StringBuilder sb = new StringBuilder();
		int read = 0;
		InputStream reader = exchange.getRequestBody();
		String s = reader.toString();
		while ((read = reader.read()) != -1) {
			sb.append((char)read);
		}
		return sb.toString();
	}
	
}