package server.model;

import java.util.HashMap;

public class PersonModel {
	
	private String personID;
	private String associatedUsername;
	private String firstName;
	private String lastName;
	private String gender;
	private String fatherID;
	private String motherID;
	private String spouseID;
	private transient HashMap<String, EventModel> events;
	private transient int arrayIndex;
	private transient int gen;

	public PersonModel(String u, String f, String l, String g, int pmaIndex, int gen) {
		associatedUsername = u;
		firstName = f;
		lastName = l;
		gender = g;
		arrayIndex = pmaIndex;
		this.setGen(gen);
		createPID();
	}
	
	public PersonModel(String associatedUsername, String personID, String firstName, String lastName, String gender,
			String fatherID, String motherID, String spouseID) {
		this.associatedUsername = associatedUsername;
		this.personID = personID;
		this.firstName = firstName;
		this.lastName = lastName;
		this.gender = gender;
		this.fatherID = fatherID;
		this.motherID = motherID;
		this.spouseID = spouseID;
	}

	public void createPID() {
		int i = associatedUsername.hashCode();
		i += firstName.hashCode();
		i += lastName.hashCode();
		i += gender.hashCode();
		i += arrayIndex;
		personID = Integer.toHexString(i);
	}
	
	public String getPersonID() {
		return personID;
	}
	
	public String getAssociatedUsername() {
		return associatedUsername;
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
	
	public String getFatherID() {
		return fatherID;
	}
	
	public String getMotherID() {
		return motherID;
	}
	
	public String getSpouseID() {
		return spouseID;
	}
	
	public HashMap<String, EventModel> getEvents() {
		return events;
	}
	
	public int getArrayIndex() {
		return arrayIndex;
	}
	
	public void setPersonID(String s) {
		personID = s;
	}
	
	public void setAssociatedUsername(String s) {
		associatedUsername = s;
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
	
	public void setFatherID(String s) {
		fatherID = s;
	}
	
	public void setMotherID(String s) {
		motherID = s;
	}
	
	public void setSpouseID(String s) {
		spouseID = s;
	}
	
	public void setEvents(HashMap<String, EventModel> e) {
		events = e;
	}
	
	public void setArrayIndex(int i) {
		arrayIndex = i;
	}

	public int getGen() {
		return gen;
	}

	public void setGen(int gen) {
		this.gen = gen;
	}
	
}