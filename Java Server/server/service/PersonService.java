package server.service;

import server.dao.AuthTokenDao;
import server.dao.PersonDao;
import server.model.PersonModel;
import server.request.PersonRequest;
import server.result.PersonResult;

public class PersonService extends Service {

	public static PersonResult run(PersonRequest req) {
		
		PersonResult res = new PersonResult();
		
		if (req.personID == null) {
			if (!AuthTokenDao.checkExistingToken(req.authToken)) {
				res.error = "invalidauth";
				return res;
			}
			
			String username = AuthTokenDao.getUsernameFromToken(req.authToken);
			
			PersonModel[] pma = PersonDao.getAllPersonsFromUsername(username);
			
			res.persons = pma;
			
			return res;
		}
		else {
			if (!AuthTokenDao.checkExistingToken(req.authToken)) {
				res.error = "invalidauth";
				return res;
			}
			
			String username = AuthTokenDao.getUsernameFromToken(req.authToken);
			
			if (!PersonDao.checkExistingPerson(req.personID)) {
				res.error = "notfound";
				return res;
			}
			
			if (!PersonDao.checkBelonging(req.personID, username)) {
				res.error = "invalidauth";
				return res;
			}
			
			PersonModel pm = PersonDao.getPerson(req.personID);
			
			PersonModel[] pma = new PersonModel[1];
			pma[0] = pm;
			
			res.persons = pma;
			
			return res;
			
		}
		
	}
	
}
