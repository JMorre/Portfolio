package server;

import java.io.IOException;
import java.net.InetSocketAddress;

import com.sun.net.httpserver.HttpServer;

import server.handler.*;

public class Server {

	private static final int MAX_WAITING_CONNECTIONS = 12;

	private HttpServer server;

	private void run(String portNumber) {

		System.out.println("Initializing HTTP Server");

		try {
			server = HttpServer.create(new InetSocketAddress(Integer.parseInt(portNumber)), MAX_WAITING_CONNECTIONS);
		}
		catch (IOException e) {
			e.printStackTrace();
			return;
		}

		server.setExecutor(null);

		System.out.println("Creating contexts");

		server.createContext("/", new DefaultHandler());
		server.createContext("/clear", new ClearHandler());
		server.createContext("/load", new LoadHandler());
		server.createContext("/fill", new FillHandler());
		server.createContext("/user/login", new LoginHandler());
		server.createContext("/user/register", new RegisterHandler());
		server.createContext("/event", new EventHandler());
		server.createContext("/person", new PersonHandler());

		System.out.println("Starting server");

		server.start();

		System.out.println("Server started");
	}

	public static void main(String[] args) {
		
		if (args.length != 1) {
			System.out.println("Invalid command line arguments");
			return;
		}
		
		int port;
		try {
			port = Integer.parseUnsignedInt(args[0]);
			if (port == 0 || port > 65535) throw new NumberFormatException();
		} catch (NumberFormatException e) {
			System.out.println("Invalid command line arguments");
			return;
		}
		
		String portNumber = args[0];
		new Server().run(portNumber);
	}
}
