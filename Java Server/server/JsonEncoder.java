package server;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import server.result.IResult;

public class JsonEncoder {
	
	public static String encodeToString(IResult res) {
		GsonBuilder builder = new GsonBuilder();
		builder.setPrettyPrinting();
		Gson gson = builder.create();
		return gson.toJson(res);
	}
	
}