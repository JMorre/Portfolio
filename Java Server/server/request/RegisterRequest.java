package server.request;

public class RegisterRequest implements IRequest {
	
	private String userName;
	private String password;
	private String email;
	private String firstName;
	private String lastName;
	private String gender;
	public transient String agent;
	public transient String ipAddress;
	
	public String getUserName() {
		return userName;
	}
	
	public String getPassword() {
		return password;
	}
	
	public String getEmail() {
		return email;
	}
	
	public String getFirstName() {
		return firstName;
	}

	public String getLastName() {
		return lastName;
	}
	
	public String getGender() {
		return gender;
	}

}
