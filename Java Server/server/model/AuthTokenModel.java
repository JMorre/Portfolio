package server.model;

public class AuthTokenModel {
	
	private String token;
	private String user;
	
	public AuthTokenModel(String t, String u) {
		token = t;
		user = u;
	}
	
	public String getToken() {
		return token;
	}
	
	public String getUser() {
		return user;
	}
	
	public void setToken(String s) {
		token = s;
	}
	
	public void setUser(String s) {
		user = s;
	}
}