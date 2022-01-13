package server.dao;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;

//print statements for debugging purposes, omitted

public class Dao {

	protected static Connection connect() {
		try {
			Class.forName("org.sqlite.JDBC");
		} catch (ClassNotFoundException e1) {}
		Connection conn = null;
		String url = "jdbc:sqlite:db/data.db";
		try {
			conn = DriverManager.getConnection(url);
			return conn;
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return null;
		}
	}
	
	protected static void executeStmt(Connection conn, String sql) {
		try (Statement stmt = conn.createStatement()) {
			stmt.execute(sql);
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
			return;
		}
	}
	
	public static void deleteAll() {
		Connection conn = connect();
		
		String del = "DELETE\n"
				+ "FROM"
				+ " ";
		
		try {
			PreparedStatement pstmt = conn.prepareStatement(del + "users;");
			pstmt.executeUpdate();
			pstmt = conn.prepareStatement(del + "persons;");
			pstmt.executeUpdate();
			pstmt = conn.prepareStatement(del + "events;");
			pstmt.executeUpdate();
			pstmt = conn.prepareStatement(del + "tokens;");
			pstmt.executeUpdate();
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		} finally {
			try {
				conn.close();
			} catch (SQLException e) {
				//System.out.println(e.getMessage());
			}
		}
	}

	public static void deleteAllMatchingData(String username) {
		Connection conn = connect();
		
		String events = "DELETE\n"
				+ "FROM"
				+ " events\n"
				+ "WHERE\n"
				+ " associatedUsername = '" + username + "';";
		
		String persons = "DELETE\n"
				+ "FROM"
				+ " persons\n"
				+ "WHERE\n"
				+ " associatedUsername = '" + username + "';";
		
		try {
			PreparedStatement pstmt = conn.prepareStatement(events);
			pstmt.executeUpdate();
			pstmt = conn.prepareStatement(persons);
			pstmt.executeUpdate();
		} catch (SQLException e) {
			//System.out.println(e.getMessage());
		} finally {
			try {
				conn.close();
			} catch (SQLException e) {
				//System.out.println(e.getMessage());
			}
		}
	}
	
}
