package server.model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.util.Random;

public class LocationModel {
	
	private String country;
	private String city;
	private String latitude;
	private String longitude;
	
	public LocationModel() {
		getRandomInfo();
	}
	
	public void getRandomInfo() {
		try (BufferedReader br = new BufferedReader(new FileReader("json/locations.json"))) {
			Random rand = new Random();
			int r = rand.nextInt(978);
			r = 4 + 6 * r;
			
			int i = 0;
			String line;
		    while ((line = br.readLine()) != null) {
		    	i++;
		    	if (i == r) break;
		    }
		    
		    country = getField(line);
		    
		    line = br.readLine();
		    
		    city = getField(line);
		    
		    line = br.readLine();
		    
		    latitude = getField(line);
		    
		    line = br.readLine();
		    
		    longitude = getField(line);
			
		} catch (Exception e) {
			
		}
	}
	
	private String getField(String line) {
		int i = 0;
		for (i = 0; i < line.length() - 1; i++) {
			if (line.charAt(i) == '"' && line.charAt(i + 1) == ':') {
				i+=3;
				break;
			}
		}
		String ret = "";
		for (; i < line.length(); i++) {
			if (line.charAt(i) == ',') break;
			ret += line.charAt(i);
		}
		if (ret.charAt(0) == '"') {
			ret = ret.substring(1, ret.length() - 1);
		}
		return ret;
	}

	public String getCountry() {
		return country;
	}
	public void setCountry(String country) {
		this.country = country;
	}
	public String getCity() {
		return city;
	}
	public void setCity(String city) {
		this.city = city;
	}
	public String getLatitude() {
		return latitude;
	}
	public void setLatitude(String latitude) {
		this.latitude = latitude;
	}
	public String getLongitude() {
		return longitude;
	}
	public void setLongitude(String longitude) {
		this.longitude = longitude;
	}
	
}
