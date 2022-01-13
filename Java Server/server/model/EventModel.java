package server.model;

public class EventModel {
	
	private String associatedUsername;
	private String eventID;
	private String personID;
	private String latitude;
	private String longitude;
	private String country;
	private String city;
	private String eventType;
	private int year;
	
	public EventModel(String type, PersonModel pm, LocationModel lm, int date) {
		eventType = type;
		associatedUsername = pm.getAssociatedUsername();
		personID = pm.getPersonID();
		latitude = lm.getLatitude();
		longitude = lm.getLongitude();
		country = lm.getCountry();
		city = lm.getCity();
		year = date;
		int i = type.hashCode() + personID.hashCode() + date;
		eventID = Integer.toHexString(i);
	}
	
	public EventModel(EventModel em, PersonModel pm) {
		associatedUsername = pm.getAssociatedUsername();
		personID = pm.getPersonID();
		latitude = em.getLatitude();
		longitude = em.getLongitude();
		country = em.getCountry();
		city = em.getCity();
		year = em.getYear();
		eventType = em.getEventType();
		int i = eventType.hashCode() + personID.hashCode() + year;
		eventID = Integer.toHexString(i);
	}

	public EventModel(String associatedUsername, String eventID, String personID, String latitude, String longitude,
			String country, String city, String eventType, int year) {
		this.associatedUsername = associatedUsername;
		this.eventID = eventID;
		this.personID = personID;
		this.latitude = latitude;
		this.longitude = longitude;
		this.country = country;
		this.city = city;
		this.eventType = eventType;
		this.year = year;
	}

	public String getEventID() {
		return eventID;
	}

	public String getAssociatedUsername() {
		return associatedUsername;
	}

	public String getPersonID() {
		return personID;
	}

	public String getLatitude() {
		return latitude;
	}

	public String getLongitude() {
		return longitude;
	}

	public String getCountry() {
		return country;
	}

	public String getCity() {
		return city;
	}

	public String getEventType() {
		return eventType;
	}

	public int getYear() {
		return year;
	}
	
	public void setEventID(String s) {
		eventID = s;
	}
	
	public void setAssociatedUsername(String s) {
		associatedUsername = s;
	}
	
	public void setPersonID(String s) {
		personID = s;
	}
	
	public void setLatitude(String s) {
		latitude = s;
	}
	
	public void setLongitude(String s) {
		longitude = s;
	}
	
	public void setCountry(String s) {
		country = s;
	}
	
	public void setCity(String s) {
		city = s;
	}
	
	public void setEventType(String s) {
		eventType = s;
	}
	
	public void setYear(int i) {
		year = i;
	}
	
}