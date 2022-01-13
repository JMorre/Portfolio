package server.service;

import server.dao.AuthTokenDao;
import server.dao.EventDao;
import server.dao.PersonDao;
import server.dao.UserDao;
import server.model.AuthTokenModel;
import server.model.PersonModel;
import server.model.UserModel;
import server.request.RegisterRequest;
import server.result.RegisterResult;

public class RegisterService extends Service {
	
	public static RegisterResult run(RegisterRequest req) {
		
		RegisterResult result = new RegisterResult();

		UserModel um = new UserModel(req.getUserName(),
				req.getPassword(),
				req.getEmail(),
				req.getFirstName(),
				req.getLastName(),
				req.getGender());
		
		if (UserDao.checkExistingUser(um.getUserName())) {
			result.error = "exists";
			return result;
		}
		
		PersonModel[] persons = createGenerations(um, 4);
		
		um.setPersonID(persons[0].getPersonID());
		
		generateEvents(persons);
		
		UserDao.insert(um);
		
		for (int i = 0; i < persons.length; i++) {
			PersonDao.insert(persons[i]);
			EventDao.insertAssociatedEvents(persons[i]);
		}
		
		AuthTokenModel auth = createAuthToken(um.getUserName(), req.agent, req.ipAddress);
		
		AuthTokenDao.insert(auth);
		
		result.setAuthToken(auth.getToken());
		result.setUserName(req.getUserName());
		result.setPersonID(um.getPersonID());
		
		return result;
	}
	
}