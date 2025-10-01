package server.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Set;

import server.model.EventModel;
import server.model.PersonModel;

//print statements for debugging purposes, omitted

public class EventDao extends Dao {

	public static void insert(EventModel em) {
		
		Connection conn = EventDao.connect();
		
		String table = "CREATE TABLE IF NOT EXISTS events (\n"
				+ " eventID TEXT NOT NULL PRIMARY KEY,\n"
				+ " associatedUsername TEXT NOT NULL,\n"
				+ " personID TEXT NOT NULL,\n"
				+ " latitude TEXT NOT NULL,\n"
				+ " longitude TEXT NOT NULL,\n"
				+ " country TEXT NOT NULL,\n"
				+ " city TEXT NOT NULL,\n"
				+ " eventType TEXT NOT NULL,\n"
				+ " year INT\n"
				+ ");";
		
		EventDao.executeStmt(conn, table);
		
		String ins = "INSERT INTO events"
				+ "(eventID,associatedUsername,personID,latitude,longitude,country,city,eventType,year) "
				+ "VALUES(?,?,?,?,?,?,?,?,?)";
		
		try (PreparedStatement pstmt = conn.prepareStatement(ins)) {
			pstmt.setString(1, em.getEventID());
			pstmt.setString(2, em.getAssociatedUsername());
			pstmt.setString(3, em.getPersonID());
			pstmt.setString(4, em.getLatitude());
			pstmt.setString(5, em.getLongitude());
			pstmt.setString(6, em.getCountry());
			pstmt.setString(7, em.getCity());
			pstmt.setString(8, em.getEventType());
			pstmt.setInt(9, em.getYear());
			pstmt.executeUpdate();
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		}
		finally {
			try {
				conn.close();
			} catch (SQLException e) {
				//System.out.println(e.getMessage());
			}
		}
	}
	
	public static void insertAssociatedEvents(PersonModel pm) {
		Set<String> keys = pm.getEvents().keySet();
		Iterator<String> it = keys.iterator();
		
		for (int i = 0; i < pm.getEvents().size(); i++) {
			String key = it.next();
			insert(pm.getEvents().get(key));
		}
	}

	public static EventModel[] getAllEventsFromUsername(String username) {
		Connection conn = EventDao.connect();
		
		String idQuery = "SELECT eventID\n"
				+ " FROM events\n"
				+ " WHERE associatedUsername = '" + username + "';";
		
		String[] ids;
		
		try (PreparedStatement pstmt = conn.prepareStatement(idQuery)) {
			
			ResultSet rs = pstmt.executeQuery();
			ArrayList<String> alIds = new ArrayList<String>();
			
			while (rs.next()) {
				alIds.add(rs.getString("eventID"));
			}
			
			ids = alIds.toArray(new String[0]);
			
		} catch (Exception e) {
			try {
				conn.close();
			} catch (SQLException e1) {

			}
			return null;
		}
		
		EventModel[] ema = new EventModel[ids.length];
		
		for (int i = 0; i < ids.length; i++) {
			
			String query = "SELECT personID,\n"
					+ " latitude,\n"
					+ " longitude,\n"
					+ " country,\n"
					+ " city,\n"
					+ " eventType,\n"
					+ " year\n"
					+ "FROM events\n"
					+ "WHERE eventID = '" + ids[i] + "';";
			
			try (PreparedStatement pstmt = conn.prepareStatement(query)) {
				
				ResultSet rs = pstmt.executeQuery();
				
				String personID = rs.getString("personID");
				String latitude = rs.getString("latitude");
				String longitude = rs.getString("longitude");
				String country = rs.getString("country");
				String city = rs.getString("city");
				String eventType = rs.getString("eventType");
				int year = rs.getInt("year");
				
				ema[i] = new EventModel(username, ids[i], personID, latitude, longitude, country, city, eventType, year);
				
			} catch (SQLException e) {
				try {
					conn.close();
				} catch (SQLException e1) {

				}
				//System.out.println(e.getMessage());
				return null;
			}
		}
		try {
			conn.close();
		} catch (SQLException e) {

		}
		return ema;
	}

	public static boolean checkExistingEvent(String eventID) {

		Connection conn = EventDao.connect();
		
		String query = "SELECT eventID\n"
				+ "FROM events\n"
				+ "WHERE eventID = '" + eventID + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {

			ResultSet rs = pstmt.executeQuery();
			if (rs.next()) {
				conn.close();
				return true;
			}
			else {
				conn.close();
				return false;
			}
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		}
		return false;
	}

	public static boolean checkBelonging(String eventID, String username) {

		Connection conn = EventDao.connect();
		
		String query = "SELECT eventID\n"
				+ "FROM events\n"
				+ "WHERE eventID = '" + eventID + "'\n"
				+ "AND associatedUsername = '" + username + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {

			ResultSet rs = pstmt.executeQuery();
			if (rs.next()) {
				conn.close();
				return true;
			}
			else {
				conn.close();
				return false;
			}
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		}
		return false;
	}

	public static EventModel getEvent(String eventID) {
		Connection conn = EventDao.connect();
		
		String query = "SELECT associatedUsername,\n"
				+ " personID,\n"
				+ " latitude,\n"
				+ " longitude,\n"
				+ " country,\n"
				+ " city,\n"
				+ " eventType,\n"
				+ " year\n"
				+ "FROM events\n"
				+ "WHERE eventID = '" + eventID + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ResultSet rs = pstmt.executeQuery();
			
			String username = rs.getString("associatedUsername");
			String personID = rs.getString("personID");
			String latitude = rs.getString("latitude");
			String longitude = rs.getString("longitude");
			String country = rs.getString("country");
			String city = rs.getString("city");
			String eventType = rs.getString("eventType");
			int year = rs.getInt("year");
			
			conn.close();
			
			return new EventModel(username, eventID, personID, latitude, longitude, country, city, eventType, year);
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}
	
}