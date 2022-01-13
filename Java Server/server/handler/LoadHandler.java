package server.handler;

import java.io.IOException;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.google.gson.JsonArray;
import com.google.gson.JsonElement;
import com.google.gson.JsonObject;
import com.google.gson.JsonSyntaxException;

import server.JsonDecoder;
import server.JsonEncoder;
import server.request.LoadRequest;
import server.result.LoadResult;
import server.service.LoadService;

public class LoadHandler extends Handler implements HttpHandler {

	@Override
	public void handle(HttpExchange exchange) throws IOException {
		
		if (!exchange.getRequestURI().getPath().equals("/load")) {
			returnBadURIError(exchange);
			return;
		}
		
		if (!exchange.getRequestMethod().equals("POST")) {
			returnBadMethodError(exchange);
			return;
		}
		
		JsonObject body;
		try {
			body = JsonDecoder.getBodyValues(exchange);
		} catch (JsonSyntaxException e) {
			returnBadPropertyError(exchange);
			return;
		}
		
		if (!verifyBody(body)) {
			returnBadPropertyError(exchange);
			return;
		}

		LoadRequest req = (LoadRequest) createRequest(body, LoadRequest.class);
		
		LoadResult res = LoadService.run(req);
		
		if (res.error == null) {
			sendResponse(exchange, JsonEncoder.encodeToString(res), 200);
		}

	}

	private static boolean verifyBody(JsonObject body) {
		
		try {
			String[] objectKeys = { "users", "persons", "events" };
			String[] usersKeys = { "userName", "password", "email", "firstName", "lastName", "gender", "personID" };
			String[] personsKeys = { "associatedUsername", "personID", "firstName", "lastName", "gender", "fatherID", "motherID", "spouseID" };
			String[] eventsKeys = { "associatedUsername", "eventID", "personID", "latitude", "longitude", "country", "city", "eventType", "year" };
			String[][] keys = { usersKeys, personsKeys, eventsKeys };
			
			for (int i = 0; i < objectKeys.length; i++) {
				JsonArray ja = body.getAsJsonArray(objectKeys[i]);
				
				for (int j = 0; j < ja.size(); j++) {
					JsonObject jo = ja.get(j).getAsJsonObject();
					
					for (int k = 0; k < keys[i].length; k++) {
						
						if (i == 2 && (k == 3 || k == 4 || k == 8)) {
							JsonElement je = jo.get(keys[i][k]);
							String s = je.getAsString();
							if (!je.getAsJsonPrimitive().isNumber() || s.length() <= 0) throw new Exception();
						}
						else if (!(i == 1 && (k == 5 || k == 6 || k == 7))) {
							JsonElement je = jo.get(keys[i][k]);
							String s = je.getAsString();
							if (!je.getAsJsonPrimitive().isString() || s.length() <= 0) throw new Exception();
						}
					}
					
				}
				
			}
			return true;
			
		} catch (Exception e) {
			return false;
		}
	}
	
}
