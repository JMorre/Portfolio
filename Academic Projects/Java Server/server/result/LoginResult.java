package server.result;

public class LoginResult implements IResult {

	private String authToken;
	private String userName;
	private String personID;
	public transient String error = null;
	
	public String getAuthToken() {
		return authToken;
	}
	
	public String getUserName() {
		return userName;
	}
	
	public String getPersonID() {
		return personID;
	}
	
	public void setAuthToken(String s) {
		authToken = s;
	}
	public void setUserName(String s) {
		userName = s;
	}
	public void setPersonID(String s) {
		personID = s;
	}
	
}
