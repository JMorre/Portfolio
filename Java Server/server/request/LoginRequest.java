package server.request;

public class LoginRequest implements IRequest {

	private String userName;
	private String password;
	public transient String agent;
	public transient String ipAddress;
	
	public String getPassword() {
		return password;
	}
	
	public void setPassword(String password) {
		this.password = password;
	}
	
	public String getUserName() {
		return userName;
	}
	
	public void setUserName(String userName) {
		this.userName = userName;
	}
	
}
