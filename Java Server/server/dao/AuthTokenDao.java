package server.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import server.model.AuthTokenModel;

//print statements for debugging purposes, omitted

public class AuthTokenDao extends Dao {
	
	public static void insert(AuthTokenModel atm) {
		
		Connection conn = AuthTokenDao.connect();
		
		String table = "CREATE TABLE IF NOT EXISTS tokens (\n"
				+ " token TEXT NOT NULL PRIMARY KEY,\n"
				+ " user TEXT NOT NULL\n"
				+ ");";
		
		AuthTokenDao.executeStmt(conn, table);
		
		String ins = "INSERT INTO tokens"
				+ "(token,user) "
				+ "VALUES(?,?)";
		
		try (PreparedStatement pstmt = conn.prepareStatement(ins)) {
			pstmt.setString(1, atm.getToken());
			pstmt.setString(2, atm.getUser());
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
	
	public static String getUsernameFromToken(String token) {
		Connection conn = AuthTokenDao.connect();
		
		String query = "SELECT user\n"
				+ "FROM tokens\n"
				+ "WHERE token = '" + token + "';";
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ResultSet rs = pstmt.executeQuery();
			
			String username = rs.getString("user");
			
			conn.close();
			
			return username;
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}

	public static boolean checkExistingToken(String authToken) {

		Connection conn = AuthTokenDao.connect();
		
		String query = "SELECT token\n"
				+ "FROM tokens\n"
				+ "WHERE token = '" + authToken + "';";
		
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

	public static AuthTokenModel[] getAllTokens(String userName) {
		
		Connection conn = AuthTokenDao.connect();
		
		String query = "SELECT token\n"
				+ "FROM tokens\n"
				+ "WHERE user = '" + userName + "';";
		
		AuthTokenModel[] atm;
		
		try (PreparedStatement pstmt = conn.prepareStatement(query)) {
			
			ArrayList<String> tokens = new ArrayList<String>();
			ResultSet rs = pstmt.executeQuery();
			
			while (rs.next()) {
				tokens.add(rs.getString("token"));
			}
			
			atm = new AuthTokenModel[tokens.size()];
			
			for (int i = 0; i < tokens.size(); i++) {
				atm[i] = new AuthTokenModel(tokens.get(i), userName);
			}
			
			conn.close();
			
			return atm;
			
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}
	
}