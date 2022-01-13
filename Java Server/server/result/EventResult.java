package server.result;

import server.model.EventModel;

public class EventResult implements IResult {

	public transient EventModel event;
	public transient EventModel[] events;
	public transient String error;
	public EventResult[] data;
	
	private String associatedUsername;
	private String eventID;
	private String personID;
	private Object latitude;
	private Object longitude;
	private String country;
	private String city;
	private String eventType;
	private Object year;
	
	public void setFields() {
		this.associatedUsername = event.getAssociatedUsername();
		if (associatedUsername == null || associatedUsername.length() == 0) associatedUsername = null;
		this.eventID = event.getEventID();
		if (eventID == null || eventID.length() == 0) eventID = null;
		this.personID = event.getPersonID();
		if (personID == null || personID.length() == 0) personID = null;
		try {
			this.latitude = Float.parseFloat(event.getLatitude());
			if ((Float) this.latitude == 0.0) this.latitude = null;
		} catch (NumberFormatException e) {
			this.latitude = null;
		}
		try {
			this.longitude = Float.parseFloat(event.getLongitude());
			if ((Float) this.longitude == 0.0) this.longitude = null;
		} catch (NumberFormatException e) {
			this.longitude = null;
		}
		try {
			this.year = event.getYear();
			if ((int) this.year == 0) this.year = null;
		} catch (Exception e) {
			this.year = null;
		}
		this.country = event.getCountry();
		if (country == null || country.length() == 0) country = null;
		this.city = event.getCity();
		if (city == null || city.length() == 0) city = null;
		this.eventType = event.getEventType();
		if (eventType == null || eventType.length() == 0) eventType = null;
	}

	public void setArray() {
		data = new EventResult[events.length];
		for (int i = 0; i < events.length; i++) {
			data[i] = new EventResult();
			data[i].event = events[i];
			data[i].setFields();
		}
		this.associatedUsername = null;
		this.eventID = null;
		this.personID = null;
		this.latitude = null;
		this.longitude = null;
		this.country = null;
		this.city = null;
		this.eventType = null;
		this.year = null;
	}
	
}
