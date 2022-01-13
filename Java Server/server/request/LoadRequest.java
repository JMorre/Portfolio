package server.request;

import server.model.EventModel;
import server.model.PersonModel;
import server.model.UserModel;

public class LoadRequest implements IRequest {

	public UserModel[] users;
	public PersonModel[] persons;
	public EventModel[] events;
	
}
