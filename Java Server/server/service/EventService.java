package server.service;


import server.dao.AuthTokenDao;
import server.dao.EventDao;
import server.model.EventModel;
import server.request.EventRequest;
import server.result.EventResult;

public class EventService extends Service {

	public static EventResult run(EventRequest req) {
		
		EventResult res = new EventResult();
		
		if (req.eventID == null) {
			if (!AuthTokenDao.checkExistingToken(req.authToken)) {
				res.error = "invalidauth";
				return res;
			}
			
			String username = AuthTokenDao.getUsernameFromToken(req.authToken);
			
			EventModel[] ema = EventDao.getAllEventsFromUsername(username);
			
			res.events = ema;
			
			return res;
		}
		else {
			if (!AuthTokenDao.checkExistingToken(req.authToken)) {
				res.error = "invalidauth";
				return res;
			}
			
			String username = AuthTokenDao.getUsernameFromToken(req.authToken);
			
			if (!EventDao.checkExistingEvent(req.eventID)) {
				res.error = "notfound";
				return res;
			}
			
			if (!EventDao.checkBelonging(req.eventID, username)) {
				res.error = "invalidauth";
				return res;
			}
			
			EventModel em = EventDao.getEvent(req.eventID);
			
			EventModel[] ema = new EventModel[1];
			ema[0] = em;
			
			res.events = ema;
			
			return res;
			
		}
		
	}
	
}
