package server.service;

import server.dao.Dao;
import server.dao.EventDao;
import server.dao.PersonDao;
import server.dao.UserDao;
import server.request.LoadRequest;
import server.result.LoadResult;

public class LoadService extends Service {

	public static LoadResult run(LoadRequest req) {
		
		LoadResult res = new LoadResult();
		
		Dao.deleteAll();
		
		int u = 0;
		if (req.users != null) {
			for (u = 0; u < req.users.length; u++) {
				UserDao.insert(req.users[u]);
			}
		}
		
		int p = 0;
		if (req.persons != null) {
			for (p = 0; p < req.persons.length; p++) {
				PersonDao.insert(req.persons[p]);
			}
		}
		
		int e = 0;
		if (req.events != null) {
			for (e = 0; e < req.events.length; e++) {
				EventDao.insert(req.events[e]);
			}
		}
		
		res.message = "Successfully added " + u + " users, " + p + " persons, and " + e + " events to the database.";
		return res;
		
	}

}
