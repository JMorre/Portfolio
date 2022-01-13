package server.service;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;
import java.util.HashMap;

import server.model.AuthTokenModel;
import server.model.EventModel;
import server.model.LocationModel;
import server.model.PersonModel;
import server.model.UserModel;

public class Service {

	private static final int THIS_YEAR = 2018;

	protected static AuthTokenModel createAuthToken(String user, String agent, String ipAddress) {
		int u = user.hashCode();
		int r = agent.hashCode();
		int i = ipAddress.hashCode();
		
		String token = Integer.toHexString(u + r + i);
		
		return new AuthTokenModel(token, user);
	}
	

	protected static AuthTokenModel createAuthToken(String user, String agent, String ipAddress, String oldTokenCode) {
		int u = user.hashCode();
		int r = agent.hashCode();
		int i = ipAddress.hashCode();
		int o = oldTokenCode.hashCode();
		
		String token = Integer.toHexString(u + r + i + o);
		
		return new AuthTokenModel(token, user);
	}
	
	protected static String getRandomName(String type) {
		int n = 0;
		String path = "json/";
		
		if (type.equals("f")) {
			n = 146;
			path += "fnames.json";
		}
		else if (type.equals("m")) {
			n = 143;
			path += "mnames.json";
		}
		else if (type.equals("s")) {
			n = 151;
			path += "snames.json";
		}
		else return null;
		
		try (BufferedReader br = new BufferedReader(new FileReader(path))) {
			
			Random rand = new Random();
			int r = rand.nextInt(n);
			r += 2;
			int i = 0;
			
		    String line;
		    while ((line = br.readLine()) != null) {
		    	i++;
		    	if (i == r) break;
		    }
		    
		    String ret = "";
		    
		    for (int j = 0; j < line.length(); j++) {
		    	if (Character.isAlphabetic(line.charAt(j))) ret += line.charAt(j);
		    }
		    
		    return ret;
		} catch (Exception e) {
			return null;
		}
	}
	
	protected static PersonModel[] createGenerations(UserModel um, int max) {
		PersonModel pm;
		if (um.getGender() == null) {
			pm = createNewPerson("m", um.getUserName(), 0, 0);
		}
		else pm = createPerson(um);
		
		int n = 0;
		for (int i = 0; i <= max; i++) {
			n += intPow(2, i);
		}
		
		PersonModel[] pma = new PersonModel[n];
		int pmaIndex = 0;
		pma[pmaIndex] = pm;
		int i = 0;
		if (i < max) {
			pmaIndex = createParentsStep(pm, i + 1, um.getUserName(), max, pma, pmaIndex + 1);
		}
		
		return pma;
	}
	
	private static int createParentsStep(PersonModel pm, int i, String username, int max, PersonModel[] pma, int pmaIndex) {
		PersonModel father;
		if (pm.getGender().equals("f") && pm.getSpouseID() != null) {
			father = createNewPerson("m", username, pmaIndex + 1, i);
		}
		else {
			father = createNewPerson("m", username, pm.getLastName(), pmaIndex + 1, i);
		}
		PersonModel mother = createNewPerson("f", username, father.getLastName(), pmaIndex + 2, i);
		
		father.setSpouseID(mother.getPersonID());
		mother.setSpouseID(father.getPersonID());
		
		pm.setFatherID(father.getPersonID());
		pm.setMotherID(mother.getPersonID());
		
		pma[pmaIndex] = father;
		pmaIndex++;
		pma[pmaIndex] = mother;
		pmaIndex++;

		if (i < max) {
			pmaIndex = createParentsStep(father, i + 1, username, max, pma, pmaIndex);
			pmaIndex = createParentsStep(mother, i + 1, username, max, pma, pmaIndex);
		}
		
		return pmaIndex;
	}
	
	private static PersonModel createPerson(UserModel um) {
		PersonModel pm = new PersonModel(um.getUserName(), um.getFirstName(), um.getLastName(), um.getGender(), 0, 0);
		return pm;
	}
	
	private static PersonModel createNewPerson(String gender, String username, int pmaIndex, int gen) {
		PersonModel pm = new PersonModel(username, getRandomName(gender), getRandomName("s"), gender, pmaIndex, gen);
		return pm;
	}
	
	private static PersonModel createNewPerson(String gender, String username, String lastName, int pmaIndex, int gen) {
		PersonModel pm = new PersonModel(username, getRandomName(gender), lastName, gender, pmaIndex, gen);
		return pm;
	}
	
	protected static void generateEvents(PersonModel[] pma) {
		
		for (int i = 0; i < pma.length; i++) {
			pma[i].setEvents(new HashMap<String, EventModel>());
			generateBirthBaptismChristeningDeath(pma[i]);
		}
		
		for (int i = 1; i < pma.length; i+=2) {
			generateMarriage(pma[i], pma[i + 1]);
		}
		
	}
	
	private static void generateMarriage(PersonModel hubby, PersonModel wifey) {
		LocationModel lm = new LocationModel();
		
		hubby.getEvents().put("marriage", new EventModel("marriage", hubby, lm, hubby.getEvents().get("birth").getYear() + 19));

		shareEvent(wifey, hubby, "marriage");
	}

	private static void generateBirthBaptismChristeningDeath(PersonModel pm) {
		
		LocationModel lm = new LocationModel();

		pm.getEvents().put("birth", new EventModel("birth", pm, lm, THIS_YEAR - (20 * (pm.getGen() + 1))));

		lm.getRandomInfo();
		
		pm.getEvents().put("baptism", new EventModel("baptism", pm, lm, pm.getEvents().get("birth").getYear() + 5));
		pm.getEvents().put("christening", new EventModel("christening", pm, lm, pm.getEvents().get("baptism").getYear()));
		
		if (getAge(pm) >= 90) {
			lm.getRandomInfo();
			pm.getEvents().put("death", new EventModel("death", pm, lm, pm.getEvents().get("birth").getYear() + 90));
		}
		
	}
	
	private static void shareEvent(PersonModel reciever, PersonModel sharer, String type) {
		EventModel newEm = new EventModel(sharer.getEvents().get(type), reciever);
		reciever.getEvents().put(type, newEm);
	}
	
	private static int getAge(PersonModel pm) {
		if (pm == null) return -1;
		if (pm.getEvents() == null) return -1;
		if (pm.getEvents().get("birth") == null) return -1;
		return THIS_YEAR - pm.getEvents().get("birth").getYear();
	}

	public static int intPow(int a, int b) {
		int r = 1;
		for (int i = 0; i < b; i++) {
			r *= a;
		}
		return r;
	}
	
}
