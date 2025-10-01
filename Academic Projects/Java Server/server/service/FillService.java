package server.service;

import server.dao.Dao;
import server.dao.EventDao;
import server.dao.PersonDao;
import server.dao.UserDao;
import server.model.PersonModel;
import server.model.UserModel;
import server.request.FillRequest;
import server.result.FillResult;

public class FillService extends Service {

	public static FillResult run(FillRequest req) {
		
		FillResult res = new FillResult();
		
		if (!UserDao.checkExistingUser(req.username)) {
			res.error = "notfound";
			return res;
		}
		
		Dao.deleteAllMatchingData(req.username);
		
		UserModel um = new UserModel(req.username, null, null, null, null, null);
		
		PersonModel[] pma = createGenerations(um, req.gen);
		
		generateEvents(pma);
		
		int persons = pma.length;
		int events = 0;
		for (int i = 0; i < pma.length; i++) {
			PersonDao.insert(pma[i]);
			EventDao.insertAssociatedEvents(pma[i]);
			events += pma[i].getEvents().size();
		}
		
		UserDao.updateField("username", req.username, "personID", pma[0].getPersonID());
		
		res.message = "Successfully added " + persons + " persons and " + events + " events to the database.";
		
		return res;
		
	}
	
}
