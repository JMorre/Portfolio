package server.result;

import server.model.PersonModel;

public class PersonResult implements IResult {

	public transient PersonModel person;
	public transient PersonModel[] persons;
	public transient String error;
	public PersonResult[] data;
	
	private String associatedUsername;
	private String personID;
	private String firstName;
	private String lastName;
	private String gender;
	private Object fatherID;
	private Object motherID;
	private Object spouseID;
	
	public void setFields() {
		this.associatedUsername = person.getAssociatedUsername();
		if (associatedUsername == null || associatedUsername.length() == 0) associatedUsername = null;
		this.personID = person.getPersonID();
		if (personID == null || personID.length() == 0) personID = null;
		this.firstName = person.getFirstName();
		if (firstName == null || firstName.length() == 0) firstName = null;
		this.lastName = person.getLastName();
		if (lastName == null || lastName.length() == 0) lastName = null;
		this.gender = person.getGender();
		if (gender == null || gender.length() == 0) gender = null;
		this.fatherID = person.getFatherID();
		if (fatherID == null || ((String)fatherID).length() == 0) fatherID = null;
		this.motherID = person.getMotherID();
		if (motherID == null || ((String)motherID).length() == 0) motherID = null;
		this.spouseID = person.getSpouseID();
		if (spouseID == null || ((String)spouseID).length() == 0) spouseID = null;
	}

	public void setArray() {
		data = new PersonResult[persons.length];
		for (int i = 0; i < persons.length; i++) {
			data[i] = new PersonResult();
			data[i].person = persons[i];
			data[i].setFields();
		}
		this.associatedUsername = null;
		this.personID = null;
		this.firstName = null;
		this.lastName = null;
		this.gender = null;
		this.fatherID = null;
		this.motherID = null;
		this.spouseID = null;
	}
	
}
