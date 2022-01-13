package server.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import server.model.PersonModel;

//print statements for debugging purposes, omitted

public class PersonDao extends Dao {

	public static void insert(PersonModel pm) {

		Connection conn = UserDao.connect();
		
		String table = "CREATE TABLE IF NOT EXISTS persons (\n"
				+ " personID TEXT NOT NULL PRIMARY KEY,\n"
				+ " associatedUsername TEXT NOT NULL,\n"
				+ " firstName TEXT NOT NULL,\n"
				+ " lastName TEXT NOT NULL,\n"
				+ " gender TEXT NOT NULL,\n"
				+ " fatherID TEXT NOT NULL,\n"
				+ " motherID TEXT NOT NULL,\n"
				+ " spouseID TEXT NOT NULL\n"
				+ ");";
		
		PersonDao.executeStmt(conn, table);
		
		String ins = "INSERT INTO persons"
				+ "(personID,associatedUsername,firstName,lastName,gender,fatherID,motherID,spouseID) "
				+ "VALUES(?,?,?,?,?,?,?,?)";
		
		try (PreparedStatement pstmt = conn.prepareStatement(ins)) {
			pstmt.setString(1, pm.getPersonID());
			pstmt.setString(2, pm.getAssociatedUsername());
			pstmt.setString(3, pm.getFirstName());
			pstmt.setString(4, pm.getLastName());
			pstmt.setString(5, pm.getGender());
			if (pm.getFatherID() == null) pstmt.setString(6, "");
			else pstmt.setString(6, pm.getFatherID());
			if (pm.getMotherID() == null) pstmt.setString(7, "");
			else pstmt.setString(7, pm.getMotherID());
			if (pm.getSpouseID() == null) pstmt.setString(8, "");
			else pstmt.setString(8, pm.getSpouseID());
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

	public static PersonModel[] getAllPersonsFromUsername(String username) {
		Connection conn = PersonDao.connect();
		
		String idQuery = "SELECT personID\n"
				+ " FROM persons\n"
				+ " WHERE associatedUsername = '" + username + "';";
		
		String[] ids;
		
		try (PreparedStatement pstmt = conn.prepareStatement(idQuery)) {
			
			ResultSet rs = pstmt.executeQuery();
			ArrayList<String> alIds = new ArrayList<String>();
			
			while (rs.next()) {
				alIds.add(rs.getString("personID"));
			}
			
			ids = alIds.toArray(new String[0]);
			
		} catch (Exception e) {
			try {
				conn.close();
			} catch (SQLException e1) {

			}
			return null;
		}
		
		PersonModel[] pma = new PersonModel[ids.length];
		
		for (int i = 0; i < ids.length; i++) {
			
			String query = "SELECT firstName,\n"
					+ " lastName,\n"
					+ " gender,\n"
					+ " fatherID,\n"
					+ " motherID,\n"
					+ " spouseID\n"
					+ "FROM persons\n"
					+ "WHERE personID = '" + ids[i] + "';";
			
			try (PreparedStatement pstmt = conn.prepareStatement(query)) {
				
				ResultSet rs = pstmt.executeQuery();
				
				String firstName = rs.getString("firstName");
				String lastName = rs.getString("lastName");
				String gender = rs.getString("gender");
				String fatherID = null;
				String motherID = null;
				String spouseID = null;
				try {
					fatherID = rs.getString("fatherID");
				} catch (SQLException e) {}
				try {
					motherID = rs.getString("motherID");
				} catch (SQLException e) {}
				try {
					spouseID = rs.getString("spouseID");
				} catch (SQLException e) {}
				
				pma[i] = new PersonModel(username, ids[i], firstName, lastName, gender, fatherID, motherID, spouseID);
				
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
		return pma;
	}

	public static boolean checkExistingPerson(String personID) {
		
		Connection conn = PersonDao.connect();
		
		String query = "SELECT personID\n"
				+ "FROM persons\n"
				+ "WHERE personID = '" + personID + "';";
		
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

	public static boolean checkBelonging(String personID, String username) {
		
		Connection conn = PersonDao.connect();
		
		String query = "SELECT personID\n"
				+ "FROM persons\n"
				+ "WHERE personID = '" + personID + "'\n"
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

	public static PersonModel getPerson(String personID) {
		
		Connection conn = PersonDao.connect();
		
		String query = "SELECT associatedUsername,\n"
				+ " firstName,\n"
				+ " lastName,\n"
				+ " gender,\n"
				+ " fatherID,\n"
				+ " motherID,\n"
				+ " spouseID\n"
				+ "FROM persons\n"
				+ "WHERE personID = '" + personID + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ResultSet rs = pstmt.executeQuery();
			
			String username = rs.getString("associatedUsername");
			String firstName = rs.getString("firstName");
			String lastName = rs.getString("lastName");
			String gender = rs.getString("gender");
			String fatherID = null;
			String motherID = null;
			String spouseID = null;
			try {
				fatherID = rs.getString("fatherID");
				if (fatherID.length() == 0) fatherID = null;
			} catch (SQLException e) {}
			try {
				motherID = rs.getString("motherID");
				if (motherID.length() == 0) motherID = null;
			} catch (SQLException e) {}
			try {
				spouseID = rs.getString("spouseID");
				if (spouseID.length() == 0) spouseID = null;
			} catch (SQLException e) {}
			
			conn.close();
			
			return new PersonModel(username, personID, firstName, lastName, gender, fatherID, motherID, spouseID);
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
		
	}
	
}