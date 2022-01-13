package server.model;

public class UserModel {
	
	private String userName;
	private String password;
	private String email;
	private String firstName;
	private String lastName;
	private String gender;
	private String personID;
	
	public UserModel(String u, String p, String e, String f, String l, String g) {
		userName = u;
		password = p;
		email = e;
		firstName = f;
		lastName = l;
		gender = g;
		personID = null;
	}
	
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
	
	public String getPersonID() {
		return personID;
	}
	
	
	
	public void setUserName(String s) {
		userName = s;
	}
	
	public void setPassword(String s) {
		password = s;
	}
	
	public void setEmail(String s) {
		email = s;
	}
	
	public void setFirstName(String s) {
		firstName = s;
	}

	public void setLastName(String s) {
		lastName = s;
	}
	
	public void setGender(String s) {
		gender = s;
	}
	
	public void setPersonID(String s) {
		personID = s;
	}
	
}