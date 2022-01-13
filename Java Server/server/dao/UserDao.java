package server.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import server.model.UserModel;

//print statements for debugging purposes, omitted

public class UserDao extends Dao {
	
	public static void insert(UserModel um) {
		
		Connection conn = UserDao.connect();
		
		String table = "CREATE TABLE IF NOT EXISTS users (\n"
				+ " username TEXT NOT NULL PRIMARY KEY,\n"
				+ " password TEXT NOT NULL,\n"
				+ " email TEXT NOT NULL,\n"
				+ " firstName TEXT NOT NULL,\n"
				+ " lastName TEXT NOT NULL,\n"
				+ " gender TEXT NOT NULL,\n"
				+ " personID TEXT NOT NULL\n"
				+ ");";
		
		UserDao.executeStmt(conn, table);
		
		String ins = "INSERT INTO users"
				+ "(username,password,email,firstName,lastName,gender,personID) "
				+ "VALUES(?,?,?,?,?,?,?)";
		
		try (PreparedStatement pstmt = conn.prepareStatement(ins)) {
			pstmt.setString(1, um.getUserName());
			pstmt.setString(2, um.getPassword());
			pstmt.setString(3, um.getEmail());
			pstmt.setString(4, um.getFirstName());
			pstmt.setString(5, um.getLastName());
			pstmt.setString(6, um.getGender());
			pstmt.setString(7, um.getPersonID());
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
	
	public static String getPassword(String username) {
		Connection conn = UserDao.connect();
		
		String query = "SELECT password\n"
				+ "FROM users\n"
				+ "WHERE username = '" + username + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ResultSet rs = pstmt.executeQuery();
			
			String s = rs.getString("password");
			
			conn.close();
			
			return s;
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}
	
	public static String getPID(String username) {
		Connection conn = UserDao.connect();
		String query = "SELECT personID\n"
				+ "FROM users\n"
				+ "WHERE username = '" + username + "';";
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			ResultSet rs = pstmt.executeQuery();
			return rs.getString("personID");
		} catch (SQLException e) {
			return null;
		}
	}

	public static boolean checkExistingUser(String username) {
		
		Connection conn = UserDao.connect();
		
		String query = "SELECT username\n"
				+ "FROM users\n"
				+ "WHERE username = '" + username + "';";
		
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

	public static void updateField(String whereField, String whereValue, String changeField, String changeValue) {
		
		Connection conn = UserDao.connect();
		
		String update = "UPDATE users\n"
				+ "SET " + changeField + " = '" + changeValue + "'\n"
				+ "WHERE\n"
				+ " " + whereField + " = '" + whereValue + "';";
		
		try {
			PreparedStatement pstmt = conn.prepareStatement(update);
			pstmt.executeUpdate();
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		}
	}
	
	public static UserModel getUserFromUsername(String username) {
		Connection conn = UserDao.connect();
		
		String query = "SELECT username,\n"
				+ " password,\n"
				+ " email,\n"
				+ " firstName,\n"
				+ " lastName,\n"
				+ " gender,\n"
				+ " personID\n"
				+ "FROM users\n"
				+ "WHERE username = '" + username + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ResultSet rs = pstmt.executeQuery();
			
			String password = rs.getString("password");
			String email = rs.getString("email");
			String firstName = rs.getString("firstName");
			String lastName = rs.getString("lastName");
			String gender = rs.getString("gender");
			String personID = rs.getString("personID");
			
			conn.close();
			
			UserModel um = new UserModel(username, password, email, firstName, lastName, gender);
			um.setPersonID(personID);
			return um;
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}
	
}