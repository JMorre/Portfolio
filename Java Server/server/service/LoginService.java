package server.service;

import server.dao.AuthTokenDao;
import server.dao.UserDao;
import server.model.AuthTokenModel;
import server.request.LoginRequest;
import server.result.LoginResult;

public class LoginService extends Service {

	public static LoginResult run(LoginRequest req) {
		
		LoginResult result = new LoginResult();
		
		if (!UserDao.checkExistingUser(req.getUserName())) {
			result.error = "notfound";
			return result;
		}
		
		String password = UserDao.getPassword(req.getUserName());
		
		if (!req.getPassword().equals(password)) {
			result.error = "invalid";
			return result;
		}
		
		AuthTokenModel[] oldTokens = AuthTokenDao.getAllTokens(req.getUserName());
		String oldTokenCode = "";
		for (int i = 0; i < oldTokens.length; i++) {
			oldTokenCode += oldTokens[i].getToken();
		}
		
		AuthTokenModel auth = createAuthToken(req.getUserName(), req.agent, req.ipAddress, oldTokenCode);
		
		AuthTokenDao.insert(auth);
		
		String personID = UserDao.getPID(req.getUserName());
		
		result.setAuthToken(auth.getToken());
		result.setUserName(req.getUserName());
		result.setPersonID(personID);
		
		return result;
	}

}
