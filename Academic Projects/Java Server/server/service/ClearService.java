package server.service;

import server.dao.Dao;
import server.request.ClearRequest;
import server.result.ClearResult;

public class ClearService extends Service {
	
	public static ClearResult run(ClearRequest req) {
		
		ClearResult result = new ClearResult();
		
		Dao.deleteAll();

		return result;
	}
	
}